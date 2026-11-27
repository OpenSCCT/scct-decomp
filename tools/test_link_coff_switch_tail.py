"""A VC6 byte-selector switch with a local DIR32 relocation for every case target."""
import struct
import unittest

from progress import built_unit_bytes


BASE = 0x401000
BODY = 33
TABLE = 36
SELECTOR = 44


def fixture():
    code = bytearray(
        b"\x81\xf9\x01\x00\x00\x00\x0f\x87\x12\x00\x00\x00"
        b"\x33\xd2\x8a\x91\x00\x00\x00\x00\xff\x24\x95\x00\x00\x00\x00"
        b"\xc2\x08\x00\xc2\x08\x00\x8d\x49\x00" + bytes(8) + b"\x00\x01\x90\x90"
    )
    names = [(b"_f", 0, 0x20, 2), (b"$L11", TABLE, 0, 3), (b"$L12", SELECTOR, 0, 3),
             (b"$L21", 27, 0, 6), (b"$L22", 30, 0, 6)]
    references = [(16, 2), (23, 1), (36, 3), (40, 4)]
    relocations = b"".join(struct.pack("<IIH", site, index, 6) for site, index in references)
    symbols = b"".join(struct.pack("<8sIhHBB", name, val, 1, kind, storage, 0)
                       for name, val, kind, storage in names)
    reloc = 60 + len(code)
    syms = reloc + len(relocations)
    header = struct.pack("<HHIIIHH", 0x14c, 1, 0, syms, len(names), 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), 60, reloc, 0,
                          len(references), 0, 0x60501020)
    obj = bytearray(header + section + code + relocations + symbols + struct.pack("<I", 4))
    retail = code.copy()
    for site, index in references:
        struct.pack_into("<I", retail, site, BASE + names[index][1])
    return obj, retail


class SwitchTailTests(unittest.TestCase):
    def setUp(self):
        self.obj, self.retail = fixture()
        self.unit = dict(offset=0, size=BODY, coff_switch_tail=16, rebuilt_symbol="_f", link_bindings={})

    def linked(self, unit=None, obj=None, retail=None, section_size=48, start=BASE):
        target = {"image": {"size": 48, "executable_sections": [
            {"code": True, "address": start, "offset": 0, "size": section_size}
        ]}}
        return built_unit_bytes(target, self.unit if unit is None else unit,
                                bytes(self.obj if obj is None else obj), self.retail if retail is None else retail)

    def test_only_body_counts_but_entire_contribution_must_match(self):
        self.assertEqual(self.linked(), self.retail[:BODY])
        for pos in (16, 23, 32, 33, TABLE, TABLE + 4, SELECTOR, 47):
            with self.subTest(pos=pos), self.assertRaises(ValueError):
                wrong = self.retail.copy()
                wrong[pos] ^= 1
                self.linked(retail=wrong)

    def test_matched_but_malformed_switches_fail(self):
        for pos, value in [(0, 0x83), (1, 0xf8), (2, 2), (7, 0x86), (8, 0x7f),
                           (13, 0xdb), (15, 0x90), (22, 0x85), (30, 0xcb),
                           (33, 0x90), (SELECTOR, 1), (SELECTOR, 2), (47, 0xcc)]:
            with self.subTest(pos=pos, value=value), self.assertRaises(ValueError):
                obj, retail = fixture()
                obj[60 + pos] = retail[pos] = value
                self.linked(obj=obj, retail=retail)

    def test_table_and_selector_must_bind_to_distinct_local_labels(self):
        for ref, index, kind in [(0, 1, 6), (1, 2, 6), (2, 4, 6), (3, 2, 6), (3, 4, 0x14)]:
            with self.subTest(ref=ref, index=index, kind=kind), self.assertRaises(ValueError):
                obj = self.obj.copy()
                struct.pack_into("<IH", obj, 108 + ref * 10 + 4, index, kind)
                self.linked(obj=obj)
        for value, owner, storage in [(36, 1, 6), (12, 1, 6), (27, 2, 6), (27, 1, 2)]:
            with self.subTest(value=value, owner=owner, storage=storage), self.assertRaises(ValueError):
                obj = self.obj.copy()
                struct.pack_into("<IhHB", obj, 148 + 3 * 18 + 8, value, owner, 0, storage)
                self.linked(obj=obj)
        for pos in (16, 23, 36, 40):
            with self.subTest(pos=pos), self.assertRaises(ValueError):
                obj = self.obj.copy()
                obj[60 + pos] = 1
                self.linked(obj=obj)

    def test_rejects_bad_length_mode_or_bounds(self):
        for extra in ({"size": 32}, {"size": 34}, {"size": 48}, {"coff_switch_tail": True},
                      {"coff_switch_tail": 17}, {"coff_alignment": 16}, {"ltcg_link": {}},
                      {"rebuilt_offset": 60}, {"rebuilt_storage_class": 3}):
            with self.subTest(extra=extra), self.assertRaises(ValueError):
                self.linked(unit=dict(self.unit, **extra))
        with self.assertRaises(ValueError):
            self.linked(section_size=47)
        with self.assertRaises(ValueError):
            self.linked(retail=self.retail[:-1])
        with self.assertRaises(ValueError):
            self.linked(start=BASE + 1)
