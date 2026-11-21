# symindex: name evidence from sibling builds

Several builds of the same engine shipped with their symbols. `symindex` turns each of them into
one tab-separated table, so that a function is named from evidence instead of being invented.
It reads two kinds of input and decodes the two C++ name manglings they use.

The tables are derived from game files. They belong under `local/evidence/`, which git ignores,
and are never committed. This folder holds only the tool, its test and this page.

## Build and test

```sh
cc -std=c99 -O2 -Wall -Wextra -o local/bin/symindex tools/evidence/symindex.c
sh tools/evidence/test_symindex.sh
```

One C file, standard library only. On Windows it also switches standard output to binary mode,
so rows end in a bare newline on every host. The test builds the tool with `${CC:-cc}` and runs
it on inputs it makes itself: an ELF written by `symindex mkelf` and a link map written by the
script. It needs no game data.

## Commands

| command | output |
| --- | --- |
| `symindex elf FILE [--label NAME]` | one row per function and object symbol of a little-endian 32-bit MIPS ELF |
| `symindex mwmap FILE [--label NAME]` | one row per symbol of the closure of a CodeWarrior link map |
| `symindex demangle NAME...` | the demangled form of each argument, one per line |
| `symindex mkelf FILE` | writes the synthetic ELF the test uses |
| `symindex --selftest` | runs the built-in demangler checks |

`--label` names the build in the first column; it defaults to the file name. The exit status is 0
on success, 1 for a file that cannot be read or is not what the command expects, 2 for a usage
error.

### `elf` rows

```text
label  kind  address  size  binding  mangled  demangled
```

- `kind` is `func` (`STT_FUNC`) or `object` (`STT_OBJECT`). Other symbol types and symbols
  without a name are left out.
- `address` is eight hex digits, `size` is decimal.
- `binding` is `local`, `global` or `weak`. Any other value is printed as `bind<N>`. In the
  CodeWarrior PS2 builds `bind13` is on the symbols several objects may define (inline and
  template functions, their static locals, vtables), which a CodeWarrior link map calls
  `multidef`.
- A file with an empty `.symtab` (a stripped retail executable) is refused with a message.

### `mwmap` rows

```text
label  kind  binding  library  object  mangled  demangled
```

The closure is the first part of the map, from `# Link map of ...` to the next line that starts
with `#`. Each of its lines reads

```text
<indent><depth>] <symbol> (<kind>,<binding>) found in <library> <object>
```

- `kind` and `binding` are copied from the line: `func`, `object` or `notype`, and `local`,
  `global` or `multidef`.
- Section lines are skipped: the ones without `(kind,binding)` and the ones of kind `section`.
- The line is split at its **last** ` found in `, and the `(kind,binding)` group is the last
  thing before that, so symbols that contain `<`, `>`, `,`, `$`, `@`, brackets or spaces come
  through whole. Padding after the symbol is dropped.
- `library` is `-` when the object was linked directly and the line names one file only.
- `object` is copied as the map has it. The linker cuts archive member names at 15 characters.
- A symbol the linker reached more than once is printed once per (library, object, symbol), in
  the order of first appearance.

The rest of the map is not read. It also holds a list of unreferenced symbols per object and a
section layout with addresses and sizes, in which the linker has already demangled the names.

## Regenerating the local indexes

```sh
s=local/bin/symindex
d=local/debug
o=local/evidence
mkdir -p $o
$s elf   $d/sc1-ps2-sled51472/SLED_514.72                   --label sc1-ps2-demo   > $o/sc1-ps2-demo.tsv
$s elf   $d/scpt-ps2-tles52149/TLES_521.49                  --label scpt-ps2-trial > $o/scpt-ps2-trial.tsv
$s elf   $d/sce-psp-ules00281/ULES-00281-SPLINTERCELL.PRX   --label sce-psp        > $o/sce-psp.tsv
$s elf   $d/sce-psp-ules00281/ULES-00281-SPLINTERCELL_M.PRX --label sce-psp-m      > $o/sce-psp-m.tsv
$s mwmap $d/scda-ps2-slus21356/SC4_OFF.MAP                  --label scda-ps2-map   > $o/scda-ps2-map.tsv
```

Looking a name up is then one `grep` or `awk -F'\t'` over `local/evidence/*.tsv`.

## Demangling

The scheme is chosen by the shape of the name. `__0` followed by `F`, `f`, `O`, `o` or `d` is an
SN name and is never tried as anything else; every other name is tried as a CodeWarrior name.
A name counts as demangled only when it parses to its last character. Otherwise the demangled
column repeats the mangled name unchanged. Nothing is guessed.

Both schemes print the same way: `Class::Name(void)` for an empty argument list, `, ` between
arguments, `const char*` and `char* const`, `Box<Bar, 0>` for templates,
`void (*)(int)` for function pointers, `Class::~Class(void)`, `operator<<`, `operator new[]`,
` const` after a const member function, and `Class::__vtable` for a vtable.

### Scheme A: Metrowerks CodeWarrior (PS2 builds)

| mangled | demangled |
| --- | --- |
| `execDot_VectorVector__7UObjectFR6FFramePv` | `UObject::execDot_VectorVector(FFrame&, void*)` |
| `appBitsCpy__FPUciPUcii` | `appBitsCpy(unsigned char*, int, unsigned char*, int, int)` |
| `__ct__Q23std7__nInitFv` | `std::__nInit::__nInit(void)` |
| `__vt__12hkBaseObject` | `hkBaseObject::__vtable` |
| `s_instance__8hkMemory` | `hkMemory::s_instance` |
| `Foo__3BarCFv` | `Bar::Foo(void) const` |

Decoded:

- `name__F<args>`, `name__<class>F<args>`, `name__<class>CF<args>` (const member) and
  `name__<class>` (static data, and compiler tables such as `__RTTI`). Every `__` outside
  template brackets is tried as the separator, leftmost first, and the first one whose remainder
  parses completely wins.
- `__ct`, `__dt`, `__vt`, the operator names (`__as`, `__eq`, `__ne`, `__pl`, `__mi`, `__ml`,
  `__dv`, `__md`, `__apl`, `__ami`, `__amu`, `__adv`, `__amd`, `__aad`, `__aor`, `__aer`,
  `__als`, `__ars`, `__vc`, `__cl`, `__nw`, `__dl`, `__nwa`, `__dla`, `__ls`, `__rs`, `__lt`,
  `__gt`, `__le`, `__ge`, `__aa`, `__oo`, `__nt`, `__co`, `__pp`, `__mm`, `__rf`, `__rm`, `__ad`,
  `__or`, `__er`, `__cm`) and conversion operators `__op<type>`.
- Classes `<len><name>` and `Q<n>...`. Template arguments inside the counted name
  (`11Box<3Bar,0>`): types, and integer constants such as `0` or `-1`.
- Template functions, `Make<3Bar>__FP3Bar`, with the return type some compiler versions
  append: `Make<3Bar>__FP3Bar_P3Bar` prints as `Bar* Make<Bar>(Bar*)`.
- Types `v c s i l x f d b w e`, prefixes `U S C V P R`, arrays `A<n>_`, function types
  `F<args>_<ret>` and member pointers `M<class><type>`. A member function pointer carries two
  hidden leading arguments, which are printed as they are encoded, the way the CodeWarrior
  linker prints them: `M3BarFPCvPv_v` is `void (Bar::*)(const void*, void*)`.
- Wrappers. The compiler names companions of a function by wrapping its mangled name:
  `@ET@name` and `@EX@name` (exception tables), `@<n>@name` and `@<n>@<m>@name` (this-adjusting
  thunks), `@STRING@name@<n>` (string constants), `@LOCAL@name@var` and `@GUARD@name@var` (static
  locals and their guards). The wrapper is copied as it is and the name inside is demangled:
  `@12@Foo__3BarFv` prints as `@12@Bar::Foo(void)`.

Passed through unchanged:

- C names, including the many runtime names that merely contain `__`.
- `__sinit_File.cpp`, `.p__sinit_File.cpp`, `__arraydtor$<n>` and the anonymous `@<n>`.
- `@GUARD@var$<n>` and other wrappers around a name that is not mangled.
- `var$localstatic<n>$name`, the older spelling of a static local.
- Any name that uses type code `1`. It occurs in a handful of PS2 render functions and the
  CodeWarrior linker does not decode it either.

### Scheme B: SN Systems `__0` names (PSP build)

| mangled | demangled |
| --- | --- |
| `__0FJDiskReadyv` | `DiskReady(void)` |
| `__0FSGetPSPFullFileNamePCcPc` | `GetPSPFullFileName(const char*, char*)` |
| `__0FKInitEngineR6SFFileManagerLinearPc` | `InitEngine(FFileManagerLinear&, char*)` |
| `__0fNUGUIComponentNexecActualTopR6GFFramePv` | `UGUIComponent::execActualTop(FFrame&, void*)` |

Counts are single letters: `A` to `Z` are 0 to 25 and `a` to `z` are 26 to 51, so `J` is 9 and
`DiskReady` has nine characters. Lengths from 52 up are `0` and a letter: `0A` is 52.

Decoded. Every form below occurs in the PSP symbol table, and only forms that occur there are
decoded:

| form | meaning |
| --- | --- |
| `__0F<name><args>` | free function; the name may be `5<namespace><name>` |
| `__0f<class><name><args>` | member function |
| `__0o<class><op><args>` | `ct` constructor, `dt` destructor, `op<type>` conversion, or an operator code of scheme A without its `__`. Seen: `as apl ami amu eq ne pl mi ml dv ls rs pp or er vc cl rf nw dl nwa dla`; the rest of that list is accepted too |
| `__0O<op><args>` | operator that is not a member |
| `__0d<class><name>` | static data member; `__vtbl` is printed as `__vtable` |
| `<count><chars>` | identifier |
| `5<scope><name>` | name inside a class or namespace; nests on the left |
| `6<class>` | class type in an argument list |
| `7<args>_` | template arguments after a name |
| `4A` | the integer constant 0 as a template argument |
| `9<n>A` | template parameter `n` (`B` is the first) of the name being declared |
| `P R C U S` | pointer, reference, const, unsigned, signed |
| `v c s i l L f d b e` | as in scheme A, except that `L` is the 64-bit integer, printed `long long` |
| `F<args>_<ret>` | function type |
| `PM<class>F<args>_<ret>` | pointer to member function; the first argument is the object reference and is printed as it is encoded |
| `T<n>` | the same type as argument `n` (`B` is the first) |
| `N<count><n>` | `count` more arguments of the same type as argument `n` |
| trailing `_<type>` | return type, present on template functions and on members of templates; printed in front |
| trailing `K` | const member function |
| trailing `T` | static member function; printed as a leading `static ` |

A template's member can name its own class with parameters instead of arguments: type parameters
as `9<n>A` and value parameters as their bare type, as in `6DBox79BACi_`. The value parameter
is printed as the constant the class has in that position, so the result reads
`Box<Bar, 0>` again.

Passed through unchanged:

- `9` references when the declared name has more than one template list (a member template of a
  class template), and any `9<n><m>` whose last letter is not `A`.
- Integer template arguments other than `4A`.
- `__sti__File_cpp` (static initialisers), the `__vtbl__...` names, static locals
  `var__L<x>____0<function>` and their guards `__LSG__var__L<x>____0<function>`.
- Type codes `x` and `w` and anything else not in the table.

### How the decoders were checked

- Scheme A against the linker itself. The layout part of the *Double Agent* map lists every
  placed symbol in the linker's own demangled form. Leaving the wrapped names aside, this tool
  decodes 26,037 distinct names from that map's closure. With spaces removed, the trailing
  `(void)` written `()` and `__vtable` written `__vt`, 25,565 of them appear in the layout letter
  for letter. The other 472 are all template functions, whose template arguments the linker
  leaves mangled and whose return type it drops.
- Scheme B against scheme A. 5,715 of the 9,767 distinct signatures decoded from the two PSP
  modules occur letter for letter among the names decoded from the PS2 builds. A sample of the
  rest was read by hand: where the function exists in a PS2 build, the PS2 signature differs in
  a way a different game explains (an added parameter, `int` where the PSP source has `long`).
  In the main module all 28 class `operator new` and `operator delete` and all 1,363
  `StaticClass`-style helpers carry the `T` suffix, and none of the 797 script natives does.
  Of the members decoded as const that have a PS2 twin, 202 are const there too and 11 are not;
  no member is const on the PS2 and not on the PSP.

## Limits

- Only little-endian 32-bit MIPS ELF files with a `.symtab` are read. DWARF sections are ignored.
- `multidef` symbols appear once per object that defines them. That is what the map says, not a
  duplicate.
- A sibling build is a different game on a different compiler. Its names are evidence for a
  spelling and a signature, not for an offset, a size or a layout.
