"""C++ exception frames read FS:[__except_list], which the C runtime defines as absolute 0."""

import struct
import unittest

from link_x86 import link_function


def object_file(external):
    names = b"__except_list\0"
    strings = struct.pack("<I", 4 + len(names)) + names
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, 74, 2, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 4, 60, 64, 0, 1, 0, 0x60000020)
    data = struct.pack("<I", 0)
    relocation = struct.pack("<IIH", 0, 1, 6)
    unit = struct.pack("<8sIhHBB", b"_unit", 0, 1, 0x20, 2, 0)
    label = struct.pack("<II", 0, 4) if external == "__except_list" else external.encode().ljust(8, b"\0")
    target = struct.pack("<8sIhHBB", label, 0, 0, 0, 2, 0)
    return header + section + data + relocation + unit + target + strings


class ExceptListTests(unittest.TestCase):
    def test_except_list_links_at_absolute_zero(self):
        bindings = {"__except_list": {"va": 0, "basis": "C runtime absolute TIB offset"}}
        self.assertEqual(link_function(object_file("__except_list"), "_unit", 4, 0x41000, bindings), bytes(4))

    def test_other_externals_still_reject_zero(self):
        with self.assertRaisesRegex(ValueError, "invalid address"):
            link_function(object_file("_data"), "_unit", 4, 0x41000, {"_data": {"va": 0, "basis": "fixture"}})


def section_with_label(label, value, storage):
    """One 8-byte section holding _unit, a second function-typed symbol and one data reference."""
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, 60 + 8 + 10, 3, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 8, 60, 68, 0, 1, 0, 0x60000020)
    relocation = struct.pack("<IIH", 0, 2, 6)
    unit = struct.pack("<8sIhHBB", b"_unit", 0, 1, 0x20, 2, 0)
    other = struct.pack("<8sIhHBB", label.ljust(8, b"\0"), value, 1, 0x20, storage, 0)
    data = struct.pack("<8sIhHBB", b"_data", 0, 0, 0, 2, 0)
    return header + section + bytes(4) + b"\xcc" * 4 + relocation + unit + other + data + struct.pack("<I", 4)


DATA = {"_data": {"va": 0x42000, "basis": "fixture"}}


class CatchBlockTests(unittest.TestCase):
    def test_catch_block_label_stays_with_its_function(self):
        linked = link_function(section_with_label(b"$L865", 6, 3), "_unit", 8, 0x41000, DATA)
        self.assertEqual(linked, struct.pack("<I", 0x42000) + b"\xcc" * 4)

    def test_second_function_in_section_is_still_rejected(self):
        for label, value, storage in ((b"_other", 6, 2), (b"$L865", 0, 3), (b"$Lx", 6, 3)):
            with self.assertRaisesRegex(ValueError, "multiple functions|expected one"):
                link_function(section_with_label(label, value, storage), "_unit", 8, 0x41000, DATA)


if __name__ == "__main__":
    unittest.main()
