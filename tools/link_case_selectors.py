"""Validate VC7's byte-indexed jump tables emitted after a compiled x86 function."""
import struct

from images import pe_file_sections


def selector_bytes(image, address, size, site, selector, table, entries):
    for _, offset, length, base, flags in pe_file_sections(image):
        if (flags & 0xe0000020 == 0x60000020 and base <= address < address + size <= table
                and selector == table + 4 * entries and selector < base + length):
            break
    else:
        raise ValueError("case selector and jump table must follow the body in its read-execute code section")

    body = image[offset + address - base:offset + address - base + size]
    # cmp r32, imm8; ja rel8/rel32; movzx r32, byte ptr [index + selector]; jmp [r32*4 + table]
    if site < 8 or site + 11 > size:
        raise ValueError("case selector operand is outside the bounded switch dispatch")
    if site >= 12 and body[site - 9:site - 7] == b"\x0f\x87":
        compare = site - 12
        displacement = struct.unpack_from("<i", body, site - 7)[0]
    elif body[site - 5] == 0x77:
        compare = site - 8
        displacement = struct.unpack_from("<b", body, site - 4)[0]
    else:
        raise ValueError("case selector requires a checked x86 unsigned bounds branch")

    index, maximum = body[compare + 1] & 7, body[compare + 2]
    load, jump = body[site - 1], body[site + 6]
    if (body[compare] != 0x83 or body[compare + 1] != 0xf8 + index or maximum >= 128
            or body[site - 3:site - 1] != b"\x0f\xb6" or load & 0xc7 != 0x80 + index
            or index == 4 or body[site + 4:site + 6] != b"\xff\x24"
            or jump != 0x85 + (load & 0x38) or (load >> 3) & 7 == 4):
        raise ValueError("case selector requires a checked x86 byte lookup feeding the indexed jump")
    default = site - 3 + displacement
    if not 0 <= default < size:
        raise ValueError("case selector default branch leaves the function")
    if (struct.unpack_from("<I", body, site)[0] != selector
            or struct.unpack_from("<I", body, site + 7)[0] != table):
        raise ValueError("case selector dispatch addresses disagree with the recorded tables")
    if selector + maximum + 1 > base + length:
        raise ValueError("case selector extends beyond its read-execute code section")
    start = offset + selector - base
    data = image[start:start + maximum + 1]
    if len(data) != maximum + 1:
        raise ValueError("case selector is truncated in the executable")
    if any(value >= entries for value in data):
        raise ValueError("case selector names an entry outside the jump table")
    return data


def check_case_selectors(rebuilt, retail, size, address, link, bindings):
    selectors = link["case_selectors"]
    if type(selectors) is not dict or not selectors:
        raise ValueError("case_selectors must map selector symbols to checked jump table symbols")
    for name, table in selectors.items():
        if (type(table) is not str or name == table or table not in link.get("tables", {})
                or name in link.get("tables", {}) or name in link.get("constants", {})
                or name in link.get("writable_strings", {})):
            raise ValueError("case selector must accompany a separate checked jump table")
        entries = link["tables"][table]
        if type(entries) is not int or not 1 <= entries <= 256:
            raise ValueError("a byte-indexed switch needs between 1 and 256 jump table entries")
        sites = [i for i, kind, symbol in link["fields"] if kind == "abs" and symbol == name]
        if (len(sites) != 1 or type(sites[0]) is not int or [sites[0] + 7, "abs", table] not in link["fields"]
                or any(s not in link["symbols"] or s not in bindings for s in (name, table))):
            raise ValueError("expected consecutive checked absolute selector and jump table operands")
        original = selector_bytes(retail, address, size, sites[0], bindings[name]["va"], bindings[table]["va"], entries)
        linked = selector_bytes(rebuilt, link["rebuilt_address"], size, sites[0],
                                link["symbols"][name], link["symbols"][table], entries)
        if original != linked:
            raise ValueError("case selector bytes differ from retail")
