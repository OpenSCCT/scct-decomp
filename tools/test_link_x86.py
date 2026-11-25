"""Exercise the two supported i386 relocations on a project-authored COFF fixture."""

import struct
import unittest

from link_x86 import link_function


def object_file(second_relocation=0x14, second_position=4):
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, 88, 3, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 8, 60, 68, 0, 2, 0, 0x60000020)
    data = struct.pack("<II", 8, 4)
    relocations = struct.pack("<IIHIIH", 0, 1, 6, second_position, 2, second_relocation)
    symbols = b"".join(struct.pack("<8sIhHBB", name, 0, sec, kind, 2, 0)
                       for name, sec, kind in [(b"_unit", 1, 0x20), (b"_data", 0, 0), (b"_callee", 0, 0x20)])
    return header + section + data + relocations + symbols + struct.pack("<I", 4)


class LinkTests(unittest.TestCase):
    def setUp(self):
        self.bindings = {"_data": {"va": 0x400000, "basis": "fixture data"},
                         "_callee": {"va": 0x40f00, "basis": "fixture function"}}

    def test_internal_addends_and_backward_relative_call(self):
        linked = link_function(object_file(), "_unit", 8, 0x41000, self.bindings)
        self.assertEqual(struct.unpack("<Ii", linked), (0x400008, -0x104))

    def test_pooled_constant_requires_exact_readonly_contents(self):
        text = object_file()
        header = struct.pack("<HHIIIHH", 0x14c, 2, 0, 130, 3, 0, 0)
        code = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 8, 100, 108, 0, 2, 0, 0x60000020)
        const = struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, 2, 128, 0, 0, 0, 0, 0x40001040)
        obj = bytearray(header + code + const + text[60:88] + b"x\0" + text[88:])
        struct.pack_into("<h", obj, 130 + 18 + 12, 2)
        def read(va, size):
            self.assertEqual((va, size), (0x400000, 2))
            return b"x\0"
        linked = link_function(obj, "_unit", 8, 0x41000, self.bindings, read_constant=read)
        self.assertEqual(struct.unpack("<Ii", linked), (0x400008, -0x104))
        obj[128] = ord("y")
        with self.assertRaisesRegex(ValueError, "differs from retail"):
            link_function(obj, "_unit", 8, 0x41000, self.bindings, read_constant=read)
        struct.pack_into("<I", obj, 96, 0xc0000040)
        with self.assertRaisesRegex(ValueError, "read-only"):
            link_function(obj, "_unit", 8, 0x41000, self.bindings, read_constant=read)

    def test_rejects_incomplete_and_unexplained_links(self):
        for obj, bindings in [
            (object_file(second_relocation=3), self.bindings),
            (object_file(second_position=2), self.bindings),
            (object_file(), {k: v for k, v in self.bindings.items() if k != "_data"}),
            (object_file(), dict(self.bindings, unused={"va": 1, "basis": "unused"})),
        ]:
            with self.subTest(bindings=bindings), self.assertRaises(ValueError):
                link_function(obj, "_unit", 8, 0x41000, bindings)
        with self.assertRaises(ValueError):
            link_function(object_file(), "_unit", 7, 0x41000, self.bindings)

    def test_vc6_writable_string_comdat(self):
        # One absolute reference to the start of a two-byte narrow literal.
        literal = b"??_C@_01A@x?$AA@"
        header = struct.pack("<HHIIIHH", 0x14c, 2, 0, 116, 2, 0, 0)
        code = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 4, 100, 104, 0, 1, 0, 0x60000020)
        data = struct.pack("<8sIIIIIIHHI", b".data", 0, 0, 2, 114, 0, 0, 0, 0, 0xc0301040)
        symbols = struct.pack("<8sIhHBB", b"_unit", 0, 1, 0x20, 2, 0)
        symbols += struct.pack("<IIIhHBB", 0, 4, 0, 2, 0, 2, 0)
        names = struct.pack("<I", 5 + len(literal)) + literal + b"\0"
        obj = bytearray(header + code + data + bytes(4) + struct.pack("<IIH", 0, 1, 6)
                        + b"x\0" + symbols + names)
        bindings = {literal.decode(): {"va": 0x450000, "basis": "fixture string"}}

        def read(va, size):
            self.assertEqual((va, size), (0x450000, 2))
            return b"x\0"

        def rebuild(obj):
            return link_function(obj, "_unit", 4, 0x41000, bindings, read_writable_string=read)

        self.assertEqual(rebuild(obj), struct.pack("<I", 0x450000))
        for pos, value in ((114, ord("y")), (115, ord("z")), (100, 1), (97, 0)):
            with self.subTest(pos=pos), self.assertRaises(ValueError):
                changed = obj.copy()
                changed[pos] = value
                rebuild(changed)
