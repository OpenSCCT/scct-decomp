"""Resolve a function's references to its own static local and guard word from their bindings."""

import struct
import unittest

from link_x86 import link_function

SLOT = b"?Obj@?1??f@@YAHXZ@4HA"
GUARD = b"?$S1@?1??f@@YAHXZ@4HA"
SLOT_VA = 0x10D51380
GUARD_VA = 0x10D51384


def static_object(*, relocation=6, addend=0, value=0, storage=3, data_flags=0xC0301080,
                  slot_section=2, guard_section=3):
    """A COFF object whose function _unit loads the static slot and stores the guard word.

    Both are private data symbols, each the first symbol of a writable .bss contribution, as
    the 13.00.9466 compiler lays out a function-local static and its guard."""
    code = b"\xa1" + struct.pack("<I", addend) + b"\xa3" + bytes(4) + b"\xc3"
    strings = bytearray(4)
    names = []
    for name in (SLOT, GUARD):
        names.append(struct.pack("<II", 0, len(strings)))
        strings += name + b"\0"
    struct.pack_into("<I", strings, 0, len(strings))
    symbols = [(b"_unit".ljust(8, b"\0"), 0, 1, 0x20, 2), (names[0], value, slot_section, 0, storage),
               (names[1], 0, guard_section, 0, storage)]
    code_at, reloc_at = 20 + 3 * 40, 20 + 3 * 40 + len(code)
    table = reloc_at + 20
    header = struct.pack("<HHIIIHH", 0x14C, 3, 0, table, len(symbols), 0, 0)
    text = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), code_at, reloc_at, 0, 2, 0, 0x60000020)
    bss = b"".join(struct.pack("<8sIIIIIIHHI", b".bss", 0, 0, 4, 0, 0, 0, 0, 0, data_flags) for _ in range(2))
    relocations = struct.pack("<IIH", 1, 1, relocation) + struct.pack("<IIH", 6, 2, relocation)
    symbol_bytes = b"".join(struct.pack("<8sIhHBB", name, v, sec, kind, store, 0)
                            for name, v, sec, kind, store in symbols)
    return header + text + bss + code + relocations + symbol_bytes + bytes(strings)


def bindings(*, slot=SLOT_VA, guard=GUARD_VA):
    return {SLOT.decode(): {"va": slot, "basis": "retail operand of the function"},
            GUARD.decode(): {"va": guard, "basis": "retail operand of the function"}}


class StaticDataTests(unittest.TestCase):
    def test_static_slot_and_guard_resolve_from_their_bindings(self):
        linked = link_function(static_object(), "_unit", 11, 0x10904000, bindings())
        self.assertEqual(linked, b"\xa1" + struct.pack("<I", SLOT_VA) + b"\xa3"
                         + struct.pack("<I", GUARD_VA) + b"\xc3")

    def test_addend_into_a_static_is_added_to_its_binding(self):
        linked = link_function(static_object(addend=8), "_unit", 11, 0x10904000, bindings())
        self.assertEqual(linked[1:5], struct.pack("<I", SLOT_VA + 8))

    def test_static_data_needs_a_binding(self):
        only_slot = {SLOT.decode(): bindings()[SLOT.decode()]}
        with self.assertRaisesRegex(ValueError, "missing link address for"):
            link_function(static_object(), "_unit", 11, 0x10904000, only_slot)

    def test_static_data_must_be_writable(self):
        with self.assertRaisesRegex(ValueError, "relative call or jump"):
            link_function(static_object(data_flags=0x40000040), "_unit", 11, 0x10904000, bindings())

    def test_static_data_must_start_its_contribution(self):
        with self.assertRaisesRegex(ValueError, "start its own contribution"):
            link_function(static_object(value=4), "_unit", 11, 0x10904000, bindings())

    def test_static_data_is_not_reached_by_a_relative_reference(self):
        with self.assertRaisesRegex(ValueError, "relative call or jump"):
            link_function(static_object(relocation=0x14), "_unit", 11, 0x10904000, bindings())

    def test_unused_static_binding_is_refused(self):
        extra = dict(bindings(), **{"_unused": {"va": 0x10D00000, "basis": "fixture"}})
        with self.assertRaisesRegex(ValueError, "unused symbol"):
            link_function(static_object(), "_unit", 11, 0x10904000, extra)


VTABLE = b"??_7UnkType_1@@6B@"
VTABLE_VA = 0x110BC1B8


def vtable_object(*, value=0, flags=0x40301040, storage=3, relocation=6):
    """A COFF object whose function _unit stores the address of a class vtable it defines itself.

    The vtable is a COMDAT in a read-only section, storage class 3 as a private contribution."""
    code = b"\xb8" + bytes(4) + b"\xc3"
    strings = bytearray(4)
    strings += VTABLE + b"\0"
    struct.pack_into("<I", strings, 0, len(strings))
    names = [b"_unit".ljust(8, b"\0"), struct.pack("<II", 0, 4)]
    symbols = [(names[0], 0, 1, 0x20, 2), (names[1], value, 2, 0, storage)]
    code_at = 20 + 2 * 40
    reloc_at = code_at + len(code)
    table = reloc_at + 10
    header = struct.pack("<HHIIIHH", 0x14C, 2, 0, table, len(symbols), 0, 0)
    text = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), code_at, reloc_at, 0, 1, 0, 0x60000020)
    rdata = struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, 4, 0, 0, 0, 0, 0, flags)
    relocations = struct.pack("<IIH", 1, 1, relocation)
    symbol_bytes = b"".join(struct.pack("<8sIhHBB", n, v, sec, kind, st, 0)
                            for n, v, sec, kind, st in symbols)
    return header + text + rdata + code + relocations + symbol_bytes + bytes(strings)


class ClassVtableTests(unittest.TestCase):
    def binding(self):
        return {VTABLE.decode(): {"va": VTABLE_VA, "basis": "the class's vtable at its retail VA"}}

    def test_defined_vtable_binds_to_the_retail_table(self):
        linked = link_function(vtable_object(), "_unit", 6, 0x10904000, self.binding())
        self.assertEqual(linked, b"\xb8" + struct.pack("<I", VTABLE_VA) + b"\xc3")

    def test_vtable_must_start_its_contribution(self):
        with self.assertRaisesRegex(ValueError, "start its own contribution"):
            link_function(vtable_object(value=4), "_unit", 6, 0x10904000, self.binding())

    def test_vtable_must_be_read_only(self):
        with self.assertRaisesRegex(ValueError, "read-only virtual function table"):
            link_function(vtable_object(flags=0xC0301080), "_unit", 6, 0x10904000, self.binding())

    def test_vtable_needs_a_binding(self):
        with self.assertRaisesRegex(ValueError, "missing link address for"):
            link_function(vtable_object(), "_unit", 6, 0x10904000, {})


if __name__ == "__main__":
    unittest.main()
