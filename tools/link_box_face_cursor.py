"""Check VC7's biased EBX cursor over the six four-index faces of a box."""

import hashlib
import re
import struct

from images import initialized_pe_data
from link_image import _file_offset
from link_vtable_exports import _export_addresses


ROW_BYTES = 4 * 4
TABLE_BYTES = 6 * ROW_BYTES
BIAS = 4


def box_face_export_args(link):
    if "box_face_cursor" not in link:
        return []
    spec = link["box_face_cursor"]
    if not isinstance(spec, dict) or set(spec) != {"symbol", "sha256"}:
        raise ValueError("a box-face cursor needs its data symbol and the SHA-256 of all 96 bytes")
    name, digest = spec["symbol"], spec["sha256"]
    if (not isinstance(name, str) or not re.fullmatch(r"\?(?:[A-Za-z_]\w*@)+@3PAY03HA", name, re.ASCII)
            or not isinstance(digest, str) or not re.fullmatch("[0-9a-f]{64}", digest)):
        raise ValueError("expected a decorated writable four-INT row array and a SHA-256 digest")
    if any(name in link.get(key, ()) for key in ("stubs", "constants", "tables", "case_selectors",
               "writable_strings", "interior_objects", "exported_vtables", "vtable_slots")):
        raise ValueError("the box-face table must have its own writable storage")
    return [f"/EXPORT:{name},DATA"]


def _check_loop(image, address, size, base, sites, digest):
    if (type(base) is not int or base % 4 or not 0 < base < base + TABLE_BYTES + BIAS < 2**32
            or base >> 31 != (base + TABLE_BYTES + BIAS) >> 31):
        raise ValueError("box-face table crosses the signed cursor limit or is unaligned")
    table = initialized_pe_data(image, base, TABLE_BYTES, writable=True)
    if hashlib.sha256(table).hexdigest() != digest:
        raise ValueError("the box-face table differs from its recorded 96 bytes")
    indices = struct.unpack("<24i", table)
    rows = [frozenset(indices[i:i + 4]) for i in range(0, len(indices), 4)]
    if any(len(row) != 4 for row in rows) or len(set(rows)) != 6 or any(indices.count(i) != 3 for i in range(8)):
        raise ValueError("expected six four-corner faces of an eight-corner box")
    off, flags = _file_offset(image, address, size)
    if not flags & 0x20000000:
        raise ValueError("box-face cursor must lie in executable code")
    code = image[off:off + size]
    if len(code) != size:
        raise ValueError("truncated box-face cursor function")
    # The compiler holds a pointer to the second INT in each row in EBX.
    # Validate the two relocated immediates and the loop that advances the row.
    # Whole-function comparison also checks every byte between these operands.
    begin, limit = sites
    if not (1 <= begin < limit - 5 and limit + 4 <= len(code)):
        raise ValueError("box-face cursor operands fall outside the function")
    start_operand = b"\xbb" + struct.pack("<I", base + BIAS)           # mov ebx, table+4
    end_operand = b"\x81\xfb" + struct.pack("<I", base + TABLE_BYTES + BIAS)
    if code[begin-1:begin+4] != start_operand or code[limit-2:limit+4] != end_operand:
        raise ValueError("expected the initial EBX address and the terminal CMP immediate")

    # VC7 may advance a parallel plane cursor before CMP and spill it before JL.
    stride_end = limit - 2
    if code[stride_end-3:stride_end] == b"\x83\xc1\x10":
        stride_end -= 3
    if code[stride_end-3:stride_end] != b"\x83\xc3\x10":
        raise ValueError("expected one four-index row advance before the comparison")
    branch = limit + 4
    if code[branch:branch+4] == b"\x89\x4c\x24\x0c":
        branch += 4
    if code[branch:branch+2] != b"\x0f\x8c" or branch + 6 > len(code):
        raise ValueError("expected a signed backedge using the terminal comparison flags")
    target = branch + 6 + struct.unpack_from("<i", code, branch + 2)[0]
    if not begin + 4 <= target < stride_end - 3:
        raise ValueError("box-face loop branch must resume within its body")

    # The ordered loads address the four INTs at EBX-4, EBX, EBX+4 and EBX+8.
    # Registers other than ESP or the live EBX may receive the corner indices.
    pos = target
    for displacement in (-4, 0, 4, 8):
        mod = 0 if displacement == 0 else 0x40
        patterns = [bytes((0x8b, mod | (reg << 3) | 3)) for reg in (0, 1, 2, 5, 6, 7)]
        if displacement:
            patterns = [pattern + bytes((displacement & 255,)) for pattern in patterns]
        loads = [at for pattern in patterns if (at := code.find(pattern, pos, stride_end - 3)) >= 0]
        if not loads:
            raise ValueError("expected four in-bounds face indices in traversal order")
        pos = min(loads) + len(patterns[0])


def resolve_box_face_cursor(rebuilt, retail, size, address, link, bindings):
    """Resolve the start and end operands after authenticating both complete row traversals."""
    box_face_export_args(link)
    spec = link["box_face_cursor"]
    name = spec["symbol"]
    symbols, placed = link["symbols"].copy(), bindings.copy()
    if (name not in symbols or not isinstance(placed.get(name), dict)
            or type(symbols[name]) is not int or type(placed[name].get("va")) is not int):
        raise ValueError("the box-face table needs both base addresses")
    if _export_addresses(rebuilt, {name})[name] != symbols[name]:
        raise ValueError("named DATA export does not identify the rebuilt box-face table")
    fields = []
    sites = {}
    for field in link["fields"]:
        if len(field) >= 3 and field[2] == name:
            if (len(field) != 4 or field[1] != "abs" or type(field[0]) is not int
                    or type(field[3]) is not int or field[3] not in (BIAS, TABLE_BYTES + BIAS)
                    or field[3] in sites):
                raise ValueError("box-face table needs precisely the start and terminal absolute operands")
            site, _, _, delta = field
            sites[delta] = site
            key = (name, delta)
            symbols[key] = symbols[name] + delta
            placed[key] = {"va": bindings[name]["va"] + delta}
            fields.append((site, "abs", key))
        else:
            fields.append(field)
    if set(sites) != {BIAS, TABLE_BYTES + BIAS}:
        raise ValueError("both start and terminal fields of the box-face cursor are required")
    operands = (sites[BIAS], sites[TABLE_BYTES + BIAS])
    _check_loop(rebuilt, link["rebuilt_address"], size, symbols[name], operands, spec["sha256"])
    _check_loop(retail, address, size, bindings[name]["va"], operands, spec["sha256"])
    return dict(link, symbols=symbols, fields=fields), placed
