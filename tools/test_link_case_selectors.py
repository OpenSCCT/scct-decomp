import struct
import unittest

from images import inspect
from progress import built_unit_bytes
from test_link_image import BASE, image


class CaseSelectorTests(unittest.TestCase):
    def setUp(self):
        self.address = BASE + 0x1000
        self.targets = self.address + 0x40
        self.selector = self.targets + 12
        self.body = (bytes.fromhex("83 f8 02 0f 87 0e 00 00 00 0f b6 88") + struct.pack("<I", self.selector)
                     + bytes.fromhex("ff 24 8d") + struct.pack("<I", self.targets) + bytes.fromhex("c3 90 c3"))
        targets = struct.pack("<3I", self.address, self.address + 23, self.address + 25)
        self.raw = image(self.body.ljust(0x40, b"\x90") + targets + bytes([2, 0, 1]))
        self.link = {"roots": ["_switch"], "stubs": [], "rebuilt_address": self.address, "rebuilt_offset": 0x200,
                     "symbols": {"selector": self.selector, "targets": self.targets},
                     "tables": {"targets": 3}, "case_selectors": {"selector": "targets"},
                     "fields": [[12, "abs", "selector"], [19, "abs", "targets"]]}
        self.unit = {"id": "selector", "offset": 0x200, "size": len(self.body), "rebuilt_symbol": "_switch",
                     "ltcg_link": self.link, "link_bindings": {
                         "selector": {"va": self.selector, "basis": "fixture"},
                         "targets": {"va": self.targets, "basis": "fixture"}}}

    def place(self, rebuilt=None, original=None):
        original = self.raw if original is None else original
        return built_unit_bytes({"image": inspect(original)}, self.unit, self.raw if rebuilt is None else rebuilt, original)

    def test_complete_switch_and_both_tables(self):
        self.assertEqual(self.place(), self.body)

    def test_checks_linked_and_retail_selector_contents(self):
        other = bytearray(self.raw)
        other[0x24d] = 2
        for side in ("rebuilt", "original"):
            with self.subTest(side=side), self.assertRaisesRegex(ValueError, "differ"):
                self.place(**{side: bytes(other)})

    def test_rejects_truncated_linked_selector(self):
        with self.assertRaisesRegex(ValueError, "truncated"):
            self.place(rebuilt=self.raw[:0x24e])

    def test_rejects_out_of_range_indices_even_if_both_images_agree(self):
        other = bytearray(self.raw)
        other[0x24c] = 3
        with self.assertRaisesRegex(ValueError, "outside the jump table"):
            self.place(bytes(other), bytes(other))

    def test_rejects_external_branch_targets_in_either_image(self):
        other = bytearray(self.raw)
        struct.pack_into("<I", other, 0x240, self.targets)
        for side in ("rebuilt", "original"):
            with self.subTest(side=side), self.assertRaisesRegex(ValueError, "outside its function|differs from retail"):
                self.place(**{side: bytes(other)})

    def test_rejects_shifted_selector_and_unrelated_target_table(self):
        self.link["symbols"]["selector"] += 1
        other = bytearray(self.raw)
        struct.pack_into("<I", other, 0x20c, self.selector + 1)
        with self.assertRaisesRegex(ValueError, "read-execute"):
            self.place(rebuilt=bytes(other))
        self.link["symbols"]["selector"] -= 1
        self.unit["link_bindings"]["selector"]["va"] += 1
        with self.assertRaisesRegex(ValueError, "read-execute"):
            self.place(original=bytes(other))
        self.link["case_selectors"]["selector"] = "wrong table"
        with self.assertRaisesRegex(ValueError, "separate checked jump table"):
            self.place()

    def test_rejects_modified_dispatch_and_branch_outside_function(self):
        for site, value in ((0x202, 0x82), (0x211, 0x25), (0x205, 0x70)):
            other = bytearray(self.raw)
            other[site] = value
            with self.subTest(site=site), self.assertRaisesRegex(ValueError, "checked x86|default branch"):
                self.place(bytes(other), bytes(other))

    def test_table_and_selector_must_be_in_the_same_read_execute_section(self):
        wrong = bytearray(self.raw)
        self.link["symbols"].update(selector=BASE + 0x200c, targets=BASE + 0x2000)
        struct.pack_into("<I", wrong, 0x20c, BASE + 0x200c)
        struct.pack_into("<I", wrong, 0x213, BASE + 0x2000)
        with self.assertRaisesRegex(ValueError, "read-execute"):
            self.place(rebuilt=bytes(wrong))
        self.unit["link_bindings"]["selector"]["va"] = BASE + 0x200c
        self.unit["link_bindings"]["targets"]["va"] = BASE + 0x2000
        with self.assertRaisesRegex(ValueError, "read-execute"):
            self.place(original=bytes(wrong))
