"""Verify separately bound named TCHAR arrays that MSVC places in shared .rdata."""
import copy
import struct
import unittest

from progress import built_unit_bytes
from test_link_image import BASE, image


def fixture():
    first, second = "?LongName@@3QBGB", "?ShortName@@3QBGB"
    names = (first + "\0" + second + "\0").encode()
    content = "One\0B\0".encode("utf-16le")
    code = b"\x68" + bytes(4) + b"\x68" + bytes(4) + b"\xc3"
    relocations = struct.pack("<IIHIIH", 1, 1, 6, 6, 2, 6)
    data = 100 + len(code) + len(relocations)
    table = data + len(content)
    obj = struct.pack("<HHIIIHH", 0x14c, 2, 0, table, 3, 0, 0)
    obj += struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), 100, 111, 0, 2, 0, 0x60000020)
    obj += struct.pack("<8sIIIIIIHHI", b".rdata", 0, 0, len(content), data, 0, 0, 0, 0, 0x40300040)
    obj += code + relocations + content
    obj += struct.pack("<8sIhHBB", b"_draw", 0, 1, 32, 2, 0)
    for string_offset, value in ((4, 0), (5 + len(first), 8)):
        obj += struct.pack("<IIIhHBB", 0, string_offset, value, 2, 0, 2, 0)
    obj += struct.pack("<I", 4 + len(names)) + names
    va = BASE + 0x2000
    linked = b"\x68" + struct.pack("<I", va) + b"\x68" + struct.pack("<I", va + 8) + b"\xc3"
    pe = image(linked, content)
    unit = dict(offset=0x200, size=len(code), rebuilt_symbol="_draw",
                link_bindings={first: dict(va=va, basis="long tag"), second: dict(va=va + 8, basis="short tag")},
                coff_readonly_strings={first: {"utf16": 8}, second: {"utf16": 4}})
    target = dict(image=dict(size=len(pe), executable_sections=[
        dict(address=BASE + 0x1000, offset=0x200, size=len(code), code=True)]))
    return obj, pe, target, unit, linked, data, table


class ReadonlyStringTests(unittest.TestCase):
    def setUp(self):
        self.obj, self.pe, self.target, self.unit, self.code, self.data, self.table = fixture()

    def check(self, obj=None, pe=None, unit=None):
        return built_unit_bytes(self.target, self.unit if unit is None else unit,
                                self.obj if obj is None else obj, self.pe if pe is None else pe)

    def test_two_named_objects_in_one_section(self):
        self.assertEqual(self.check(), self.code)

    def test_rejects_content_mutations_for_each_object_in_both_images(self):
        for offset in (0, 6, 8, 10):
            for key, original, base in (("obj", self.obj, self.data), ("pe", self.pe, 0x400)):
                changed = bytearray(original)
                changed[base + offset] ^= 1
                with self.subTest(offset=offset, side=key), self.assertRaises(ValueError):
                    self.check(**{key: bytes(changed)})

    def test_rejects_shifted_boundaries_or_wrong_linkage_permissions_and_encoding(self):
        for offset, fmt, value in ((self.table + 18 + 8, "<I", 4), (self.table + 36 + 8, "<I", 0),
                                   (self.table + 18 + 16, "B", 3), (96, "<I", 0xc0300040),
                                   (101, "<I", 2), (119, "<H", 0x14)):
            changed = bytearray(self.obj)
            struct.pack_into(fmt, changed, offset, value)
            with self.subTest(coff_offset=offset), self.assertRaises(ValueError):
                self.check(obj=bytes(changed))
        for size in ({"ascii": 8}, {"utf16": 6}, {"utf16": 10}):
            unit = copy.deepcopy(self.unit)
            unit["coff_readonly_strings"]["?LongName@@3QBGB"] = size
            with self.subTest(size=size), self.assertRaises(ValueError):
                self.check(unit=unit)
        first = "?LongName@@3QBGB"
        for va in (BASE + 0x2001, BASE + 0x2002, BASE + 0x2008):
            unit = copy.deepcopy(self.unit)
            unit["link_bindings"][first]["va"] = va
            with self.subTest(va=va), self.assertRaises(ValueError):
                self.check(unit=unit)

    def test_requires_defined_decorated_const_array_and_file_backed_readonly_retail(self):
        unit = copy.deepcopy(self.unit)
        unit["coff_readonly_strings"]["?LongName@@3PAGB"] = unit["coff_readonly_strings"].pop("?LongName@@3QBGB")
        with self.assertRaises(ValueError):
            self.check(unit=unit)
        writable = image(self.code, "One\0B\0".encode("utf-16le"), data_flags=0xc0000040)
        with self.assertRaises(ValueError):
            self.check(pe=writable)
