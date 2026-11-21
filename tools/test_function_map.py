"""Unmatched code is split along the function map without double counting."""

import json
import tempfile
import unittest
from pathlib import Path

from function_map import convert, load, unmatched_functions


class FunctionMapTests(unittest.TestCase):
    def test_round_trip_from_the_ghidra_inventory(self):
        # Section at RVA 0x1000 is stored at file offset 0x400; Ghidra ranges are inclusive.
        manifest = dict(image=dict(sha256="ab" * 32, executable_sections=[
            dict(name=".text", offset=0x400, size=0x100, address=0x10001000, code=True)]))
        inventory = "\n".join([
            "#sha256=" + "AB" * 32, "#base=10000000", "#language=x86:LE:32:default",
            "rva\tname\tsource\tentry_export\tthunk\tinline\tnoreturn\tranges_rva_inclusive\taliases\tblock",
            "1030\tf\tDEFAULT\tfalse\tfalse\tfalse\tfalse\t1030-1037,1040-1043\tf\t.text",
            "1010\tg\tDEFAULT\tfalse\tfalse\tfalse\tfalse\t1010-101f\tg\t.text",
            "5000\th\tDEFAULT\tfalse\tfalse\tfalse\tfalse\t5000-5003\th\t.data"]) + "\n"
        with tempfile.TemporaryDirectory() as folder:
            paths = [Path(folder) / name for name in ("t.json", "inv.tsv", "map.txt")]
            paths[0].write_text(json.dumps(manifest), encoding="utf-8")
            paths[1].write_text(inventory, encoding="utf-8")
            paths[2].write_text(convert(paths[0], paths[1]), encoding="utf-8")
            self.assertEqual(load(paths[2], "ab" * 32),
                             [(0x410, [(0x410, 0x420)]), (0x430, [(0x430, 0x438), (0x440, 0x444)])])
            with self.assertRaises(ValueError):
                load(paths[2], "cd" * 32)
            manifest["image"]["sha256"] = "cd" * 32
            paths[0].write_text(json.dumps(manifest), encoding="utf-8")
            with self.assertRaises(ValueError):
                convert(paths[0], paths[1])

    def test_units_take_precedence_and_bytes_are_counted_once(self):
        functions = [(0x10, [(0x10, 0x20)]), (0x18, [(0x18, 0x28)]), (0x30, [(0x30, 0x38)])]
        pending, leftover = unmatched_functions(0x100, [(0x10, 0x40)], [(0x30, 0x38)], functions, region=0x20)
        self.assertEqual(pending, [(0x10, 0x10), (0x18, 0x8)])
        # 0x28-0x30 and 0x38-0x40 are covered by nothing; regions split at 0x20 and 0x40.
        self.assertEqual(leftover, [(0x20, 0x40, 0x10)])
        total = sum(n for _, n in pending) + sum(n for *_, n in leftover) + 8
        self.assertEqual(total, 0x30)

    def test_function_bytes_outside_code_are_ignored(self):
        pending, leftover = unmatched_functions(0x100, [(0x10, 0x20)], [], [(0x08, [(0x08, 0x18)])])
        self.assertEqual(pending, [(0x08, 0x08)])
        self.assertEqual(leftover, [(0x10, 0x20, 0x8)])

    def test_malformed_intervals_are_rejected(self):
        with tempfile.TemporaryDirectory() as folder:
            path = Path(folder) / "map.txt"
            path.write_text("10 20-10\n", encoding="utf-8")
            with self.assertRaises(ValueError):
                load(path)


if __name__ == "__main__":
    unittest.main()
