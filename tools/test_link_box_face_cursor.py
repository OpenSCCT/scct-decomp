import hashlib
import struct
import unittest

from images import inspect
from progress import built_unit_bytes
from test_link_image import BASE, image


# Bits 0, 1 and 2 of the corner index are its unit-cube X, Y and Z coordinates.
# On each face, walk the other two coordinates around their shared square.
def cube_faces():
    indices = []
    square = ((0, 0), (1, 0), (1, 1), (0, 1))
    for axis in range(3):
        u, v = (axis + 1) % 3, (axis + 2) % 3
        for side in (0, 1):
            indices.extend((side << axis) | (i << u) | (j << v) for i, j in square)
    return struct.pack("<24I", *indices)


FACES = cube_faces()
SYMBOL = "?GFrustumFaceVertices@@3PAY03HA"
DATA = BASE + 0x2000
RW_DATA = 0xC0000040
R_DATA = 0x40000040
RX_DATA = 0x60000040


def function(base, extra=b""):
    # EBX starts at the second index in row zero. Reads use the equivalent
    # offsets -4, 0, +4 and +8. The end comparison uses the same bias.
    return (
        b"\xbb" + struct.pack("<I", base + 4)
        + bytes.fromhex("8b 43 fc 8b 13 8b 4b 04 8b 7b 08")
        + bytes.fromhex("83 c3 10 81 fb") + struct.pack("<I", base + 100)
        + bytes.fromhex("0f 8c e6 ff ff ff")  # jl to the first indexed load
        + extra + b"\xc3"
    )


def exported_image(code, data, flags, export_name, export_target):
    """Add a separate read-only .edata section with one named data export."""
    result = bytearray(image(code, data, flags))
    optional = 0x40 + 24
    struct.pack_into("<H", result, 0x40 + 6, 3)
    struct.pack_into("<I", result, optional + 92, 16)
    struct.pack_into("<II", result, optional + 96, 0x3000, 0x100)
    struct.pack_into("<8sIIIIIIHHI", result, optional + 0xe0 + 80,
                     b".edata", 0x200, 0x3000, 0x200, 0x600, 0, 0, 0, 0, R_DATA)
    exports = bytearray(0x200)
    struct.pack_into("<IIHH7I", exports, 0, 0, 0, 0, 0, 0x3040, 1, 1, 1, 0x3028, 0x302c, 0x3030)
    struct.pack_into("<IIH", exports, 0x28, export_target, 0x3050, 0)
    exports[0x40:0x48] = b"box.dll\0"
    name = export_name.encode("ascii") + b"\0"
    exports[0x50:0x50 + len(name)] = name
    exports[0x90:0x99] = b"BOX.Face\0"
    return bytes(result + exports)


class BoxFaceCursorTests(unittest.TestCase):
    def setUp(self):
        self.bases = {"rebuilt": DATA + 0x20, "original": DATA + 0x100}
        self.export = (SYMBOL, self.bases["rebuilt"] - BASE)
        self.codes = {side: function(base) for side, base in self.bases.items()}
        self.tables = {side: FACES for side in self.bases}
        self.flags = {"rebuilt": RW_DATA, "original": RW_DATA}
        self.spec = {"symbol": SYMBOL, "sha256": hashlib.sha256(FACES).hexdigest()}
        self.link = {
            "roots": ["_clip"], "stubs": [], "rebuilt_address": BASE + 0x1000,
            "rebuilt_offset": 0x200, "symbols": {SYMBOL: self.bases["rebuilt"]},
            "fields": [[1, "abs", SYMBOL, 4], [21, "abs", SYMBOL, 100]],
            "box_face_cursor": self.spec,
        }
        self.unit = {
            "id": "clip-box", "offset": 0x200, "size": len(self.codes["original"]),
            "rebuilt_symbol": "_clip", "ltcg_link": self.link,
            "link_bindings": {SYMBOL: {"va": self.bases["original"], "basis": "fixture"}},
        }

    def place(self):
        def pe(side):
            data = bytes(self.bases[side] - DATA) + self.tables[side]
            code = self.codes[side].ljust(0x80, b"\x90") + b"\xc3"
            if side == "rebuilt":
                return exported_image(code, data, self.flags[side], *self.export)
            return image(code, data, self.flags[side])

        original = pe("original")
        return built_unit_bytes({"image": inspect(original)}, self.unit, pe("rebuilt"), original)

    def test_rebinds_bias_and_limit_between_distinct_tables(self):
        self.assertNotEqual(self.codes["rebuilt"], self.codes["original"])
        self.assertEqual(self.place(), self.codes["original"])

    def test_checks_both_operands_and_all_table_bytes_on_each_side(self):
        for side in self.bases:
            for site in (1, 21):
                with self.subTest(side=side, site=site):
                    saved = self.codes[side]
                    wrong = bytearray(saved)
                    wrong[site] ^= 4
                    self.codes[side] = bytes(wrong)
                    with self.assertRaises(ValueError):
                        self.place()
                    self.codes[side] = saved
            for index in (0, 7, 15, 23):
                with self.subTest(side=side, index=index):
                    wrong = bytearray(FACES)
                    wrong[index * 4] ^= 1
                    self.tables[side] = bytes(wrong)
                    with self.assertRaises(ValueError):
                        self.place()
                    self.tables[side] = FACES

    def test_rejects_changed_stride_reads_comparison_and_backedge(self):
        cases = {
            "load behind cursor": (7, 0xf8), "load at cursor": (9, 0x11),
            "next load": (12, 8), "last load": (15, 12),
            "cursor initialization register": (0, 0xbe), "cursor stride": (18, 8),
            "comparison register": (20, 0xfe), "unsigned branch": (26, 0x82),
            "backedge skips first load": (27, 0xe9), "backedge reinitializes cursor": (27, 0xe1),
        }
        for name, (index, byte) in cases.items():
            for side in self.bases:
                with self.subTest(case=name, side=side):
                    saved = self.codes[side]
                    wrong = bytearray(saved)
                    wrong[index] = byte
                    self.codes[side] = bytes(wrong)
                    with self.assertRaises(ValueError):
                        self.place()
                    self.codes[side] = saved

    def test_rejects_wrong_addends_or_duplicate_cursor_fields(self):
        fields = self.link["fields"]
        for wrong in (
            [fields[0]], [fields[1]], [fields[0], fields[0], fields[1]],
            [[1, "abs", SYMBOL, 100], [21, "abs", SYMBOL, 4]],
            [[1, "abs", SYMBOL, 4], [21, "rel32", SYMBOL, 100]],
        ):
            with self.subTest(fields=wrong):
                self.link["fields"] = wrong
                with self.assertRaises(ValueError):
                    self.place()

    def test_face_symbol_cannot_have_another_link_role(self):
        for name, value in (("stubs", [SYMBOL]), ("constants", {SYMBOL: 96}),
                            ("tables", {SYMBOL: 24}), ("interior_objects", {SYMBOL: 96})):
            with self.subTest(role=name):
                self.link[name] = value
                with self.assertRaises(ValueError):
                    self.place()
                self.link.pop(name)
                self.link["stubs"] = []

    def test_requires_the_recorded_digest_even_when_both_images_agree(self):
        changed = bytearray(FACES)
        changed[92] ^= 1
        self.tables = {side: bytes(changed) for side in self.bases}
        with self.assertRaises(ValueError):
            self.place()
        self.tables = {side: FACES for side in self.bases}
        for digest in ("", "garbage", "f" * 64):
            with self.subTest(digest=digest):
                self.spec["sha256"] = digest
                with self.assertRaises(ValueError):
                    self.place()

    def test_requires_the_named_data_export_at_the_recorded_rebuilt_base(self):
        expected = self.bases["rebuilt"] - BASE
        for name, target in (("?Other@@3PAY03HA", expected), (SYMBOL, expected + 4), (SYMBOL, 0x3090)):
            with self.subTest(name=name, target=hex(target)):
                self.export = (name, target)
                with self.assertRaises(ValueError):
                    self.place()

    def test_resigned_table_must_still_contain_six_faces_of_eight_corners(self):
        indices = struct.unpack("<24I", FACES)
        repeated_corner = list(indices)
        # Keep every vertex's overall multiplicity unchanged.
        repeated_corner[0], repeated_corner[9] = repeated_corner[9], repeated_corner[0]
        cases = {
            "index eight": (8, *indices[1:]),
            "repeated corner": repeated_corner,
            "three identical face pairs": tuple(range(8)) * 3,
            "incorrect total for two vertices": (7, *indices[1:]),
        }
        for reason, values in cases.items():
            with self.subTest(reason=reason):
                table = struct.pack("<24I", *values)
                self.tables = {side: table for side in self.bases}
                self.spec["sha256"] = hashlib.sha256(table).hexdigest()
                with self.assertRaisesRegex(ValueError, "six four-corner faces"):
                    self.place()

    def test_requires_initialized_non_executable_data_on_each_side(self):
        for side in self.bases:
            for flags in (R_DATA, RX_DATA, 0xe0000040, 0xc0000080):
                with self.subTest(side=side, flags=hex(flags)):
                    self.flags[side] = flags
                    with self.assertRaises(ValueError):
                        self.place()
                    self.flags[side] = RW_DATA
