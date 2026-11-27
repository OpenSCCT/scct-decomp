"""Replay the VC7.0 frame handler and exception tables for the MGM page vector.

Run python pc/evidence/versus_mgm_page_stack_eh.py STEAM_ROOT --cl PATH_TO_CL.
The normal verify_build.py gate checks the 684-byte vector function itself.
"""

import argparse
import os
from pathlib import Path
import struct
import sys
import tempfile

PC = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PC))
import verify_build as vb
from link_image import _file_offset
from link_x86 import symbol_index


def require(condition, message):
    if not condition:
        raise ValueError(message)


def contribution(obj, section):
    start = 20 + (section - 1) * 40
    name = obj[start:start + 8].rstrip(b"\0")
    size, raw, relocations = struct.unpack_from("<III", obj, start + 16)
    count, = struct.unpack_from("<H", obj, start + 32)
    fields = list(struct.iter_unpack("<IIH", obj[relocations:relocations + count * 10]))
    return name, obj[raw:raw + size], fields


def verify_tables(obj, retail, unit, target):
    _, symbols, functions, _, _ = symbol_index(obj)
    code_section, = functions[unit["rebuilt_symbol"].encode()]
    _, _, fields = contribution(obj, code_section)
    # The function's prologue pushes its compiler-generated frame handler.
    handler_field, = [index for offset, index, kind in fields if offset == 6 and kind == 6]
    label, value, section, _, storage = symbols[handler_field]
    name, stub, fields = contribution(obj, section)
    require(value == 0 and storage == 6 and name == b".text$x", "unexpected handler symbol")
    require(stub == b"\xb8" + bytes(4) + b"\xe9" + bytes(4), "unexpected handler instructions")
    require([(p, k) for p, _, k in fields] == [(1, 6), (6, 20)], "unexpected handler relocations")

    handler_address = unit["link_bindings"][label.decode()]["va"]
    pos, flags = _file_offset(retail, handler_address, len(stub))
    require(flags & 0x20000000, "retail handler outside executable code")
    retail_stub = retail[pos:pos + len(stub)]
    metadata_address, = struct.unpack_from("<I", retail_stub, 1)
    runtime_name = symbols[fields[1][1]][0].decode()
    require(runtime_name == "___CxxFrameHandler", "unexpected exception runtime")
    runtime_addresses = {record["link_bindings"][runtime_name]["va"] for record in target["units"]
                if runtime_name in record.get("link_bindings", {})}
    code, = [s for s in target["image"]["executable_sections"] if s["code"]]
    runtime, = [address for address in runtime_addresses
                if code["address"] <= address < code["address"] + code["size"]]
    linked_stub = b"\xb8" + struct.pack("<I", metadata_address) + b"\xe9"
    linked_stub += struct.pack("<i", runtime - handler_address - len(stub))
    require(linked_stub == retail_stub, "linked frame handler differs from retail")

    _, info_offset, data_section, _, _ = symbols[fields[0][1]]
    name, contents, fields = contribution(obj, data_section)
    require(name == b".xdata$x" and info_offset == 104 and len(contents) == 132,
            "unexpected exception data layout")
    data_address = metadata_address - info_offset
    filepos, flags = _file_offset(retail, data_address, len(contents))
    require(flags & 0xe0000000 == 0x40000000, "retail exception data outside read-only data")
    function_address = code["address"] + unit["offset"] - code["offset"]
    linked = bytearray(contents)
    catch_offsets, internal_offsets = [], []
    for offset, index, kind in fields:
        _, relative, dest_section, _, _ = symbols[index]
        require(kind == 6 and linked[offset:offset + 4] == bytes(4), "unexpected table relocation")
        if dest_section == code_section:
            catch_offsets.append((offset, relative))
            value = function_address + relative
        else:
            require(dest_section == data_section, "table target outside function and exception data")
            internal_offsets.append((offset, relative))
            value = data_address + relative
        struct.pack_into("<I", linked, offset, value)
    require(catch_offsets == [(44, 418), (60, 430)], "unexpected in-function catch targets")
    require(internal_offsets == [(80, 32), (100, 48), (112, 0), (120, 64)],
            "unexpected exception table references")
    require(linked == retail[filepos:filepos + len(linked)], "linked exception tables differ from retail")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("steam_root", type=Path)
    parser.add_argument("--cl", required=True, type=Path)
    args = parser.parse_args()
    target = vb.load_target(PC / "config/steam-252084-versus.json")
    unit, = [u for u in target["units"] if u["id"] == "versus-mgm-page-stack-vector-insert"]
    retail = vb.verify(target, args.steam_root / target["file"])
    env = {k: v for k, v in os.environ.items() if k not in ("CL", "_CL_", "INCLUDE")}
    compiler = args.cl.resolve()
    env["PATH"] = str(compiler.parent) + os.pathsep + env["PATH"]
    require(vb.compiler_identity(str(compiler), env) == unit["toolchain"], "unexpected compiler")
    with tempfile.TemporaryDirectory() as tmp:
        obj = vb.compile_unit(unit, str(compiler), env, Path(tmp), []).read_bytes()
    require(vb.compare_unit(PC, target, unit, retail, obj) == unit["match"], "function receipt differs")
    verify_tables(obj, retail, unit, target)
    print("Verified the 684-byte std::vector function, its 10-byte handler and 132 bytes of exception tables.")


if __name__ == "__main__":
    main()
