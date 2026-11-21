# Versus switches for VC7.0 13.00.9466 units

This note is the `recipe_evidence` basis for Steam 252084 Versus units built
with Microsoft C/C++ 13.00.9466, the exact compiler build that the Versus Rich
header names. It establishes which switches the retail code requires, and which
units can be told apart from VC7.1 code.

## The compiler is the original build

[versus-vc70-9466.md](versus-vc70-9466.md) identifies the compiler and records
its SHA-256 digests. The Versus Rich header lists, all from build 9466:

- 40 C objects (product `0x1c`) and 81 C++ objects (product `0x1d`), compiled
  normally;
- 292 C++ objects (product `0x2c`) compiled for link-time code generation
  (`/GL`), whose code LINK 7.00.9466 generated with `/LTCG`.

The PE optional header records linker version 7.00. LINK.EXE 7.00.9466 from
the same disc links the link-time code generation units, as described in
[TOOLCHAIN.md](../TOOLCHAIN.md#link-time-code-generation-versus).

No `original_compiler` is recorded: the compiler used here is the original.

## Switches the retail code requires

[`versus_vc70_flag_experiments.py`](versus_vc70_flag_experiments.py) rebuilds
the source behind every 13.00.9466 unit under each alternative, links each unit
at its retail address (relinking the DLL for link-time code generation units),
and counts byte-identical units. At the time of writing:

| Switches (normal objects) | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy` | 26 of 26 | 2,335 of 2,335 |
| `/O2 /G6 /Gy` | 26 | 2,335 |
| `/Ox /Gy` | 22 | 1,827 |
| `/O2 /Oy- /Gy` | 11 | 1,074 |
| `/O2 /G5 /Gy` | 9 | 508 |
| `/O1 /Gy`, `/Od /Gy` | 0 each | 0 each |

| Switches (exception frames) | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy /GX` | 22 of 22 | 2,307 of 2,307 |
| `/Ox /Gy /GX` | 17 | 1,697 |
| `/O2 /Gy` | 6 | 486 |
| `/O2 /Gy /EHa` | 5 | 458 |
| `/O2 /Oy- /Gy /GX` | 2 | 121 |
| `/O1 /Gy /GX` | 0 | 0 |

| Switches (link-time code generation) | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy /GL` | 11 of 11 | 1,208 of 1,208 |
| `/Ox /Gy /GL` | 8 | 824 |
| `/O2 /Oy- /Gy /GL` | 5 | 319 |
| `/O2 /Gy` (no `/GL`) | 0 | 0 |
| `/O1 /Gy /GL`, `/Od /Gy /GL` | 0 each | 0 each |

| Switches (link-time code generation, exception frames) | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy /GX /GL` | 23 of 23 | 2,916 of 2,916 |
| `/Ox /Gy /GX /GL` | 22 | 2,764 |
| `/O2 /Gy /EHa /GL` | 2 | 200 |
| `/O2 /Gy /GL` | 1 | 144 |
| `/O2 /Gy /GX` (no `/GL`) | 0 | 0 |
| `/O1 /Gy /GX /GL` | 0 | 0 |

What this establishes:

- **`/O2`.** Size optimisation (`/O1`) and no optimisation (`/Od`) reproduce
  no unit. `/Ox` lacks the frame-pointer and stack-probe choices of `/O2` and
  fails on some units; disabling frame-pointer omission (`/Oy-`) fails on most.
- **`/GX`** for units with C++ exception frames. Asynchronous handling
  (`/EHa`) and no exception handling reproduce only units whose frames do not
  depend on it.
- **`/GL`** for link-time code generation units. Without it, no such unit
  reproduces.

**Limits.** `/G6` generates the same code as the VC7.0 default, so the target
processor switch cannot be determined. `/Gy` packages each function in its own
section and is not claimed. Some link-time code generation units were matched
with `/Ob1`; with the default inlining they mostly differ, but the difference
depends on where the source places helper definitions, so those units are not
covered by this note and stay candidates.

## Which units receive this note

A 13.00.9466 unit receives this note when its switches are one of the four
families above, recording the claimed switches (`/O2`, with `/GX` and `/GL`
where used). A normal unit also needs VC7.1 13.10.3052, given the same build
command, not to reproduce it; otherwise its compiler cannot be told apart and it
stays a candidate. Link-time code generation units always qualify: only VC7.0
`/GL` objects appear in the Rich header, and LINK 7.00.9466 generated their
code. At the time of writing, 79 units (8,574 bytes) qualify; 3 normal units
that VC7.1 also reproduces do not.
