"""Check complete private string objects from /GF- COFF before applying any function relocation."""
import copy
import struct
import unittest

from progress import built_unit_bytes
from test_link_image import BASE, image


def fixture():
    objects = [(b"$SG1", 0, 2), (b"$SG2", 8, 2), (b"$SG3", 0, 3), (b"$SG4", 4, 3)]
    code = (b"\x68" + bytes(4)) * len(objects) + b"\xc3"
    relocs = b"".join(struct.pack("<IIH", 5 * i + 1, i + 1, 6) for i in range(len(objects)))
    symbols = [(b"_hud", 0, 1, 0x20, 2), *((n, v, s, 0, 3) for n, v, s in objects)]
    # The ASCII literal has three alignment bytes. Each .bss label represents an empty TCHAR array.
    contents = b"Menu\0\0\0\0R\0\0\0"
    start = 140
    rloc = start + len(code)
    data = rloc + len(relocs)
    sym = data + len(contents)
    obj = struct.pack("<HHIIIHH", 0x14c, 3, 0, sym, len(symbols), 0, 0)
    obj += struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), start, rloc, 0, 4, 0, 0x60000020)
    obj += struct.pack("<8sIIIIIIHHI", b".data", 0, 0, len(contents), data, 0, 0, 0, 0, 0xc0300040)
    obj += struct.pack("<8sIIIIIIHHI", b".bss", 0, 0, 6, 0, 0, 0, 0, 0, 0xc0300080)
    obj += code + relocs + contents
    obj += b"".join(struct.pack("<8sIhHBB", *entry, 0) for entry in symbols) + struct.pack("<I", 4)
    addresses = (BASE + 0x2000, BASE + 0x2008, BASE + 0x2010, BASE + 0x2014)
    linked = b"".join(b"\x68" + struct.pack("<I", va) for va in addresses) + b"\xc3"
    pe = image(linked, contents + bytes(12), data_flags=0xc0000040)
    names = [n.decode() for n, _, _ in objects]
    unit = dict(offset=0x200, size=len(code), rebuilt_symbol="_hud",
                link_bindings={n: dict(va=va, basis="fixture reference") for n, va in zip(names, addresses)},
                coff_private_strings=dict(zip(names, ({"ascii": 5}, {"utf16": 4}, {"utf16": 2}, {"utf16": 2}))))
    target = dict(image=dict(size=len(pe), executable_sections=[
        dict(address=BASE + 0x1000, offset=0x200, size=len(code), code=True)]))
    return obj, pe, unit, target, linked


class PrivateStringTests(unittest.TestCase):
    def setUp(self):
        self.obj, self.pe, self.unit, self.target, self.code = fixture()

    def check(self, obj=None, unit=None, image=None):
        return built_unit_bytes(self.target, self.unit if unit is None else unit,
                                self.obj if obj is None else obj, self.pe if image is None else image)

    def test_complete_private_strings_and_uninitialized_terminators(self):
        self.assertEqual(self.check(), self.code)

    def test_rejects_mutated_strings_in_either_artifact(self):
        for offset in (0, 4, 8, 10):
            for side, original in (("obj", self.obj), ("image", self.pe)):
                changed = bytearray(original)
                start = changed.index(b"Menu\0")
                changed[start + offset] ^= 1
                with self.subTest(side=side, offset=offset), self.assertRaises(ValueError):
                    self.check(**{side: bytes(changed)})
        altered = bytearray(self.pe)
        altered[altered.index(b"Menu\0") + 16] = 1
        with self.assertRaises(ValueError):
            self.check(image=bytes(altered))

    def test_rejects_shifted_overlapping_or_unreferenced_objects(self):
        for key, value in (("$SG1", BASE + 0x2001), ("$SG2", BASE + 0x2009), ("$SG3", BASE + 0x2012), ("$SG3", BASE + 0x2014)):
            unit = copy.deepcopy(self.unit)
            unit["link_bindings"][key]["va"] = value
            with self.subTest(key=key), self.assertRaises(ValueError):
                self.check(unit=unit)
        changed = bytearray(self.obj)
        table, = struct.unpack_from("<I", changed, 8)
        for start in (1, 4, 8):
            struct.pack_into("<I", changed, table + 18 + 8, start)
            with self.subTest(coff_offset=start), self.assertRaises(ValueError):
                self.check(obj=bytes(changed))
        unit = copy.deepcopy(self.unit)
        unit["coff_private_strings"]["$SG5"] = {"ascii": 1}
        unit["link_bindings"]["$SG5"] = dict(va=BASE + 0x2020, basis="unused")
        with self.assertRaises(ValueError):
            self.check(unit=unit)

    def test_rejects_partial_objects_invalid_storage_and_ambiguous_modes(self):
        for value in ({"ascii": 4}, {"ascii": 7}, {"ascii": True}, {"utf16": 5}, {"ascii": 5, "utf16": 5}):
            unit = copy.deepcopy(self.unit)
            unit["coff_private_strings"]["$SG1"] = value
            with self.subTest(value=value), self.assertRaises(ValueError):
                self.check(unit=unit)
        for offset, fmt, value in ((141, "<I", 4), (140 + 21 + 8, "<H", 0x14),
                                   (60 + 36, "<I", 0x60300040), (60 + 32, "<H", 1),
                                   (100 + 20, "<I", 140), (60 + 20, "<I", 0)):
            altered = bytearray(self.obj)
            struct.pack_into(fmt, altered, offset, value)
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                self.check(obj=bytes(altered))
        for flag in ("ltcg_link", "coff_rtti_vtable", "coff_switch_tail"):
            with self.subTest(flag=flag), self.assertRaises(ValueError):
                self.check(unit=dict(self.unit, **{flag: {}}))

    def test_empty_string_requires_file_backed_retail_data(self):
        unit = copy.deepcopy(self.unit)
        unit["link_bindings"]["$SG3"]["va"] = BASE + 0x2400
        with self.assertRaises(ValueError):
            self.check(unit=unit)
