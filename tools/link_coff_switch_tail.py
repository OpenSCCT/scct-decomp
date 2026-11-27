"""Authenticate the complete VC6 COFF contribution of a byte-indexed diagnostic switch."""
import struct

from link_x86 import link_function, region, symbol_index


def switch_tail_site(unit):
    """The only manifest hint is the location of the selector-address operand."""
    site = unit["coff_switch_tail"]
    name = unit.get("rebuilt_symbol")
    if (type(site) is not int or type(unit.get("size")) is not int or
            not 16 <= site <= unit["size"] - 11 or not isinstance(name, str) or not name or
            not isinstance(unit.get("link_bindings"), dict) or
            {"ltcg_link", "coff_alignment", "rebuilt_offset", "rebuilt_storage_class"}.intersection(unit)):
        raise ValueError("a COFF switch tail needs a named linked function and an in-body selector operand")
    return site


def link_switch_tail(obj, unit, address, original, section_end, **readers):
    """Return just the code after validating the compiler's trailing tables and padding."""
    site = switch_tail_site(unit)
    name, size, offset = unit["rebuilt_symbol"], unit["size"], unit["offset"]
    _, symbols, functions, section_functions, _ = symbol_index(bytes(obj))
    matches = functions.get(name.encode("ascii"), ())
    if len(matches) != 1 or section_functions[matches[0]] != 1:
        raise ValueError("expected a single COFF switch function")
    section = matches[0]
    header = 20 + 40 * (section - 1)
    length, start, relocations = struct.unpack_from("<III", obj, header + 16)
    count, _, flags = struct.unpack_from("<HHI", obj, header + 32)
    # These VC6 functions are 16-aligned, executable, read-only .text COMDATs.
    if (obj[header:header + 8].rstrip(b"\0") != b".text" or flags & 0xe0f01020 != 0x60501020 or
            address & 15 or not size < length or offset + length > section_end or
            original is None or offset + length > len(original)):
        raise ValueError("COFF switch contribution exceeds its measured code section or has invalid alignment")
    code = region(obj, start, length)
    reloc = {}
    for pos, index, kind in struct.iter_unpack("<IIH", region(obj, relocations, 10 * count)):
        if pos in reloc or index not in symbols:
            raise ValueError("invalid COFF switch relocation")
        reloc[pos] = (kind, symbols[index])

    def label(pos, storage):
        kind, (label_name, value, owner, symbol_type, cls) = reloc.get(pos, (None, (b"", 0, 0, 0, 0)))
        if (kind != 6 or owner != section or symbol_type != 0 or cls != storage or
                not label_name.startswith(b"$L") or not label_name[2:].isdigit() or
                code[pos:pos + 4] != bytes(4)):
            raise ValueError("switch address must be a zero-addend DIR32 relocation to a compiler-owned label")
        return value

    # cmp ecx, maximum; ja default; xor edx,edx; mov dl,[ecx+selector]; jmp [edx*4+table]
    dispatch = site - 16
    if (code[dispatch:dispatch + 2] != b"\x81\xf9" or code[site - 10:site - 8] != b"\x0f\x87" or
            code[site - 4:site] != b"\x33\xd2\x8a\x91" or code[site + 4:site + 7] != b"\xff\x24\x95"):
        raise ValueError("expected a bounded VC6 byte-indexed switch dispatch")
    maximum, = struct.unpack_from("<I", code, dispatch + 2)
    displacement, = struct.unpack_from("<i", code, site - 8)
    default = site - 4 + displacement
    selector, table = label(site, 3), label(site + 7, 3)
    entries, partial = divmod(selector - table, 4)
    if (table != ((size + 3) & ~3) or partial or not 1 <= entries <= 256 or
            maximum >= 256 or not site + 11 <= default < size):
        raise ValueError("switch table, selector or default has invalid bounds")
    end = selector + maximum + 1
    if length != ((end + 15) & ~15):
        raise ValueError("switch selector and final alignment must consume the complete COFF contribution")
    # A final ret 8 ends these member functions. VC6 aligns the table with LEA ECX,[ECX+0],
    # and aligns the end of the selector with single-byte NOPs.
    if (code[size - 3:size] != b"\xc2\x08\x00" or code[size:table] != b"\x8d\x49\x00" or
            code[end:] != b"\x90" * (length - end)):
        raise ValueError("unexpected code boundary or padding in COFF switch")
    slots = set(range(table, selector, 4))
    if ({p for p in reloc if p + 4 > size} != slots or
            {p for p in reloc if p < site + 11 and p + 4 > dispatch} != {site, site + 7}):
        raise ValueError("unexpected relocation in the switch dispatch or trailer")
    for pos, (_, (_, value, owner, _, _)) in reloc.items():
        if owner == section and value >= size and pos not in (site, site + 7):
            raise ValueError("unexpected reference into the compiler's trailing switch data")
    arms = {label(pos, 6) for pos in slots}
    if (len(arms) != entries or default not in arms or any(not site + 11 <= arm < size for arm in arms) or
            set(code[selector:end]) != set(range(entries))):
        raise ValueError("every distinct switch arm must be in the body and reachable by the selector")
    linked = link_function(obj, name, length, address, unit["link_bindings"], **readers)
    if linked != original[offset:offset + length]:
        raise ValueError("linked switch code, targets, selector or padding differ from retail")
    return linked[:size]
