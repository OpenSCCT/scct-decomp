import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent / "ci"))
from no_game_data import problems


class GameDataGuardTests(unittest.TestCase):
    def test_sources_and_manifests_pass(self):
        self.assertEqual(problems("pc/src/campaign_string_deletion.c", b"struct S;\n"), [])
        self.assertEqual(problems("pc/config/units/steam-252084-versus/000000.json", b"[]\n"), [])

    def test_game_files_and_build_output_fail(self):
        self.assertTrue(problems("pc/local/x.c", b""))
        self.assertTrue(problems("System/splintercell3.exe", b"MZ"))
        self.assertTrue(problems("ps2/SLES_532.87", b""))
        self.assertTrue(problems("pc/src/renamed.c", b"\x7fELF"))
        self.assertTrue(problems("pc/src/renamed.c", b"\x4c\x01" + bytes(18)))
        self.assertTrue(problems("maps/x.dat", b"\xc1\x83\x2a\x9e"))
        self.assertTrue(problems("big.json", bytes(5 * 1024 * 1024 + 1)))


if __name__ == "__main__":
    unittest.main()
