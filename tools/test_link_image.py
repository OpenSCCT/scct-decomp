import struct
import unittest

from images import file_pe_data, inspect
from link_image import link_arguments, place_function, stub_object
from progress import built_unit_bytes

BASE = 0x10000000


def image(code, data=b"", data_flags=0x40000040):
    """A minimal x86 PE: headers, a code section at RVA 0x1000 and a data section at 0x2000."""
    pe = 0x40
    header = bytearray(0x200)
    header[:2] = b"MZ"
    struct.pack_into("<I", header, 0x3C, pe)
    header[pe:pe + 4] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", header, pe + 4, 0x14C, 2, 0, 0, 0, 0xE0, 0x2102)
    struct.pack_into("<H", header, pe + 24, 0x10B)
    struct.pack_into("<I", header, pe + 24 + 28, BASE)
    table = pe + 24 + 0xE0
    struct.pack_into("<8sIIIIIIHHI", header, table, b".text", 0x200, 0x1000, 0x200, 0x200, 0, 0, 0, 0, 0x60000020)
    struct.pack_into("<8sIIIIIIHHI", header, table + 40, b".data", 0x200, 0x2000, 0x200, 0x400, 0, 0, 0, 0, data_flags)
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


class WritableStringTests(unittest.TestCase):
    symbol = "?NameText_None@@3QBGB"
    value = "None\0".encode("utf-16le")
    linked = BASE + 0x2000
    original = BASE + 0x2004

    def setUp(self):
        self.link = {"rebuilt_offset": 0x200, "rebuilt_address": BASE + 0x1000,
                     "fields": [[1, "abs", self.symbol]], "symbols": {self.symbol: self.linked},
                     "writable_strings": {self.symbol: len(self.value)}}
        self.bindings = {self.symbol: {"va": self.original, "basis": "fixture name registration"}}

    @staticmethod
    def code(va):
        return b"\x68" + struct.pack("<I", va) + b"\xc3"

    def place(self, *, linked_text=None, retail_text=None, linked_va=None, retail_flags=0xc0000040):
        rebuilt = image(self.code(self.linked if linked_va is None else linked_va),
                        self.value if linked_text is None else linked_text)
        retail = image(self.code(self.original), b"\x00" * 4 + (self.value if retail_text is None else retail_text),
                       data_flags=retail_flags)
        unit = {"offset": 0x200, "size": 6, "ltcg_link": self.link, "link_bindings": self.bindings}
        return built_unit_bytes({"image": inspect(retail)}, unit, rebuilt, retail)

    def test_named_const_array_can_match_writable_retail_storage(self):
        self.assertEqual(self.place(), self.code(self.original))

    def test_changed_string_on_either_side_is_refused(self):
        for key in ("linked_text", "retail_text"):
            with self.subTest(key=key), self.assertRaisesRegex(ValueError, "differs from retail"):
                self.place(**{key: "Node\0".encode("utf-16le")})

    def test_shifted_linked_referent_is_refused(self):
        with self.assertRaisesRegex(ValueError, "does not refer"):
            self.place(linked_va=self.linked + 2)
        self.link["symbols"][self.symbol] += 2
        with self.assertRaisesRegex(ValueError, "differs from retail"):
            self.place(linked_va=self.linked + 2)

    def test_shifted_retail_referent_is_refused(self):
        self.bindings[self.symbol]["va"] += 2
        with self.assertRaisesRegex(ValueError, "differs from retail"):
            self.place()

    def test_checks_complete_terminated_string(self):
        for length in (len(self.value) - 2, len(self.value) + 2):
            self.link["writable_strings"][self.symbol] = length
            with self.subTest(length=length), self.assertRaisesRegex(ValueError, "complete terminated"):
                self.place()

    def test_each_string_requires_an_absolute_field(self):
        self.link["fields"] = []
        with self.assertRaisesRegex(ValueError, "no field refers"):
            self.place()
        self.link["fields"] = [[1, "rel32", self.symbol]]
        with self.assertRaisesRegex(ValueError, "absolute reference"):
            self.place()

    def test_retail_storage_must_be_writable_initialized_data(self):
        for flags in (0x40000040, 0xc0000080, 0xe0000040):
            with self.subTest(flags=flags), self.assertRaisesRegex(ValueError, "file-backed writable data section"):
                self.place(retail_flags=flags)

    def test_distinct_objects_with_equal_spelling_cannot_share_an_address(self):
        other = "?NameText_NoneAgain@@3QBGB"
        self.link["fields"].append([6, "abs", other])
        self.link["writable_strings"][other] = len(self.value)
        for pooled_linked, pooled_retail in ((False, False), (True, False), (False, True)):
            with self.subTest(pooled_linked=pooled_linked, pooled_retail=pooled_retail):
                linked = self.linked if pooled_linked else self.linked + len(self.value)
                original = self.original if pooled_retail else self.original + len(self.value)
                self.link["symbols"][other] = linked
                self.bindings[other] = {"va": original, "basis": "second registration"}
                code = self.code(self.linked)[:-1] + self.code(linked)
                expected = self.code(self.original)[:-1] + self.code(original)
                rebuilt = image(code, self.value * 2)
                retail = image(expected, b"\0" * 4 + self.value * 2, data_flags=0xc0000040)
                unit = {"offset": 0x200, "size": len(code), "ltcg_link": self.link, "link_bindings": self.bindings}
                target = {"image": inspect(retail)}
                if pooled_linked or pooled_retail:
                    with self.assertRaisesRegex(ValueError, "overlapping writable string"):
                        built_unit_bytes(target, unit, rebuilt, retail)
                else:
                    self.assertEqual(built_unit_bytes(target, unit, rebuilt, retail), expected)


class JumpTableTests(unittest.TestCase):
    """A switch's jump table, placed after its function in the linked DLL and in retail."""

    def setUp(self):
        self.built = BASE + 0x1000
        self.address = 0x10904000
        self.retail_table = self.address + 0x20
        # jmp [table + eax*4]; three arms; two pad bytes; the table with three entries at built + 12.
        self.function = b"\xff\x24\x85" + struct.pack("<I", self.built + 12) + b"\xc3\xc3\xc3"
        self.code = self.function + b"\xcc\xcc" + struct.pack("<3I", self.built + 7, self.built + 8, self.built + 9)
        self.link = {"roots": ["_driver"], "stubs": [], "rebuilt_offset": 0x200, "rebuilt_address": self.built,
                     "fields": [[3, "abs", "$L_table"]], "symbols": {"$L_table": self.built + 12},
                     "tables": {"$L_table": 3}}
        self.bindings = {"$L_table": {"va": self.retail_table, "basis": "fixture retail jump table"}}
        self.retail = {self.retail_table: struct.pack("<3I", self.address + 7, self.address + 8, self.address + 9)}

    def read(self, va, size):
        return self.retail.get(va, b"")[:size]

    def place(self, code=None, **changes):
        link = dict(self.link, **changes)
        return place_function(image(self.code if code is None else code), len(self.function), self.address,
                              link, self.bindings, read_table=self.read)

    def test_table_is_placed_at_its_retail_address(self):
        self.assertEqual(self.place(), b"\xff\x24\x85" + struct.pack("<I", self.retail_table) + b"\xc3\xc3\xc3")

    def test_entries_must_match_the_retail_table(self):
        self.retail[self.retail_table] = struct.pack("<3I", self.address + 7, self.address + 9, self.address + 8)
        with self.assertRaisesRegex(ValueError, "differs from retail"):
            self.place()

    def test_retail_table_must_lie_after_its_function(self):
        self.bindings = {"$L_table": {"va": self.address + 5, "basis": "fixture"}}
        with self.assertRaisesRegex(ValueError, "after its function"):
            self.place()

    def test_entries_must_name_labels_inside_the_linked_function(self):
        code = self.function + b"\xcc\xcc" + struct.pack("<3I", self.built + 7, self.built + 8, self.built + 20)
        with self.assertRaisesRegex(ValueError, "outside its function"):
            self.place(code)

    def test_declared_table_must_be_referred_to_by_a_field(self):
        with self.assertRaisesRegex(ValueError, "no field refers"):
            self.place(fields=[])

    def test_table_needs_the_retail_image(self):
        with self.assertRaisesRegex(ValueError, "retail image"):
            place_function(image(self.code), len(self.function), self.address, self.link, self.bindings)

    def test_table_needs_a_positive_entry_count(self):
        with self.assertRaisesRegex(ValueError, "entry count"):
            self.place(tables={"$L_table": 0})

    def test_table_field_must_be_absolute(self):
        with self.assertRaises(ValueError):
            self.place(fields=[[3, "rel32", "$L_table"]])

    def test_file_pe_data_reads_code_as_the_file_stores_it(self):
        pe32 = bytearray(image(self.code))
        struct.pack_into("<H", pe32, 0x40 + 24, 0x10B)  # the PE32 optional header magic
        self.assertEqual(file_pe_data(bytes(pe32), self.built, len(self.code)), self.code)
        with self.assertRaisesRegex(ValueError, "file-backed"):
            file_pe_data(bytes(pe32), BASE + 0x9000, 4)


if __name__ == "__main__":
    unittest.main()
