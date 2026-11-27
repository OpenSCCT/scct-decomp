"""Verify UTF-16 string objects in initialized writable retail data for an LTCG receipt."""

from images import initialized_pe_data
from link_image import _file_offset


def check_writable_strings(rebuilt, retail, link, bindings):
    """Each named object has an absolute reference and a byte length including its terminator."""
    strings = link["writable_strings"]
    if not isinstance(strings, dict) or not strings:
        raise ValueError("writable_strings must map string symbols to their UTF-16 byte lengths")
    if strings.keys() & (link.get("constants", {}).keys() | link.get("tables", {}).keys()):
        raise ValueError("a writable string cannot also be a read-only constant or a jump table")

    referenced = set()
    for _, kind, name in link["fields"]:
        if name in strings:
            if kind != "abs":
                raise ValueError(f"writable string {name} needs an absolute reference")
            referenced.add(name)
    if referenced != strings.keys():
        raise ValueError("writable_strings names a symbol to which no field refers")

    linked_ranges, retail_ranges = [], []
    for name, length in strings.items():
        if type(length) is not int or length < 2 or length % 2:
            raise ValueError(f"invalid UTF-16 byte length for {name}")
        if name not in link["symbols"] or name not in bindings:
            raise ValueError(f"writable string {name} has no address")
        linked = link["symbols"][name]
        original = bindings[name]["va"]
        if type(linked) is not int or type(original) is not int or (linked | original) & 1:
            raise ValueError(f"unaligned UTF-16 string address for {name}")

        # The source can declare its initialized array const even when the game put it in .data.
        _, flags = _file_offset(rebuilt, linked, length)
        data = initialized_pe_data(rebuilt, linked, length, writable=bool(flags & 0x80000000))
        if data != initialized_pe_data(retail, original, length, writable=True):
            raise ValueError(f"writable string {name} differs from retail")
        text = data.decode("utf-16le")
        if not text.endswith("\0") or "\0" in text[:-1]:
            raise ValueError(f"expected one complete terminated UTF-16 string for {name}")
        linked_ranges.append((linked, linked + length))
        retail_ranges.append((original, original + length))

    # Identical spellings can be distinct objects. Do not accept a pooled or overlapping array
    # as the backing storage for two independently named strings.
    for ranges in (linked_ranges, retail_ranges):
        ranges.sort()
        if any(left[1] > right[0] for left, right in zip(ranges, ranges[1:])):
            raise ValueError("overlapping writable string objects")
