"""Verify complete named and compiler-private string objects in shared VC7 COFF data sections."""
import re
import struct

from images import initialized_pe_data
from link_x86 import link_function, region, symbol_index


def coff_string_spec(unit):
    if (not unit.get("rebuilt_symbol") or not isinstance(unit.get("link_bindings"), dict)
            or {"ltcg_link", "rebuilt_offset", "rebuilt_storage_class",
                "coff_rtti_vtable", "coff_switch_tail"}.intersection(unit)):
        raise ValueError("COFF strings require a named linked COFF function")
    result = {}
    for key in ("coff_private_strings", "coff_readonly_strings"):
        if key not in unit:
            continue
        strings = unit[key]
        if not isinstance(strings, dict) or not strings:
            raise ValueError("expected a nonempty map of bound COFF strings")
        public = key == "coff_readonly_strings"
        # MSVC decorates a global const unsigned short array as ?name@@3QBGB.
        pattern = r"\?[A-Za-z_][A-Za-z_0-9]*@@3QBGB" if public else r"\$SG[0-9]+"
        for name, description in strings.items():
            if (not isinstance(name, str) or not re.fullmatch(pattern, name)
                    or name not in unit["link_bindings"] or not isinstance(description, dict)
                    or set(description) not in ({"ascii"}, {"utf16"})
                    or public and "utf16" not in description):
                raise ValueError("invalid COFF string symbol, encoding or binding")
            encoding, length = next(iter(description.items()))
            width = 2 if encoding == "utf16" else 1
            if type(length) is not int or length < width or length % width:
                raise ValueError("invalid terminated COFF string length")
            result[name.encode("ascii")] = ("utf-16le" if width == 2 else "ascii", width, length, public)
    return result


def string_contents(obj, symbols, index, width, length, public):
    name, value, section, kind, storage = symbols[index]
    section_count, = struct.unpack_from("<H", obj, 2)
    if kind or storage != (2 if public else 3) or not 1 <= section <= section_count:
        raise ValueError("expected a defined COFF data object with the recorded linkage")
    header = 20 + 40 * (section - 1)
    raw_name, _, _, size, raw, _, _, relocs, _, flags = struct.unpack_from("<8sIIIIIIHHI", obj, header)
    section_name = raw_name.rstrip(b"\0")
    if public and section_name != b".rdata":
        raise ValueError("a named const TCHAR array must occupy read-only initialized COFF data")
    required = {b".data": 0xc0000040, b".rdata": 0x40000040, b".bss": 0xc0000080}
    if (section_name not in required or (flags & 0xe0f010e0) != (required[section_name] | 0x00300000)
            or relocs or value % 4 or value + length > size):
        raise ValueError("expected a four-byte-aligned string in non-relocated COFF data")
    # The section symbol is not another object. All other defined data labels bound the
    # current object's storage, including optional zero padding before the next aligned object.
    neighbors = [v for i, (n, v, sec, _, _) in symbols.items()
                 if sec == section and i != index and n != section_name]
    if value in neighbors:
        raise ValueError("ambiguous COFF string start")
    end = min((v for v in neighbors if v > value), default=size)
    after = value + length
    aligned_end = (after + 3) & ~3
    if not after <= end <= aligned_end:
        raise ValueError("string length does not occupy its complete COFF object")
    if section_name == b".bss":
        if raw or length != width:
            raise ValueError("only a single empty terminator can be a zero-filled COFF string")
        return bytes(width), True
    if not raw:
        raise ValueError("initialized COFF strings need a file-backed contribution")
    data = region(obj, raw, size)
    if any(data[after:end]):
        raise ValueError("nonzero data after the COFF string terminator")
    return data[value:after], section_name == b".data"


def link_coff_strings(obj, unit, length, address, original, **readers):
    spec = coff_string_spec(unit)
    if original is None:
        raise ValueError("COFF strings need the locked retail image")
    _, symbols, functions, _, _ = symbol_index(bytes(obj))
    matches = functions.get(unit["rebuilt_symbol"].encode("ascii"), ())
    if len(matches) != 1:
        raise ValueError("expected one function containing the bound COFF string references")
    header = 20 + 40 * (matches[0] - 1)
    _, start, relocs = struct.unpack_from("<III", obj, header + 16)
    count, = struct.unpack_from("<H", obj, header + 32)
    refs = {}
    for site, index, mode in struct.iter_unpack("<IIH", region(obj, relocs, count * 10)):
        name = symbols[index][0]
        if name not in spec:
            if re.fullmatch(rb"\$SG[0-9]+", name):
                raise ValueError("a referenced private COFF string has no encoding and length")
            continue
        if (mode != 6 or site + 4 > length or region(obj, start + site, 4) != bytes(4)
                or name in refs and refs[name] != index):
            raise ValueError("COFF strings need zero-addend absolute references")
        refs[name] = index
    if refs.keys() != spec.keys():
        raise ValueError("a declared COFF string is not referenced by the function")

    view = bytearray(obj)
    symbol_table, = struct.unpack_from("<I", obj, 8)
    originals = []
    for name, index in refs.items():
        if sum(sym[0] == name for sym in symbols.values()) != 1:
            raise ValueError("ambiguous COFF string label")
        encoding, width, size, public = spec[name]
        content, writable = string_contents(obj, symbols, index, width, size, public)
        text = content.decode(encoding)
        if not text.endswith("\0") or "\0" in text[:-1]:
            raise ValueError("expected one complete terminated COFF string")
        va = unit["link_bindings"][name.decode()]["va"]
        if type(va) is not int or va % 4:
            raise ValueError("expected a four-byte-aligned retail COFF string address")
        if content != initialized_pe_data(original, va, size, writable=writable):
            raise ValueError(f"COFF string {name.decode()} differs from retail")
        originals.append((va, va + size))
        # The regular linker handles the code and every relocation unchanged. Expose each
        # authenticated data object as an external reference in the symbol view.
        struct.pack_into("<IhHB", view, symbol_table + index * 18 + 8, 0, 0, 0, 2)
    originals.sort()
    if any(a[1] > b[0] for a, b in zip(originals, originals[1:])):
        raise ValueError("overlapping COFF string objects in retail")
    return link_function(view, unit["rebuilt_symbol"], length, address, unit["link_bindings"], **readers)
