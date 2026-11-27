"""The ltcg_callees field: which units a unit links with, and which externals LINK.EXE leaves unresolved."""

import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "pc"))
import verify_build  # noqa: E402
from progress import ordered_object_units, callee_units  # noqa: E402

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


class ObjectOrderTests(unittest.TestCase):
    def setUp(self):
        self.a = unit("a", callees=["b", "c"])
        self.b = unit("b")
        self.c = unit("c", command=WITH_GL.replace("src/a.cpp", "src/c.cpp"))
        self.records = [self.a, self.b, self.c]

    def ordered(self):
        callees = callee_units(self.records, self.a)
        return [u["id"] for u in ordered_object_units(self.a, callees)]

    def test_default_preserves_every_record_and_the_primary_stays_first(self):
        self.assertEqual(self.ordered(), ["a", "b", "c"])

    def test_named_order_can_place_a_callee_first_and_link_each_compile_once(self):
        self.a["ltcg_link"]["object_order"] = ["c", "b", "a"]
        self.assertEqual(self.ordered(), ["c", "b"])

    def test_rejects_missing_unknown_repeated_or_nonstring_units(self):
        for order in ([], ["c", "b"], ["c", "b", "x"], ["a", "b", "b"], ["a", [], "c"]):
            with self.subTest(order=order), self.assertRaisesRegex(ValueError, "exactly once"):
                self.a["ltcg_link"]["object_order"] = order
                self.ordered()

    def test_rejects_order_on_a_standalone_unit(self):
        self.b["ltcg_link"]["object_order"] = ["b"]
        with self.assertRaisesRegex(ValueError, "exactly once"):
            callee_units(self.records, self.b)

    def test_each_compile_input_distinguishes_an_object(self):
        self.a["ltcg_link"]["object_order"] = ["c", "a", "b"]
        for field, value in (("inputs", ["src/a.cpp", "src/b.h"]),
                             ("build_command", WITH_GL.replace("/O2", "/O1")),
                             ("system_headers", {}), ("toolchain", "another compiler")):
            with self.subTest(field=field):
                changed = dict(self.b, **{field: value})
                self.assertEqual(ordered_object_units(self.a, [changed, self.c]),
                                 [self.c, self.a, changed])


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


class DiscoveryLinkTests(unittest.TestCase):
    def test_successful_forced_probe_supplies_source_and_compiler_externals_to_strict_link(self):
        from pathlib import Path
        from tempfile import TemporaryDirectory
        from unittest.mock import patch
        from subprocess import CompletedProcess

        output = ("caller.obj : error LNK2001: unresolved external symbol _external\n"
                  " CIL library( CIL module) : error LNK2001: unresolved external symbol __fltused\n")
        caller = unit("caller")
        caller["ltcg_link"]["stubs"] = ["_external"]
        with TemporaryDirectory() as directory:
            folder = Path(directory)
            with patch.object(verify_build.subprocess, "run", return_value=CompletedProcess([], 0, output)) as probe, \
                 patch.object(verify_build, "run_tool") as strict, \
                 patch.object(verify_build, "stub_object", return_value=b"stubs") as stub:
                verify_build.link_with_callees(caller, [], folder / "caller.obj", [], folder / "cl.exe",
                                               {}, folder, [])
                self.assertIn("/FORCE:UNRESOLVED", probe.call_args.args[0])
                stub.assert_called_once_with(["_external", "__fltused"])
                self.assertNotIn("/FORCE:UNRESOLVED", strict.call_args.args[0])
                self.assertIn(str(folder / "caller_stubs.obj"), strict.call_args.args[0])


class StubPlanTests(unittest.TestCase):
    def test_a_declared_external_is_stubbed_once(self):
        self.assertEqual(verify_build.stub_plan(["_a", "__fltused"], ["__fltused", "_a"]),
                         (["__fltused", "_a"], []))

    def test_fltused_is_stubbed_without_a_declaration(self):
        # A callee that uses floating point makes LINK.EXE report __fltused; no record declares it.
        self.assertEqual(verify_build.stub_plan(["__fltused"], []), (["__fltused"], []))

    def test_other_undeclared_externals_are_still_refused(self):
        self.assertEqual(verify_build.stub_plan(["?Foo@@YAXXZ", "__fltused"], []),
                         (["__fltused"], ["?Foo@@YAXXZ"]))

    def test_nothing_unresolved_needs_no_stub(self):
        self.assertEqual(verify_build.stub_plan([], ["_a"]), ([], []))


if __name__ == "__main__":
    unittest.main()
