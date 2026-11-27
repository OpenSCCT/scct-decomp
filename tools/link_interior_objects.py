"""Resolve absolute references to elements of writable objects in an LTCG image."""

from link_image import _sections


def _check_object(image, address, length):
    base, sections = _sections(image)
    if type(address) is not int or not 0 <= address < address + length <= 2**32:
        raise ValueError("invalid writable object address or extent")
    for rva, virtual_size, _, _, flags in sections:
        # Runtime-initialized arrays may occupy the zero-filled tail of .data.
        if (flags & 0xe0000020 == 0xc0000000 and flags & 0xc0
                and base + rva <= address and address + length <= base + rva + virtual_size):
            return
    raise ValueError("the whole object must fit in writable, non-executable PE data")


def resolve_interior_objects(rebuilt, original, link, bindings):
    """Give each checked element address a distinct key for normal field placement."""
    objects = link["interior_objects"]
    if not isinstance(objects, dict) or not objects:
        raise ValueError("interior_objects needs named writable objects and their byte sizes")
    symbols = link["symbols"].copy()
    placed = bindings.copy()
    for name, length in objects.items():
        if type(length) is not int or length <= 0 or name not in symbols or name not in bindings:
            raise ValueError("interior object needs a positive extent and both base addresses")
        if (name in link.get("stubs", ()) or any(name in link.get(key, {}) for key in
                ("constants", "tables", "case_selectors", "writable_strings"))):
            raise ValueError("interior object must have its own writable storage")
        _check_object(rebuilt, symbols[name], length)
        _check_object(original, bindings[name]["va"], length)

    fields = []
    referenced = set()
    for field in link["fields"]:
        if len(field) == 3:
            fields.append(field)
            continue
        if len(field) != 4:
            raise ValueError("expected an address field with an optional object offset")
        site, kind, name, addend = field
        if kind != "abs" or name not in objects or type(addend) is not int or not 0 < addend < objects[name]:
            raise ValueError("an interior field needs an absolute reference strictly inside its object")
        key = (name, addend)
        symbols[key] = symbols[name] + addend
        placed[key] = {"va": bindings[name]["va"] + addend}
        fields.append((site, kind, key))
        referenced.add(name)
    if referenced != objects.keys():
        raise ValueError("interior object has no interior reference")
    return dict(link, symbols=symbols, fields=fields), placed
