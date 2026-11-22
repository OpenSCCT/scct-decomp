"""Place a function from a link-time code generation (LTCG) build at its retail address.

With VC7.0 /GL and LINK /LTCG, the linker generates the code and chooses calling
conventions from the callers it sees, so a unit's rebuilt artifact is a linked DLL,
not an object file. The DLL is linked from the unit's object, scaffolding roots that
call the function the way retail code does, and a stub object holding one int3 code
section for every external the source declares but does not define.

A unit's "ltcg_link" record names the roots and stubs, the function's file offset and
virtual address in the DLL, and every address field in the function: its offset,
whether it is absolute or a rel32 branch, and the symbol it refers to. The built field
must refer to that symbol's recorded DLL address; it is then rewritten with the retail
address from the unit's link_bindings, as tools/link_x86.py does for COFF relocations.
Constants the source defines (string literals) are compared with retail byte for byte.
A jump table the compiler places after the function is a symbol too: the record names it in
"tables" with its entry count, and check_table compares its entries with the retail table.
"""

import struct

LINK_OPTIONS = ("/nologo", "/LTCG", "/DLL", "/NOENTRY", "/NODEFAULTLIB", "/BASE:0x10000000")


def stub_object(names):
    """A COFF object with one 1-byte int3 code section per external symbol.

    __except_list is absolute 0, as the C runtime defines it; its section stays unused."""
    names = list(names)
    if len(set(names)) != len(names) or not all(isinstance(n, str) and n for n in names):
        raise ValueError("stub names must be distinct non-empty strings")
    strtab = bytearray(4)
    sections = bytearray()
    symbols = bytearray()
    raw = 20 + 40 * len(names)
    for i in range(len(names)):
        sections += struct.pack("<8sIIIIIIHHI", b".text$s", 0, 0, 1, raw + i, 0, 0, 0, 0, 0x60100020)
    for i, name in enumerate(names):
        encoded = name.encode("ascii")
        if len(encoded) <= 8:
            field = encoded.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strtab))
            strtab += encoded + b"\0"
        if name == "__except_list":
            # The C runtime defines this as the absolute offset 0 of the thread information block.
            symbols += field + struct.pack("<IhHBB", 0, -1, 0, 2, 0)
        else:
            symbols += field + struct.pack("<IhHBB", 0, i + 1, 0x20, 2, 0)
    struct.pack_into("<I", strtab, 0, len(strtab))
    header = struct.pack("<HHIIIHH", 0x14C, len(names), 0, raw + len(names), len(names), 0, 0)
    return header + bytes(sections) + b"\xcc" * len(names) + bytes(symbols) + bytes(strtab)


def link_arguments(link):
    """The fixed LINK.EXE options plus the unit's roots, as a list of arguments."""
    roots = link["roots"]
    if not roots or not all(isinstance(r, str) and r and " " not in r for r in roots):
        raise ValueError("an LTCG unit needs named scaffolding roots")
    return [*LINK_OPTIONS, *(f"/INCLUDE:{r}" for r in roots)]


def _sections(image):
    if image[:2] != b"MZ":
        raise ValueError("expected a linked PE image")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe:pe + 4] != b"PE\0\0" or struct.unpack_from("<H", image, pe + 4)[0] != 0x14C:
        raise ValueError("expected an x86 PE image")
    count, optional = struct.unpack_from("<H", image, pe + 6)[0], struct.unpack_from("<H", image, pe + 20)[0]
    base = struct.unpack_from("<I", image, pe + 24 + 28)[0]
    table = pe + 24 + optional
    result = []
    for i in range(count):
        name, vsize, rva, rsize, raw = struct.unpack_from("<8sIIII", image, table + 40 * i)
        flags = struct.unpack_from("<I", image, table + 40 * i + 36)[0]
        result.append((rva, vsize, raw, rsize, flags))
    return base, result


def _file_offset(image, va, size):
    base, sections = _sections(image)
    for rva, vsize, raw, rsize, flags in sections:
        if rva <= va - base and va - base + size <= rva + min(vsize, rsize):
            return raw + va - base - rva, flags
    raise ValueError(f"address 0x{va:x} is outside the linked image's sections")


TABLE_ENTRY_LIMIT = 0x1000


def check_table(image, built, size, address, linked, retail, count, read_table):
    """Check a jump table that the compiler placed after its function.

    The table holds absolute addresses of labels inside the function, so each entry must lie in
    the linked function. Rebased to the retail function, the entries must be the bytes retail holds
    at the table's retail address, which must also lie after the function's end."""
    if type(count) is not int or not 0 < count <= TABLE_ENTRY_LIMIT:
        raise ValueError("a jump table needs a positive entry count")
    if read_table is None:
        raise ValueError("jump tables need the retail image")
    if type(linked) is not int or type(retail) is not int:
        raise ValueError("jump table addresses must be integers")
    if linked < built + size or retail < address + size:
        raise ValueError("a jump table must lie after its function in the image and in retail")
    start, _ = _file_offset(image, linked, 4 * count)
    entries = struct.unpack_from(f"<{count}I", image, start)
    if any(not built <= entry < built + size for entry in entries):
        raise ValueError("a jump table entry lies outside its function")
    rebased = [(address + entry - built) & 0xFFFFFFFF for entry in entries]
    if read_table(retail, 4 * count) != struct.pack(f"<{count}I", *rebased):
        raise ValueError(f"jump table at 0x{retail:x} differs from retail")


def place_function(image, size, address, link, bindings, *, read_constant=None, read_table=None):
    """Return the function's bytes from the linked DLL as they appear at retail `address`."""
    offset, built = link["rebuilt_offset"], link["rebuilt_address"]
    if type(offset) is not int or type(built) is not int:
        raise ValueError("record the function's file offset and address in the linked image")
    start, flags = _file_offset(image, built, size)
    if start != offset or not flags & 0x20000000:
        raise ValueError("the function's offset and address disagree or lie outside code")
    code = bytearray(image[offset:offset + size])
    symbols, constants = link["symbols"], link.get("constants", {})
    tables = link.get("tables", {})
    if type(tables) is not dict:
        raise ValueError("tables maps each jump table to its entry count")
    referenced = set()
    seen = set()
    for site, kind, name in link["fields"]:
        if type(site) is not int or not 0 <= site <= size - 4 or site in seen:
            raise ValueError("address field outside the function or repeated")
        if any(abs(site - other) < 4 for other in seen):
            raise ValueError("overlapping address fields")
        seen.add(site)
        if name not in symbols or name not in bindings:
            raise ValueError(f"address field refers to an unrecorded symbol: {name}")
        value = struct.unpack_from("<I", code, site)[0]
        if kind == "abs":
            target = value
        elif kind == "rel32":
            target = (built + site + 4 + value) & 0xFFFFFFFF
        else:
            raise ValueError(f"unknown address field kind: {kind!r}")
        if target != symbols[name]:
            raise ValueError(f"the field at +0x{site:x} does not refer to {name}")
        retail = bindings[name]["va"]
        if name in tables:
            if kind != "abs":
                raise ValueError(f"jump table {name} is referred to by an absolute field")
            check_table(image, built, size, address, target, retail, tables[name], read_table)
            referenced.add(name)
        elif name in constants:
            length = constants[name]
            if read_constant is None or type(length) is not int or length <= 0:
                raise ValueError("constants need their size and the retail image")
            at, _ = _file_offset(image, target, length)
            if read_constant(retail, length) != image[at:at + length]:
                raise ValueError(f"constant {name} differs from retail")
        value = retail if kind == "abs" else (retail - (address + site + 4)) & 0xFFFFFFFF
        struct.pack_into("<I", code, site, value)
    if set(tables) - referenced:
        raise ValueError("tables name a jump table that no field refers to")
    return bytes(code)
