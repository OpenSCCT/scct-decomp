#!/bin/sh
# Build symindex and check it against inputs this script makes itself.
# No game data is involved: the ELF comes from "symindex mkelf" and the link
# map is written below.
#
#   sh tools/evidence/test_symindex.sh          (uses cc)
#   CC=gcc sh tools/evidence/test_symindex.sh

set -u

here=$(cd "$(dirname "$0")" && pwd)
work=${TMPDIR:-/tmp}/symindex-test.$$
mkdir "$work" || exit 1
trap 'rm -rf "$work"' EXIT
trap 'exit 1' HUP INT TERM

failures=0

# Report a failed check.
fail() {
    echo "FAIL: $*"
    failures=$((failures + 1))
}

# Print one tab-separated row from its fields.
row() {
    printf '%s' "$1"
    shift
    for field in "$@"; do
        printf '\t%s' "$field"
    done
    printf '\n'
}

# same NAME EXPECTED ACTUAL: the two files must be identical.
same() {
    if cmp -s "$2" "$3"; then
        echo "ok: $1"
    else
        fail "$1"
        diff "$2" "$3"
    fi
}

# status NAME EXPECTED COMMAND...: the command must exit with that status
# and print nothing on standard output.
status() {
    name=$1
    expected=$2
    shift 2
    "$@" > "$work/stdout" 2> "$work/stderr"
    actual=$?
    if [ "$actual" -eq "$expected" ] && [ ! -s "$work/stdout" ]; then
        echo "ok: $name"
    else
        fail "$name (exit status $actual, expected $expected)"
    fi
}

# --- build -----------------------------------------------------------------

sym=$work/symindex
if ! ${CC:-cc} -std=c99 -O2 -Wall -Wextra -o "$sym" "$here/symindex.c" \
        > "$work/build.log" 2>&1; then
    cat "$work/build.log"
    echo "FAIL: symindex.c does not compile"
    exit 1
fi
if [ -s "$work/build.log" ]; then
    cat "$work/build.log"
    fail "symindex.c compiles with warnings"
else
    echo "ok: build without warnings"
fi

# --- demanglers ------------------------------------------------------------

if "$sym" --selftest > "$work/selftest.out"; then
    echo "ok: $(cat "$work/selftest.out")"
else
    cat "$work/selftest.out"
    fail "built-in demangler checks"
fi

"$sym" demangle 'isIPAddress__FPc' '__0FIMainLoopP6HUEngine' \
    '__sinit_Core.cpp' 'plain_c_name' > "$work/demangle.out"
{
    echo 'isIPAddress(char*)'
    echo 'MainLoop(UEngine*)'
    echo '__sinit_Core.cpp'
    echo 'plain_c_name'
} > "$work/demangle.expected"
same "demangle command" "$work/demangle.expected" "$work/demangle.out"

# --- ELF symbol table ------------------------------------------------------

"$sym" mkelf "$work/test.elf" || fail "mkelf"
"$sym" elf "$work/test.elf" --label demo > "$work/elf.out"
{
    row demo func 00100000 64 local 'init_ps2_system__Fv' \
        'init_ps2_system(void)'
    row demo func 00100040 128 global \
        'execDot_VectorVector__7UObjectFR6FFramePv' \
        'UObject::execDot_VectorVector(FFrame&, void*)'
    row demo func 001000c0 8 weak '__0FJDiskReadyv' 'DiskReady(void)'
    row demo func 001000c8 24 bind13 'StartFadeOut__13CThemeChannelFv' \
        'CThemeChannel::StartFadeOut(void)'
    row demo object 00200000 16 global '__vt__12hkBaseObject' \
        'hkBaseObject::__vtable'
    row demo object 00200010 4 local 's_instance__8hkMemory' \
        'hkMemory::s_instance'
    row demo func 001000e0 32 global 'SND_fn_tduGetLowestResourceSwitch' \
        'SND_fn_tduGetLowestResourceSwitch'
    row demo func 00100100 12 global \
        '__0fNUGUIComponentNexecActualTopR6GFFramePv' \
        'UGUIComponent::execActualTop(FFrame&, void*)'
} > "$work/elf.expected"
same "elf rows" "$work/elf.expected" "$work/elf.out"

"$sym" elf --label early "$work/test.elf" | cut -f1 | sort -u > "$work/label.out"
echo early > "$work/label.expected"
same "label before the file" "$work/label.expected" "$work/label.out"

"$sym" elf "$work/test.elf" | cut -f1 | sort -u > "$work/label.out"
echo test.elf > "$work/label.expected"
same "default label is the file name" "$work/label.expected" "$work/label.out"

# Damaged and foreign inputs must be refused, not half-read.
dd if="$work/test.elf" of="$work/short.elf" bs=1 count=200 2> /dev/null
echo 'not an ELF file' > "$work/text.elf"
{
    printf '\177ELF\002\002\001'
    awk 'BEGIN { while (i++ < 400) printf "x" }'
} > "$work/elf64be.elf"
status "truncated ELF is refused" 1 "$sym" elf "$work/short.elf"
status "non-ELF file is refused" 1 "$sym" elf "$work/text.elf"
status "64-bit big-endian ELF is refused" 1 "$sym" elf "$work/elf64be.elf"
status "missing file is reported" 1 "$sym" elf "$work/no-such-file"
status "missing arguments are a usage error" 2 "$sym" elf
status "unknown command is a usage error" 2 "$sym" frobnicate x
status "options before the command are a usage error" 2 \
    "$sym" --label demo elf "$work/test.elf"

# --- CodeWarrior link map --------------------------------------------------

long=$(awk 'BEGIN { while (i++ < 5000) s = s "a"; print s }')
{
    printf '# Link map of ENTRYPOINT\r\n'
    printf '  1] .vubss found in demo.lib vu0.o   \r\n'
    printf '   2] JumpTable (notype,global) found in demo.lib vu0.o   \r\n'
    printf '     4] hkDummySingletoncreate__Fv (func,local) found in hkbase.a hkbasesystem.o \r\n'
    printf '      5] __vt__12hkBaseObject (object,multidef) found in engine_cw39_f.lib uncontroller.o \r\n'
    printf '   2] .p__sinit_UnController.cpp      (object,local) found in engine_cw39_f.lib uncontroller.o \r\n'
    printf '      6] __vt__12hkBaseObject (object,multidef) found in engine_cw39_f.lib uncontroller.o \r\n'
    printf '      6] __vt__12hkBaseObject (object,multidef) found in hkbase.a hkbaseobject.o \r\n'
    printf '    3] __ct__Q23std39basic_filebuf<c,Q23std14char_traits<c>>FP7__sFILE (func,multidef) found in ANSICPP.LIB iostream.o     \r\n'
    printf '    3] @GUARD@fin$1688 (object,local) found in ANSICPP.LIB iostream.o     \r\n'
    printf '    3] @STRING@showMessage__14hkDefaultErrorFPCciPCcPCci6hkBool@4 (object,local) found in hkbase.a hkdefaulterror.\r\n'
    printf '  1] init_ps2_system__Fv (func,global) found in main.c \r\n'
    printf '       7] .rodata (section,local) found in libc.a impure.o/      \r\n'
    printf '  2] odd (func,global) found in here (func,global) found in demo.lib odd.o\r\n'
    printf '  2] %s (object,global) found in demo.lib long.o\r\n' "$long"
    printf '\r\n'
    printf '# Unreferenced symbols:\r\n'
    printf '\tunused__Fv\t(main.c )\r\n'
    printf '  2] late__Fv (func,global) found in demo.lib late.o\r\n'
} > "$work/test.map"
"$sym" mwmap "$work/test.map" --label map > "$work/map.out"
{
    row map notype global demo.lib vu0.o JumpTable JumpTable
    row map func local hkbase.a hkbasesystem.o 'hkDummySingletoncreate__Fv' \
        'hkDummySingletoncreate(void)'
    row map object multidef engine_cw39_f.lib uncontroller.o \
        '__vt__12hkBaseObject' 'hkBaseObject::__vtable'
    row map object local engine_cw39_f.lib uncontroller.o \
        '.p__sinit_UnController.cpp' '.p__sinit_UnController.cpp'
    row map object multidef hkbase.a hkbaseobject.o \
        '__vt__12hkBaseObject' 'hkBaseObject::__vtable'
    row map func multidef ANSICPP.LIB iostream.o \
        '__ct__Q23std39basic_filebuf<c,Q23std14char_traits<c>>FP7__sFILE' \
        'std::basic_filebuf<char, std::char_traits<char>>::basic_filebuf(__sFILE*)'
    row map object local ANSICPP.LIB iostream.o '@GUARD@fin$1688' \
        '@GUARD@fin$1688'
    row map object local hkbase.a hkdefaulterror. \
        '@STRING@showMessage__14hkDefaultErrorFPCciPCcPCci6hkBool@4' \
        '@STRING@hkDefaultError::showMessage(const char*, int, const char*, const char*, int, hkBool)@4'
    row map func global - main.c 'init_ps2_system__Fv' 'init_ps2_system(void)'
    row map func global demo.lib odd.o 'odd (func,global) found in here' \
        'odd (func,global) found in here'
    row map object global demo.lib long.o "$long" "$long"
} > "$work/map.expected"
same "mwmap rows" "$work/map.expected" "$work/map.out"

status "file that is not a link map is refused" 1 "$sym" mwmap "$work/test.elf"
status "missing map is reported" 1 "$sym" mwmap "$work/no-such-file"

# Rows end in a bare newline on every host.
tr -d '\r' < "$work/map.out" > "$work/map.lf"
same "no carriage returns in the output" "$work/map.lf" "$work/map.out"

# --- result ----------------------------------------------------------------

if [ "$failures" -ne 0 ]; then
    echo "$failures check(s) failed"
    exit 1
fi
echo "all checks passed"
