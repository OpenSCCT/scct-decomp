"""Function boundaries for code that has no unit yet.

Each target may have pc/function_maps/<target>.txt, written from Ghidra's whole-image
analysis. It holds addresses only, never game bytes: one line per function, giving the
file offset of its entry point followed by the file-offset intervals of its body as
`start-end` pairs (end exclusive), all in hexadecimal. Lines starting with # are comments.

The ByteMatch export uses it to draw unmatched code function by function instead of as
one block. Matched units always take precedence; a byte belongs to at most one function.

Regenerate it from a Ghidra function inventory (see pc/README.md, "Function maps"):
    python tools/function_map.py pc/config/TARGET.json INVENTORY.tsv pc/function_maps/TARGET.txt
"""

import json
import re
import sys
from pathlib import Path


def convert(manifest, inventory):
    """Text of a function map from pc/ExportFunctionInventory.java output for the locked image."""
    target = json.loads(Path(manifest).read_text(encoding="utf-8"))
    image = target["image"]
    text = Path(inventory).read_text(encoding="utf-8").splitlines()
    header = dict(line[1:].split("=", 1) for line in text if line.startswith("#") and "=" in line)
    if header.get("sha256", "").lower() != image["sha256"]:
        raise ValueError("the inventory was exported from another image")
    base = int(header["base"], 16)

    def offset(rva):
        for section in image["executable_sections"]:
            if section["address"] <= base + rva < section["address"] + section["size"]:
                return section["offset"] + base + rva - section["address"]
        return None

    functions = []
    rows = [line.split("\t") for line in text if line and not line.startswith(("#", "rva\t"))]
    for row in rows:
        entry, spans = offset(int(row[0], 16)), []
        for field in row[7].split(","):
            if not field:
                continue
            low, high = (int(x, 16) for x in field.split("-"))
            start, last = offset(low), offset(high)
            if start is not None and last is not None and last - start == high - low:
                spans.append((start, last + 1))
        if entry is not None and spans:
            functions.append((entry, spans))
    lines = ["# Function boundaries from Ghidra whole-image analysis, as file offsets.",
             f"# Image SHA-256 {image['sha256']}",
             "# entry start-end [start-end ...] (hexadecimal, end exclusive)"]
    lines += [f"{entry:x} " + " ".join(f"{a:x}-{b:x}" for a, b in spans) for entry, spans in sorted(functions)]
    return "\n".join(lines) + "\n"


def load(path, image_sha256=None):
    """[(entry, [(start, end), ...]), ...] from a function map file."""
    functions = []
    for number, text in enumerate(Path(path).read_text(encoding="utf-8").splitlines(), 1):
        if text.startswith("# Image SHA-256 ") and image_sha256 and text.split()[-1] != image_sha256:
            raise ValueError(f"{path}: function map belongs to another image")
        if not text.strip() or text.startswith("#"):
            continue
        fields = text.split()
        if not re.fullmatch(r"[0-9a-f]+", fields[0]) or len(fields) < 2:
            raise ValueError(f"{path}:{number}: expected an entry offset and intervals")
        spans = []
        for field in fields[1:]:
            match = re.fullmatch(r"([0-9a-f]+)-([0-9a-f]+)", field)
            if not match or int(match[1], 16) >= int(match[2], 16):
                raise ValueError(f"{path}:{number}: invalid interval {field!r}")
            spans.append((int(match[1], 16), int(match[2], 16)))
        functions.append((int(fields[0], 16), spans))
    return functions


def unmatched_functions(size, code, units, functions, region=0x10000, address=lambda offset: offset):
    """Bytes of each mapped function inside `code` that no unit and no earlier function covers.

    size: image size; code: [(start, end)] measured code ranges; units: [(start, end)];
    functions: as returned by load(). Returns [(entry, bytes)] for functions with bytes left,
    and [(start, end, bytes)] for the code bytes no unit or function covers, grouped by
    `region`-aligned stretches of each code range (as file offsets mapped by `address`).
    """
    claimed = bytearray(b"\1" * size)
    for start, end in code:
        claimed[start:end] = bytes(end - start)
    for start, end in units:
        claimed[start:end] = b"\1" * (end - start)
    result = []
    for entry, spans in functions:
        count = 0
        for start, end in spans:
            start, end = max(0, start), min(size, end)
            if start < end:
                count += claimed[start:end].count(0)
                claimed[start:end] = b"\1" * (end - start)
        if count:
            result.append((entry, count))
    leftover = []
    for start, end in code:
        at = start
        while at < end:
            stop = min(end, at + region - address(at) % region)
            count = claimed[at:stop].count(0)
            if count:
                leftover.append((at, stop, count))
            at = stop
    return result, leftover


if __name__ == "__main__":
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    Path(sys.argv[3]).write_text(convert(sys.argv[1], sys.argv[2]), encoding="utf-8", newline="\n")
