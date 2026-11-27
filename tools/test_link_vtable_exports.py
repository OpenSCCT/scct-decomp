import copy
import struct
import unittest

from images import inspect
from link_vtable_exports import resolve_vtable_exports, vtable_export_args
from progress import built_unit_bytes
from test_link_image import BASE, image


POLYS = "??_7UPolys@@6B@"
MODEL = "??_7UModel@@6B@"
METHOD = "?Destroy@UPolys@@UAEXXZ"
SLOT = POLYS + "+0x24"
RETAIL_BASE = 0x10900000
PE_OPTIONAL = 0x40 + 24
EXPORT_RVA = 0x2080
EXPORT_SIZE = 0x140
FUNCTIONS_RVA = 0x20b0
NAMES_RVA = 0x20c0
ORDINALS_RVA = 0x20d0
FORWARDER_RVA = 0x21a0


def function(base, polys, model):
    # Store two independently linked vtable addresses into different subobjects.
    return (b"\xc7\x01" + struct.pack("<I", base + polys)
            + b"\xc7\x41\x04" + struct.pack("<I", base + model) + b"\xc3")


def fixture(base, tables, *, fields=None, exports=None, bad_ordinal=None):
    """Make an x86 PE with two vtables and an optional IMAGE_EXPORT_DIRECTORY."""
    code = bytearray(0x180)
    code[:14] = function(base, *(fields or tables))
    code[0x100:0x106] = b"\xb8\x01\0\0\0\xc3"
    code[0x110:0x116] = b"\xb8\x02\0\0\0\xc3"
    result = bytearray(image(bytes(code), bytes(0x200)))
    struct.pack_into("<I", result, PE_OPTIONAL + 28, base)
    struct.pack_into("<I", result, PE_OPTIONAL + 92, 16)

    def offset(rva):
        return 0x400 + rva - 0x2000 if rva >= 0x2000 else 0x200 + rva - 0x1000

    for table, slot in zip(tables, (0x1100, 0x1110)):
        struct.pack_into("<I", result, offset(table), base + slot)
    if exports is None:
        return bytes(result)

    struct.pack_into("<II", result, PE_OPTIONAL + 96, EXPORT_RVA, EXPORT_SIZE)
    struct.pack_into("<IIHH7I", result, offset(EXPORT_RVA), 0, 0, 0, 0, 0x20d8, 1,
                     len(exports), len(exports), FUNCTIONS_RVA, NAMES_RVA, ORDINALS_RVA)
    result[offset(0x20d8):offset(0x20d8) + 8] = b"mvt.dll\0"
    name_rva = 0x20e0
    for ordinal, (_, target) in enumerate(exports):
        struct.pack_into("<I", result, offset(FUNCTIONS_RVA) + 4 * ordinal, target)
    # Name lookups index the EAT through the ordinal array. Name and EAT order differ.
    for i, (ordinal, (name, _)) in enumerate(sorted(enumerate(exports), key=lambda entry: entry[1][0])):
        encoded = name.encode("ascii") + b"\0"
        result[offset(name_rva):offset(name_rva) + len(encoded)] = encoded
        struct.pack_into("<I", result, offset(NAMES_RVA) + 4 * i, name_rva)
        struct.pack_into("<H", result, offset(ORDINALS_RVA) + 2 * i,
                         len(exports) if name == bad_ordinal else ordinal)
        name_rva += len(encoded)
    forwarder = b"OTHER.Forwarded\0"
    result[offset(FORWARDER_RVA):offset(FORWARDER_RVA) + len(forwarder)] = forwarder
    return bytes(result)


def slot_fixture(base, tables, *, exported=False, method=0x1120, operand=None):
    exports = list(zip((POLYS, MODEL), tables)) if exported else None
    result = bytearray(fixture(base, tables, exports=exports))
    slot_rva = tables[0] + 9 * 4
    struct.pack_into("<I", result, 0x400 + slot_rva - 0x2000, base + method)
    result[0x320:0x326] = b"\xb8\x03\0\0\0\xc3"
    # The destructor dispatches through the pointer stored at this absolute slot.
    slot_address = base + (slot_rva if operand is None else operand)
    result[0x20d:0x214] = b"\xff\x15" + struct.pack("<I", slot_address) + b"\xc3"
    return bytes(result)


class ExportedVtableTests(unittest.TestCase):
    def setUp(self):
        self.retail_tables = (0x2024, 0x2058)
        self.original = fixture(RETAIL_BASE, self.retail_tables)
        self.target = {"image": inspect(self.original)}
        self.tables = (0x2010, 0x2040)
        self.exports = list(zip((POLYS, MODEL), self.tables))
        self.image = fixture(BASE, self.tables, exports=self.exports)
        self.link = {
            "roots": ["?driver@@YAXXZ"], "stubs": [],
            "rebuilt_offset": 0x200, "rebuilt_address": BASE + 0x1000,
            "exported_vtables": [POLYS, MODEL], "symbols": {},
            "fields": [[2, "abs", POLYS], [9, "abs", MODEL]],
        }
        self.bindings = {
            name: {"va": RETAIL_BASE + rva, "basis": "fixture vtable"}
            for name, rva in zip((POLYS, MODEL), self.retail_tables)
        }

    def placed(self, rebuilt=None, *, link=None, original=None, bindings=None):
        unit = {"offset": 0x200, "size": 14, "ltcg_link": self.link if link is None else link,
                "link_bindings": self.bindings if bindings is None else bindings}
        return built_unit_bytes(self.target, unit, self.image if rebuilt is None else rebuilt,
                                self.original if original is None else original)

    def test_named_exports_recover_the_same_retail_bytes_after_two_layout_changes(self):
        self.assertCountEqual(vtable_export_args(self.link), [f"/EXPORT:{name},DATA" for name in (POLYS, MODEL)])
        for tables in (self.tables, tuple(reversed(self.tables)), (0x2034, 0x2018)):
            with self.subTest(tables=tables):
                rebuilt = fixture(BASE, tables, exports=list(zip((POLYS, MODEL), tables)))
                resolved = resolve_vtable_exports(rebuilt, self.original, self.link, self.bindings)
                self.assertEqual(resolved["symbols"], {POLYS: BASE + tables[0], MODEL: BASE + tables[1]})
                self.assertEqual(self.link["symbols"], {})
                self.assertEqual(self.placed(rebuilt), function(RETAIL_BASE, *self.retail_tables))

    def test_absolute_operand_must_equal_the_named_export(self):
        for fields in ((self.tables[0] + 4, self.tables[1]), tuple(reversed(self.tables))):
            with self.subTest(fields=fields), self.assertRaises(ValueError):
                self.placed(fixture(BASE, self.tables, fields=fields, exports=self.exports))

    def test_export_arguments_reject_linker_qualifiers_and_aliases(self):
        for name in ("??_7UPolys,DATA@@6B@", "??_7UPolys=Other@@6B@", POLYS + ",NONAME",
                     "??_7U Polys@@6B@", "??_7U\tPolys@@6B@", POLYS + "\n", "_data"):
            with self.subTest(name=name), self.assertRaises(ValueError):
                vtable_export_args(dict(self.link, exported_vtables=[name]))

    def test_duplicate_manifest_or_pe_names_are_rejected(self):
        with self.assertRaises(ValueError):
            vtable_export_args(dict(self.link, exported_vtables=[POLYS, POLYS]))
        with self.assertRaises(ValueError):
            self.placed(fixture(BASE, self.tables, exports=self.exports + [(POLYS, self.tables[1])]))

    def test_missing_export_forwarder_and_invalid_ordinal_are_rejected(self):
        for target, ordinal in ((None, None), (FORWARDER_RVA, None), (self.tables[0], POLYS)):
            exports = [(MODEL, self.tables[1])]
            if target is not None:
                exports.append((POLYS, target))
            with self.subTest(target=target, ordinal=ordinal), self.assertRaises(ValueError):
                self.placed(fixture(BASE, self.tables, exports=exports, bad_ordinal=ordinal))

    def test_both_vtables_must_be_in_file_backed_read_only_data(self):
        tables = (0x1050, self.tables[1])
        with self.assertRaises(ValueError):
            self.placed(fixture(BASE, tables, exports=list(zip((POLYS, MODEL), tables))))
        bindings = copy.deepcopy(self.bindings)
        bindings[POLYS]["va"] = RETAIL_BASE + 0x1050
        with self.assertRaises(ValueError):
            self.placed(original=fixture(RETAIL_BASE, (0x1050, self.retail_tables[1])), bindings=bindings)

    def test_export_cannot_also_be_a_stub_or_have_a_fixed_address(self):
        for link in (dict(self.link, stubs=[POLYS]), dict(self.link, symbols={POLYS: BASE + self.tables[0]})):
            with self.subTest(link=link), self.assertRaises(ValueError):
                self.placed(link=link)

    def test_every_export_needs_its_own_absolute_field(self):
        for fields in ([self.link["fields"][0]], [[2, "rel32", POLYS], self.link["fields"][1]]):
            with self.subTest(fields=fields), self.assertRaises(ValueError):
                self.placed(link=dict(self.link, fields=fields))


class VtableSlotTests(unittest.TestCase):
    def setUp(self):
        self.retail_tables = (0x2024, 0x2058)
        self.original = slot_fixture(RETAIL_BASE, self.retail_tables)
        self.target = {"image": inspect(self.original)}
        self.tables = (0x2010, 0x2040)
        self.rebuilt = slot_fixture(BASE, self.tables, exported=True)
        self.link = {
            "roots": ["?driver@@YAXXZ"], "stubs": [],
            "rebuilt_offset": 0x200, "rebuilt_address": BASE + 0x1000,
            "exported_vtables": [POLYS, MODEL], "symbols": {METHOD: BASE + 0x1120},
            "vtable_slots": {SLOT: [POLYS, 9, METHOD]},
            "fields": [[2, "abs", POLYS], [9, "abs", MODEL], [15, "abs", SLOT]],
        }
        self.bindings = {
            POLYS: {"va": RETAIL_BASE + self.retail_tables[0], "basis": "fixture vtable"},
            MODEL: {"va": RETAIL_BASE + self.retail_tables[1], "basis": "fixture vtable"},
            METHOD: {"va": RETAIL_BASE + 0x1120, "basis": "fixture virtual method"},
            SLOT: {"va": RETAIL_BASE + self.retail_tables[0] + 36, "basis": "fixture virtual slot"},
        }

    def placed(self, *, rebuilt=None, original=None, link=None, bindings=None):
        unit = {"offset": 0x200, "size": 20, "ltcg_link": self.link if link is None else link,
                "link_bindings": self.bindings if bindings is None else bindings}
        return built_unit_bytes(self.target, unit, self.rebuilt if rebuilt is None else rebuilt,
                                self.original if original is None else original)

    def test_slot_rebases_with_the_export_and_checks_the_method_on_both_sides(self):
        for tables in (self.tables, tuple(reversed(self.tables))):
            with self.subTest(tables=tables):
                rebuilt = slot_fixture(BASE, tables, exported=True)
                self.assertEqual(self.placed(rebuilt=rebuilt), self.original[0x200:0x214])
        with self.assertRaises(ValueError):
            self.placed(rebuilt=slot_fixture(BASE, self.tables, exported=True, method=0x1110))
        with self.assertRaises(ValueError):
            self.placed(original=slot_fixture(RETAIL_BASE, self.retail_tables, method=0x1110))

    def test_wrong_slot_index_table_or_method_name_is_rejected(self):
        other = "?Other@@YAXXZ"
        symbols = {**self.link["symbols"], other: BASE + 0x1110}
        bindings = {**self.bindings, other: {"va": RETAIL_BASE + 0x1110, "basis": "second fixture method"}}
        for entry in ([POLYS, 8, METHOD], [MODEL, 9, METHOD], [POLYS, 9, other]):
            with self.subTest(entry=entry), self.assertRaises(ValueError):
                self.placed(link=dict(self.link, symbols=symbols, vtable_slots={SLOT: entry}), bindings=bindings)

    def test_method_requires_a_known_rebuilt_address_and_retail_binding(self):
        with self.assertRaises(ValueError):
            self.placed(link=dict(self.link, symbols={}))
        with self.assertRaises(ValueError):
            self.placed(bindings={name: binding for name, binding in self.bindings.items() if name != METHOD})

    def test_slot_requires_the_recorded_retail_address_and_uses_no_fixed_rebuilt_address(self):
        for va in (None, self.bindings[SLOT]["va"] - 4):
            bindings = copy.deepcopy(self.bindings)
            if va is None:
                del bindings[SLOT]
            else:
                bindings[SLOT]["va"] = va
            with self.subTest(va=va), self.assertRaises(ValueError):
                self.placed(bindings=bindings)
        with self.assertRaises(ValueError):
            self.placed(link=dict(self.link, symbols={**self.link["symbols"], SLOT: BASE + self.tables[0] + 36}))
        with self.assertRaises(ValueError):
            self.placed(rebuilt=slot_fixture(BASE, self.tables, exported=True, operand=self.tables[0] + 32))

    def test_slot_cannot_also_be_a_linker_stub(self):
        with self.assertRaises(ValueError):
            self.placed(link=dict(self.link, stubs=[SLOT]))

    def test_slot_cannot_reach_or_pass_another_known_vtable(self):
        # In each case the slot still contains the right executable method on both sides.
        # Its offset reaches the other vtable's first slot, or falls one entry inside it.
        for side in ("rebuilt", "retail"):
            for other_table in ("exported", "fixed"):
                for distance in (36, 32):
                    with self.subTest(side=side, other_table=other_table, distance=distance):
                        built_tables, retail_tables = self.tables, self.retail_tables
                        if side == "rebuilt":
                            built_tables = (built_tables[0], built_tables[0] + distance)
                        else:
                            retail_tables = (retail_tables[0], retail_tables[0] + distance)
                        bindings = copy.deepcopy(self.bindings)
                        bindings[MODEL]["va"] = RETAIL_BASE + retail_tables[1]
                        link = copy.deepcopy(self.link)
                        if other_table == "fixed":
                            link["exported_vtables"].remove(MODEL)
                            link["symbols"][MODEL] = BASE + built_tables[1]
                        with self.assertRaises(ValueError):
                            self.placed(rebuilt=slot_fixture(BASE, built_tables, exported=True),
                                        original=slot_fixture(RETAIL_BASE, retail_tables),
                                        link=link, bindings=bindings)


if __name__ == "__main__":
    unittest.main()
