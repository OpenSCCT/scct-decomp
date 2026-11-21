import json
from pathlib import Path
import tempfile
import unittest

from manifests import load_target, save_receipt, save_receipts
from progress import write


class ManifestTests(unittest.TestCase):
    def test_inline_and_split_units_share_one_view_and_keep_ownership(self):
        with tempfile.TemporaryDirectory() as tmp:
            edition = Path(tmp) / "pc"
            (edition / "config").mkdir(parents=True)
            path = edition / "config/target.json"
            inline = {"id": "one", "offset": 20}
            separate = {"id": "two", "offset": 10}
            write(path, {"units": [inline], "unit_files": ["other.json"]})
            write(edition / "other.json", [separate])
            self.assertEqual(load_target(path)["units"], [separate, inline])
            receipt = dict(separate, match={"bytes_sha256": "fixture"})
            save_receipt(path, receipt, write)
            self.assertEqual(json.loads((edition / "other.json").read_text()), [receipt])
            self.assertEqual(json.loads(path.read_text())["units"], [inline])
            with self.assertRaisesRegex(ValueError, "changed"):
                save_receipt(path, dict(receipt, offset=15), write)
            write(path, {"units": [inline]})
            self.assertEqual(load_target(path)["units"], [inline])

    def test_batch_receipts_rewrite_only_the_files_that_own_a_change(self):
        with tempfile.TemporaryDirectory() as tmp:
            edition = Path(tmp) / "pc"
            (edition / "config").mkdir(parents=True)
            path = edition / "config/target.json"
            inline = {"id": "one", "offset": 20, "match": {"inputs_sha256": "old"}}
            separate = {"id": "two", "offset": 10, "match": {"inputs_sha256": "old"}}
            untouched = {"id": "three", "offset": 30, "match": {"inputs_sha256": "kept"}}
            write(path, {"units": [inline], "unit_files": ["other.json", "third.json"]})
            write(edition / "other.json", [separate])
            write(edition / "third.json", [untouched])
            written = []

            def record(file, value):
                written.append(file.name)
                write(file, value)

            fresh = [dict(unit, match={"inputs_sha256": "new"}) for unit in (inline, separate)]
            save_receipts(path, [*fresh, untouched], record)
            self.assertEqual(sorted(written), ["other.json", "target.json"])
            self.assertEqual([u["match"]["inputs_sha256"] for u in load_target(path)["units"]], ["new", "new", "kept"])
            with self.assertRaisesRegex(ValueError, "changed"):
                save_receipts(path, [dict(fresh[0], offset=21)], record)
            with self.assertRaisesRegex(ValueError, "missing"):
                save_receipts(path, [{"id": "absent", "match": {}}], record)

    def test_file_lists_reject_duplicates_escape_and_non_list_files(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp) / "pc"
            (root / "config").mkdir(parents=True)
            path = root / "config/target.json"
            write(root / "unit.json", [])
            for files in [["unit.json", "unit.json"], ["../other.json"], ["config/target.json"]]:
                write(path, {"units": [], "unit_files": files})
                with self.subTest(files=files), self.assertRaises(ValueError):
                    load_target(path)
            write(root / "unit.json", {"unexpected": 1})
            write(path, {"units": [], "unit_files": ["unit.json"]})
            with self.assertRaises(ValueError):
                load_target(path)
