# Campaign compiler and switches: VC7.1, `/O2`

This note is the `recipe_evidence` basis for Steam 252084 Campaign units built
with Microsoft C/C++ 13.10.3052 using `/O2 /Gy` (15,767 units, 846,057 bytes)
or `/O2 /Gy /EHa` (137 units, 20,272 bytes). It establishes three things:
the original compiler, that the compiler used here generates the same code,
and which switches the retail code requires.

## Original compiler: Microsoft C/C++ 13.10.3077

- The Campaign executable's PE optional header records linker version 7.10,
  the linker of Visual Studio .NET 2003. Its DOS stub has no Rich header, so the
  executable does not name its compiler directly.
- The Versus executable, which shipped in the same release, keeps its Rich
  header. It records 27 objects from product `0x0060` build 3077, the Visual
  Studio .NET 2003 C++ compiler 13.10.3077, so that compiler was in use for
  this release. Versus was mostly built with VC7.0 and is not covered here.
- 13.10.3077 is the Visual Studio .NET 2003 RTM release. The only 13.10.3077
  compiler available to this project is the Standard edition in the .NET
  Framework SDK 1.1, which rejects optimisation (warning D4029) and emits
  unoptimised code. It cannot reproduce optimised retail code.

The units therefore record 13.10.3077 as `original_compiler` and are built
with 13.10.3052.

## 13.10.3052 generates the same code as 13.10.3077

The compiler used here is `cl.exe` 13.10.3052 from the Microsoft Visual C++
Toolkit 2003 (SHA-256
`9e45887874de83876ada2adc9943daa9094d1c1f1f9c3d93eac5ad57a1cbee2a`).
Microsoft built the C runtime library twice with the same sources and switches:
once with each compiler.

| Library | Members | CodeView build stamps | SHA-256 |
| --- | --- | --- | --- |
| Toolkit 2003 `libc.lib` | 722 | 1,188 × 13.10.3052, none 3077 | `af02bc1c20fe8ca453542ee530b7c79549ac8292b1c83f82a046cb51e835a3c0` |
| VS .NET 2003 RTM `libc.lib` | 722 | 1,188 × 13.10.3077, none 3052 | `25f494ca0238ae308edeab90dfaaa8c616b12f804a2156b51b9fba50eb144af1` |

[`compare_libraries.py`](compare_libraries.py) pairs the members by name and
their functions by public symbol. All 1,136 paired functions (187,234 bytes)
are identical, in bytes and in the position, type and target of every
relocation. No paired function differs.

**Limit.** The runtime is compiled with Microsoft's runtime switches (`/O1`
family), not the game's `/O2`. The comparison shows the two builds share one
code generator across a large, varied body of code; it does not exercise every
`/O2` transformation. No public build pair of `/O2` code is known.

## Switches the retail code requires

[`flag_experiments.py`](flag_experiments.py) rebuilds every source file behind
these units under each alternative with 13.10.3052, links each unit at its
retail address with its recorded bindings, and counts byte-identical units.

| Switches | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy` | 15,767 of 15,767 | 846,057 of 846,057 |
| `/O2 /G5 /Gy`, `/O2 /G6 /Gy`, `/O2 /GB /Gy` | 15,767 each | 846,057 each |
| `/Ox /Gy` | 15,766 | 845,951 |
| `/O2 /Oy- /Gy` | 6,674 | 322,175 |
| `/O1 /Gy` | 3,692 | 84,950 |
| `/Od /Gy` | 0 | 0 |

| Switches (catch-block units) | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /Gy /EHa` | 137 of 137 | 20,272 of 20,272 |
| `/Ox /Gy /EHa` | 137 | 20,272 |
| `/O2 /Gy /GX`, `/O2 /Gy /EHs`, `/O1 /Gy /EHa` | 0 each | 0 each |

What this establishes:

- **`/O2`.** Unoptimised (`/Od`) and size-optimised (`/O1`) builds fail most
  units. Keeping the frame pointer (`/Oy-`) fails more than half, so the retail
  code omits it, as `/O2` does. `/Ox` differs from `/O2` only in string pooling
  (`/GF`). The one unit it fails, `SND_fn_vSetCurrentLanguage`, is the only one
  of these units that references a pooled string literal; without `/GF` the literal lands in writable
  data, while retail reads it from read-only data. The evidence records `/O2`.
- **`/EHa`.** The 137 catch-block units keep their `try` region and spill its
  locals to memory, which only asynchronous exception handling produces. `/GX`
  and `/EHs` remove the try region. The evidence records `/O2 /EHa`.
- **Processor tuning is undetermined.** `/G5`, `/G6` and the default `/GB`
  produce identical code for every unit, so no `/G` switch is claimed.
- **`/Gy` is packaging, not evidence.** It places each function in its own
  COMDAT section so a single function can be linked and compared. It does not
  change instruction bytes and is not part of the recorded original switches.

## Reproducing

```
python pc/evidence/compare_libraries.py TOOLKIT_2003/libc.lib VS2003_RTM/libc.lib
python pc/evidence/flag_experiments.py TOOLKIT_2003/cl.exe STEAM/System/splintercell3.exe
```

The second command verifies the executable against the locked Campaign image
before rebuilding. Neither command needs or writes game data in the repository.
