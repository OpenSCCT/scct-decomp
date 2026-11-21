"""Compare the code two x86 COFF static libraries contain, member by member.

Usage: python compare_libraries.py FIRST.lib SECOND.lib

Members are paired by archive name. Within each pair, executable sections are
paired by the public function symbol that starts them. A pair agrees when the
section bytes and the positions of its relocations are identical; relocation
targets are symbolic and are compared by name. Debug sections (.debug$S,
.debug$T) and the producer stamps they carry are not compared, because they
record the compiler build itself.
"""

import hashlib
import struct
import sys
from collections import Counter


def members(data):
    if data[:8] != b"!<arch>\n":
        raise ValueError("not a COFF archive")
    position, longnames = 8, b""
    while position + 60 <= len(data):
        header = data[position:position + 60]
        name = header[:16].decode("latin-1").rstrip()
        size = int(header[48:58])
        body = data[position + 60:position + 60 + size]
        if name == "//":
            longnames = body
        elif name not in ("/", ""):
            if name.startswith("/") and name[1:].isdigit():
                start = int(name[1:])
                name = longnames[start:longnames.index(b"\0", start)].decode("latin-1") if b"\0" in longnames[start:] \
                    else longnames[start:].split(b"/\n")[0].decode("latin-1")
            yield name.rstrip("/"), body
        position += 60 + size + (size & 1)


def functions(obj):
    machine, sections, _, table, count, optional, _ = struct.unpack_from("<HHIIIHH", obj)
    if machine != 0x14C or optional:
        return {}
    strings = table + 18 * count
    out, index = {}, 0
    while index < count:
        short, value, section, kind, storage, aux = struct.unpack_from("<8sIhHBB", obj, table + 18 * index)
        if short[:4] == b"\0\0\0\0":
            offset = strings + int.from_bytes(short[4:], "little")
            short = obj[offset:obj.index(b"\0", offset)]
        name = short.rstrip(b"\0")
        if kind == 0x20 and storage == 2 and value == 0 and 1 <= section <= sections:
            header = 20 + 40 * (section - 1)
            size, raw, relocs = struct.unpack_from("<III", obj, header + 16)
            nrelocs, = struct.unpack_from("<H", obj, header + 32)
            flags, = struct.unpack_from("<I", obj, header + 36)
            if flags & 0x20 and size:
                fixups = []
                for i in range(nrelocs):
                    site, symbol, rtype = struct.unpack_from("<IIH", obj, relocs + 10 * i)
                    target = struct.unpack_from("<8s", obj, table + 18 * symbol)[0]
                    if target[:4] == b"\0\0\0\0":
                        o = strings + int.from_bytes(target[4:], "little")
                        target = obj[o:obj.index(b"\0", o)]
                    fixups.append((site, rtype, target.rstrip(b"\0")))
                out[name] = (obj[raw:raw + size], sorted(fixups))
        index += 1 + aux
    return out


def main(first, second):
    a = dict(members(open(first, "rb").read()))
    b = dict(members(open(second, "rb").read()))
    paired = sorted(set(a) & set(b))
    tally = Counter()
    for name in paired:
        fa, fb = functions(a[name]), functions(b[name])
        for symbol in sorted(set(fa) & set(fb)):
            tally["paired functions"] += 1
            tally["paired bytes"] += len(fa[symbol][0])
            if fa[symbol] == fb[symbol]:
                tally["identical functions"] += 1
            else:
                tally["different functions"] += 1
                print("differs", name, symbol.decode("latin-1"))
    for path in (first, second):
        # CodeView compile records store the frontend and backend version as
        # 16-bit major, minor and build words.
        data = open(path, "rb").read()
        stamps = {build: data.count(struct.pack("<HHH", 13, 10, build)) for build in (3052, 3077)}
        print(f"{path}: CodeView 13.10.build stamps {stamps}")
    print(f"{first}: {len(a)} members, SHA-256 {hashlib.sha256(open(first, 'rb').read()).hexdigest()}")
    print(f"{second}: {len(b)} members, SHA-256 {hashlib.sha256(open(second, 'rb').read()).hexdigest()}")
    print(f"paired members: {len(paired)}")
    for key in ("paired functions", "paired bytes", "identical functions", "different functions"):
        print(f"{key}: {tally[key]}")


if __name__ == "__main__":
    main(*sys.argv[1:3])
