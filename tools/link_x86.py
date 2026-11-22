"""Resolve x86 COFF external references in one complete C function at its retail VA."""

from collections import Counter, defaultdict
from functools import lru_cache
import struct


def region(data, offset, size):
    if offset < 0 or size < 0 or offset + size > len(data):
        raise ValueError("COFF range outside object")
    return data[offset:offset + size]


@lru_cache(maxsize=1)
def symbol_index(obj):
    """Parse the current translation unit once even when hundreds of its functions match."""
    machine, sections, _, table, entries, optional, _ = struct.unpack_from("<HHIIIHH", obj)
    if machine != 0x14c or optional or not entries:
        raise ValueError("expected x86 COFF with a symbol table")
    region(obj, 20, sections * 40)
    region(obj, table, entries * 18)
    strings = table + entries * 18
    string_size, = struct.unpack_from("<I", obj, strings)
    names = region(obj, strings, string_size)
    symbols = {}
    functions = defaultdict(list)
    section_functions = Counter()
    handlers = defaultdict(list)
    index = 0
    while index < entries:
        short, value, section, kind, storage, aux = struct.unpack_from("<8sIhHBB", obj, table + index * 18)
        if short[:4] == b"\0" * 4:
            start = int.from_bytes(short[4:], "little")
            end = names.find(b"\0", start)
            if not 4 <= start <= end:
                raise ValueError("invalid COFF symbol name")
            short = names[start:end]
        name = short.rstrip(b"\0")
        symbols[index] = (name, value, section, kind, storage)
        # A C++ catch block is emitted after the function's return in the same section,
        # under a private $L label; it belongs to that function rather than starting another.
        catch_block = storage == 3 and value > 0 and name.startswith(b"$L") and name[2:].isdigit()
        # A function's frame handler stub ends its unwind section after the funclets.
        frame_handler = storage == 3 and value > 0 and name.startswith(b"__ehhandler$")
        if kind == 0x20 and 1 <= section <= sections and frame_handler:
            handlers[name].append(section)
        if kind == 0x20 and 1 <= section <= sections and not catch_block and not frame_handler:
            section_functions[section] += 1
            if value == 0 and storage in (2, 3):
                functions[name].append(section)
        index += 1 + aux
    if index != entries:
        raise ValueError("invalid COFF auxiliary symbol count")
    return sections, symbols, functions, section_functions, handlers


def handler_stub(obj, section, value):
    """True when the label is the frame handler stub that ends a .text$x section."""
    header = 20 + (section - 1) * 40
    sec_name, = struct.unpack_from("<8s", obj, header)
    size, raw = struct.unpack_from("<II", obj, header + 16)
    return (sec_name.rstrip(b"\0") == b".text$x" and value + 10 == size
            and obj[raw + value] == 0xb8 and obj[raw + value + 5] == 0xe9)


def writable_data(obj, section):
    """True when the section is initialized or uninitialized data that the program may write."""
    header = 20 + (section - 1) * 40
    flags, = struct.unpack_from("<I", obj, header + 36)
    return (not flags & 0x20 and bool(flags & 0xc0) and bool(flags & 0x40000000)
            and bool(flags & 0x80000000))


def is_class_vtable(name):
    """True for a class's vtable, ??_7<class>@@6B@, or a base subobject's table, ??_7<class>@@6B<base>@@@."""
    if isinstance(name, bytes):
        name = name.decode("latin-1")
    return name.startswith("??_7") and "@@6B" in name and name.endswith("@") and len(name) > 9


def readonly_data(obj, section):
    """True when the section is initialized, read-only, non-executable data."""
    header = 20 + (section - 1) * 40
    flags, = struct.unpack_from("<I", obj, header + 36)
    return (not flags & 0x20 and bool(flags & 0x40) and bool(flags & 0x40000000)
            and not flags & 0x80000000)


def switch_arms(obj, body, section, size, symbols, relocation_data):
    """Return the symbol indices of the switch arm labels that this section's jump tables name.

    A jump table is the run of consecutive 4-byte absolute entries that begins at a local label
    (storage class 3) which the code reaches by an indirect jump, FF 24 with a SIB byte of scale 4
    and no base register: jmp [label + index*4]. Each local label in that run is an arm.
    """
    entries = {}
    for position, sym_index, relocation in struct.iter_unpack("<IIH", relocation_data):
        entries[position] = (sym_index, relocation)

    def local_label(sym_index):
        symbol, _, sym_section, kind, _ = symbols[sym_index]
        return (kind == 0 and sym_section == section
                and symbol.startswith(b"$L") and symbol[2:].isdigit())

    arms = set()
    for position, (sym_index, relocation) in entries.items():
        _, value, _, _, storage = symbols[sym_index]
        if (relocation != 6 or storage != 3 or not local_label(sym_index)
                or value >= size or position < 3 or position + 4 > size):
            continue
        sib = body[position - 1]
        if (body[position - 3:position - 1] != b"\xff\x24" or (sib & 0xc7) != 0x85
                or ((sib >> 3) & 7) == 4):
            continue
        entry = value
        while entry + 4 <= size and entry in entries and entries[entry][1] == 6:
            arm = entries[entry][0]
            if symbols[arm][4] not in (3, 6) or not local_label(arm):
                break
            arms.add(arm)
            entry += 4
    return arms


def link_function(obj, name, length, address, bindings, *, read_constant=None):
    """Return the fully linked section. The retail function bytes are never an input."""
    sections, symbols, functions, section_functions, handlers = symbol_index(bytes(obj))
    matches = functions.get(name.encode("ascii"), ())
    if name.startswith("__ehhandler$"):
        # The unit is the whole unwind section: the funclets and this frame handler stub.
        matches = handlers.get(name.encode("ascii"), ())
        if len(matches) == 1:
            unwind_name, = struct.unpack_from("<8s", obj, 20 + (matches[0] - 1) * 40)
            if unwind_name.rstrip(b"\0") != b".text$x":
                raise ValueError("a frame handler must be in the unwind code section")
    if len(matches) != 1:
        raise ValueError(f"expected one complete COFF function named {name}")
    section = matches[0]
    if section_functions[section] != 1:
        raise ValueError("COFF section contains multiple functions")
    header = 20 + (section - 1) * 40
    size, start, relocs = struct.unpack_from("<III", obj, header + 16)
    count, _, flags = struct.unpack_from("<HHI", obj, header + 32)
    if size != length or not count or flags & 0x20000020 != 0x20000020 or flags & 0x01000000:
        raise ValueError("expected a complete executable section with standard relocations")
    body = bytearray(region(obj, start, size))
    relocation_data = region(obj, relocs, count * 10)
    used = set()
    fields = set()
    arms = switch_arms(obj, body, section, size, symbols, relocation_data)
    for position, sym_index, relocation in struct.iter_unpack("<IIH", relocation_data):
        symbol, value, sym_section, kind, storage = symbols[sym_index]
        # VC6 writes a switch's arms as class 6 (IMAGE_SYM_CLASS_LABEL) labels. The COFF
        # specification defines class 6 as a label, so one is local only when a jump table
        # of this section names it.
        table_arm = storage == 6 and sym_index in arms
        local = ((storage == 3 or table_arm) and kind == 0 and sym_section == section
                 and symbol.startswith(b"$L") and symbol[2:].isdigit())
        private = storage in (3, 6) and not local
        # C++ exception frames push this function's own frame handler, a label in the
        # compiler's .text$x unwind section, by absolute address. VC7.1 names it
        # __ehhandler$<function>; VC7.0 uses an unnamed $L label (storage class 6) on the
        # stub that ends the section: mov eax, <FuncInfo>; jmp __CxxFrameHandler.
        handler = (private and relocation == 6 and sym_section != section
                   and ((storage == 3 and kind == 0x20 and symbol == b"__ehhandler$" + name.encode("ascii"))
                        or (storage == 6 and kind == 0 and symbol.startswith(b"$L") and symbol[2:].isdigit()
                            and 1 <= sym_section <= sections and handler_stub(obj, sym_section, value))))
        # The frame handler stub loads its function's FuncInfo, a compiler label in .xdata$x;
        # the binding names the retail FuncInfo, which the audit checks structurally.
        funcinfo = False
        if private and relocation == 6 and kind == 0 and 1 <= sym_section <= sections and symbol.startswith(b"$T"):
            info_name, = struct.unpack_from("<8s", obj, 20 + (sym_section - 1) * 40)
            funcinfo = info_name.rstrip(b"\0") == b".xdata$x"
        # A function-local static is private data: its storage slot and its guard word are each
        # the start of a writable .bss or .data contribution, and the code reaches them by absolute
        # DIR32 reference. Like an external global, each takes its address from the binding.
        private_data = (private and relocation == 6 and storage == 3 and kind == 0
                        and 1 <= sym_section <= sections and sym_section != section
                        and not symbol.startswith(b"$") and writable_data(obj, sym_section))
        # A class's virtual function table is a read-only COMDAT that the object defines, and the code
        # stores its address. A binding names the retail table; the local copy is not compared.
        class_vtable = (private and relocation == 6 and storage == 3 and kind == 0
                        and 1 <= sym_section <= sections and sym_section != section
                        and is_class_vtable(symbol)
                        and readonly_data(obj, sym_section))
        if local:
            if relocation != 6 or value >= size:
                raise ValueError("invalid section-local switch label")
            dest = address + value
        else:
            if handler:
                dest_header = 20 + (sym_section - 1) * 40
                dest_name, = struct.unpack_from("<8s", obj, dest_header)
                dest_size, = struct.unpack_from("<I", obj, dest_header + 16)
                dest_flags, = struct.unpack_from("<I", obj, dest_header + 36)
                if dest_name.rstrip(b"\0") != b".text$x" or dest_flags & 0x20000020 != 0x20000020 or value >= dest_size:
                    raise ValueError("frame handler must be a label in the unwind code section")
            elif class_vtable:
                if value != 0:
                    raise ValueError("a class vtable must start its own contribution")
            elif private_data:
                if value != 0:
                    raise ValueError("private data must start its own contribution")
            elif funcinfo:
                pass
            elif private:
                # MSVC may choose a register ABI for a static procedure within this translation unit.
                if (relocation != 0x14 or sym_section == section or functions.get(symbol) != [sym_section]
                        or section_functions[sym_section] != 1 or kind != 0x20 or value != 0):
                    raise ValueError("expected a relative call or jump to one defined private function")
                dest_header = 20 + (sym_section - 1) * 40
                dest_size, dest_raw = struct.unpack_from("<II", obj, dest_header + 16)
                dest_flags, = struct.unpack_from("<I", obj, dest_header + 36)
                if not dest_size or dest_flags & 0x20000020 != 0x20000020:
                    raise ValueError("private function must start an executable contribution")
                region(obj, dest_raw, dest_size)
            elif value != 0 or storage != 2 or not 0 <= sym_section <= sections:
                raise ValueError("expected an external symbol at the start of its contribution")
            symbol = symbol.decode("ascii")
            if symbol not in bindings:
                raise ValueError(f"missing link address for {symbol}")
            binding = bindings[symbol]
            dest = binding["va"]
            # The C runtime defines __except_list as the absolute offset 0 of the thread
            # information block, addressed through FS.
            low = 0 if symbol == "__except_list" and not sym_section else 1
            if type(dest) is not int or not low <= dest <= 0xffffffff or not binding["basis"].strip():
                raise ValueError(f"invalid address or missing evidence for {symbol}")
            if sym_section and kind == 0 and is_class_vtable(symbol):
                # A C++ virtual function table holds relocated pointers, so its compiled
                # contents cannot be compared before linking; the binding names the retail table.
                const_header = 20 + (sym_section - 1) * 40
                const_flags, = struct.unpack_from("<I", obj, const_header + 36)
                if value != 0 or const_flags & 0xe0000040 != 0x40000040:
                    raise ValueError(f"expected a read-only virtual function table for {symbol}")
            elif funcinfo or handler or private_data:
                pass
            elif sym_section and kind != 0x20:
                const_header = 20 + (sym_section - 1) * 40
                const_size, const_start = struct.unpack_from("<II", obj, const_header + 16)
                const_relocs, _, const_flags = struct.unpack_from("<HHI", obj, const_header + 32)
                if (kind != 0 or not const_size or const_relocs or const_flags & 0xe0000040 != 0x40000040
                        or read_constant is None):
                    raise ValueError(f"expected an initialized read-only constant for {symbol}")
                if region(obj, const_start, const_size) != read_constant(dest, const_size):
                    raise ValueError(f"compiled constant differs from retail for {symbol}")
            used.add(symbol)
        field = set(range(position, position + 4))
        if position + 4 > size or fields & field:
            raise ValueError("invalid or overlapping relocation fields")
        fields.update(field)
        addend, = struct.unpack_from("<I", body, position)
        if local and addend:
            raise ValueError("switch label relocation has a nonzero addend")
        if private and addend and not funcinfo and not private_data and not class_vtable:
            raise ValueError("private function relocation has a nonzero addend")
        if relocation == 0x14:  # IMAGE_REL_I386_REL32
            dest -= address + position + 4
        elif relocation != 6:  # IMAGE_REL_I386_DIR32
            raise ValueError(f"unsupported i386 relocation {relocation:#x}")
        struct.pack_into("<I", body, position, (addend + dest) & 0xffffffff)
    if used != set(bindings):
        raise ValueError("binding table includes an unused symbol")
    return bytes(body)
