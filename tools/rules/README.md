# rules: the code-rule checker

`rules.c` makes the **[match]** tier of the [code rules](../../docs/code-rules/rules.md)
mechanical, so "matched" is computed rather than argued. It reads the unit manifests and the
sources they name and reports, per executable, **bytes matched** and **matched under the rules**.

```text
cc -std=c99 -O2 -Wall -Wextra -o local/bin/rules tools/rules/rules.c
local/bin/rules                         # both numbers, and the findings per rule
local/bin/rules --findings              # one line per finding: path:line: rule tier message
local/bin/rules --explain <unit id>     # the [match] findings that hold one unit back
local/bin/rules --units local/units.tsv # every unit with its status and rules
local/bin/rules --json reports/rules.json
local/bin/rules --check                 # fail when reports/rules.json is stale (CI)
sh tools/rules/test_rules.sh            # synthetic fixtures against a reviewed expectation
```

## How a unit is judged

A finding belongs to the declaration or function it sits in. A unit's function is found in its
inputs by its rebuilt symbol (`_name`, `_name@8`, `@name@8`, `?name@Class@@…`, `??1Class@@…`;
a function that a macro invocation defines is found under its pasted name). The unit is charged
with that function's findings and with those of everything the function names, followed
transitively: types, globals, macros, and the `static` or inline helpers compiled into it. A
function in the same file that names none of them is not charged.

When the function cannot be found by name (a template instantiation, a nested macro), the unit
is charged with everything in its source files. `source_found_by` in the report counts both.

## Scope

- **One executable at a time.** Campaign and Versus are two programs. Two declarations
  conflict (R1, R2) only when some unit of the same executable can see both.
- **C++ type identity.** R1 compares declarations within their enclosing namespace. Reopened
  blocks share the same namespace, and unnamed namespaces are shared within a translation unit.
  A unit that uses a qualified type follows that type's declarations. Unqualified lookup starts
  in the enclosing namespace and works outwards.
- **Project files only.** Quoted includes are followed when they name a project file. An
  angle-bracket include (`#include <vector>`) is the toolchain's own header, which a unit
  whose record has `system_headers` compiles against; the checker never reads it, so nothing
  in it is a finding. The fixture `system_includes.cpp` keeps a decoy `src/vector` to prove it.
- **One side of a build conditional.** Tokens and declarations inside a plain `#ifdef NAME`
  or `#ifndef NAME` are followed only for units whose inputs define, or do not define,
  `NAME`. Include guards and `#if` expressions are not treated as conditionals.
- **Markers.** A comment directly above a declaration or function that says `FAKEMATCH` or
  `PROBE` is an R17 finding on it, so every unit that names it is `MATCH-PENDING`.

## Rows implemented

| rule | fires on |
| --- | --- |
| R1 | one type name defined in two files with different bodies, including types a macro defines; a `struct`/`class` keyword that differs between a forward declaration and the definition |
| R2 | `extern` of a global in a source file, inside a function, or inside a macro; one global declared with different types |
| R4 | a constant offset added to a `(char *)`/`(BYTE *)` cast, then a dereference cast; `this` cast to a byte pointer |
| R13 | a virtual named `pad…` or `dummy…` |
| R17 | `volatile` on a local, a parameter or a cast, or on a member or global, without a `// volatile: <evidence>` note; a local declared and never used; empty `if`/`else`; a bare `;` statement; `do { } while ( 0 )` outside a macro; self-assignment; the literals `+ 0` and `* 1`; padding members (`pad`, `_pad`, `padding…`) not marked as named by the SDK or file format |
| R18 | `__asm`, `_asm`, `__emit`, `naked`, `INCLUDE_ASM` |

Advisory findings never change a count: placeholder and address-like names (R7), `__fastcall`
functions with an unread second parameter (R12), tokens outside the dialect (R22), prototypes in
source files (R25), filler members that name no offset (R27), functions without a header comment
(R33), bodies without braces, assignments in `if` conditions and `!!` (R35), `#if 0` (R37), and
member addresses taken by offset without a dereference cast (R4).

The report also counts `one_function_several_addresses`: source functions that are the receipt
of more than one unit of a target. Retail keeps one function per address, so such a source
function stands for several original ones (R34). The count is informational until the
maintainers rule on it.

## Rows not implemented yet

- **R1, prefix copies:** a struct whose fields copy a prefix of another struct's and that is
  reached through a cast.
- **R13, slot comparison:** a declared virtual with no slot in the binary's vtable. This needs a
  table of the retail vtables, which the manifests do not carry yet.
- **R4, offset macros** outside `offsetof` field tables.

Until they exist, review covers them. The checker never licenses a match: it only blocks one.

## Changing a rule

The tables at the top of `rules.c` hold the placeholder, filler, byte-type, dialect and assembly
spellings. A change to them is a rule change: it is recorded in `AGENTS.md` with its reason, and
`tools/rules/tests/expected.txt` and `reports/rules.json` change in the same commit.
