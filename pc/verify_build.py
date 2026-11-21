"""Rebuild the Steam 252084 PC units and verify their checked-in byte receipts."""

import argparse
from collections import Counter
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
from progress import compare_unit, summary, verify, write
from link_image import link_arguments, stub_object
from manifests import load_target, save_receipts


CLANG_X86_TARGET = "i686-pc-windows-msvc"


def compiler_identity(cl, env, *, clang=False):
    if clang:
        version = subprocess.run([cl, "--target=" + CLANG_X86_TARGET, "--version"], env=env,
                                 capture_output=True, text=True, errors="replace", check=True).stdout
        build = re.search(r"(?m)^clang version ([\d.]+) \([^\n]*\b([0-9a-f]{40})\)", version)
        if not build or f"Target: {CLANG_X86_TARGET}" not in version:
            raise ValueError(f"cannot identify revision and x86 target of Clang at {cl}")
        return f"Clang {build[1]} ({build[2]}) for {CLANG_X86_TARGET}"
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


def rebuild_unit(unit, cl, env, build_dir):
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
    subprocess.run([cl, *args], cwd=build_dir, env=env, check=True)
    if not obj.is_file():
        raise ValueError(f"compiler produced no object at {outputs[0]}")
    if "ltcg_link" in unit:
        # Link-time code generation: link the object, its scaffolding roots and stubs
        # for undefined externals into a DLL with the LINK.EXE beside the compiler.
        if "/GL" not in args:
            raise ValueError("an LTCG unit compiles with /GL")
        stubs = obj.with_name(obj.stem + "_stubs.obj")
        dll = obj.with_suffix(".dll")
        stubs.write_bytes(stub_object(unit["ltcg_link"]["stubs"]))
        linker = Path(cl).with_name("LINK.EXE")
        subprocess.run([str(linker), *link_arguments(unit["ltcg_link"]), "/OUT:" + str(dll), str(obj), str(stubs)],
                       cwd=build_dir, env=env, check=True, stdout=subprocess.DEVNULL)
        return dll
    return obj


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
                        help="after a unit's edited inputs rebuild every retail byte, record its new receipt")
    args = parser.parse_args()
    env = os.environ.copy()
    # cl prepends CL and appends _CL_ to the command line.
    env.pop("CL", None)
    env.pop("_CL_", None)
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
        skipped = Counter()
        skipped_bytes = 0
        for unit in target["units"]:
            if "match" not in unit:
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
            key = (unit["toolchain"], unit["build_command"], tuple(sorted(unit["inputs"])),
                   link and (tuple(link["roots"]), tuple(link["stubs"])))
            recipes.setdefault(key, []).append(unit)
        gated = 0
        updated = []
        for (toolchain, *_), units in recipes.items():
            cl, build_env = compilers[toolchain]
            with tempfile.TemporaryDirectory(prefix="scct-decomp-") as tmp:
                obj = rebuild_unit(units[0], cl, build_env, Path(tmp).resolve()).read_bytes()
            for unit in units:
                receipt = compare_unit(PC, target, unit, original, obj)
                if receipt != unit["match"]:
                    # compare_unit has already required every rebuilt byte to equal retail,
                    # so only the fingerprint of the edited inputs can differ here.
                    if not args.update_receipts or receipt["bytes_sha256"] != unit["match"]["bytes_sha256"]:
                        raise ValueError(f"{unit['id']}: rebuilt receipt differs from checked-in receipt")
                    unit["match"] = receipt
                    updated.append(unit)
                byte_count += unit["size"]
                gated += 1
                print(f"PASS {target_id}/{unit['id']} at file offset 0x{unit['offset']:x} ({unit['size']} bytes)")
        if updated:
            save_receipts(manifest, updated, write)
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
