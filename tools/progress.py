"""Create reproducible, per-executable matching reports using Python's standard library."""

import argparse
import hashlib
import json
from pathlib import Path
import re
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from images import coff_symbol_offset, file_pe_data, initialized_pe_data, inspect, readonly_pe_data, span
from link_image import place_function
from link_coff_switch_tail import link_switch_tail, switch_tail_site
from link_box_face_cursor import box_face_export_args, resolve_box_face_cursor
from link_interior_objects import resolve_interior_objects
from link_vtable_exports import resolve_vtable_exports, vtable_export_args
from link_writable_strings import check_writable_strings
from link_case_selectors import check_case_selectors
from link_coff_strings import coff_string_spec, link_coff_strings
from link_x86 import link_function
from link_coff_rtti_vtables import check_rtti_spec, link_rtti_function
from manifests import load_target, save_receipt


ROOT = Path(__file__).resolve().parents[1]
EDITIONS = ("ps2", "pc")


def encoded(obj):
    return json.dumps(obj, indent=2, ensure_ascii=False) + "\n"


def write(path, value):
    path.write_text(encoded(value), encoding="utf-8", newline="\n")


def identity(value):
    if not isinstance(value, str) or not re.fullmatch("[a-z0-9][a-z0-9-]*", value):
        raise ValueError(f"invalid identifier: {value!r}")
    return value


def digest(value):
    if not isinstance(value, str) or not re.fullmatch("[a-f0-9]{64}", value):
        raise ValueError("expected a lowercase SHA-256 digest")
    return value


def spans(records, limit):
    ordered = sorted(span(r["offset"], r["size"], limit) for r in records)
    if any(a[1] > b[0] for a, b in zip(ordered, ordered[1:])):
        raise ValueError("overlapping ranges would double count progress")
    return ordered


def contains(ranges, bounds):
    return any(begin <= bounds[0] and bounds[1] <= end for begin, end in ranges)


def named_callees(unit):
    """The unit IDs that a unit's ltcg_callees field names, validated; empty when it has no field."""
    if "ltcg_callees" not in unit:
        return []
    named = unit["ltcg_callees"]
    if "ltcg_link" not in unit:
        raise ValueError(f"{unit['id']}: ltcg_callees needs an ltcg_link record")
    if (not isinstance(named, list) or not named or len(set(named)) != len(named)
            or not all(isinstance(identifier, str) and identifier for identifier in named)):
        raise ValueError(f"{unit['id']}: ltcg_callees must be a non-empty list of distinct unit IDs")
    return named


def ordered_object_units(unit, callees):
    """Order and coalesce named LTCG translation units only when the receipt requests it."""
    records = [unit, *callees]
    link = unit.get("ltcg_link", {})
    if "object_order" not in link:
        return records
    order = link["object_order"]
    by_id = {record["id"]: record for record in records}
    if (not callees or not isinstance(order, list)
            or not all(isinstance(identifier, str) for identifier in order)
            or len(order) != len(by_id) or set(order) != set(by_id)):
        raise ValueError(f"{unit['id']}: object_order must name every unit in the link exactly once")

    result, seen = [], set()
    for identifier in order:
        record = by_id[identifier]
        headers = record.get("system_headers")
        recipe = (record["toolchain"], record["build_command"], tuple(sorted(record["inputs"])),
                  None if headers is None else tuple(sorted(headers.items())))
        if recipe not in seen:
            seen.add(recipe)
            result.append(record)
    return result


def context_objects(owner):
    """Return independently compiled source objects that receive no matching credit."""
    if "ltcg_context" not in owner:
        return []
    entries = owner["ltcg_context"]
    if "ltcg_link" not in owner or not isinstance(entries, list) or not entries:
        raise ValueError(f"{owner['id']}: ltcg_context needs an LTCG link and at least one object")
    result = []
    for entry in entries:
        required = {"id", "inputs", "build_command"}
        if (not isinstance(entry, dict) or not required <= entry.keys()
                or entry.keys() - required - {"system_headers"}):
            raise ValueError(f"{owner['id']}: each context object needs id, inputs and build_command")
        identifier = identity(entry["id"])
        inputs = entry["inputs"]
        if (not isinstance(inputs, list) or not all(isinstance(path, str) for path in inputs)
                or not any(Path(path).suffix.lower() in (".c", ".cpp") for path in inputs)
                or not set(inputs) <= set(owner["inputs"])):
            raise ValueError(f"{identifier}: context source and headers must be listed in the owning unit's inputs")
        if not isinstance(entry["build_command"], str) or not entry["build_command"].strip():
            raise ValueError(f"{identifier}: a context object needs a compile command")
        result.append(dict(entry, toolchain=owner["toolchain"]))
    return result


def callee_units(units, unit):
    """The objects for one LTCG link, including transitive callees and their source context.

    Each callee is built with link-time code generation by the unit's own compiler, so the link
    decides every calling convention between the units. A callee must carry /GL in its recorded
    command and name the same toolchain, and a unit cannot be its own callee."""
    if not named_callees(unit) and "ltcg_context" not in unit:
        ordered_object_units(unit, [])
        return []
    by_id = {u["id"]: u for u in units}
    closure, seen, pending = [], {unit["id"]}, [unit]
    while pending:
        owner = pending.pop(0)
        for identifier in named_callees(owner):
            if identifier == unit["id"]:
                raise ValueError(f"{unit['id']}: a callee names this unit")
            if identifier in seen:
                continue
            seen.add(identifier)
            callee = by_id.get(identifier)
            if callee is None:
                raise ValueError(f"{unit['id']}: unknown callee unit {identifier}")
            if "/GL" not in callee["build_command"].split():
                raise ValueError(f"{unit['id']}: callee {identifier} is not built with /GL")
            if callee["toolchain"] != unit["toolchain"]:
                raise ValueError(f"{unit['id']}: callee {identifier} names another compiler")
            closure.append(callee)
            pending.append(callee)
    for owner in [unit, *closure]:
        for context in context_objects(owner):
            identifier = context["id"]
            if identifier in by_id or identifier in seen:
                raise ValueError(f"{unit['id']}: context object ID {identifier} collides with another object")
            seen.add(identifier)
            closure.append(context)
    ordered_object_units(unit, closure)
    return closure


def inputs_digest(folder, unit, image_hash, file_cache=None, callees=()):
    """The fingerprint of a unit's inputs. A unit linked with callees also binds theirs."""
    if file_cache is None:
        file_cache = {}
    inputs = unit["inputs"]
    if not isinstance(inputs, list) or not any(Path(p).suffix.lower() in (".c", ".cpp") for p in inputs):
        raise ValueError("a matching unit requires its independently written C or C++ source")
    if not unit["toolchain"].strip() or not unit["build_command"].strip():
        raise ValueError("record the compiler version and reproducible build command")
    headers = unit.get("system_headers")
    if headers is not None:
        # The toolchain's own headers that the compile reads, by path under its include folder.
        # They are not project files, so the record carries their hashes and the recipe binds them.
        if not isinstance(headers, dict) or not unit["toolchain"].startswith("Microsoft C/C++ "):
            raise ValueError("system_headers maps a Microsoft C/C++ unit's headers to their SHA-256")
        for relative, value in headers.items():
            parts = relative.split("/")
            if not relative or "\\" in relative or ":" in relative or any(p in ("", ".", "..") for p in parts):
                raise ValueError(f"invalid system header path: {relative!r}")
            digest(value)
    evidence = unit.get("recipe_evidence")
    if evidence is not None:
        if (evidence["compiler"] != unit["toolchain"] or not isinstance(evidence["flags"], list)
                or not all(isinstance(flag, str) and flag for flag in evidence["flags"])):
            raise ValueError("record the original compiler and flags for this unit")
        if not set(evidence["flags"]) <= set(unit["build_command"].split()):
            raise ValueError("evidence flags must appear in the unit's build command")
        # When the original compiler build is unavailable, the note may establish that the
        # compiler used here generates the same code; it names the original separately.
        original = evidence.get("original_compiler")
        if original is not None and (type(original) is not str or not original.strip()
                                     or original == evidence["compiler"]):
            raise ValueError("name a different original compiler, or leave it out")
        basis = evidence["basis"]
        if Path(basis).suffix.lower() != ".md":
            raise ValueError("original compiler and flag evidence requires a reviewed Markdown note")
        inputs = [*inputs, basis]
    fingerprints = {}
    for relative in sorted(inputs):
        if relative not in file_cache:
            path = (folder / relative).resolve()
            if not path.is_relative_to(folder.resolve()) or Path(relative).is_absolute():
                raise ValueError("build inputs must be project-relative")
            data = path.read_bytes().replace(b"\r\n", b"\n")
            file_cache[relative] = (hashlib.sha256(data).hexdigest(), bool(data.strip()))
        fingerprint, nonempty = file_cache[relative]
        if evidence and relative == evidence["basis"] and not nonempty:
            raise ValueError("original compiler and flag evidence is empty")
        fingerprints[relative] = fingerprint
    recipe = {k: v for k, v in unit.items() if k != "match"}
    if "coff_private_strings" in unit or "coff_readonly_strings" in unit:
        coff_string_spec(unit)
    if "coff_rtti_vtable" in unit:
        check_rtti_spec(unit)
    if "coff_switch_tail" in unit:
        switch_tail_site(unit)
    if "link_bindings" in unit:
        linker = Path(__file__).with_name("link_image.py" if "ltcg_link" in unit else "link_x86.py")
        validators = [linker]
        if "coff_private_strings" in unit or "coff_readonly_strings" in unit:
            validators.append(linker.with_name("link_coff_strings.py"))
        if "coff_rtti_vtable" in unit:
            validators.append(linker.with_name("link_coff_rtti_vtables.py"))
        if "coff_switch_tail" in unit:
            validators.append(linker.with_name("link_coff_switch_tail.py"))
        if "writable_strings" in unit.get("ltcg_link", {}):
            validators.append(linker.with_name("link_writable_strings.py"))
        if "case_selectors" in unit.get("ltcg_link", {}):
            validators.append(linker.with_name("link_case_selectors.py"))
        if "box_face_cursor" in unit.get("ltcg_link", {}):
            box_face_export_args(unit["ltcg_link"])
            validators.extend(linker.with_name(name) for name in
                              ("link_box_face_cursor.py", "link_vtable_exports.py", "images.py"))
        if "interior_objects" in unit.get("ltcg_link", {}):
            validators.append(linker.with_name("link_interior_objects.py"))
        if {"exported_vtables", "vtable_slots"}.intersection(unit.get("ltcg_link", {})):
            vtable_export_args(unit["ltcg_link"])
            validators.append(linker.with_name("link_vtable_exports.py"))
        for validator in validators:
            if validator not in file_cache:
                file_cache[validator] = hashlib.sha256(validator.read_bytes().replace(b"\r\n", b"\n")).hexdigest()
            fingerprints["tools/" + validator.name] = file_cache[validator]
    payload = json.dumps([image_hash, recipe, fingerprints], sort_keys=True).encode()
    if callees:
        # The unit's bytes come from the callees' sources and recipes too, so they are bound as well.
        callee_digests = [inputs_digest(folder, callee, image_hash, file_cache) for callee in callees]
        payload = json.dumps([image_hash, recipe, fingerprints, callee_digests], sort_keys=True).encode()
    return hashlib.sha256(payload).hexdigest()


def summary(folder, target):
    image = target["image"]
    image_hash = digest(image["sha256"])
    expected_format = {"pc": "pe32-x86", "ps2": "elf32-mipsel"}[folder.name]
    if image["format"] != expected_format:
        raise ValueError("image format belongs to another edition")
    all_sections = image["executable_sections"]
    executable = spans(all_sections, image["size"])
    if not executable or any(type(s["code"]) is not bool for s in all_sections):
        raise ValueError("invalid executable-section inventory")
    code = spans([s for s in all_sections if s["code"]], image["size"])
    # RWX sections on the PS2 discs combine code and data. A reviewed range map
    # can replace section inference once all the code in the image is identified.
    complete = bool(code) and (folder.name == "pc" or all(s["code"] for s in all_sections))
    if "code_map" in target:
        mapped = target["code_map"]
        code = spans(mapped["ranges"], image["size"])
        if not code or not mapped["basis"].strip() or not all(contains(executable, r) for r in code):
            raise ValueError("code map needs evidence and file-backed executable ranges")
        complete = True
    total = sum(end - begin for begin, end in code) if complete else None
    units = target["units"]
    ranges = spans(units, image["size"])
    if not all(contains(code if complete else executable, r) for r in ranges):
        raise ValueError("unit outside the target's measured code or executable sections")
    if len({identity(u["id"]) for u in units}) != len(units):
        raise ValueError("duplicate unit id")
    matched_bytes = matched_units = candidate_bytes = candidate_units = 0
    file_cache = {}
    for unit in units:
        if "rebuilt_symbol" in unit:
            if "rebuilt_offset" in unit or not unit["rebuilt_symbol"]:
                raise ValueError("choose one rebuilt artifact location")
        elif type(unit.get("rebuilt_offset")) is not int or unit["rebuilt_offset"] < 0:
            raise ValueError("missing or invalid rebuilt offset")
        if "rebuilt_storage_class" in unit:
            if (type(unit["rebuilt_storage_class"]) is not int or unit["rebuilt_storage_class"] != 3
                    or "rebuilt_symbol" not in unit or "link_bindings" in unit
                    or "ltcg_link" in unit or "coff_alignment" in unit):
                raise ValueError("private COFF receipts require one named, unlinked function symbol")
        signature = inputs_digest(folder, unit, image_hash, file_cache, callee_units(units, unit))
        if "match" in unit:
            if unit["match"]["inputs_sha256"] != signature:
                raise ValueError(f"{unit['id']}: changed build inputs; reverify this unit")
            digest(unit["match"]["bytes_sha256"])
            if unit.get("recipe_evidence") is not None:
                matched_bytes += unit["size"]
                matched_units += 1
            else:
                candidate_bytes += unit["size"]
                candidate_units += 1
    return dict(id=identity(target["id"]), label=target["label"], scope=target["scope"],
                sha256=image_hash, matched_bytes=matched_bytes, total_bytes=total,
                matched_units=matched_units, candidate_bytes=candidate_bytes, candidate_units=candidate_units,
                percent=round(100 * matched_bytes / total, 6) if total else None,
                evidence=f"{folder.name}/config/{target['id']}.json")


def report(root):
    editions = []
    for edition in EDITIONS:
        folder = root / edition
        targets = []
        for path in sorted((folder / "config").glob("*.json")):
            target = load_target(path)
            if target["id"] != path.stem:
                raise ValueError(f"target id differs from filename: {path}")
            targets.append(summary(folder, target))
        stage = "Awaiting a reference executable"
        if targets:
            started = any(t["matched_units"] or t["candidate_units"] for t in targets)
            stage = "Matching in progress" if started else "Reference builds identified"
        editions.append(dict(id=edition, stage=stage, targets=targets))
    return dict(schema_version=1, editions=editions)


def verify(target, original):
    data = original.read_bytes()
    if inspect(data) != target["image"]:
        raise ValueError("reference binary differs from the locked build")
    for unit in target["units"]:
        if "match" in unit:
            start, end = span(unit["offset"], unit["size"], len(data))
            if hashlib.sha256(data[start:end]).hexdigest() != unit["match"]["bytes_sha256"]:
                raise ValueError(f"{unit['id']}: receipt differs from retail")
    return data


def built_unit_bytes(target, unit, output, original=None):
    """Obtain the complete function at its specified position in the linked image."""
    if "coff_private_strings" in unit or "coff_readonly_strings" in unit:
        coff_string_spec(unit)
    if "coff_rtti_vtable" in unit:
        check_rtti_spec(unit)
        if original is None:
            raise ValueError("COFF RTTI verification needs the retail image")
    if "coff_switch_tail" in unit:
        switch_tail_site(unit)
    if "rebuilt_storage_class" in unit:
        if (type(unit["rebuilt_storage_class"]) is not int or unit["rebuilt_storage_class"] != 3
                or "rebuilt_symbol" not in unit or "link_bindings" in unit
                or "ltcg_link" in unit or "coff_alignment" in unit):
            raise ValueError("private COFF receipts require one named, unlinked function symbol")
    if "ltcg_link" in unit:
        # The rebuilt artifact is a DLL linked with link-time code generation.
        if original is None or "link_bindings" not in unit or "coff_alignment" in unit:
            raise ValueError("an LTCG unit needs link bindings and the retail image")
        a, b = span(unit["offset"], unit["size"], len(original))
        for s in target["image"]["executable_sections"]:
            if s["code"] and s["offset"] <= a < b <= s["offset"] + s["size"]:
                link, bindings = unit["ltcg_link"], unit["link_bindings"]
                if "exported_vtables" in link or "vtable_slots" in link:
                    link = resolve_vtable_exports(output, original, link, bindings)
                address = s["address"] + a - s["offset"]
                if "box_face_cursor" in link:
                    link, bindings = resolve_box_face_cursor(output, original, unit["size"], address, link, bindings)
                if "interior_objects" in link:
                    link, bindings = resolve_interior_objects(output, original, link, bindings)
                if "writable_strings" in link:
                    check_writable_strings(output, original, link, bindings)
                if "case_selectors" in link:
                    check_case_selectors(output, original, unit["size"], address, link, bindings)
                return place_function(output, unit["size"], address, link, bindings,
                                      read_constant=lambda va, size: readonly_pe_data(original, va, size),
                                      read_table=lambda va, size: file_pe_data(original, va, size))
        raise ValueError("link address outside a measured code section")
    readers = {}
    if original is not None and "link_bindings" in unit:
        readers = {
            "read_constant": lambda va, size: readonly_pe_data(original, va, size),
            "read_writable_string": lambda va, size: initialized_pe_data(original, va, size, writable=True),
        }
    if "coff_alignment" in unit:
        alignment = unit["coff_alignment"]
        if (type(alignment) is not int or alignment != 16 or original is None
                or "rebuilt_symbol" not in unit):
            raise ValueError("expected a 16-byte aligned COFF contribution and retail image")
        start, end = span(unit["offset"], unit["size"], len(original))
        for section in target["image"]["executable_sections"]:
            if section["code"] and section["offset"] <= start < end <= section["offset"] + section["size"]:
                address = section["address"] + start - section["offset"]
                tail = -(address + unit["size"]) % alignment
                if not tail or address % alignment or end + tail > section["offset"] + section["size"]:
                    raise ValueError("COFF alignment extends beyond the code section or has invalid bounds")
                length = unit["size"] + tail
                if "coff_private_strings" in unit or "coff_readonly_strings" in unit:
                    contribution = link_coff_strings(output, unit, length, address, original, **readers)
                elif "coff_rtti_vtable" in unit:
                    contribution = link_rtti_function(output, unit, length, address, original, **readers)
                elif "link_bindings" in unit:
                    contribution = link_function(output, unit["rebuilt_symbol"], length, address,
                                                 unit["link_bindings"], **readers)
                else:
                    offset = coff_symbol_offset(output, unit["rebuilt_symbol"], length)
                    contribution = output[offset:offset + length]
                following = contribution[unit["size"]:]
                if following != b"\x90" * tail or original[end:end + tail] != following:
                    raise ValueError("COFF alignment differs from retail padding")
                return contribution[:unit["size"]]
        raise ValueError("aligned function outside a measured code section")
    if "link_bindings" in unit:
        a, b = span(unit["offset"], unit["size"], target["image"]["size"])
        for s in target["image"]["executable_sections"]:
            if s["code"] and s["offset"] <= a < b <= s["offset"] + s["size"]:
                address = s["address"] + a - s["offset"]
                if "coff_private_strings" in unit or "coff_readonly_strings" in unit:
                    return link_coff_strings(output, unit, unit["size"], address, original, **readers)
                if "coff_switch_tail" in unit:
                    return link_switch_tail(output, unit, address, original, s["offset"] + s["size"], **readers)
                if "coff_rtti_vtable" in unit:
                    return link_rtti_function(output, unit, unit["size"], address, original, **readers)
                return link_function(output, unit["rebuilt_symbol"], unit["size"], address, unit["link_bindings"],
                                     **readers)
        raise ValueError("link address outside a measured code section")
    offset = (coff_symbol_offset(output, unit["rebuilt_symbol"], unit["size"],
                                 unit.get("rebuilt_storage_class", 2))
              if "rebuilt_symbol" in unit else unit["rebuilt_offset"])
    c, d = span(offset, unit["size"], len(output))
    return output[c:d]


def compare_unit(folder, target, unit, original, output):
    """Compare a complete built unit against an already verified reference image."""
    a, b = span(unit["offset"], unit["size"], len(original))
    body = built_unit_bytes(target, unit, output, original)
    if original[a:b] != body:
        raise ValueError(f"{unit['id']}: compiler output differs from retail")
    return dict(bytes_sha256=hashlib.sha256(body).hexdigest(),
                inputs_sha256=inputs_digest(folder, unit, target["image"]["sha256"],
                                            callees=callee_units(target["units"], unit)))


def match(folder, target, unit_id, retail, rebuilt):
    original = verify(target, retail)
    if retail.samefile(rebuilt):
        raise ValueError("supply the compiler/linker's output as the rebuilt artifact")
    unit = next((u for u in target["units"] if u["id"] == unit_id), None)
    if unit is None:
        raise ValueError(f"unknown unit: {unit_id}")
    unit["match"] = compare_unit(folder, target, unit, original, rebuilt.read_bytes())
    summary(folder, target)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    probe = commands.add_parser("identify", help="print an executable's hash and section inventory")
    probe.add_argument("file", type=Path)
    for name in ("verify", "match"):
        cmd = commands.add_parser(name, help="verify the reference baseline" if name == "verify"
                                  else "compare a compiled unit and record its exact match")
        cmd.add_argument("edition", choices=EDITIONS)
        cmd.add_argument("target", type=identity)
        cmd.add_argument("retail", type=Path)
        if name == "match":
            cmd.add_argument("unit", type=identity)
            cmd.add_argument("rebuilt", type=Path)
    generate = commands.add_parser("report", help="regenerate the public progress feed")
    generate.add_argument("--check", action="store_true", help="fail when the committed feed is stale")
    args = parser.parse_args()
    if args.command == "identify":
        print(encoded(inspect(args.file.read_bytes())), end="")
    elif args.command in ("verify", "match"):
        folder = ROOT / args.edition
        path = folder / "config" / (args.target + ".json")
        target = load_target(path)
        if args.command == "verify":
            verify(target, args.retail)
        else:
            match(folder, target, args.unit, args.retail, args.rebuilt)
            save_receipt(path, next(u for u in target["units"] if u["id"] == args.unit), write)
        print(f"Verified {target['label']}")
    else:
        feed = report(ROOT)
        path = ROOT / "reports" / "progress.json"
        if args.check:
            if path.read_text(encoding="utf-8") != encoded(feed):
                raise ValueError("stale report; run the report command")
            print("Progress feed is current.")
        else:
            write(path, feed)


if __name__ == "__main__":
    try:
        main()
    except (ValueError, KeyError, TypeError, OSError, struct.error) as error:
        sys.exit(f"Progress error: {error}")
