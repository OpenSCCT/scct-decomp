import struct
import unittest

from link_image import link_arguments, place_function, stub_object

BASE = 0x10000000


def image(code, data=b""):
    """A minimal x86 PE: headers, a code section at RVA 0x1000 and a data section at 0x2000."""
    pe = 0x40
    header = bytearray(0x200)
    header[:2] = b"MZ"
    struct.pack_into("<I", header, 0x3C, pe)
    header[pe:pe + 4] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", header, pe + 4, 0x14C, 2, 0, 0, 0, 0xE0, 0x2102)
    struct.pack_into("<I", header, pe + 24 + 28, BASE)
    table = pe + 24 + 0xE0
    struct.pack_into("<8sIIIIIIHHI", header, table, b".text", 0x200, 0x1000, 0x200, 0x200, 0, 0, 0, 0, 0x60000020)
    struct.pack_into("<8sIIIIIIHHI", header, table + 40, b".rdata", 0x200, 0x2000, 0x200, 0x400, 0, 0, 0, 0, 0x40000040)
    return bytes(header) + code.ljust(0x200, b"\xcc") + data.ljust(0x200, b"\0")


class LinkImageTests(unittest.TestCase):
    def setUp(self):
        # mov eax, [data]; push string; call callee; ret
        self.built = BASE + 0x1000
        code = (b"\xa1" + struct.pack("<I", BASE + 0x1100) + b"\x68" + struct.pack("<I", BASE + 0x2000)
                + b"\xe8" + struct.pack("<i", BASE + 0x1101 - (self.built + 15)) + b"\xc3")
        self.image = image(code, b"hi\0")
        self.link = {"roots": ["_driver"], "stubs": ["_data", "_callee"], "rebuilt_offset": 0x200,
                     "rebuilt_address": self.built, "constants": {"_hi": 3},
                     "fields": [[1, "abs", "_data"], [6, "abs", "_hi"], [11, "rel32", "_callee"]],
                     "symbols": {"_data": BASE + 0x1100, "_hi": BASE + 0x2000, "_callee": BASE + 0x1101}}
        self.bindings = {"_data": {"va": 0x10C00000, "basis": "fixture"}, "_hi": {"va": 0x10B00000, "basis": "fixture"},
                         "_callee": {"va": 0x10950000, "basis": "fixture"}}
        self.retail = {0x10B00000: b"hi\0"}

    def read(self, va, size):
        return self.retail.get(va, b"")[:size]

    def test_fields_are_rebound_to_retail(self):
        address = 0x10904000
        placed = place_function(self.image, 16, address, self.link, self.bindings, read_constant=self.read)
        expected = (b"\xa1" + struct.pack("<I", 0x10C00000) + b"\x68" + struct.pack("<I", 0x10B00000)
                    + b"\xe8" + struct.pack("<i", 0x10950000 - (address + 15)) + b"\xc3")
        self.assertEqual(placed, expected)

    def test_field_must_refer_to_its_symbol(self):
        link = dict(self.link, fields=[[1, "abs", "_hi"], [6, "abs", "_data"], [11, "rel32", "_callee"]])
        with self.assertRaises(ValueError):
            place_function(self.image, 16, 0x10904000, link, self.bindings, read_constant=self.read)

    def test_constant_must_equal_retail(self):
        self.retail = {0x10B00000: b"ho\0"}
        with self.assertRaises(ValueError):
            place_function(self.image, 16, 0x10904000, self.link, self.bindings, read_constant=self.read)

    def test_offset_and_address_must_agree(self):
        with self.assertRaises(ValueError):
            place_function(self.image, 16, 0x10904000, dict(self.link, rebuilt_offset=0x210), self.bindings,
                           read_constant=self.read)

    def test_overlapping_fields_are_refused(self):
        link = dict(self.link, fields=[[1, "abs", "_data"], [3, "abs", "_data"]])
        with self.assertRaises(ValueError):
            place_function(self.image, 16, 0x10904000, link, self.bindings, read_constant=self.read)

    def test_stub_object_has_one_code_section_per_name(self):
        obj = stub_object(["_a", "?LongDecoratedName@@3HA"])
        self.assertEqual(struct.unpack_from("<HH", obj, 0), (0x14C, 2))
        self.assertIn(b"?LongDecoratedName@@3HA\0", obj)
        with self.assertRaises(ValueError):
            stub_object(["_a", "_a"])

    def test_link_arguments_include_roots(self):
        self.assertIn("/INCLUDE:_driver", link_arguments(self.link))
        self.assertIn("/LTCG", link_arguments(self.link))


if __name__ == "__main__":
    unittest.main()
