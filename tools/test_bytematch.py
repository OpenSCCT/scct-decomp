"""The ByteMatch export names each function and rolls up function and byte totals."""

from pathlib import Path
import tempfile
import unittest

from bytematch import build_report, source_name, virtual_address
from progress import inputs_digest
from test_progress import pe, target


class NamingTests(unittest.TestCase):
    def test_decorated_c_symbols_name_their_source_function(self):
        self.assertEqual(source_name("_SND_fn_vSetCurrentLanguage@4"), "SND_fn_vSetCurrentLanguage")
        self.assertEqual(source_name("@destroy_child@4"), "destroy_child")
        self.assertEqual(source_name("_memcpy"), "memcpy")
        self.assertIsNone(source_name("??1UClass@@UAE@XZ"))

    def test_virtual_address_follows_the_section_mapping(self):
        item = dict(image=dict(executable_sections=[dict(offset=0x400, size=0x1000, address=0x10001000)]))
        self.assertEqual(virtual_address(item, 0x480), 0x10001080)
        with self.assertRaises(ValueError):
            virtual_address(item, 0x2000)


class ReportTests(unittest.TestCase):
    def test_report_rolls_up_function_counts_and_categories(self):
        with tempfile.TemporaryDirectory() as tmp:
            folder = Path(tmp) / "pc"
            (folder / "src").mkdir(parents=True)
            (folder / "function_maps").mkdir()
            (folder / "src" / "game_unit.c").write_text("int f(void) { return 0; }\n", encoding="utf-8")
            (folder / "src" / "crt_helper.c").write_text("int g(void) { return 0; }\n", encoding="utf-8")
            (folder / "basis.md").write_text("Synthetic compiler evidence.\n", encoding="utf-8")

            item = target(pe())
            sha = item["image"]["sha256"]
            verified = dict(
                id="game-fn", offset=1024, size=16, rebuilt_offset=0,
                inputs=["src/game_unit.c"], toolchain="synthetic", build_command="synthetic /O2",
                recipe_evidence=dict(compiler="synthetic", flags=["/O2"], basis="basis.md"),
            )
            verified["match"] = dict(bytes_sha256="11" * 32, inputs_sha256=inputs_digest(folder, verified, sha))
            candidate = dict(
                id="crt-fn", offset=1040, size=12, rebuilt_offset=0,
                inputs=["src/crt_helper.c"], toolchain="synthetic", build_command="synthetic /O2",
            )
            candidate["match"] = dict(bytes_sha256="22" * 32, inputs_sha256=inputs_digest(folder, candidate, sha))
            item["units"] = [verified, candidate]

            # Code section is 100 bytes at file offsets 1024..1124 (0x400..0x464).
            # Units cover 0x400..0x41c (28 bytes). Map adds two unmatched functions (20 + 16 bytes)
            # leaving 36 unassigned bytes that must not be counted as functions.
            (folder / "function_maps" / "synthetic.txt").write_text(
                f"# Image SHA-256 {sha}\n41c 41c-430\n430 430-440\n",
                encoding="utf-8",
            )

            report = build_report(folder, item)
            measures = report["measures"]
            self.assertEqual(measures["total_code"], "100")
            self.assertEqual(measures["matched_code"], "16")
            self.assertEqual(measures["total_functions"], 4)
            self.assertEqual(measures["matched_functions"], 1)
            self.assertAlmostEqual(measures["matched_functions_percent"], 25.0)

            categories = {c["id"]: c["measures"] for c in report["categories"]}
            self.assertEqual(categories["game"]["total_functions"], 3)
            self.assertEqual(categories["game"]["matched_functions"], 1)
            self.assertAlmostEqual(categories["game"]["matched_functions_percent"], 100 / 3)
            self.assertEqual(categories["runtime"]["total_functions"], 1)
            self.assertEqual(categories["runtime"]["matched_functions"], 0)
            self.assertEqual(categories["runtime"]["matched_functions_percent"], 0.0)

            self.assertEqual(sum(u["measures"]["total_functions"] for u in report["units"]), 4)
            self.assertEqual(sum(u["measures"]["matched_functions"] for u in report["units"]), 1)

            # Without a function map, the unmapped remainder still carries zero-function measures.
            (folder / "function_maps" / "synthetic.txt").unlink()
            fallback = build_report(folder, item)
            self.assertEqual(fallback["measures"]["total_functions"], 2)
            self.assertEqual(fallback["measures"]["matched_functions"], 1)
            self.assertAlmostEqual(fallback["measures"]["matched_functions_percent"], 50.0)
            unmapped = fallback["units"][-1]
            self.assertEqual(unmapped["name"], "pc/unmapped-code")
            self.assertEqual(unmapped["measures"]["total_functions"], 0)
            self.assertEqual(unmapped["measures"]["matched_functions"], 0)
            self.assertEqual(unmapped["measures"]["matched_functions_percent"], 0)


if __name__ == "__main__":
    unittest.main()
