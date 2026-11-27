"""Authenticate a VC6 primary single-slot vftable and its RTTI before resolving its COFF address."""

import re
import struct

from images import initialized_pe_data, pe_file_sections, readonly_pe_data
from link_x86 import link_function, region, symbol_index


def _address(value):
    return type(value) is int and 0 < value <= 0xffffffff


def check_rtti_spec(unit):
    spec = unit.get("coff_rtti_vtable")
    if (not isinstance(spec, dict) or set(spec) != {"symbol", "locator_va", "type_info_vtable_va", "deleting_destructor"}
            or any(key in unit for key in ("ltcg_link", "coff_switch_tail", "rebuilt_storage_class", "rebuilt_offset"))
            or not isinstance(unit.get("link_bindings"), dict)):
        raise ValueError("expected an ordinary COFF unit with one primary RTTI vftable")
    name = spec["symbol"]
    match = re.fullmatch(r"\?\?_7([A-Za-z_]\w*)@@6B@", name, re.ASCII) if isinstance(name, str) else None
    slot = spec["deleting_destructor"]
    if (not match or not isinstance(unit["link_bindings"].get(name), dict)
            or not _address(unit["link_bindings"][name].get("va"))
            or not isinstance(unit.get("rebuilt_symbol"), str)
            or not _address(spec["locator_va"]) or not _address(spec["type_info_vtable_va"])
            or not isinstance(slot, dict) or set(slot) != {"va", "size", "link_bindings"}
            or not _address(slot["va"]) or type(slot["size"]) is not int or slot["size"] <= 0
            or not isinstance(slot["link_bindings"], dict)):
        raise ValueError("invalid RTTI vftable, locator or deleting destructor")
    return match.group(1).encode("ascii")


def _executable(image, va, size):
    for _, offset, length, address, flags in pe_file_sections(image):
        if flags & 0xe0000020 == 0x60000020 and address <= va and va + size <= address + length:
            return region(image, offset + va - address, size)
    raise ValueError("the RTTI method must occupy file-backed executable code")


class _Rtti:
    def __init__(self, obj, image, spec, owner, readers):
        self.obj = obj
        self.image = image
        self.spec = spec
        self.owner = owner
        self.readers = readers
        self.count, self.symbols, self.functions, _, _ = symbol_index(bytes(obj))
        self.symbol_table = struct.unpack_from("<I", obj, 8)[0]
        self.locations = {}
        self.sections = {}

    def definition(self, index, va, *, offset=0, writable=False):
        """Check the object and its retail counterpart, leaving only pointer fields to traverse."""
        name, value, sec, kind, storage = self.symbols[index]
        if (value != offset or not 1 <= sec <= self.count or kind or storage != 2
                or not _address(va) or va % 4):
            raise ValueError("invalid or misaligned external RTTI definition")
        if self.locations.setdefault(sec, va) != va or self.sections.setdefault(va, sec) != sec:
            raise ValueError("inconsistent mapping between RTTI definitions and retail addresses")
        header = 20 + 40 * (sec - 1)
        size, raw, relocs = struct.unpack_from("<III", self.obj, header + 16)
        count, _, flags = struct.unpack_from("<HHI", self.obj, header + 32)
        required = 0xc0001040 if writable else 0x40001040
        if not size or flags & 0xe10010e0 != required:
            raise ValueError("expected an initialized RTTI data COMDAT with matching protection")
        data = region(self.obj, raw, size)
        actual = bytearray(initialized_pe_data(self.image, va, size, writable=writable))
        refs = {}
        for pos, sym, mode in struct.iter_unpack("<IIH", region(self.obj, relocs, count * 10)):
            if (mode != 6 or pos % 4 or pos + 4 > size or pos in refs or sym not in self.symbols
                    or data[pos:pos + 4] != bytes(4)):
                raise ValueError("invalid RTTI pointer relocation or nonzero addend")
            target, = struct.unpack_from("<I", actual, pos)
            if not _address(target):
                raise ValueError("missing retail RTTI pointer")
            refs[pos] = sym, target
            actual[pos:pos + 4] = bytes(4)
        if data != actual:
            raise ValueError("RTTI record contents differ from retail")
        return name, data, refs

    def type_descriptor(self, index, va):
        name, data, refs = self.definition(index, va, writable=True)
        if (set(refs) != {0} or not name.startswith(b"??_R0?AV") or not name.endswith(b"@@@8")
                or data != bytes(8) + b"." + name[5:-2] + b"\0"):
            raise ValueError("invalid MSVC class type descriptor")
        sym, ptr = refs[0]
        if (self.symbols[sym] != (b"??_7type_info@@6B@", 0, 0, 0, 2)
                or ptr != self.spec["type_info_vtable_va"]):
            raise ValueError("invalid type_info vftable reference")
        # type_info itself has a primary vftable and a named descriptor referring back to it.
        locator, first = struct.unpack("<II", readonly_pe_data(self.image, ptr - 4, 8))
        sig, off, cd_offset, info_type, _ = struct.unpack("<5I", readonly_pe_data(self.image, locator, 20))
        expected = struct.pack("<II", ptr, 0) + b".?AVtype_info@@\0"
        if (sig or off or cd_offset
                or initialized_pe_data(self.image, info_type, len(expected), writable=True) != expected):
            raise ValueError("type_info vftable lacks its own identifying primary descriptor")
        _executable(self.image, first, 1)
        return name

    def hierarchy(self, index, va):
        name, data, refs = self.definition(index, va)
        if name != b"??_R3" + self.owner + b"@@8" or len(data) != 16 or set(refs) != {12}:
            raise ValueError("invalid RTTI class hierarchy")
        count, = struct.unpack_from("<I", data, 8)
        array_name, array, bases = self.definition(*refs[12])
        if (not 0 < count <= 256 or array_name != b"??_R2" + self.owner + b"@@8"
                or len(array) != 4 * count + 1 or array[-1] != 0 or set(bases) != set(range(0, count * 4, 4))):
            raise ValueError("invalid RTTI base-class array")
        for ordinal in range(count):
            bname, bdata, fields = self.definition(*bases[ordinal * 4])
            if not bname.startswith(b"??_R1") or len(bdata) != 24 or set(fields) != {0}:
                raise ValueError("invalid RTTI base-class descriptor")
            tname = self.type_descriptor(*fields[0])
            if not bname.endswith(tname[8:-2] + b"8") or (ordinal == 0 and tname != b"??_R0?AV" + self.owner + b"@@@8"):
                raise ValueError("base-class descriptor names a different class")

    def deleting_destructor(self, index, va):
        symbol, value, sec, kind, storage = self.symbols[index]
        scalar = b"??_G" + self.owner + b"@@UAEPAXI@Z"
        if storage == 105:
            entry = self.symbol_table + index * 18
            fallback, search = struct.unpack_from("<II", self.obj, entry + 18)
            if (symbol != b"??_E" + self.owner + b"@@UAEPAXI@Z" or value or sec or kind != 0x20
                    or self.obj[entry + 17] != 1 or search != 2 or fallback not in self.symbols):
                raise ValueError("unexpected weak deleting-destructor relocation")
            symbol, value, sec, kind, storage = self.symbols[fallback]
        methods = self.functions.get(scalar, [])
        slot = self.spec["deleting_destructor"]
        if (symbol != scalar or value or kind != 0x20 or storage != 2 or len(methods) != 1
                or sec not in (0, methods[0]) or va != slot["va"]):
            raise ValueError("vftable slot is not the expected defined scalar deleting destructor")
        length, = struct.unpack_from("<I", self.obj, 20 + 40 * (methods[0] - 1) + 16)
        size = slot["size"]
        if length not in (size, (size + 15) & ~15):
            raise ValueError("deleting-destructor extent differs from its COFF contribution")
        code = link_function(self.obj, scalar.decode(), length, va, slot["link_bindings"], **self.readers)
        if code != _executable(self.image, va, length) or code[size:] != b"\x90" * (length - size):
            raise ValueError("compiled scalar deleting destructor differs from its retail slot")

    def table(self, index, va):
        name, data, refs = self.definition(index, va - 4, offset=4)
        if name != self.spec["symbol"].encode() or len(data) != 8 or set(refs) != {0, 4}:
            raise ValueError("expected a locator followed by a single virtual function")
        if refs[0][1] != self.spec["locator_va"]:
            raise ValueError("vftable locator differs from its declared retail address")
        lname, col, fields = self.definition(*refs[0])
        if (lname != b"??_R4" + self.owner + b"@@6B@" or col != bytes(20)
                or set(fields) != {12, 16}):
            raise ValueError("invalid complete-object locator for primary vftable")
        tname = self.type_descriptor(*fields[12])
        if tname != b"??_R0?AV" + self.owner + b"@@@8":
            raise ValueError("complete-object locator names the wrong class")
        self.hierarchy(*fields[16])
        self.deleting_destructor(*refs[4])


def link_rtti_function(obj, unit, length, address, image, **readers):
    owner = check_rtti_spec(unit)
    spec = unit["coff_rtti_vtable"]
    check = _Rtti(obj, image, spec, owner, readers)
    name = spec["symbol"]
    binding = unit["link_bindings"][name]
    candidates = [n for n, s in check.symbols.items() if s[0] == name.encode()]
    if len(candidates) != 1:
        raise ValueError("expected one defined RTTI vftable symbol")
    index = candidates[0]
    check.table(index, binding["va"])
    sections = check.functions.get(unit["rebuilt_symbol"].encode(), [])
    if len(sections) != 1:
        raise ValueError("missing or ambiguous function containing the vftable reference")
    header = 20 + 40 * (sections[0] - 1)
    _, start, relocs = struct.unpack_from("<III", obj, header + 16)
    count, = struct.unpack_from("<H", obj, header + 32)
    uses = [(pos, mode) for pos, sym, mode in struct.iter_unpack("<IIH", region(obj, relocs, count * 10)) if sym == index]
    if not uses or any(mode != 6 or pos + 4 > length or region(obj, start + pos, 4) != bytes(4) for pos, mode in uses):
        raise ValueError("expected an absolute reference to the authenticated vftable with no addend")
    # The ordinary COFF linker already resolves imported data symbols at their bound addresses.
    # Expose the independently validated definition through that interface. Only its symbol-table
    # value and section number change in this view; every contribution and relocation is original.
    view = bytearray(obj)
    struct.pack_into("<Ih", view, check.symbol_table + 18 * index + 8, 0, 0)
    return link_function(view, unit["rebuilt_symbol"], length, address, unit["link_bindings"], **readers)
