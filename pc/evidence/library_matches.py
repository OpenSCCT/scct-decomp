"""Find named third-party library functions that occur byte for byte in the Steam executables.

Other Windows programs that shipped with a PDB or a link map carry the names of the static
library code they link: the C runtime, D3DX, the Microsoft Layer for Unicode. Where such a
function is linked into Chaos Theory too, its bytes are the same apart from the operands
that depend on where the linker put things, so its name, its library and its object file
transfer.

For each named function of a source build the bytes are taken with those operands masked:
relative call and jump targets, and 32-bit operands that point into the source image. The
masked pattern is searched in the code of each Steam executable. A hit must agree on every
unmasked byte, and its masked operands must point into the Steam image. A location is kept
when exactly one address matches and the name comes from a library the game itself links.

Usage:
    python pc/evidence/library_matches.py GAME_DIR BUILDS.tsv OUT_DIR

BUILDS.tsv lists the source builds, one per line: label, executable, PDB or MAP file,
tab-separated, with paths relative to the list. The builds, like the game, stay under
local/. OUT_DIR receives matches.tsv (every hit) and library-functions.tsv (the kept
locations). Needs Capstone 5 (python -m pip install capstone==5.0.7).
"""
import bisect
import collections
import csv
import glob
import json
import os
import re
import struct
import sys

import capstone

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
BS = chr(92)
MIN_LENGTH = 24     # bytes of code
MIN_FIXED = 18      # bytes that are not masked operands
MIN_ANCHOR = 7      # longest run of unmasked bytes, used to search
RUNTIME_LIBS = ("libcmt", "libc.", "libcmtd", "libcd", "msvcrt", "libcp", "msvcprt", "oldnames", "libci")


class PE:
    """The parts of an x86 PE image this comparison reads."""

    def __init__(self, path):
        self.data = d = open(path, "rb").read()
        e = struct.unpack_from("<I", d, 0x3c)[0]
        if d[e:e + 4] != b"PE\0\0":
            raise ValueError("not a PE image: " + path)
        sections = struct.unpack_from("<H", d, e + 6)[0]
        optional_size = struct.unpack_from("<H", d, e + 20)[0]
        optional = e + 24
        self.base = struct.unpack_from("<I", d, optional + 28)[0]
        self.size = struct.unpack_from("<I", d, optional + 56)[0]
        self.sections = []
        for i in range(sections):
            at = optional + optional_size + 40 * i
            name, virtual_size, va, raw_size, raw = struct.unpack_from("<8sIIII", d, at)
            flags = struct.unpack_from("<I", d, at + 36)[0]
            self.sections.append((name.rstrip(b"\0").decode("latin1"), va, virtual_size, raw, raw_size, flags))

    def read(self, rva, count):
        for _, va, _, raw, raw_size, _ in self.sections:
            if va <= rva < va + raw_size:
                return self.data[rva - va + raw:rva - va + raw + count]
        return None

    def is_code(self, rva):
        for _, va, virtual_size, _, raw_size, flags in self.sections:
            if va <= rva < va + max(virtual_size, raw_size):
                return bool(flags & 0x20000000)
        return False

    def segment_rva(self, segment, offset):
        if 1 <= segment <= len(self.sections):
            return self.sections[segment - 1][1] + offset
        return None


def pdb_streams(path):
    """Return the streams of a PDB container, version 7.00 or 2.00."""
    d = open(path, "rb").read()
    streams = []
    if d.startswith(b"Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0"):
        block, _, _, directory_bytes, _, map_block = struct.unpack_from("<6I", d, 32)
        count = (directory_bytes + block - 1) // block
        blocks = struct.unpack_from("<%dI" % count, d, map_block * block)
        directory = b"".join(d[b * block:(b + 1) * block] for b in blocks)[:directory_bytes]
        n = struct.unpack_from("<I", directory, 0)[0]
        sizes = struct.unpack_from("<%dI" % n, directory, 4)
        at = 4 + 4 * n
        width, form = 4, "I"
    elif d.startswith(b"Microsoft C/C++ program database 2.00\r\n\x1aJG\0\0"):
        block = struct.unpack_from("<I", d, 0x2c)[0]
        root_size = struct.unpack_from("<I", d, 0x34)[0]
        count = (root_size + block - 1) // block
        pages = struct.unpack_from("<%dH" % count, d, 0x3c)
        directory = b"".join(d[p * block:(p + 1) * block] for p in pages)[:root_size]
        n = struct.unpack_from("<H", directory, 0)[0]
        sizes = [struct.unpack_from("<I", directory, 4 + 8 * i)[0] for i in range(n)]
        at = 4 + 8 * n
        width, form = 2, "H"
    else:
        raise ValueError("not a PDB 2.00 or 7.00 file: " + path)
    for size in sizes:
        if size in (0, 0xffffffff):
            streams.append(b"")
            continue
        count = (size + block - 1) // block
        blocks = struct.unpack_from("<%d%s" % (count, form), directory, at)
        at += width * count
        streams.append(b"".join(d[b * block:(b + 1) * block] for b in blocks)[:size])
    return streams


def symbol_name(record, at, counted):
    """A symbol's name: length-prefixed in old records, zero-terminated in new ones."""
    if counted:
        return record[at + 1:at + 1 + record[at]].decode("latin1")
    end = record.find(b"\0", at)
    return record[at:end if end >= 0 else len(record)].decode("latin1")


def symbol_records(stream, start=0, end=None):
    end = len(stream) if end is None else end
    at = start
    while at + 4 <= end:
        length, kind = struct.unpack_from("<HH", stream, at)
        if length < 2:
            break
        yield kind, stream[at + 4:at + 2 + length]
        at += 2 + length


def pdb_symbols(path, pe):
    """Return (functions, labels): [(rva, size, name, module)] from the module streams, {rva: name} from the publics."""
    streams = pdb_streams(path)
    dbi = streams[3]
    functions, labels = [], {}
    if not dbi:
        return functions, labels
    if struct.unpack_from("<i", dbi, 0)[0] == -1:
        records = struct.unpack_from("<H", dbi, 20)[0]
        modules_size = struct.unpack_from("<i", dbi, 24)[0]
        modules_at = 64
        new_layout = struct.unpack_from("<I", dbi, 4)[0] >= 19970606
    else:
        records = struct.unpack_from("<H", dbi, 4)[0]
        modules_size = struct.unpack_from("<i", dbi, 8)[0]
        modules_at = 24
        new_layout = False
    if records < len(streams):
        for kind, record in symbol_records(streams[records]):
            try:
                if kind in (0x110e, 0x1009, 0x110d, 0x110c, 0x1008, 0x1007):      # publics and data
                    offset, segment = struct.unpack_from("<IH", record, 4)
                    name = symbol_name(record, 10, kind in (0x1009, 0x1008, 0x1007))
                elif kind in (0x0203, 0x0201, 0x0202):                              # the same, 16-bit type indices
                    offset, segment = struct.unpack_from("<IH", record, 0)
                    name = symbol_name(record, 8, True)
                else:
                    continue
            except (struct.error, IndexError):
                continue
            rva = pe.segment_rva(segment, offset)
            if rva is not None:
                labels.setdefault(rva, name)
    at = modules_at
    end = modules_at + max(modules_size, 0)
    while at + 48 <= end:
        stream, symbols_size = struct.unpack_from("<HI", dbi, at + (34 if new_layout else 26))
        names = at + (64 if new_layout else 48)
        first = dbi.find(b"\0", names)
        second = dbi.find(b"\0", first + 1)
        if first < 0 or second < 0 or second > end:
            break
        module = dbi[names:first].decode("latin1")
        archive = dbi[first + 1:second].decode("latin1")
        tag = module if module == archive or not archive else archive + " : " + module
        at = (second + 1 + 3) & ~3
        if stream == 0xffff or stream >= len(streams) or symbols_size < 4:
            continue
        data = streams[stream]
        for kind, record in symbol_records(data, 4, min(symbols_size, len(data))):
            try:
                if kind in (0x1110, 0x110f, 0x100a, 0x100b):        # procedures
                    length = struct.unpack_from("<I", record, 12)[0]
                    offset, segment = struct.unpack_from("<IH", record, 28)
                    name = symbol_name(record, 35, kind in (0x100a, 0x100b))
                elif kind in (0x020a, 0x020b):                       # procedures, 16-bit type indices
                    length = struct.unpack_from("<I", record, 12)[0]
                    offset, segment = struct.unpack_from("<IH", record, 24)
                    name = symbol_name(record, 33, True)
                else:
                    continue
            except (struct.error, IndexError):
                continue
            rva = pe.segment_rva(segment, offset)
            if rva is not None and length and name:
                functions.append((rva, length, name, tag))
    return functions, labels


MAP_LINE = re.compile(r"^\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8})\s+(?:f\s+)?(?:i\s+)?(\S.*)?$")


def map_symbols(path, pe):
    """Return (functions, labels) from a Microsoft link map; sizes are filled in later."""
    functions, labels = [], {}
    for line in open(path, encoding="latin1", errors="replace"):
        found = MAP_LINE.match(line)
        if not found or int(found[1], 16) == 0:
            continue
        rva = int(found[4], 16) - pe.base
        if 0 < rva < pe.size:
            labels.setdefault(rva, found[3])
            if pe.is_code(rva):
                functions.append((rva, 0, found[3], (found[5] or "").strip()))
    return functions, labels


def load(exe, symbols):
    """Read a source build: its image and its functions with sizes."""
    pe = PE(exe)
    functions, labels = (map_symbols if symbols.lower().endswith(".map") else pdb_symbols)(symbols, pe)
    known = {f[0] for f in functions}
    functions += [(rva, 0, name, "") for rva, name in labels.items() if rva not in known and pe.is_code(rva)]
    starts = sorted(set(labels) | {f[0] for f in functions})
    sized = []
    for rva, size, name, module in functions:
        if not size:
            # a function without a recorded length runs to the next known label
            index = bisect.bisect_right(starts, rva)
            size = (starts[index] if index < len(starts) else rva) - rva
            if not 0 < size <= 0x4000:
                continue
        sized.append((rva, size, name, module))
    return pe, sized


md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True


def signature(pe, rva, size):
    """Return (code, [(offset, kind)]) for one function; kind is 'r' relative or 'a' absolute. None if unusable."""
    code = pe.read(rva, size)
    if not code or len(code) < size:
        return None
    code = code.rstrip(b"\xcc\x90")
    if len(code) < MIN_LENGTH:
        return None
    low, high = pe.base, pe.base + pe.size
    masks = []
    at = 0
    for insn in md.disasm(code, pe.base + rva):
        raw = insn.bytes
        if insn.imm_size == 4:
            opcode = raw[0] if raw[0] != 0x0f else 0x100 | raw[1]
            if opcode in (0xe8, 0xe9) or 0x180 <= opcode <= 0x18f:
                masks.append((at + insn.imm_offset, "r"))
            elif low <= struct.unpack_from("<I", raw, insn.imm_offset)[0] < high:
                masks.append((at + insn.imm_offset, "a"))
        if insn.disp_size == 4 and low <= struct.unpack_from("<I", raw, insn.disp_offset)[0] < high:
            masks.append((at + insn.disp_offset, "a"))
        at += insn.size
    if at != len(code) or len(code) - 4 * len(masks) < MIN_FIXED:
        return None          # data in the range, a wrong size, or too little left to compare
    return code, masks


class Target:
    """One Steam executable's code."""

    def __init__(self, name, path):
        self.name = name
        self.pe = PE(path)
        self.text = [(va, self.pe.data[raw:raw + min(raw_size, virtual_size or raw_size)])
                     for section, va, virtual_size, raw, raw_size, flags in self.pe.sections
                     if flags & 0x20000000 and section != ".bind"]

    def find(self, code, masks):
        """All RVAs where the masked pattern occurs with its operands pointing into this image."""
        hidden = set()
        for position, _ in masks:
            hidden.update(range(position, position + 4))
        best = (0, 0)
        start = None
        for i in range(len(code) + 1):
            if i < len(code) and i not in hidden:
                start = i if start is None else start
            elif start is not None:
                best = max(best, (start, i), key=lambda run: run[1] - run[0])
                start = None
        if best[1] - best[0] < MIN_ANCHOR:
            return []
        anchor = code[best[0]:best[1]]
        fixed = [i for i in range(len(code)) if i not in hidden]
        low, high = self.pe.base, self.pe.base + self.pe.size
        hits = []
        for va, text in self.text:
            at = text.find(anchor)
            tries = 0
            while at >= 0:
                tries += 1
                if tries > 400:
                    return []        # the anchor is too common to mean anything
                first = at - best[0]
                if first >= 0 and first + len(code) <= len(text) and all(text[first + i] == code[i] for i in fixed):
                    valid = True
                    for position, kind in masks:
                        value = struct.unpack_from("<I", text, first + position)[0]
                        if kind == "r":
                            valid = valid and 0x1000 <= (va + first + position + 4 + value) & 0xffffffff < self.pe.size
                        else:
                            valid = valid and low <= value < high
                    if valid:
                        hits.append(va + first)
                at = text.find(anchor, at + 1)
        return hits


def search(game, builds, out_dir):
    """Search every source build in both Steam executables and write matches.tsv."""
    targets = [Target("campaign", os.path.join(game, "System", "splintercell3.exe")),
               Target("versus", os.path.join(game, "Versus", "System", "SCCT_Versus.ex"))]
    with open(os.path.join(out_dir, "matches.tsv"), "w", encoding="utf-8", newline="\n") as matches:
        matches.write("target\trva\tsize\tfixed\ttarget_hits\tsource\tsource_rva\tname\tmodule\n")
        for label, exe, symbols in builds:
            pe, functions = load(exe, symbols)
            seen = {}
            counts = collections.Counter()
            for rva, size, name, module in functions:
                found = signature(pe, rva, size) if size >= MIN_LENGTH and pe.is_code(rva) else None
                if found is None:
                    continue
                code, masks = found
                hidden = {i for position, _ in masks for i in range(position, position + 4)}
                key = (bytes(0 if i in hidden else b for i, b in enumerate(code)), tuple(masks))
                for target in targets:
                    if (target.name, key) not in seen:
                        seen[(target.name, key)] = target.find(code, masks)
                    hits = seen[(target.name, key)]
                    counts[target.name] += bool(hits)
                    for hit in hits:
                        matches.write("%s\t%06x\t%d\t%d\t%d\t%s\t%06x\t%s\t%s\n" % (
                            target.name, hit, len(code), len(code) - 4 * len(masks), len(hits), label, rva, name, module))
            print("%-24s %6d named functions, matches: campaign %d, versus %d" % (
                label, len(functions), counts["campaign"], counts["versus"]), flush=True)


def classify(module, name):
    """Return (library, object) for a module record, or from the name's shape when no module is recorded."""
    path = module.replace("/", BS)
    low = path.lower()
    obj = re.split(r" : |:", path)[-1].split(BS)[-1] if path else ""
    library = ""
    for part in path.split(" : "):
        tail = part.split(BS)[-1].lower()
        if tail.endswith(".lib"):
            library = tail
    if not library and ":" in low and not re.match(r"^[a-z]:\\", low):
        library = low.split(":")[0] + ".lib"         # the map form "library:object.obj"
    if library.startswith(RUNTIME_LIBS):
        return ("C/C++ runtime, VS .NET 2003" if ".net 2003" in low else "C/C++ runtime"), obj
    if library.startswith("d3dx"):
        return "D3DX", obj
    if library.startswith("unicows"):
        return "Microsoft Layer for Unicode", obj
    if library:
        return "other: " + library, obj
    if not path and (re.match(r"^_?D3DX\w+(@\d+)?$", name) or "@D3DX@@" in name):
        return "D3DX", ""
    return "", obj


def existing_units():
    """The units already recorded for the Steam executables, by (target, rva)."""
    units = {}
    for target in ("campaign", "versus"):
        for path in glob.glob(os.path.join(ROOT, "pc", "config", "units", "steam-252084-" + target, "*.json")):
            for unit in json.load(open(path, encoding="utf-8")):
                units[(target, unit["offset"])] = unit      # RVA and file offset coincide in both code sections
    return units


def keep(out_dir):
    """Reduce matches.tsv to the locations whose name transfers and write library-functions.tsv."""
    rows = collections.defaultdict(list)
    with open(os.path.join(out_dir, "matches.tsv"), encoding="utf-8") as f:
        for row in csv.DictReader(f, delimiter="\t", quoting=csv.QUOTE_NONE):
            if row.get("module") is not None:
                rows[(row["target"], int(row["rva"], 16))].append(row)
    units = existing_units()
    kept = []
    dropped = collections.Counter()
    for (target, rva), claims in sorted(rows.items()):
        size = max(int(row["size"]) for row in claims)
        claims = [(classify(row["module"], row["name"]), row) for row in claims if int(row["size"]) == size]
        libraries = collections.Counter(found[0] for found, _ in claims)
        linked = [name for name in libraries if name and not name.startswith("other")]
        if not linked:
            dropped["game object or a library the game does not link"] += 1
            continue
        if min(int(row["target_hits"]) for _, row in claims) != 1:
            dropped["library code at several addresses"] += 1
            continue
        library = max(linked, key=lambda name: libraries[name])
        if library.startswith("C/C++") and any(name.endswith("2003") for name in linked):
            library = "C/C++ runtime, VS .NET 2003"
        names = collections.Counter(row["name"] for found, row in claims if found[0] in linked)
        obj = next((found[1] for found, _ in claims if found[0] in linked and found[1]), "")
        kept.append((target, rva, size, library, obj, names.most_common(1)[0][0], len(names) > 1,
                     sorted({row["source"] for _, row in claims}), units.get((target, rva))))
    with open(os.path.join(out_dir, "library-functions.tsv"), "w", encoding="utf-8", newline="\n") as f:
        f.write("target\trva\tbytes\tlibrary\tobject\tname\tother_names\tbuilds\tunit\n")
        for target, rva, size, library, obj, name, aliases, builds, unit in kept:
            f.write("%s\t0x%06x\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n" % (
                target, rva, size, library, obj, name, "yes" if aliases else "", ",".join(builds), unit["id"] if unit else ""))
    print("not kept:", dict(dropped))
    for target in ("campaign", "versus"):
        totals = collections.defaultdict(lambda: [0, 0, 0])
        for row in kept:
            if row[0] == target:
                totals[row[3]][0] += 1
                totals[row[3]][1] += row[2]
                totals[row[3]][2] += row[8] is not None
        for library, (count, size, already) in sorted(totals.items(), key=lambda item: -item[1][1]):
            print("%-9s %-30s %4d functions %7d bytes, %d already units" % (target, library, count, size, already))


def main():
    game, listing, out_dir = sys.argv[1:4]
    base = os.path.dirname(os.path.abspath(listing))
    builds = []
    for line in open(listing, encoding="utf-8"):
        if line.strip() and not line.startswith("#"):
            label, exe, symbols = line.rstrip("\n").split("\t")
            builds.append((label, os.path.join(base, exe), os.path.join(base, symbols)))
    os.makedirs(out_dir, exist_ok=True)
    search(game, builds, out_dir)
    keep(out_dir)


if __name__ == "__main__":
    main()
