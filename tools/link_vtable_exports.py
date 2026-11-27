"""Bind compiler-emitted vtables by their named exports in the actual LTCG DLL."""

import re
import struct

from images import readonly_pe_data
from link_image import _file_offset


def vtable_export_args(link):
    if "exported_vtables" not in link:
        if "vtable_slots" in link:
            raise ValueError("vtable slots need a named vtable export")
        return []
    names = link["exported_vtables"]
    if (not isinstance(names, list) or not names or
            any(not isinstance(n, str) or not re.fullmatch(r"\?\?_7(?:[A-Za-z_]\w*@)+@6B@", n, re.ASCII)
                for n in names) or len(set(names)) != len(names)):
        raise ValueError("expected distinct decorated primary vtable names for export")
    if set(names).intersection(link.get("stubs", ())):
        raise ValueError("an exported vtable cannot be supplied by a stub")
    return [f"/EXPORT:{name},DATA" for name in sorted(names)]


def _export_addresses(image, requested):
    # The PE32 optional header starts 24 bytes after the PE signature.
    pe, = struct.unpack_from("<I", image, 0x3c)
    optional = pe + 24
    if (struct.unpack_from("<H", image, optional)[0] != 0x10b or
            struct.unpack_from("<H", image, pe + 20)[0] < 104 or
            not struct.unpack_from("<I", image, optional + 92)[0]):
        raise ValueError("expected a PE32 export directory")
    base, = struct.unpack_from("<I", image, optional + 28)
    rva, size = struct.unpack_from("<II", image, optional + 96)
    if not rva or size < 40:
        raise ValueError("missing PE export directory")
    directory = readonly_pe_data(image, base + rva, size)

    def table(start, count, width):
        offset = start - rva
        if not 0 <= offset <= len(directory) - count * width:
            raise ValueError("export table extends outside the PE export directory")
        return offset

    functions, names, addresses, pointers, ordinals = struct.unpack_from("<5I", directory, 20)
    addresses = table(addresses, functions, 4)
    pointers = table(pointers, names, 4)
    ordinals = table(ordinals, names, 2)
    result = {}
    for i in range(names):
        name_rva, = struct.unpack_from("<I", directory, pointers + i * 4)
        start = table(name_rva, 1, 1)
        end = directory.find(b"\0", start)
        if end < 0:
            raise ValueError("unterminated PE export name")
        name = directory[start:end].decode("ascii")
        if name not in requested:
            continue
        ordinal, = struct.unpack_from("<H", directory, ordinals + 2 * i)
        if ordinal >= functions or name in result:
            raise ValueError("invalid or duplicate named export")
        target, = struct.unpack_from("<I", directory, addresses + 4 * ordinal)
        if not target or rva <= target < rva + size:
            raise ValueError("exported vtable must be defined in the DLL, not forwarded")
        result[name] = base + target
    if result.keys() != requested:
        raise ValueError("a vtable is missing from the PE export directory")
    return result


def _check_vtable(image, address):
    if type(address) is not int or address % 4:
        raise ValueError("expected an aligned vtable in read-only data")
    first_slot, = struct.unpack("<I", readonly_pe_data(image, address, 4))
    _, flags = _file_offset(image, first_slot, 1)
    if flags & 0x20000020 != 0x20000020:
        raise ValueError("the first vtable entry must reference executable code")


def resolve_vtable_exports(rebuilt, original, link, bindings):
    """Resolve each named vtable independently of the field that uses its address."""
    vtable_export_args(link)
    names = set(link["exported_vtables"])
    slots = link.get("vtable_slots", {})
    if not isinstance(slots, dict):
        raise ValueError("vtable_slots maps each slot to its table, index and method")
    fields = names.union(slots)
    if any(fields.intersection(link.get(key, ())) for key in
           ("symbols", "stubs", "tables", "constants", "case_selectors", "writable_strings", "interior_objects")):
        raise ValueError("an exported vtable cannot also have a fixed address or another field role")
    used = set()
    for field in link["fields"]:
        if field[2] in fields:
            if len(field) != 3 or field[1] != "abs":
                raise ValueError("a vtable or vtable slot needs an absolute reference")
            used.add(field[2])
    if used != fields or not fields.issubset(bindings):
        raise ValueError("every exported vtable needs a field and a retail binding")
    resolved = _export_addresses(rebuilt, names)
    if (len(set(resolved.values())) != len(names) or
            len({bindings[name]["va"] for name in names}) != len(names)):
        raise ValueError("distinct vtables must occupy distinct addresses")
    for name, address in resolved.items():
        _check_vtable(rebuilt, address)
        _check_vtable(original, bindings[name]["va"])
    known_tables = {n: va for n, va in link["symbols"].items()
                    if n.startswith("??_7") and n.endswith("@") and n in bindings}
    known_tables.update(resolved)
    retail_tables = {n: bindings[n]["va"] for n in known_tables}
    for alias, spec in slots.items():
        if not isinstance(spec, list) or len(spec) != 3:
            raise ValueError("expected a vtable, slot index and method")
        table, index, method = spec
        if (table not in names or type(index) is not int or not 0 < index < 2**30
                or alias != f"{table}+0x{4 * index:x}" or method not in link["symbols"] or method not in bindings):
            raise ValueError("invalid named vtable slot")
        offset = 4 * index
        if bindings[alias]["va"] != bindings[table]["va"] + offset:
            raise ValueError("slot address disagrees with its retail vtable")
        for image, tables, expected in ((rebuilt, known_tables, link["symbols"][method]),
                                        (original, retail_tables, bindings[method]["va"])):
            base = tables[table]
            if any(base < other <= base + offset for other in tables.values()):
                raise ValueError("slot crosses the start of another known vtable")
            # Read from the start so the slot cannot extend outside this read-only section.
            entries = readonly_pe_data(image, base, offset + 4)
            actual, = struct.unpack_from("<I", entries, offset)
            if actual != expected or _file_offset(image, actual, 1)[1] & 0x20000020 != 0x20000020:
                raise ValueError(f"vtable slot {index} does not contain {method}")
        resolved[alias] = resolved[table] + offset
    return dict(link, symbols={**link["symbols"], **resolved})
