"""Export strict, source-backed matching totals using objdiff's v2 report format."""

import argparse
from pathlib import Path
import re

from function_map import load as load_function_map, unmatched_functions
from progress import EDITIONS, ROOT, summary, write
from manifests import load_target


def code_measures(total, matched, functions=0, matched_functions=0):
    return dict(total_code=str(total), matched_code=str(matched),
                matched_code_percent=100 * matched / total if total else 0,
                total_functions=functions, matched_functions=matched_functions,
                matched_functions_percent=100 * matched_functions / functions if functions else 0)


CATEGORIES = {"game": "Game code", "runtime": "C runtime library"}


def source_name(symbol):
    """The C name behind an x86 decorated symbol; C++ mangled names are left to the reader."""
    match = re.fullmatch(r"[_@]?([A-Za-z_$][\w$]*)(?:@\d+)?", symbol)
    return match[1] if match and not symbol.startswith("?") else None


def virtual_address(target, offset):
    for section in target["image"]["executable_sections"]:
        if section["offset"] <= offset < section["offset"] + section["size"]:
            return section["address"] + offset - section["offset"]
    raise ValueError("unit outside the executable sections")


def build_report(folder, target):
    counts = summary(folder, target)
    if counts["total_bytes"] is None:
        raise ValueError("This image has no measured code denominator yet")
    units = []
    described = 0
    totals = {key: [0, 0, 0, 0] for key in CATEGORIES}
    for unit in target["units"]:
        size = unit["size"]
        verified = "match" in unit and unit.get("recipe_evidence") is not None
        measures = code_measures(size, size if verified else 0, 1, int(verified))
        source = next(path for path in unit["inputs"] if path.lower().endswith((".c", ".cpp")))
        symbol = unit.get("rebuilt_symbol", unit["id"])
        details = dict(virtual_address=str(virtual_address(target, unit["offset"])))
        if source_name(symbol) and source_name(symbol) != symbol:
            details["demangled_name"] = source_name(symbol)
        function = dict(name=symbol, size=str(size), fuzzy_match_percent=100 if verified else 0, metadata=details)
        # Units are grouped by the source file that rebuilds them, as the map draws folders.
        stem = Path(source).stem
        category = "runtime" if stem.startswith("crt_") else "game"
        totals[category][0] += size
        totals[category][1] += size if verified else 0
        totals[category][2] += 1
        totals[category][3] += int(verified)
        units.append(dict(name=f'{folder.name}/{stem}/{unit["id"]}', measures=measures, functions=[function],
                          metadata=dict(source_path=f"{folder.name}/{source}", complete=verified,
                                        progress_categories=[category])))
        described += size
    remainder = counts["total_bytes"] - described
    function_map = folder / "function_maps" / f'{target["id"]}.txt'
    if remainder and function_map.is_file():
        # Unmatched code is drawn function by function, from the analysis map.
        code = [(s["offset"], s["offset"] + s["size"]) for s in target["image"]["executable_sections"] if s["code"]]
        spans = [(u["offset"], u["offset"] + u["size"]) for u in target["units"]]
        pending, leftover = unmatched_functions(target["image"]["size"], code, spans,
                                                load_function_map(function_map, target["image"]["sha256"]),
                                                address=lambda offset: virtual_address(target, offset))
        for entry, size in pending:
            address = virtual_address(target, entry)
            function = dict(name=f"fun_{address:08x}", size=str(size), fuzzy_match_percent=0,
                            metadata=dict(virtual_address=str(address)))
            measures = code_measures(size, 0, 1, 0)
            units.append(dict(name=f"{folder.name}/not-started/{address & ~0xFFFF:08x}/fun_{address:08x}",
                              measures=measures, functions=[function],
                              metadata=dict(complete=False, progress_categories=["game"])))
            totals["game"][0] += size
            totals["game"][2] += 1
            remainder -= size
        # Code that neither a unit nor a mapped function covers (alignment, unanalysed code)
        # is drawn as one tile per 64 KB of address space.
        for start, _, size in leftover:
            address = virtual_address(target, start)
            measures = code_measures(size, 0)
            units.append(dict(name=f"{folder.name}/not-started/{address & ~0xFFFF:08x}/unassigned",
                              measures=measures, metadata=dict(complete=False, progress_categories=["game"])))
            totals["game"][0] += size
            remainder -= size
        if remainder:
            raise ValueError("function map accounting differs from the measured code")
    if remainder:
        # Code no unit or mapped function covers is counted as game code until it is identified.
        units.append(dict(name=f"{folder.name}/unmapped-code", measures=code_measures(remainder, 0),
                          metadata=dict(progress_categories=["game"])))
        totals["game"][0] += remainder
    total_functions = sum(total[2] for total in totals.values())
    matched_functions = sum(total[3] for total in totals.values())
    return dict(version=2,
                measures=code_measures(counts["total_bytes"], counts["matched_bytes"],
                                       total_functions, matched_functions),
                units=units, categories=[dict(id=key, name=name, measures=code_measures(*totals[key]))
                                         for key, name in CATEGORIES.items()])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("edition", choices=EDITIONS)
    parser.add_argument("target")
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    folder = ROOT / args.edition
    inputs = {path.stem: path for path in (folder / "config").glob("*.json")}
    if args.target not in inputs:
        parser.error("unknown target")
    result = build_report(folder, load_target(inputs[args.target]))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    write(args.output, result)
