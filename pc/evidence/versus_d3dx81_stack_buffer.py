"""Check the DirectX 8.1 release archive and optionally replay compiler switch controls."""

import argparse
from collections import Counter
from hashlib import sha256
import os
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

from compare_libraries import members

PC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PC.parent / "tools"))

from link_x86 import handler_stub, symbol_index
from manifests import load_target
from progress import built_unit_bytes, verify

ARCHIVE_SHA256 = "39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28"
MEMBER_SHA256 = {
    "stack": "c408d992d338ee5ee22114334311632ef9909ca69d33ae318d3bdaef39d1ea49",
    "buffer": "9548a984a3d527878dc5313785cce8bb1808ac2f533d5998f30b73d0204f9ae7",
}
SWITCHES = ("/O1 /GX", "/O1", "/O1 /EHsc", "/O1 /EHa", "/O2 /GX", "/Ox /GX",
            "/Od /GX", "/O1 /Ob0 /GX", "/O1 /G5 /GX", "/O1 /G6 /GX",
            "/O1 /Oy- /GX", "/O2 /Os /GX")


def check_producer(obj):
    section_count, symbols, _, _, _ = symbol_index(obj)
    comp_ids = {value for name, value, *_ in symbols.values() if name == b"@comp.id"}
    versions = set()
    for index in range(section_count):
        header = 20 + 40 * index
        if obj[header:header + 8] != b".debug$S":
            continue
        size, start = struct.unpack_from("<II", obj, header + 16)
        records = obj[start:start + size]
        pos = 4
        while pos + 4 <= len(records):
            length, tag = struct.unpack_from("<HH", records, pos)
            if length < 2 or pos + 2 + length > len(records):
                raise ValueError("invalid CodeView record")
            if tag == 0x1013:  # S_COMPILE2
                versions.add(struct.unpack_from("<I7H", records, pos + 4))
            pos += length + 2
    if comp_ids != {0x001d23da} or versions != {(513, 6, 13, 0, 9176, 13, 0, 9178)}:
        raise ValueError("expected the 13.00.9176/9178 x86 C++ producer")


def check_archive(path):
    data = path.read_bytes()
    if sha256(data).hexdigest() != ARCHIVE_SHA256:
        raise ValueError("expected the DirectX 8.1 release d3dx8.lib")
    objects = {}
    for name, obj in members(data):
        for stem, digest in MEMBER_SHA256.items():
            if name.replace("\\", "/") == f"obj/i386/cd3dx{stem}.obj":
                if stem in objects or sha256(obj).hexdigest() != digest:
                    raise ValueError(f"ambiguous or different library member: {name}")
                check_producer(obj)
                objects[stem] = obj
    if objects.keys() != MEMBER_SHA256.keys():
        raise ValueError("missing SDK member")
    return objects


def check_function(target, unit, retail, obj):
    if unit["offset"] == 0x28d303:
        # The compiler gives the private exception handler a different local label per build.
        # Select only the label at the actual end-of-section frame-handler stub.
        _, symbols, _, _, _ = symbol_index(obj)
        bindings = unit["link_bindings"].copy()
        old, = [name for name in bindings if name.startswith("$L")]
        candidates = [name.decode("ascii") for name, offset, section, kind, storage in symbols.values()
                      if storage == 6 and kind == 0 and name.startswith(b"$L") and section > 0
                      and handler_stub(obj, section, offset)]
        if len(candidates) != 1:
            return False
        bindings[candidates[0]] = bindings.pop(old)
        unit = dict(unit, link_bindings=bindings)
    start = unit["offset"]
    try:
        return built_unit_bytes(target, unit, obj, retail) == retail[start:start + unit["size"]]
    except ValueError:
        return False


def match_counts(target, units, retail, objects):
    return Counter(stem for stem, group in units.items() for unit in group
                   if check_function(target, unit, retail, objects[stem]))


def controls(compiler, target, units, retail):
    compiler = compiler.resolve()
    env = dict(os.environ, PATH=str(compiler.parent) + os.pathsep + os.environ.get("PATH", ""))
    for name in ("CL", "_CL_", "INCLUDE"):
        env.pop(name, None)
    with tempfile.TemporaryDirectory() as folder:
        for flags in SWITCHES:
            objects = {}
            for stem in MEMBER_SHA256:
                output = Path(folder) / f"{stem}.obj"
                command = [str(compiler), "/nologo", "/c", "/Gy", *flags.split(), "/Fo" + str(output),
                           str(PC / "src" / f"d3dx_{stem}.cpp")]
                subprocess.run(command, cwd=folder, env=env, check=True, stdout=subprocess.DEVNULL)
                objects[stem] = output.read_bytes()
            counts = match_counts(target, units, retail, objects)
            print(f"{flags:<18} {counts['stack']}/9 stack  {counts['buffer']}/9 buffer")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive", type=Path, help="DirectX 8.1 SDK release d3dx8.lib")
    parser.add_argument("retail", type=Path, help="locked Versus executable")
    parser.add_argument("--cl", type=Path, help="period x86 compiler for the C++ switch controls")
    args = parser.parse_args()
    target = load_target(PC / "config/steam-252084-versus.json")
    retail = verify(target, args.retail)
    units = {}
    totals = {}
    for stem, start, end in (("stack", 0x28d144, 0x28d3eb), ("buffer", 0x28d3eb, 0x28d4e2)):
        group = sorted((unit for unit in target["units"] if start <= unit["offset"] < end),
                       key=lambda unit: unit["offset"])
        cursor = start
        for unit in group:
            if unit["offset"] != cursor:
                raise ValueError(f"gap or overlap in {stem} receipts at {cursor:#x}")
            cursor += unit["size"]
        if len(group) != 9 or cursor != end:
            raise ValueError(f"incomplete {stem} receipt range")
        units[stem] = group
        totals[stem] = end - start
    counts = match_counts(target, units, retail, check_archive(args.archive))
    if any(counts[stem] != len(group) for stem, group in units.items()):
        raise ValueError(f"incomplete retail match: {counts}")
    print("Release archive: " + ", ".join(f"{counts[stem]}/{len(units[stem])} {stem} ({size} bytes)"
                                         for stem, size in totals.items()))
    if args.cl:
        controls(args.cl, target, units, retail)


if __name__ == "__main__":
    main()
