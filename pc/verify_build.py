"""Rebuild the Steam 252084 PC units and verify their checked-in byte receipts."""

import argparse
import hashlib
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from fnmatch import fnmatch
import os
from pathlib import Path
import re
import shlex
import shutil
import struct
import subprocess
import sys
import tempfile

PC = Path(__file__).resolve().parent
sys.path.insert(0, str(PC.parent / "tools"))
from progress import callee_units, compare_unit, summary, verify, write
from link_image import link_arguments, stub_object
from link_vtable_exports import vtable_export_args
from manifests import load_target, save_receipts


CLANG_X86_TARGET = "i686-pc-windows-msvc"
CLANG_RELEASE_19_1_0_SHA256 = "e6936af3d8a4e2badd139699816f40235e724e2131ee05651c94c1c371f7fb53"


def compiler_identity(cl, env, *, clang=False):
    if clang:
        version = subprocess.run([cl, "--target=" + CLANG_X86_TARGET, "--version"], env=env,
                                 capture_output=True, text=True, errors="replace", check=True).stdout
        build = re.search(r"(?m)^clang version ([\d.]+) \([^\n]*\b([0-9a-f]{40})\)", version)
        if build and f"Target: {CLANG_X86_TARGET}" in version:
            return f"Clang {build[1]} ({build[2]}) for {CLANG_X86_TARGET}"
        # The official 19.1.0 release prints no git revision. Its exact banner and the binary's
        # SHA-256, recorded in pc/TOOLCHAIN.md, identify it; any other build is refused.
        digest = hashlib.sha256(Path(cl).read_bytes()).hexdigest()
        if (re.search(r"(?m)^clang version 19\.1\.0$", version) and f"Target: {CLANG_X86_TARGET}" in version
                and digest == CLANG_RELEASE_19_1_0_SHA256):
            return f"Clang 19.1.0 for {CLANG_X86_TARGET}"
        raise ValueError(f"cannot identify revision and x86 target of Clang at {cl}")
    # VC6 and the Visual C++ Toolkit 2003 report their x86 builds in the banner.
    banner = subprocess.run([cl], env=env, capture_output=True, text=True, errors="replace")
    legacy = re.search(r"Microsoft .*Compiler Version ((?:12|13)\.\d+\.\d+) for 80x86\b", banner.stderr + banner.stdout)
    if legacy:
        return f"Microsoft C/C++ {legacy[1]} for x86"
    result = subprocess.run([cl, "/Bv", "/?"], env=env, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True, errors="replace", check=True)
    version = re.search(r"(?im)[\\/]cl\.exe:\s*Version (\d+\.\d+\.\d+\.\d+)", result.stdout)
    arch = re.search(r"Microsoft .*C/C\+\+ Optimizing Compiler Version [\d.]+ for (\w+)", result.stdout)
    if not version or not arch:
        raise ValueError(f"could not identify Microsoft C/C++ compiler at {cl}")
    return f"Microsoft C/C++ {version[1]} for {arch[1]}"


def run_tool(command, streams, *, cwd, env, stdout=subprocess.PIPE):
    """Run one build tool with its output captured, so concurrent recipes never interleave output.

    The output is recorded in streams and printed later, in recipe order. A nonzero exit raises
    CalledProcessError, as subprocess.run(check=True) does."""
    completed = subprocess.run(command, stdout=stdout, stderr=subprocess.PIPE, cwd=cwd, env=env)
    streams.append((completed.stdout or b"", completed.stderr or b""))
    if completed.returncode:
        raise subprocess.CalledProcessError(completed.returncode, command, completed.stdout, completed.stderr)


SHOW_INCLUDES = "Note: including file:"
LINE_DIRECTIVE = re.compile(r'^#line \d+ "(.*)"\s*$')


def system_include_dir(cl):
    """The toolchain's own header folder: the nearest include folder above the compiler.

    It is beside the bin folder in the Toolkit 2003 and VC6 layouts, and three folders up from
    MSVC 19.x's bin/Host*/x86. The folder must hold yvals.h, which every Microsoft C++ library has."""
    for parent in Path(cl).resolve().parents[:4]:
        if (parent / "include" / "yvals.h").is_file():
            return parent / "include"
    raise ValueError(f"no system header folder (include/yvals.h) above {cl}")


def header_digest(path):
    """The SHA-256 of a header, with CRLF line ends read as LF, as unit inputs are hashed."""
    return hashlib.sha256(path.read_bytes().replace(b"\r\n", b"\n")).hexdigest()


def reports_includes(toolchain):
    """True when the compiler prints the headers it reads (/showIncludes, from 13.00 on); VC6 does not."""
    return not toolchain.startswith("Microsoft C/C++ 12.")


def stage_system_headers(unit, cl, stage):
    """Copy the system headers a unit records into stage, after checking each recorded hash.

    The compile then sees only these headers through INCLUDE, so a header the record does not
    name cannot be read."""
    include = system_include_dir(cl)
    for relative, expected in unit["system_headers"].items():
        source = include / relative
        if not source.is_file():
            raise ValueError(f"{unit['id']}: system header {relative} is not in {include}")
        if header_digest(source) != expected:
            raise ValueError(f"{unit['id']}: system header {relative} differs from the one recorded")
        destination = stage / relative
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source, destination)


def system_headers_read(paths, include, build_dir):
    """The headers under include among the paths a compile read, as {relative path: SHA-256}.

    Paths are keyed in lower case, as Windows resolves them. A header that is neither a system
    header nor one of the unit's inputs is refused."""
    read = {}
    for text in paths:
        path = (build_dir / text).resolve()
        if path.is_relative_to(include):
            read[path.relative_to(include).as_posix().lower()] = header_digest(path)
        elif not path.is_relative_to(build_dir):
            raise ValueError(f"the compile read {path}, outside its inputs and system headers")
    return dict(sorted(read.items()))


def decode(output):
    return output.decode("mbcs" if os.name == "nt" else "utf-8", "replace")


def compile_unit(unit, cl, env, build_dir, streams, found=None):
    """Compile a unit with its recorded command in build_dir, and return the object it writes.

    A unit with a system_headers record compiles against its toolchain's own headers through
    INCLUDE, and the headers the compile reads must be exactly the recorded ones: a compiler from
    13.00 on lists them with /showIncludes, and for VC6 a preprocessing run (/E) names them in its
    #line directives. With found, a dictionary, the compile reads the whole include folder and
    found receives the headers it read; otherwise only the recorded headers are staged."""
    # Recipes use relative forward-slash paths, even on Windows.
    program, *args = shlex.split(unit["build_command"])
    if "rebuilt_symbol" not in unit:
        raise ValueError("expected a named x86 COFF function")
    if program.lower() in ("cl", "cl.exe") and "/c" in args and unit["toolchain"].startswith("Microsoft C/C++ "):
        outputs = [arg[3:] or args[i + 1] for i, arg in enumerate(args) if arg.startswith("/Fo")]
    elif (program in ("clang", "clang.exe") and "-c" in args and unit["toolchain"].startswith("Clang ")
          and [a for a in args if a.startswith("--target=")] == ["--target=" + CLANG_X86_TARGET]):
        outputs = [args[i + 1] for i, arg in enumerate(args[:-1]) if arg == "-o"]
    else:
        raise ValueError("expected a compile-only recipe for the selected x86 compiler")
    if len(outputs) != 1:
        raise ValueError("expected one object output in the build command")
    obj = (build_dir / outputs[0]).resolve()
    if not obj.is_relative_to(build_dir / "local") or obj.suffix.lower() != ".obj":
        raise ValueError("expected a local/*.obj output")
    for relative in unit["inputs"]:
        destination = build_dir / relative
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(PC / relative, destination)
    obj.parent.mkdir(parents=True, exist_ok=True)
    if obj.exists():
        raise ValueError("the expected object already exists in the fresh build directory")
    if "system_headers" not in unit:
        run_tool([cl, *args], streams, cwd=build_dir, env=env)
    else:
        if not unit["toolchain"].startswith("Microsoft C/C++ "):
            raise ValueError(f"{unit['id']}: system headers are recorded for Microsoft C/C++ units only")
        if found is not None:
            include = system_include_dir(cl)
        else:
            include = build_dir / "local" / "system-include"
            include.mkdir(parents=True)
            stage_system_headers(unit, cl, include)
        include_env = dict(env, INCLUDE=str(include))
        reported = reports_includes(unit["toolchain"])
        local = []
        try:
            run_tool([cl, *args, *(["/showIncludes"] if reported else [])], local, cwd=build_dir, env=include_env)
            if not reported:
                # Preprocess with the same options, without /c and /Fo, to list what was read.
                options = [a for i, a in enumerate(args) if a != "/c" and not a.startswith("/Fo")
                           and not (i and args[i - 1] == "/Fo")]
                run_tool([cl, *options, "/E"], local, cwd=build_dir, env=include_env)
        except subprocess.CalledProcessError:
            streams.extend(local)
            raise
        stdout, stderr = local[0]
        if reported:
            paths = [line[len(SHOW_INCLUDES):].strip() for line in decode(stdout).splitlines()
                     if line.startswith(SHOW_INCLUDES)]
            # The include notes are long; the replayed output keeps the compiler's other lines.
            stdout = b"".join(line for line in stdout.splitlines(keepends=True)
                              if not line.startswith(SHOW_INCLUDES.encode()))
        else:
            lines = decode(local[1][0]).splitlines()
            paths = [m[1].replace("\\\\", "\\") for m in map(LINE_DIRECTIVE.match, lines) if m]
        read = system_headers_read(paths, include.resolve(), build_dir.resolve())
        if found is not None:
            found.update(read)
        elif read != unit["system_headers"]:
            extra = sorted(set(read) ^ set(unit["system_headers"]))
            raise ValueError(f"{unit['id']}: the compile reads other system headers than the record names "
                             f"({', '.join(extra)}); rerun with --update-receipts")
        streams.append((stdout, stderr))
    if not obj.is_file():
        raise ValueError(f"compiler produced no object at {outputs[0]}")
    return obj


UNRESOLVED = re.compile(r'unresolved external symbol (?:"[^"]*" \(([^()\s]+)\)|(\S+))')


def unresolved_externals(output):
    """The externals that LINK.EXE reported as unresolved, in the order it reported them."""
    names = []
    for match in UNRESOLVED.finditer(output):
        name = match[1] or match[2]
        if name not in names:
            names.append(name)
    return names


# MSVC's floating-point code needs the marker __fltused, which the C runtime defines. A callee that
# uses floating point makes LINK.EXE report it, and no record declares it, so it is stubbed whenever
# the probe reports it.
IMPLICIT_STUBS = ("__fltused",)


def stub_plan(unresolved, declared):
    """Return (names to stub, unresolved names that neither a record nor an implicit stub covers)."""
    names = [name for name in declared if name in unresolved]
    names += [name for name in IMPLICIT_STUBS if name in unresolved and name not in names]
    undeclared = [name for name in unresolved
                  if name not in declared and name not in IMPLICIT_STUBS]
    return names, undeclared


def link_with_callees(unit, callees, obj, member_objects, cl, env, build_dir, streams):
    """Link a unit's object with the objects of its callees into one DLL.

    The link decides the calling convention of every call between these units, as the original
    link did. A stub is made only for an external that the linked objects leave unresolved, so no
    stub shadows a callee's definition. An external that no object defines and no record declares
    stays unresolved, and LINK.EXE fails the build. The implicit stubs in IMPLICIT_STUBS are made
    without a declaration."""
    links = [m.get("ltcg_link", {"roots": [], "stubs": []}) for m in [unit, *callees]]
    roots = list(dict.fromkeys(root for link in links for root in link["roots"]))
    declared = list(dict.fromkeys(name for link in links for name in link["stubs"]))
    linker = Path(cl).with_name("LINK.EXE")
    exports = sorted({arg for link in links for arg in vtable_export_args(link)})
    options = [*link_arguments({"roots": roots}), *exports]
    objects = [str(obj), *(str(path) for path in member_objects)]
    # Continue through code generation so the discovery link also reports compiler-generated
    # externals. The final link below remains strict and rejects unresolved symbols.
    probe = subprocess.run([str(linker), *options, "/FORCE:UNRESOLVED",
                            "/OUT:" + str(obj.with_name(obj.stem + "_probe.dll")), *objects],
                           cwd=build_dir, env=env, capture_output=True, text=True, errors="replace")
    unresolved = unresolved_externals(probe.stdout)
    if probe.returncode:
        raise ValueError(f"{unit['id']}: LINK.EXE failed: {probe.stdout.strip()}")
    names, undeclared = stub_plan(unresolved, declared)
    if any(name in names for link in links for name in link.get("exported_vtables", [])):
        raise ValueError("the link cannot satisfy an exported vtable with a stub")
    if undeclared:
        raise ValueError(f"{unit['id']}: unresolved external {undeclared[0]}: no linked object defines it "
                         "and no record declares it as a stub")
    dll = obj.with_suffix(".dll")
    args = [*options, "/OUT:" + str(dll), *objects]
    if names:
        stubs = obj.with_name(obj.stem + "_stubs.obj")
        stubs.write_bytes(stub_object(names))
        args.append(str(stubs))
    run_tool([str(linker), *args], streams, cwd=build_dir, env=env)
    return dll


def rebuild_unit(unit, cl, env, build_dir, streams, callees=(), found=None):
    obj = compile_unit(unit, cl, env, build_dir, streams, found)
    if "ltcg_link" in unit:
        # Link-time code generation: link the object, its scaffolding roots and stubs
        # for undefined externals into a DLL with the LINK.EXE beside the compiler.
        if "/GL" not in shlex.split(unit["build_command"])[1:]:
            raise ValueError("an LTCG unit compiles with /GL")
        if callees:
            member_objects = [compile_unit(callee, cl, env, build_dir / callee["id"], streams)
                              for callee in callees]
            return link_with_callees(unit, callees, obj, member_objects, cl, env, build_dir, streams)
        stubs = obj.with_name(obj.stem + "_stubs.obj")
        dll = obj.with_suffix(".dll")
        stubs.write_bytes(stub_object(unit["ltcg_link"]["stubs"]))
        linker = Path(cl).with_name("LINK.EXE")
        run_tool([str(linker), *link_arguments(unit["ltcg_link"]), *vtable_export_args(unit["ltcg_link"]),
                  "/OUT:" + str(dll), str(obj), str(stubs)],
                 streams, cwd=build_dir, env=env, stdout=subprocess.DEVNULL)
        return dll
    if callees:
        raise ValueError(f"{unit['id']}: ltcg_callees needs an ltcg_link record")
    return obj


def build_recipe(units, compilers, callees=(), discover=False):
    """Rebuild one recipe's object in a directory of its own, and return (object, error, output).

    A failure is returned rather than raised, so the caller can print the tools' output in
    recipe order before it reports the error. With discover, a unit with a system_headers
    record compiles against the whole include folder and the record receives the headers read."""
    unit = units[0]
    cl, env = compilers[unit["toolchain"]]
    streams = []
    found = {} if discover and "system_headers" in unit else None
    try:
        with tempfile.TemporaryDirectory(prefix="scct-decomp-") as tmp:
            obj = rebuild_unit(unit, cl, env, Path(tmp).resolve(), streams, callees, found).read_bytes()
    except Exception as error:
        return None, error, streams
    if found is not None:
        for each in units:
            each["system_headers"] = found
    return obj, None, streams


def build_recipes(recipes, compilers, jobs, discover=False):
    """Yield (units, (object, error, output)) for each (units, callees) recipe, in order.

    With jobs=1 each recipe is built when its turn comes, as the gate always did. With more
    jobs, the builds run concurrently in threads and are still yielded in recipe order."""
    def build(recipe):
        units, callees = recipe
        return units, build_recipe(units, compilers, callees, discover)

    if jobs == 1:
        for recipe in recipes:
            yield build(recipe)
        return
    pool = ThreadPoolExecutor(max_workers=jobs)
    try:
        yield from pool.map(build, recipes)
    finally:
        # Recipes that have not started are dropped, so a failure stops the gate as it did serially.
        pool.shutdown(wait=True, cancel_futures=True)


def replay(streams):
    """Print a recipe's captured tool output as the serial gate printed it, before its PASS lines."""
    for stdout, stderr in streams:
        for data, stream in ((stdout, sys.stdout), (stderr, sys.stderr)):
            if data:
                stream.flush()
                stream.buffer.write(data)
                stream.buffer.flush()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("steam_root", type=Path, help="installed Splinter Cell Chaos Theory folder")
    parser.add_argument("--cl", action="append", help="x86 cl.exe path; repeat for different toolsets")
    parser.add_argument("--clang", action="append", default=[], help="clang.exe path for x86 Windows candidates")
    parser.add_argument("--skip-unavailable", action="store_true",
                        help="gate the units whose compiler was supplied and list the rest as skipped")
    parser.add_argument("--source", action="append", default=[], metavar="PATTERN",
                        help="gate only units with an input matching this pattern, such as 'src/sound_*'; repeatable")
    parser.add_argument("--update-receipts", action="store_true",
                        help="after a unit's edited inputs rebuild every retail byte, record its new receipt "
                             "(or its first one), and the system headers it reads")
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 1,
                        help="recipes to build at once (default: one per core); 1 builds them one at a time")
    args = parser.parse_args()
    if args.jobs < 1:
        parser.error("--jobs must be at least 1")
    env = os.environ.copy()
    # cl prepends CL and appends _CL_ to the command line.
    env.pop("CL", None)
    env.pop("_CL_", None)
    # A compile sees no headers but its inputs, and its recorded system headers through INCLUDE.
    env.pop("INCLUDE", None)
    env["VSLANG"] = "1033"
    compilers = {}
    requests = [(path, False) for path in (args.cl or ["cl.exe"])]
    requests.extend((path, True) for path in args.clang)
    for requested, clang in requests:
        resolved = shutil.which(requested)
        if resolved is None:
            raise ValueError(f"compiler not found: {requested}")
        cl = str(Path(resolved).resolve())
        build_env = dict(env, PATH=str(Path(cl).parent) + os.pathsep + env.get("PATH", ""))
        identity = compiler_identity(cl, build_env, clang=clang)
        compilers[identity] = (cl, build_env)
    for edition in ("campaign", "versus"):
        target_id = f"steam-252084-{edition}"
        manifest = PC / "config" / f"{target_id}.json"
        target = load_target(manifest)
        if target["id"] != target_id:
            raise ValueError(f"unexpected target ID in {manifest}")
        if not args.update_receipts:
            # A stale receipt stops the gate here; --update-receipts rebuilds it instead.
            summary(PC, target)
        retail = args.steam_root / target["file"]
        original = verify(target, retail)
        byte_count = 0
        recipes = {}
        callees_of = {}
        skipped = Counter()
        skipped_bytes = 0
        for unit in target["units"]:
            if "match" not in unit and not args.update_receipts:
                raise ValueError(f"{unit['id']}: missing checked-in match receipt")
            if args.source and not any(fnmatch(path, pattern) for path in unit["inputs"] for pattern in args.source):
                continue
            if unit["toolchain"] not in compilers:
                if args.skip_unavailable:
                    skipped[unit["toolchain"]] += 1
                    skipped_bytes += unit["size"]
                    continue
                option = "--clang" if unit["toolchain"].startswith("Clang ") else "--cl"
                raise ValueError(f"{unit['id']}: pass {option} for {unit['toolchain']}")
            link = unit.get("ltcg_link")
            callees = callee_units(target["units"], unit)
            headers = unit.get("system_headers")
            key = (unit["toolchain"], unit["build_command"], tuple(sorted(unit["inputs"])),
                   link and (tuple(link["roots"]), tuple(link["stubs"]), tuple(vtable_export_args(link))),
                   headers is not None and tuple(sorted(headers.items())))
            if callees:
                # A unit linked with callees has a recipe of its own, since the callees are part of its build.
                key += (unit["id"],)
            recipes.setdefault(key, []).append(unit)
            callees_of[key] = callees
        gated = 0
        updated = []
        builds = build_recipes([(units, callees_of[key]) for key, units in recipes.items()], compilers, args.jobs,
                               discover=args.update_receipts)
        try:
            for units, (obj, error, streams) in builds:
                replay(streams)
                if error is not None:
                    raise error
                for unit in units:
                    receipt = compare_unit(PC, target, unit, original, obj)
                    if receipt != unit.get("match"):
                        # compare_unit has already required every rebuilt byte to equal retail,
                        # so only the fingerprint of the edited inputs can differ here.
                        if not args.update_receipts or receipt["bytes_sha256"] != unit.get("match", receipt)["bytes_sha256"]:
                            raise ValueError(f"{unit['id']}: rebuilt receipt differs from checked-in receipt")
                        unit["match"] = receipt
                        updated.append(unit)
                    byte_count += unit["size"]
                    gated += 1
                    print(f"PASS {target_id}/{unit['id']} at file offset 0x{unit['offset']:x} ({unit['size']} bytes)")
        finally:
            builds.close()
        if updated:
            save_receipts(manifest, updated, write, fields=("match", "system_headers"))
            print(f"{target_id}: recorded {len(updated)} new receipts")
        totals = summary(PC, load_target(manifest))
        for toolchain, count in sorted(skipped.items()):
            print(f"SKIP {target_id}: {count} units need {toolchain}")
        scope = "" if gated == len(target["units"]) else f" of {len(target['units'])}"
        print(f"{target_id}: {gated}{scope} functions, {byte_count:,} / {totals['total_bytes']:,} bytes"
              + (f"; {sum(skipped.values())} functions ({skipped_bytes:,} bytes) skipped" if skipped else ""))


if __name__ == "__main__":
    try:
        main()
    except (KeyError, ValueError, OSError, struct.error, subprocess.CalledProcessError) as error:
        sys.exit(f"Verification failed: {error}")
