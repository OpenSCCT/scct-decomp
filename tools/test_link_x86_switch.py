"""Exercise compiler-owned switch destination relocations using a synthetic i386 COFF."""
import struct
import unittest

from link_x86 import link_function


def switch_object(*, value=12, section=1, kind=0, storage=3, label=b"$L200",
                  relocation=6, addend=0, second_position=4):
    header = struct.pack("<HHIIIHH", 0x14c, 2, 0, 136, 3, 0, 0)
    text = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 16, 100, 116, 0, 2, 0, 0x60000020)
    other = struct.pack("<8sIIIIIIHHI", b".other", 0, 0, 0, 0, 0, 0, 0, 0, 0x40000040)
    code = struct.pack("<IIII", 8, addend, 0, 0)
    relocs = struct.pack("<IIHIIH", 0, 1, 6, second_position, 2, relocation)
    symbols = b"".join(struct.pack("<8sIhHBB", *fields, 0) for fields in [
        (b"_unit", 0, 1, 0x20, 2), (b"_data", 0, 0, 0, 2),
        (label, value, section, kind, storage),
    ])
    return header + text + other + code + relocs + symbols + struct.pack("<I", 4)


class SwitchLabelTests(unittest.TestCase):
    bindings = {"_data": {"va": 0x500000, "basis": "fixture external data"}}

    def test_local_destination_follows_compiled_section(self):
        obj = switch_object()
        for address in [0x41000, 0x50000]:
            with self.subTest(address=address):
                linked = link_function(obj, "_unit", 16, address, self.bindings)
                self.assertEqual(struct.unpack("<IIII", linked), (0x500008, address + 12, 0, 0))

    def test_rejects_invalid_local_destinations(self):
        for changes in [
            {"value": 16}, {"value": 17}, {"section": 2}, {"section": 0},
            {"kind": 0x20}, {"storage": 6}, {"label": b"$L"}, {"label": b"$L20x"},
            {"relocation": 0x14}, {"addend": 1}, {"second_position": 2},
        ]:
            with self.subTest(changes=changes), self.assertRaises(ValueError):
                link_function(switch_object(**changes), "_unit", 16, 0x41000, self.bindings)

    def test_extra_binding_cannot_supply_local_label(self):
        bindings = dict(self.bindings, **{"$L200": {"va": 0x500000, "basis": "unrelated external"}})
        with self.assertRaisesRegex(ValueError, "unused"):
            link_function(switch_object(), "_unit", 16, 0x41000, bindings)


def table_object(*, jump=b"\xff\x24\x85", arm_storage=6, addend=0, extra_label=False):
    """A 20-byte function: an indirect jump through a table at offset 7, then two arms and a return.

    The table holds two absolute entries, to class 6 arm labels at offsets 16 and 19, after a
    class 3 base label at offset 7. extra_label adds a class 6 label at offset 16 that
    no table names.
    """
    code = jump + b"\0\0\0\0" + struct.pack("<I", addend) + b"\0\0\0\0" + b"\x90\x90\x90\x90\xc3"
    symbols = [(b"_unit", 0, 1, 0x20, 2), (b"$L300", 7, 1, 0, 3),
               (b"$L301", 16, 1, 0, arm_storage), (b"$L302", 19, 1, 0, arm_storage)]
    relocs = [(3, 1), (7, 2), (11, 3)]
    if extra_label:
        symbols.append((b"$L303", 19, 1, 0, 6))
        relocs.append((16, 4))
    relocations = b"".join(struct.pack("<IIH", position, index, 6) for position, index in relocs)
    table = 20 + 40 + len(code) + len(relocations)
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, table, len(symbols), 0, 0)
    text = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), 60, 60 + len(code), 0,
                       len(relocs), 0, 0x60000020)
    symbol_bytes = b"".join(struct.pack("<8sIhHBB", name.ljust(8, b"\0"), value, section, kind,
                                        storage, 0)
                            for name, value, section, kind, storage in symbols)
    return header + text + code + relocations + symbol_bytes + struct.pack("<I", 4)


class SwitchTableTests(unittest.TestCase):
    def test_class6_arms_of_a_switch_table_link_to_their_offsets(self):
        linked = link_function(table_object(), "_unit", 20, 0x41000, {})
        self.assertEqual(linked, b"\xff\x24\x85" + struct.pack("<III", 0x41007, 0x41010, 0x41013)
                         + b"\x90\x90\x90\x90\xc3")

    def test_class6_label_without_an_indirect_jump_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "relative call or jump"):
            link_function(table_object(jump=b"\x90\x90\x90"), "_unit", 20, 0x41000, {})

    def test_class6_label_that_no_table_names_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "relative call or jump"):
            link_function(table_object(extra_label=True), "_unit", 20, 0x41000, {})

    def test_class6_arm_must_not_carry_an_addend(self):
        with self.assertRaisesRegex(ValueError, "nonzero addend"):
            link_function(table_object(addend=1), "_unit", 20, 0x41000, {})
