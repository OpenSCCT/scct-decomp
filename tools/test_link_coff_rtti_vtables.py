"""Exercise a project-authored VC6-style COFF and its corresponding PE RTTI graph."""

import copy
import struct
import unittest

from images import inspect
from link_x86 import link_function
from progress import built_unit_bytes


VTABLE = "??_7Widget@@6B@"
SCALAR = "??_GWidget@@UAEPAXI@Z"
VECTOR = "??_EWidget@@UAEPAXI@Z"
LOCATOR = "??_R4Widget@@6B@"
HIERARCHY = "??_R3Widget@@8"
BASE_ARRAY = "??_R2Widget@@8"
BASE = "??_R1A@?0A@EA@Widget@@8"
TYPE = "??_R0?AVWidget@@@8"
TYPE_INFO = "??_7type_info@@6B@"
CODE = 0x60000020
READONLY = 0x40301040
WRITABLE = 0xc0301040


def u32(value):
    return struct.pack("<I", value)


class Fixture:
    def __init__(self):
        # The primary vftable symbol starts four bytes into its own contribution.
        # A weak external vector deleting destructor falls back to the scalar method.
        self.parts = [
            ("_ctor", 0x401000, CODE, b"\xb8" + bytes(4) + b"\xc3", [(1, VTABLE, 6)]),
            (SCALAR, 0x401030, CODE, b"\xe8" + bytes(4) + b"\xc3", [(1, "_release", 20)]),
            (VTABLE, 0x402020, READONLY, bytes(8), [(0, LOCATOR, 6), (4, VECTOR, 6)]),
            (LOCATOR, 0x402040, READONLY, bytes(20), [(12, TYPE, 6), (16, HIERARCHY, 6)]),
            (HIERARCHY, 0x402080, READONLY, bytes(8) + u32(1) + bytes(4), [(12, BASE_ARRAY, 6)]),
            (BASE_ARRAY, 0x4020a0, READONLY, bytes(5), [(0, BASE, 6)]),
            (BASE, 0x4020c0, READONLY, bytes(12) + u32(0xffffffff) + bytes(8), [(0, TYPE, 6)]),
            (TYPE, 0x403010, WRITABLE, bytes(8) + b".?AVWidget@@\0", [(0, TYPE_INFO, 6)]),
        ]
        self.address = {name: va for name, va, *_ in self.parts}
        self.address.update({VTABLE: 0x402024, VECTOR: 0x401030, "_release": 0x401050, TYPE_INFO: 0x4020f0})
        self.section = {}
        self.raw = {}
        self.relocs = {}
        self.symbol = {}
        self.image = self.make_pe()
        self.obj = self.make_coff()
        self.unit = dict(offset=0x200, size=6, rebuilt_symbol="_ctor",
                         link_bindings={VTABLE: dict(va=self.address[VTABLE], basis="Widget primary vftable")},
                         coff_rtti_vtable=dict(symbol=VTABLE, locator_va=self.address[LOCATOR],
                                               type_info_vtable_va=self.address[TYPE_INFO],
                                               deleting_destructor=dict(va=self.address[SCALAR], size=6,
                                                                        link_bindings={"_release": dict(
                                                                            va=0x401050, basis="release helper")})))
        self.target = {"image": inspect(self.image)}

    @staticmethod
    def file_offset(va):
        for first, raw in ((0x403000, 0x500), (0x402000, 0x300), (0x401000, 0x200)):
            if va >= first:
                return raw + va - first
        raise ValueError("invalid fixture address")

    def make_pe(self):
        pe = bytearray(0x600)
        pe[:2] = b"MZ"
        struct.pack_into("<I", pe, 60, 0x80)
        pe[0x80:0x84] = b"PE\0\0"
        struct.pack_into("<HH", pe, 0x84, 0x14c, 3)
        struct.pack_into("<H", pe, 0x94, 0x60)
        struct.pack_into("<H", pe, 0x98, 0x10b)
        struct.pack_into("<I", pe, 0x98 + 28, 0x400000)
        for i, (name, rva, raw, length, flags) in enumerate([
                (b".text", 0x1000, 0x200, 0x100, CODE), (b".rdata", 0x2000, 0x300, 0x200, 0x40000040),
                (b".data", 0x3000, 0x500, 0x100, 0xc0000040)]):
            at = 0xf8 + i * 40
            struct.pack_into("<8s4I", pe, at, name, length, rva, length, raw)
            struct.pack_into("<I", pe, at + 36, flags)
        for _, va, _, data, refs in self.parts:
            raw = self.file_offset(va)
            pe[raw:raw + len(data)] = data
            for pos, target, kind in refs:
                value = self.address[target]
                if kind == 20:
                    value -= va + pos + 4
                struct.pack_into("<I", pe, raw + pos, value)
        info = self.address[TYPE_INFO]
        struct.pack_into("<II", pe, self.file_offset(info - 4), 0x402100, self.address["_release"])
        struct.pack_into("<5I", pe, self.file_offset(0x402100), 0, 0, 0, 0x403040, 0x402140)
        name = u32(info) + bytes(4) + b".?AVtype_info@@\0"
        at = self.file_offset(0x403040)
        pe[at:at + len(name)] = name
        return pe

    def make_coff(self):
        declarations = [(name, 4 if name == VTABLE else 0, sec, 32 if flags == CODE else 0, 2)
                        for sec, (name, _, flags, _, _) in enumerate(self.parts, 1)]
        declarations.extend([("_release", 0, 0, 32, 2), (TYPE_INFO, 0, 0, 0, 2), (VECTOR, 0, 0, 32, 105)])
        indices = {decl[0]: i for i, decl in enumerate(declarations)}
        strings = bytearray(4)
        symbols = bytearray()
        for name, value, sec, kind, storage in declarations:
            encoded = name.encode()
            if len(encoded) > 8:
                offset = len(strings)
                strings += encoded + b"\0"
                encoded = bytes(4) + u32(offset)
            symbols += struct.pack("<8sIhHBB", encoded, value, sec, kind, storage, int(storage == 105))
            if storage == 105:
                symbols += struct.pack("<II10x", indices[SCALAR], 2)
        struct.pack_into("<I", strings, 0, len(strings))
        obj = bytearray(20 + len(self.parts) * 40)
        for i, (name, _, flags, data, refs) in enumerate(self.parts):
            hdr, raw = 20 + 40 * i, len(obj)
            obj += data
            relocs = len(obj)
            for pos, target, kind in refs:
                obj += struct.pack("<IIH", pos, indices[target], kind)
            label = b".text" if flags == CODE else (b".data" if flags == WRITABLE else b".rdata")
            struct.pack_into("<8sIIIIIIHHI", obj, hdr, label, 0, 0, len(data), raw, relocs, 0, len(refs), 0, flags)
            self.section[name], self.raw[name], self.relocs[name] = hdr, raw, relocs
        start = len(obj)
        self.symbol = {name: start + i * 18 for name, i in indices.items()}
        struct.pack_into("<HHIIIHH", obj, 0, 0x14c, len(self.parts), 0, start, len(symbols) // 18, 0, 0)
        return obj + symbols + strings

    def linked(self, unit=None, obj=None, image=None):
        return built_unit_bytes(self.target, unit if unit is not None else self.unit,
                                self.obj if obj is None else obj, self.image if image is None else image)


class RttiVtableTests(unittest.TestCase):
    def setUp(self):
        self.f = Fixture()

    def test_rebuilds_ctor_only_after_authenticating_all_referents(self):
        f = self.f
        self.assertEqual(f.linked(), f.image[0x200:0x206])
        with self.assertRaises(ValueError):
            link_function(f.obj, "_ctor", 6, 0x401000, f.unit["link_bindings"])

    def test_retail_graph_mutations(self):
        f = self.f
        fields = ((VTABLE, -4), (VTABLE, 0), (LOCATOR, 0), (LOCATOR, 12), (LOCATOR, 16), (HIERARCHY, 8),
                  (HIERARCHY, 12), (BASE_ARRAY, 0), (BASE_ARRAY, 4), (BASE, 12), (TYPE, 0), (TYPE, 8),
                  (TYPE, 16), (SCALAR, 0), (SCALAR, 1), (SCALAR, 5), (TYPE_INFO, 3))
        for name, offset in fields:
            image = f.image.copy()
            image[f.file_offset(f.address[name]) + offset] ^= 1
            with self.subTest(name=name, offset=offset), self.assertRaises(ValueError):
                f.linked(image=image)

    def test_coff_graph_mutations(self):
        f = self.f
        positions = [f.symbol[VTABLE] + 8, f.symbol[VECTOR] + 18, f.symbol[VECTOR] + 22,
                     f.raw[VTABLE], f.raw[LOCATOR], f.raw[HIERARCHY] + 8, f.raw[BASE_ARRAY] + 4,
                     f.raw[BASE] + 12, f.raw[TYPE] + 8, f.raw[SCALAR], f.raw["_ctor"] + 1,
                     f.relocs["_ctor"] + 8, f.relocs[BASE] + 4, f.section[TYPE] + 39]
        for position in positions:
            obj = f.obj.copy()
            obj[position] ^= 1
            with self.subTest(position=position), self.assertRaises(ValueError):
                f.linked(obj=obj)

    def test_type_info_must_identify_its_own_vftable(self):
        f = self.f
        for va in (f.address[TYPE_INFO] - 4, 0x402100, 0x40210c, 0x403040, 0x403048):
            image = f.image.copy()
            image[f.file_offset(va)] ^= 1
            with self.subTest(va=va), self.assertRaises(ValueError):
                f.linked(image=image)

    def test_manifest_changes_and_conflicting_modes(self):
        for path in (("link_bindings", VTABLE, "va"), ("coff_rtti_vtable", "locator_va"),
                     ("coff_rtti_vtable", "type_info_vtable_va"), ("coff_rtti_vtable", "deleting_destructor", "va"),
                     ("coff_rtti_vtable", "deleting_destructor", "size"),
                     ("coff_rtti_vtable", "deleting_destructor", "link_bindings", "_release", "va")):
            unit = copy.deepcopy(self.f.unit)
            field = unit
            for key in path[:-1]:
                field = field[key]
            field[path[-1]] += 4
            with self.subTest(path=path), self.assertRaises(ValueError):
                self.f.linked(unit=unit)
        for field in ("ltcg_link", "coff_switch_tail", "rebuilt_offset", "rebuilt_storage_class"):
            with self.subTest(field=field), self.assertRaises(ValueError):
                self.f.linked(unit={**self.f.unit, field: 1})


if __name__ == "__main__":
    unittest.main()
