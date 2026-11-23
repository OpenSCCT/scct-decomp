"""Read a target's inline units and optional edition-relative files of unit records."""

import json
from pathlib import Path


def groups(path, config):
    yield path, config["units"]
    edition = path.parent.parent.resolve()
    seen = {path.resolve()}
    for name in config.get("unit_files", []):
        relative = Path(name)
        file = (edition / relative).resolve()
        if (relative.is_absolute() or not file.is_relative_to(edition) or file.suffix != ".json"
                or file in seen):
            raise ValueError(f"invalid or repeated unit file: {name}")
        seen.add(file)
        rows = json.loads(file.read_text(encoding="utf-8"))
        if not isinstance(rows, list):
            raise ValueError(f"expected a list of units in {name}")
        yield file, rows


def load_target(path):
    config = json.loads(path.read_text(encoding="utf-8"))
    units = [u for _, rows in groups(path, config) for u in rows]
    return dict(config, units=sorted(units, key=lambda u: u["offset"]))


def save_receipt(path, unit, write):
    """Update the receipt in the file that owns this unit, preserving its neighbors."""
    config = json.loads(path.read_text(encoding="utf-8"))
    for file, rows in groups(path, config):
        for stored in rows:
            if stored["id"] != unit["id"]:
                continue
            if {k: v for k, v in stored.items() if k != "match"} != {k: v for k, v in unit.items() if k != "match"}:
                raise ValueError(f"{unit['id']}: unit definition changed during verification")
            stored["match"] = unit["match"]
            write(file, config if file == path else rows)
            return
    raise ValueError(f"unit missing while saving receipt: {unit['id']}")


def save_receipts(path, units, write, fields=("match",)):
    """Update many receipts at once, rewriting each owning file a single time.

    Only the named fields may differ from the stored unit; the verifier also records the
    system headers a unit's compile read."""
    config = json.loads(path.read_text(encoding="utf-8"))
    pending = {unit["id"]: unit for unit in units}
    for file, rows in groups(path, config):
        changed = False
        for stored in rows:
            unit = pending.pop(stored["id"], None)
            if unit is None:
                continue
            if ({k: v for k, v in stored.items() if k not in fields}
                    != {k: v for k, v in unit.items() if k not in fields}):
                raise ValueError(f"{unit['id']}: unit definition changed during verification")
            for field in fields:
                if field in unit and stored.get(field) != unit[field]:
                    stored[field] = unit[field]
                    changed = True
        if changed:
            write(file, config if file == path else rows)
    if pending:
        raise ValueError(f"unit missing while saving receipt: {sorted(pending)[0]}")
