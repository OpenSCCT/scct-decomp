# AGENTS.md: project guide for matching work

This file is the project profile for the [code rules](docs/code-rules/rules.md). Read it before
writing or reviewing source here. Where it and the rules disagree, this file wins; where it and a
tool disagree, check the tool before bending the source.

## What counts

The campaign's product is readable source. The headline number is **matched under the rules**:
units whose bytes match *and* whose source passes every **[match]** rule (R1, R2, R4, R13, R17,
R18). Bytes matched is the second number. Report both, every time.

| status | meaning | where it is recorded |
| --- | --- | --- |
| candidate | every byte of the unit is rebuilt from committed source | the unit's `match` receipt |
| verified | candidate, plus reviewed evidence of the original compiler and flags | `recipe_evidence` |
| matched under the rules | the unit's source passes every [match] rule | computed by `rules`, never by hand |
| `MATCH-PENDING` | bytes match, a [match] rule fails: open work, not progress | computed by `rules` |
| `ORIGINAL-ASM` | the evidence shows the original was written in assembly | listed apart, counted neither way |

A byte-exact unit is always kept. A style rule the bytes defeat gets
`// RULE-EXCEPTION: <rule>, <reason the bytes give>` at the code. A [match] rule cannot be
excepted: the unit stays `MATCH-PENDING` until the real source is found.

Passing the checker is necessary, not sufficient. Its rows are deliberately narrow, so a unit can
pass them and still fail the reader test (a padding array with an innocent name, an invented
confident name, a merged variable). Review decides those; see "Review" below.

## Compilers and dialect (R22)

| target | original toolchain, from the binary | rebuilt with |
| --- | --- | --- |
| Campaign (`System/splintercell3.exe`) | Microsoft C/C++ 13.10.3077 (Visual Studio .NET 2003), linker 7.10, static C runtime; see [pc/TOOLCHAIN.md](pc/TOOLCHAIN.md) | Visual C++ Toolkit 2003, 13.10.3052, shown code-identical in [the Campaign basis](pc/evidence/campaign-vc71-o2.md) |
| Versus (`Versus/System/SCCT_Versus.ex`) | linker 7.00 with C and C++ producers of several builds; [open question](pc/evidence/versus-compiler-question.md) | 13.10.3052 where [the Versus basis](pc/evidence/versus-vc71-o2.md) covers the unit |
| PS2 programs | not yet established | nothing verified |

Write only what Microsoft C/C++ 13.10 accepts with the unit's recorded flags:

- **C units are C89.** Declarations sit at the top of a block. No `for`-loop declarations,
  `stdint.h`, `stdbool.h`, designated initializers, compound literals or variable-length arrays.
  `//` comments, `__int64`, `__forceinline`, `__declspec`, `__cdecl`, `__stdcall` and `__fastcall`
  are accepted.
- **C++ units are C++98.** No `nullptr`, `auto`, `enum class`, `override`, range `for`, `static_assert`.
  A variable declared in a `for` header stays in scope after the loop unless the unit's flags
  say `/Zc:forScope`. `wchar_t` is `unsigned short` unless the flags say `/Zc:wchar_t`: the
  Campaign exports mangle wide strings as `PBG`.
- **Rejected outright:** `__attribute__`, `regparm` and every other GCC or Clang spelling. A
  unit that needs one was not written the way the original was.

A unit recorded against any other compiler (MSVC 19.x, Clang, VC6 where no evidence names VC6
objects, GCC for the PS2) is a lead. Re-verify it with the period compiler before building on it:
`pc/verify_build.py` skips nothing silently and prints which compiler each skipped unit needs.

## Evidence sources (R6, R7, R12, R20)

In order of weight:

1. **The retail executables**, verified against the manifest hashes: the Campaign export table
   (150 names), run-time type information in both programs, UnrealScript native registration
   tables, wide-string allocation tags, error and log strings, vtables.
2. **Named C runtime objects** of the Visual C++ Toolkit 2003 libraries
   ([how they were compared](pc/evidence/compare_libraries.py)).
3. **Sibling builds of the same engine that shipped with symbols.** They name functions, classes,
   translation units and, in one case, types. Index them with
   [`tools/evidence/symindex`](tools/evidence/README.md); the indexes stay under `local/evidence/`.

   | build | what it carries | SHA-256 of the indexed file |
   | --- | --- | --- |
   | *Splinter Cell* PS2 demo, SLED-51472 (2003-01-15), `SLED_514.72` | symbol table, CodeWarrior DWARF 1 `.debug` and `.line` sections: functions, globals, types | `2082c55a0376607887060589fc6a6798a3609e7c787d3c314a39ca20f0c7efe7` |
   | *Splinter Cell* PS2, SLUS-20652 (2003-03-03), `LOADER.PS2` | symbol table and debug sections of the boot loader | `138983093dd9c47ef5d1f1c0e008195efa9d71fc9aea6113de81073207c79f2e` |
   | *Pandora Tomorrow* PS2 trial, TLES-52149 (2004-03-25), `TLES_521.49` | symbol table: 13,528 functions with mangled signatures, including the network overlay | `70ff0ab494fea445669ae3d7934c5c48823cf053dd8064e7062576dda3e21568` |
   | *Double Agent* PS2, SLUS-21356 (2006-06-20), `SC4_OFF.MAP` | linker map: every symbol with its library and object file | `cad479fa966a51d157d6d8077e08495dfd804549bf0eb4cd7ab34e8a5e038abc` |
   | *Double Agent* PS2 preview, SLES-53826 (2006-06-22), `SC4_OFF.MAP` | the same, one build later | `ed8e6f3421c842f10584e18308be608924e59484b9576f4303c28007028aa32a` |
   | *Essentials* PSP, ULES-00281 and ULUS-10070 (identical files), `…SPLINTERCELL.PRX` | symbol table: 9,361 functions with mangled signatures | `5b03a8042fd598452e08674f71a9b58f8ffd244ed7d90bde9601bc7a6f88a400` |
   | *Essentials* PSP, multiplayer module, `…SPLINTERCELL_M.PRX` | symbol table: 9,550 functions | `45dcbfa4cda7d88f6b8a1d366425d573bf4f2ed19d4dec03c4d8467d0077e945` |

   A sibling build names a Chaos Theory function only once the function is identified
   independently: by an export, a native registration entry, a vtable slot of an RTTI-named class,
   or a string it prints. The sibling then supplies the owning class, the parameter types and the
   spelling. It is a different game on a different compiler: never copy an offset, a size or a
   layout from it without the Chaos Theory bytes agreeing.
4. **Sources that stay out.** The [provenance rules](https://github.com/OpenSCCT/OpenSCCT/blob/main/re/PROVENANCE.md)
   hold here: game files and anything derived from them live in `local/`; short identifiers
   (class, function and field names, addresses) may be committed, code may not. Licensed engine
   source and headers, SDK source and leaked material are never a reference, not even to check a
   match.

Record where a name comes from. A name we invent is allowed and is recorded as invented in the
unit's `identification`; it is never presented as original.

## Naming style, by module (R8, R28, R29)

The style follows the evidence of each module's own code. Mixing two styles in one module is
worse than either.

| module | style | examples from evidence |
| --- | --- | --- |
| Unreal engine and game code (Core, Engine, Echelon packages, drivers) | C++. Classes carry `U` (object), `A` (actor), `F` (plain struct), `T` (template), `E` (enum). Methods and members are `PascalCase`; booleans start with `b`; globals start with `G`; script natives are `exec<Name>` taking `( FFrame& Stack, void* const Result )` | `UObject::execDot_VectorVector`, `AActor`, `FFrame`, `TArray` |
| Sound library (the `SND_` exports) | C. `SND_fn_<result><Name>`, where the result letters are Hungarian: `v` void, `b` boolean, `l` long, `ul` unsigned long, `uc` unsigned char, `r` fixed-point real, `f` float, `p`/`pv`/`pst` pointers, `sz` string, `h` handle, `e` enum, `td` typedef'd value | `SND_fn_lGetSoundTextureCount`, `SND_fn_rMulRealRealQuickSnd`, `SND_fn_pvMallocSnd` |
| C runtime | Microsoft's own names | the named VC7.1 runtime objects |
| anything not yet identified | the placeholder patterns below, never a confident invented name | |

Most committed sources predate this profile: they are C stand-ins for C++ members, with invented
`noun_verb_<rva>` names. Those names are placeholders (R7): open naming work, reported by the
checker, not a failed match.

**Placeholder patterns** the checker reports: `FUN_`, `DAT_`, `sub_`, `unk_`, `local_`, `param_`,
`field_0x`, `uStack`, `iVar`, `m_Unk`, `UnkType_`, `VirtualSlot<n>`; numbered generic names
(`temp1`, `ptr2`, `arg1`, `v3`); and address-like names, a prefix followed by six to eight hex
digits (`cleanup_1fdb50`, `array_tag_7b7b08`, `r007710`).

**Unknown members** are named by offset, `unk_<hex offset>`, and cover only a range no recovered
code touches (R27). `gap`, `unknown`, `reserved`, `before_<member>` and `unused` name no offset;
the checker reports them.

## Layout (R23, R32, R33, R35)

- Four-space indent, K&R braces, as the committed sources have. One statement per line.
- A unit opens with `/* unit.c -- purpose */` (or `//` in C++), then its includes, its data, its
  functions in binary order.
- Every function has a header comment naming it. Say what it does only when that is known;
  otherwise the name alone, or a `guess:` line.
- 100 columns.

Neither executable ships line information, and no committed source uses `__LINE__`, `__FILE__`
or `assert`, so layout changes cannot change the bytes. They do change the unit's receipt: see
"Receipts" below. Formatting goes in its own commit.

## Where unfinished work lives

`src/` holds only units with a byte receipt. A reconstruction that does not yet match stays
under `local/` or on a branch; it is never parked in `src/` behind an `#if`. `#if 0` and
"kept for reference" blocks are not source (R37).

## Commands

Set `$game` to the Steam folder and `$cl` to the Toolkit 2003 `cl.exe`
(SHA-256 `9e45887874de83876ada2adc9943daa9094d1c1f1f9c3d93eac5ad57a1cbee2a`).

| step | command |
| --- | --- |
| per-function check | `python pc/workflow.py <target> $game diff <unit> <object>` |
| byte gate, one lane | `python pc/verify_build.py $game --cl $cl --skip-unavailable --source 'src/sound_*'` |
| byte gate, everything this compiler builds | `python pc/verify_build.py $game --cl $cl --skip-unavailable` |
| byte gate, complete | `python pc/verify_build.py $game --cl … --cl … --clang …` with every recorded compiler |
| build the rule checker | `cc -std=c99 -O2 -Wall -Wextra -o local/bin/rules tools/rules/rules.c` |
| `rules`: both numbers | `local/bin/rules` |
| `rules`: every finding | `local/bin/rules --findings` |
| `rules`: why one unit is pending | `local/bin/rules --explain <unit id>` |
| regenerate the reports | `python tools/progress.py report` and `local/bin/rules --json reports/rules.json` |
| tests | `python -m unittest discover -s tools`, `sh tools/rules/test_rules.sh`, `sh tools/evidence/test_symindex.sh` |

### Receipts

A unit's receipt binds the hash of every input file. Editing a source, even a comment,
invalidates the receipts of every unit that lists it. After an edit:

```text
python pc/verify_build.py $game --cl $cl --skip-unavailable --source 'src/<files>' --update-receipts
```

The verifier rebuilds each affected unit, requires every rebuilt byte to equal retail, and only
then records the new receipt. A unit whose compiler was not supplied is skipped and keeps its
stale receipt, which CI rejects: never edit a source whose units you cannot rebuild.

## Lanes and merging

- Lanes are disjoint by source file. A lane that renames or retypes something shared owns the
  header that declares it and runs alone, or after the lanes that include that header.
- Fix in tiers, one commit each: [free] changes (comments, banners, layout) first, then each
  [checked] or [evidence] change with its gate run. Never mix formatting with code changes.
- A fix that breaks a match is reverted or reshaped, never kept.
- Before a merge: rebase, run the byte gate for the lane from a clean rebuild, run `rules` and
  compare with the main branch, regenerate both reports, and read a sample of the changed
  functions against the reader test.

### Review

The checker cannot see these; a reviewer must:

- a struct member array that only pushes later members into place (`unsigned char fields[0x1cc - 4]`);
- a one-member struct wrapped around an argument to steer how it is passed;
- one local reused for two meanings; a temporary with no meaning;
- a confident invented name or description;
- a `BUG:` or `NOTE:` label on code a simpler source would also produce;
- a `RULE-EXCEPTION` that excuses fake code.

Send a fakematch back as `MATCH-PENDING`. Never rewrite it during a merge.

## Rule changes

None yet: the catalogue applies as written. Tightening or relaxing a rule is a maintainers'
ruling, recorded here with its reason, and the checker changes in the same commit. Four rulings
are open:

1. **Members written as free functions.** 463 definitions are `__fastcall` functions whose
   second parameter is never read: a C spelling of a C++ member, with a dummy standing in for
   EDX. R12 asks for the method. The checker reports them as advisory; making the pattern
   [match] is mechanical if the maintainers want it.
2. **Unwind funclets and frame-handler stubs as units.** The compiler emits these for a parent
   function's exception states. The C that reproduces them alone uses `volatile` globals as
   state flags, which R17 blocks. They may be better counted with their parent function than
   as functions of their own.
3. **Period compiler as a condition of a match.** Candidates that only Clang or MSVC 19.x
   reproduce are leads, not matches of 2005 source.
4. **One source function counted at several addresses.** 159 source functions are each the
   receipt of several retail functions: 2,034 units and 84,097 bytes, one of them at 106
   addresses. Retail keeps a separate copy at every address, so the original had that many
   functions (template instantiations or inline copies, most likely), and a faithful source
   has each of them (R34). `rules` counts these as `one_function_several_addresses`; whether
   they block a match is not decided.

## Tooling

New tooling is written in C (C99, standard library only, one file per tool, built with one
`cc` line). Avoid adding Python. The existing Python tools stay as they are; extend them only
where the change belongs to their own job, as the verifier's receipt update does.

Before a batch of matching lanes, and again after every three, ask whether a tool would save
more time than it costs: a vtable-slot table for R13, a prefix-copy check for R1, an evidence
lookup from unit to sibling symbol are the known candidates.
