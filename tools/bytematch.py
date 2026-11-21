"""Export strict, source-backed matching totals using objdiff's v2 report format."""

import argparse
from pathlib import Path
import re

from progress import EDITIONS, ROOT, summary, write
from manifests import load_target


def byte_measures(total, matched):
    return dict(total_code=str(total), matched_code=str(matched),
                matched_code_percent=100 * matched / total if total else 0)


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
    totals = {key: [0, 0] for key in CATEGORIES}
    for unit in target["units"]:
        size = unit["size"]
        verified = "match" in unit and unit.get("recipe_evidence") is not None
        measures = byte_measures(size, size if verified else 0)
        measures.update(total_functions=1, matched_functions=int(verified))
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
        units.append(dict(name=f'{folder.name}/{stem}/{unit["id"]}', measures=measures, functions=[function],
                          metadata=dict(source_path=f"{folder.name}/{source}", complete=verified,
                                        progress_categories=[category])))
        described += size
    remainder = counts["total_bytes"] - described
    if remainder:
        # Code not yet assigned to a unit is counted as game code until it is identified.
        units.append(dict(name=f"{folder.name}/unmapped-code", measures=byte_measures(remainder, 0),
                          metadata=dict(progress_categories=["game"])))
        totals["game"][0] += remainder
    return dict(version=2, measures=byte_measures(counts["total_bytes"], counts["matched_bytes"]),
                units=units, categories=[dict(id=key, name=name, measures=byte_measures(*totals[key]))
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
