"""The system_headers field: a unit compiled against its toolchain's own headers binds their hashes."""

import hashlib
import json
import sys
from pathlib import Path
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "pc"))
import verify_build  # noqa: E402
from manifests import save_receipts  # noqa: E402
from progress import inputs_digest, write  # noqa: E402

TOOLCHAIN = "Microsoft C/C++ 13.10.3052 for x86"
IMAGE = "0" * 64


def sha(data):
    return hashlib.sha256(data).hexdigest()


def unit(**extra):
    return dict(id="a", offset=0, size=1, rebuilt_symbol="_a", inputs=["src/a.cpp"], toolchain=TOOLCHAIN,
                build_command="cl /nologo /O2 /c /Folocal/a.obj src/a.cpp", **extra)


class Toolchain:
    """A fake toolchain folder: bin/cl.exe beside include/ with yvals.h and the given headers."""

    def __init__(self, root, headers):
        (root / "bin").mkdir(parents=True)
        (root / "bin" / "cl.exe").write_bytes(b"")
        (root / "include" / "sys").mkdir(parents=True)
        for name, data in {"yvals.h": b"/* yvals */\n", **headers}.items():
            (root / "include" / name).write_bytes(data)
        self.cl = str(root / "bin" / "cl.exe")
        self.include = root / "include"


class SystemHeaderTests(unittest.TestCase):
    def test_include_folder_is_found_above_the_compiler(self):
        with tempfile.TemporaryDirectory() as tmp:
            tool = Toolchain(Path(tmp), {})
            self.assertEqual(verify_build.system_include_dir(tool.cl), tool.include.resolve())
            nested = Path(tmp) / "bin" / "Hostx64" / "x86"
            nested.mkdir(parents=True)
            self.assertEqual(verify_build.system_include_dir(str(nested / "cl.exe")), tool.include.resolve())

    def test_headers_read_are_keyed_under_include_and_hashed_as_inputs(self):
        with tempfile.TemporaryDirectory() as tmp:
            tool = Toolchain(Path(tmp) / "tk", {"VECTOR": b"v\r\n", "sys/types.h": b"t\n"})
            build = Path(tmp) / "build"
            (build / "src").mkdir(parents=True)
            (build / "src" / "a.h").write_bytes(b"")
            read = verify_build.system_headers_read(
                [str(tool.include / "VECTOR"), str(tool.include / "sys" / "types.h"), "src/a.h"],
                tool.include.resolve(), build.resolve())
            self.assertEqual(read, {"sys/types.h": sha(b"t\n"), "vector": sha(b"v\n")})

    def test_a_header_outside_inputs_and_include_is_refused(self):
        with tempfile.TemporaryDirectory() as tmp:
            tool = Toolchain(Path(tmp), {})
            elsewhere = Path(tmp) / "other.h"
            elsewhere.write_bytes(b"")
            with self.assertRaisesRegex(ValueError, "outside its inputs"):
                verify_build.system_headers_read([str(elsewhere)], tool.include.resolve(),
                                                 (Path(tmp) / "bin").resolve())

    def test_staging_copies_only_recorded_headers_with_matching_hashes(self):
        with tempfile.TemporaryDirectory() as tmp:
            tool = Toolchain(Path(tmp) / "tk", {"vector": b"v\n", "map": b"m\n"})
            stage = Path(tmp) / "stage"
            verify_build.stage_system_headers(unit(system_headers={"vector": sha(b"v\n")}), tool.cl, stage)
            self.assertEqual(sorted(p.name for p in stage.iterdir()), ["vector"])
            with self.assertRaisesRegex(ValueError, "differs from the one recorded"):
                verify_build.stage_system_headers(unit(system_headers={"map": sha(b"other\n")}), tool.cl,
                                                  Path(tmp) / "stage2")
            with self.assertRaisesRegex(ValueError, "is not in"):
                verify_build.stage_system_headers(unit(system_headers={"list": sha(b"")}), tool.cl,
                                                  Path(tmp) / "stage3")


class ReceiptTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.folder = Path(self.tmp.name)
        (self.folder / "src").mkdir()
        (self.folder / "src" / "a.cpp").write_text("#include <vector>\n")

    def tearDown(self):
        self.tmp.cleanup()

    def test_the_header_hashes_are_part_of_the_receipt(self):
        plain = inputs_digest(self.folder, unit(), IMAGE)
        one = inputs_digest(self.folder, unit(system_headers={"vector": sha(b"1")}), IMAGE)
        two = inputs_digest(self.folder, unit(system_headers={"vector": sha(b"2")}), IMAGE)
        self.assertEqual(len({plain, one, two}), 3)

    def test_malformed_records_are_refused(self):
        for headers in ([], {"../vector": sha(b"")}, {"C:/x": sha(b"")}, {"sys\\types.h": sha(b"")},
                        {"vector": "short"}):
            with self.assertRaises(ValueError, msg=headers):
                inputs_digest(self.folder, unit(system_headers=headers), IMAGE)
        clang = unit(system_headers={})
        clang["toolchain"] = "Clang 19.1.0 for i686-pc-windows-msvc"
        with self.assertRaises(ValueError):
            inputs_digest(self.folder, clang, IMAGE)

    def test_the_verifier_may_record_headers_and_nothing_else(self):
        config = self.folder / "config"
        config.mkdir()
        manifest = config / "t.json"
        stored = unit(system_headers={})
        write(manifest, dict(id="t", units=[stored]))
        updated = dict(stored, system_headers={"vector": sha(b"v")}, match={"bytes_sha256": IMAGE})
        with self.assertRaisesRegex(ValueError, "changed during verification"):
            save_receipts(manifest, [updated], write)
        save_receipts(manifest, [updated], write, fields=("match", "system_headers"))
        saved = json.loads(manifest.read_text())["units"][0]
        self.assertEqual(saved["system_headers"], {"vector": sha(b"v")})
        self.assertEqual(saved["match"], {"bytes_sha256": IMAGE})


if __name__ == "__main__":
    unittest.main()
