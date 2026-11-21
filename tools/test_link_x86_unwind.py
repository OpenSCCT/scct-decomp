"""A C++ function's unwind section links as one unit: its funclets and frame handler stub."""

import struct
import unittest

from link_x86 import link_function


def unwind_object(handler_name=b"__ehhandler$?f@@YAXXZ", info_section=b".xdata$x", info_name=b"$T7"):
    """Two sections: .text$x (8-byte funclet, 10-byte handler stub) and .xdata$x with FuncInfo at 4."""
    text = bytes.fromhex("8b4df0e900000000") + bytes.fromhex("b800000000e900000000")
    xdata = bytes(24)
    strings = bytearray(b"\0\0\0\0")
    def name(raw):
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = len(strings)
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, offset)
    symbols = [
        (name(b"$L1"), 0, 1, 0x20, 3),
        (name(handler_name), 8, 1, 0x20, 3),
        (name(info_name), 4, 2, 0, 3),
        (name(b"??1Parent@@UAE@XZ"), 0, 0, 0x20, 2),
        (name(b"___CxxFrameHandler"), 0, 0, 0x20, 2),
    ]
    relocs = struct.pack("<IIH", 4, 3, 0x14) + struct.pack("<IIH", 9, 2, 6) + struct.pack("<IIH", 14, 4, 0x14)
    header_size = 20 + 2 * 40
    text_raw = header_size
    reloc_raw = text_raw + len(text)
    xdata_raw = reloc_raw + len(relocs)
    table = xdata_raw + len(xdata)
    header = struct.pack("<HHIIIHH", 0x14C, 2, 0, table, len(symbols), 0, 0)
    sections = struct.pack("<8sIIIIIIHHI", b".text$x", 0, 0, len(text), text_raw, reloc_raw, 0, 3, 0, 0x60501020)
    sections += struct.pack("<8sIIIIIIHHI", info_section.ljust(8, b"\0"), 0, 0, len(xdata), xdata_raw, 0, 0, 0, 0, 0x40300040)
    table_bytes = b"".join(struct.pack("<8sIhHBB", n, v, s, k, c, 0) for n, v, s, k, c in symbols)
    struct.pack_into("<I", strings, 0, len(strings))
    return header + sections + text + relocs + xdata + table_bytes + bytes(strings)


BINDINGS = {
    "??1Parent@@UAE@XZ": {"va": 0x10001000, "basis": "fixture"},
    "$T7": {"va": 0x10c00000, "basis": "fixture"},
    "___CxxFrameHandler": {"va": 0x10b00000, "basis": "fixture"},
}


class UnwindSectionTests(unittest.TestCase):
    def test_funclets_and_handler_link_as_one_unit(self):
        linked = link_function(unwind_object(), "__ehhandler$?f@@YAXXZ", 18, 0x10bc0000, BINDINGS)
        self.assertEqual(linked[:3], bytes.fromhex("8b4df0"))
        self.assertEqual(struct.unpack_from("<i", linked, 4)[0], 0x10001000 - (0x10bc0000 + 8))
        self.assertEqual(struct.unpack_from("<I", linked, 9)[0], 0x10c00000)
        self.assertEqual(struct.unpack_from("<i", linked, 14)[0], 0x10b00000 - (0x10bc0000 + 18))

    def test_handler_must_name_an_unwind_section_and_funcinfo_its_data(self):
        with self.assertRaisesRegex(ValueError, "expected one complete COFF function"):
            link_function(unwind_object(), "__ehhandler$?g@@YAXXZ", 18, 0x10bc0000, BINDINGS)
        with self.assertRaisesRegex(ValueError, "relative call or jump"):
            link_function(unwind_object(info_section=b".data"), "__ehhandler$?f@@YAXXZ", 18, 0x10bc0000, BINDINGS)


if __name__ == "__main__":
    unittest.main()
