# Versus compiler and switches: VC7.1, `/O2`

This note is the `recipe_evidence` basis for Steam 252084 Versus units built
with Microsoft C/C++ 13.10.3052 using `/O2 /Gy` (including the `/G5` and `/G6`
spellings, 2,751 units, 143,273 bytes) or `/O2 /Gy /GX` (300 units, 36,569
bytes). It covers only units that the VC7.0 compiler does not reproduce.

## Two compilers built this executable

The Versus Rich header lists the tools that produced its objects. The C and
C++ entries are:

| Product | Build | Objects | Compiler |
| --- | --- | --- | --- |
| `0x001c` / `0x001d` | 9466 | 40 C, 81 C++ | VC7.0 (Visual Studio .NET 2002 RTM) |
| `0x001c` / `0x001d` | 9177, 9178 | 81 C, 83 C++ | VC7.0 family pre-release builds |
| `0x0060` | 3077 | 27 C++ | VC7.1 13.10.3077 (Visual Studio .NET 2003 RTM) |

The header does not map objects to addresses, so each unit's compiler has to
be established from its code.

## Which units came from VC7.1

The only optimising VC7.0 compiler available to this project is 13.00.9176,
from the Windows XP SP1 DDK. The .NET Framework SDK 1.0 has VC7.0 13.00.9466,
but it is the Standard edition, which rejects optimisation (warning D4029).

[`versus_compiler_experiments.py`](versus_compiler_experiments.py) rebuilds
every Versus 13.10.3052 unit with another compiler, using the unit's own
switches. With 13.00.9176 it reproduces 330 of 3,397 units (9,205 of 190,429
bytes). The other 3,067 units need a VC7.1 code generator. Since the Rich
header names exactly one VC7.1 build, they came from its 13.10.3077 objects.
The script prints the units 13.00.9176 reproduces; those units receive no
evidence and stay candidates, because their compiler cannot be told apart.

**Limit.** VC7.0 RTM 13.00.9466 itself cannot be run optimised, so whether it
would reproduce any of these 3,067 units is untested. 13.00.9176 is an earlier
build of the same product, and the attribution rests on it.

## 13.10.3052 generates the same code as 13.10.3077

[Campaign compiler and switches](campaign-vc71-o2.md)
shows that Microsoft's C runtime library built by each compiler is identical
in all 1,136 paired functions. The units therefore record 13.10.3077 as
`original_compiler` and are built with 13.10.3052.

## Switches the retail code requires

[`versus_flag_experiments.py`](versus_flag_experiments.py) rebuilds every
source file behind the `/O2`-family and `/O2 /GX` units under each alternative
with 13.10.3052 and counts byte-identical units.

| Switches | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy` | 3,009 of 3,009 | 150,249 of 150,249 |
| `/O2 /G5 /Gy`, `/O2 /G6 /Gy`, `/O2 /GB /Gy`, `/Ox /Gy` | 3,009 each | 150,249 each |
| `/O2 /Oy- /Gy` | 1,570 | 91,673 |
| `/O1 /Gy` | 1,459 | 30,761 |
| `/Od /Gy` | 0 | 0 |

| Switches (C++ units) | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy /GX`, `/O2 /Gy /EHsc`, `/Ox /Gy /GX` | 300 each | 36,569 each |
| `/O2 /Gy /EHa`, `/O2 /Gy` (no exception handling), `/O1 /Gy /GX` | 0 each | 0 each |

What this establishes:

- **`/O2`.** `/Od` and `/O1` fail most units, and keeping the frame pointer
  (`/Oy-`) fails about half. `/Ox` differs from `/O2` only in string pooling,
  which none of these units exercises. The Campaign experiment found a unit
  that requires it; the evidence records `/O2` for both programs.
- **`/GX`.** The C++ destructors need synchronous exception handling
  (`/GX`, which is `/EHsc`). Asynchronous handling and none both fail every
  unit. The evidence records `/O2 /GX`.
- **Processor tuning is undetermined.** `/G5`, `/G6` and the default `/GB`
  produce identical code, so no `/G` switch is claimed, even where a unit's
  build command spells one.
- **`/Gy` is packaging, not evidence**, as in the Campaign note.

## Reproducing

```
python pc/evidence/versus_compiler_experiments.py DDK_XPSP1/cl.exe 9176 STEAM/Versus/System/SCCT_Versus.exe
python pc/evidence/versus_flag_experiments.py TOOLKIT_2003/cl.exe STEAM/Versus/System/SCCT_Versus.exe
```

Both commands verify the executable against the locked Versus image first.
