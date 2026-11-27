"""Verify the additional exception records and writable globals of FStats::Render.

Run python pc/evidence/versus_stats_render_eh.py STEAM_ROOT --cl PATH_TO_CL.
Code coverage comes from the normal function receipt. These checks also cover the
compiler's separately emitted cleanup functions and the associated static data.
"""

import argparse
import os
from pathlib import Path
import re
import struct
import sys
import tempfile

PC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PC))
import verify_build as vb
from link_image import _file_offset, _sections
from images import readonly_pe_data


def require(condition, message):
    if not condition:
        raise ValueError(message)


def code_bytes(image, address, length):
    pos, flags = _file_offset(image, address, length)
    require(flags & 0xe0000020 == 0x60000020, "expected read-only executable code")
    return image[pos:pos + length]


def relative_target(code, address, site):
    require(code[site] == 0xe9, "expected a direct tail jump")
    return address + site + 5 + struct.unpack_from("<i", code, site + 1)[0]


def cleanup_table(image, render, destructor, runtime):
    # The VC7 compiler installs a function-specific handler before reserving locals.
    prologue = code_bytes(image, render, 13)
    require(prologue[:9] == bytes.fromhex("55 8b ec 83 e4 f8 6a ff 68"), "unexpected renderer prologue")
    handler, = struct.unpack_from("<I", prologue, 9)
    stub = code_bytes(image, handler, 10)
    require(stub[0] == 0xb8 and relative_target(stub, handler, 5) == runtime, "unexpected frame handler")
    metadata, = struct.unpack_from("<I", stub, 1)
    info = struct.unpack("<8I", readonly_pe_data(image, metadata, 32))
    magic, count, table = info[:3]
    require(magic == 0x19930520 and count == 250 and info[3:] == (0, 0, 0, 0, 0xffffffff),
            "unexpected C++ exception data for the renderer")

    items = list(struct.iter_unpack("<iI", readonly_pe_data(image, table, 8 * count)))
    first = items[0][1]
    following = first
    result = []
    for index, (state, address) in enumerate(items):
        require(-1 <= state < index and address == following, "invalid cleanup state or function boundary")
        # Each cleanup computes the address of an FString local in EBP's frame,
        # then tail-calls FString::~FString. Both stack displacement widths occur.
        op = code_bytes(image, address, 2)
        require(op in (b"\x8d\x4d", b"\x8d\x8d"), "unexpected cleanup receiver")
        lea_size = 3 if op[1] == 0x4d else 6
        body = code_bytes(image, address, lea_size + 5)
        require(relative_target(body, address, lea_size) == destructor, "cleanup calls the wrong destructor")
        result.append((state, address - first, body[:lea_size]))
        following = address + len(body)
    require(following == handler and handler - first == 2723, "unexpected cleanup code extent")
    return handler, result


def writable_value(image, address, size):
    base, sections = _sections(image)
    for rva, length, raw, raw_size, flags in sections:
        offset = address - base - rva
        if 0 <= offset and offset + size <= length and flags & 0xe0000000 == 0xc0000000:
            backed = max(0, min(size, raw_size - offset))
            return image[raw + offset:raw + offset + backed] + bytes(size - backed)
    raise ValueError("expected writable storage for a stats global")


def verify_owners(rebuilt, retail, unit, symbols, target):
    render = unit["rebuilt_symbol"]
    destructor = "??1FString@@QAE@XZ"
    runtime = "___CxxFrameHandler"
    link, bindings = unit["ltcg_link"], unit["link_bindings"]
    section, = [s for s in target["image"]["executable_sections"] if s["code"]
                and s["offset"] <= unit["offset"] < s["offset"] + s["size"]]
    address = section["address"] + unit["offset"] - section["offset"]
    runtime_addresses = {u["link_bindings"][runtime]["va"] for u in target["units"]
                         if runtime in u.get("link_bindings", {})}
    retail_runtime, = [a for a in runtime_addresses if section["address"] <= a < section["address"] + section["size"]]
    require(link["rebuilt_address"] == symbols[render], "link map does not name the rendered function")
    require(link["symbols"][destructor] == symbols[destructor], "link map disagrees on the destructor")
    r_handler, r_states = cleanup_table(retail, address, bindings[destructor]["va"], retail_runtime)
    b_handler, b_states = cleanup_table(rebuilt, symbols[render], symbols[destructor], symbols[runtime])
    label = "__ehhandler$" + render
    require(r_handler == bindings[label]["va"] and b_handler == link["symbols"][label],
            "the renderer's exception record names the wrong handler")
    require(r_states == b_states, "stack slots, cleanup code or unwind transitions differ")

    expected = {
        "?GSecondsPerCycle@@3NA": struct.pack("<d", 1.0),
        "?GActorStatMinimum@@3MA": struct.pack("<f", 0.5),
        "?GStats@@3VFStats@@A": bytes(0x120),
        "?GEngineStats@@3VFEngineStats@@A": bytes(0x294),
        "?FName_Names@@3V?$TArray@PAUFNameEntry@@@@A": bytes(12),
    }
    for name, value in expected.items():
        require(link["symbols"][name] == symbols[name], "link map disagrees on " + name)
        require(writable_value(rebuilt, symbols[name], len(value)) == value
                and writable_value(retail, bindings[name]["va"], len(value)) == value,
                "static storage differs for " + name)


def map_symbols(path):
    symbols = {}
    for line in path.read_text().splitlines():
        match = re.match(r"^\s*[0-9a-f]+:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\b", line, re.I)
        if match:
            symbols[match[1]] = int(match[2], 16)
    return symbols


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("steam_root", type=Path)
    parser.add_argument("--cl", required=True, type=Path)
    args = parser.parse_args()
    target = vb.load_target(PC / "config/steam-252084-versus.json")
    unit, = [u for u in target["units"] if u["id"] == "versus-stats-render"]
    retail = vb.verify(target, args.steam_root / target["file"])
    compiler = str(args.cl.resolve())
    env = {k: v for k, v in os.environ.items() if k not in ("CL", "_CL_", "INCLUDE", "LINK", "_LINK_")}
    env["PATH"] = str(Path(compiler).parent) + os.pathsep + env["PATH"]
    env["LINK"] = "/MAP:stats-render.map"
    require(vb.compiler_identity(compiler, env) == unit["toolchain"], "compiler identity differs")
    with tempfile.TemporaryDirectory() as tmp:
        build = Path(tmp).resolve()
        members = vb.callee_units(target["units"], unit)
        rebuilt = vb.rebuild_unit(unit, compiler, env, build, [], members).read_bytes()
        require(vb.compare_unit(PC, target, unit, retail, rebuilt) == unit["match"], "function receipt differs")
        verify_owners(rebuilt, retail, unit, map_symbols(build / "stats-render.map"), target)
    print("Verified FStats::Render, all 250 FString cleanup states and five writable globals.")


if __name__ == "__main__":
    main()
