"""The ltcg_callees field: which units a unit links with, and which externals LINK.EXE leaves unresolved."""

import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "pc"))
import verify_build  # noqa: E402
from progress import callee_units  # noqa: E402

TOOLCHAIN = "Microsoft C/C++ 13.00.9466 for x86"
WITH_GL = "cl /nologo /O2 /Gy /GL /c /Folocal/a.obj src/a.cpp"
WITHOUT_GL = "cl /nologo /O2 /Gy /c /Folocal/a.obj src/a.cpp"


def unit(identifier, *, callees=None, command=WITH_GL, toolchain=TOOLCHAIN, link=True):
    record = {"id": identifier, "toolchain": toolchain, "build_command": command,
              "inputs": ["src/a.cpp"], "rebuilt_symbol": "?a@@YAXXZ"}
    if link:
        record["ltcg_link"] = {"roots": ["?driver@@YAXXZ"], "stubs": []}
    if callees is not None:
        record["ltcg_callees"] = callees
    return record


class CalleeUnitTests(unittest.TestCase):
    def test_a_unit_without_the_field_links_alone(self):
        caller = unit("a")
        self.assertEqual(callee_units([caller], caller), [])

    def test_callees_follow_in_the_order_named_then_their_own(self):
        a = unit("a", callees=["b", "c"])
        units = [a, unit("b", callees=["d"]), unit("c"), unit("d")]
        self.assertEqual([u["id"] for u in callee_units(units, a)], ["b", "c", "d"])

    def test_invalid_fields_are_rejected(self):
        cases = {
            "unknown callee": ([unit("a", callees=["x"])], "unknown callee unit x"),
            "callee without /GL": ([unit("a", callees=["b"]), unit("b", command=WITHOUT_GL)],
                                   "not built with /GL"),
            "callee on another compiler": ([unit("a", callees=["b"]),
                                            unit("b", toolchain="Microsoft C/C++ 13.10.3052 for x86")],
                                           "names another compiler"),
            "unit names itself": ([unit("a", callees=["b"]), unit("b", callees=["a"])],
                                  "a callee names this unit"),
            "no ltcg_link record": ([unit("a", callees=["b"], link=False), unit("b")],
                                    "needs an ltcg_link record"),
            "empty list": ([unit("a", callees=[])], "non-empty list"),
            "repeated ID": ([unit("a", callees=["b", "b"]), unit("b")], "distinct"),
        }
        for label, (units, message) in cases.items():
            with self.subTest(label):
                with self.assertRaisesRegex(ValueError, message):
                    callee_units(units, units[0])


class UnresolvedExternalTests(unittest.TestCase):
    def test_names_come_from_the_link_messages(self):
        output = (
            'versus_probe_obj : error LNK2001: unresolved external symbol "void __cdecl Escape(void *)" '
            "(?Escape@@YAXPAX@Z)\n"
            'versus_probe_obj : error LNK2001: unresolved external symbol "unsigned short * ProbeBuffer" '
            "(?ProbeBuffer@@3PAGA)\n"
            "helper_obj : error LNK2001: unresolved external symbol _appMemcpy\n"
            "helper_obj : error LNK2001: unresolved external symbol __imp__wcslen\n"
            "other_obj : error LNK2019: unresolved external symbol ?Foo@@YAXXZ referenced in function _Bar\n"
            "LINK : fatal error LNK1120: 5 unresolved externals\n"
        )
        self.assertEqual(verify_build.unresolved_externals(output),
                         ["?Escape@@YAXPAX@Z", "?ProbeBuffer@@3PAGA", "_appMemcpy", "__imp__wcslen", "?Foo@@YAXXZ"])

    def test_a_clean_link_has_no_unresolved_externals(self):
        self.assertEqual(verify_build.unresolved_externals("Generating code\nFinished generating code\n"), [])


if __name__ == "__main__":
    unittest.main()
