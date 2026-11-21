# Campaign compiler and switches: VC7.1, `/O2 /GS`

This note is the `recipe_evidence` basis for Steam 252084 Campaign units built
with Microsoft C/C++ 13.10.3052 using `/O2 /GS /Gy`. It covers objects that the
original build compiled with buffer security checks.

## Compiler

The compiler is the one established in
[campaign-vc71-o2.md](campaign-vc71-o2.md). The original is 13.10.3077; the
build here uses 13.10.3052, which generates the same code. That note's
evidence and its limit apply unchanged.

## Switches the retail code requires

**`/GS`.** The retail functions in these units do two things:

- In the prologue, they copy the security cookie at VA `0x111d36d0` into the
  frame.
- Before returning, they reload that copy and call `__security_check_cookie`
  at VA `0x10f30c59`.

Only the compiler's buffer security check emits this pair. Without `/GS`, a
function compiles with no cookie and no check call, so it cannot match.

[`flag_experiments.py`](flag_experiments.py) rebuilds every `/O2 /GS /Gy`
source file under each alternative, as in the `/O2` note. These are the results
for the 12 units in seven files at the time of writing:

| Switches | Units identical | Bytes identical |
| --- | --- | --- |
| `/O2 /GS /Gy` | 12 of 12 | 2,011 of 2,011 |
| `/Ox /GS /Gy` | 12 | 2,011 |
| `/O2 /Gy` (no `/GS`) | 1 | 3 |
| `/O2 /Oy- /GS /Gy` | 1 | 3 |
| `/O1 /GS /Gy` | 1 | 3 |

The one unit that matches under every alternative is a three-byte function
with no local buffer. The compiler gives it no cookie with or without `/GS`.

What this establishes:

- **`/GS`.** Removing it fails every unit that has a cookie.
- **`/O2`.** It holds for the same reasons as in the `/O2` note: `/O1` and
  `/Oy-` fail. `/Ox` differs only in string pooling, which none of these units
  exercises. The evidence records `/O2 /GS`.
- **`/Gy`.** It is packaging, as in the `/O2` note, and is not recorded.

## Reproducing

```
python pc/evidence/flag_experiments.py TOOLKIT_2003/cl.exe STEAM/System/splintercell3.exe
```
