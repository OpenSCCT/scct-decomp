# Versus compilers tested with VC7.0 RTM 13.00.9466

This note is the `recipe_evidence` basis for Steam 252084 Versus units built
on or after 2026-11-21. It answers the open question in
[versus-compiler-question.md](versus-compiler-question.md) and replaces the
13.00.9176 test in [versus-vc71-o2.md](versus-vc71-o2.md).

## The compiler

The Versus Rich header names 121 objects from VC7.0 build 9466, the compiler
of Visual Studio .NET 2002. The optimising edition is now available here, from
a Visual Studio .NET 2002 Professional disc owned by the project lead. It runs
on 64-bit Windows without installation.

| File | Version | SHA-256 |
| --- | --- | --- |
| `cl.exe` | 13.00.9466.0 | `05be307f04d8c3a9c211b77e85a63992be4642f14b4de31c04f9bb3d7bb1d65f` |
| `c1.dll` | | `b4992fc795a21fd808f156f13d129ce8ccc0d6fbcbf4187f0a9db349678db989` |
| `c1xx.dll` | | `30c3affd786752b4a037c4b4f035b7962d1fb5a335366e093bc73d0eb02e5558` |
| `c2.dll` | | `3755d22dd896ca0045b22b0478d6ad56185d0c98845e2aa2e1d2300460289ad0` |

It accepts `/O2` without warning D4029, unlike the Standard edition in the
.NET Framework SDK.

## Which units came from VC7.1

[`versus_compiler_experiments.py`](versus_compiler_experiments.py) rebuilds
every Versus 13.10.3052 unit with 13.00.9466, using each unit's own switches.
At the time of writing:

| Switches | Units | Reproduced by 13.00.9466 |
| --- | --- | --- |
| `/O2 /Gy` | 2,395 (59,936 bytes) | 214 (4,352 bytes) |
| `/O2 /G6 /Gy` | 173 (76,655 bytes) | 45 (2,800 bytes) |
| `/O2 /Gy /GX` | 495 (47,666 bytes) | 1 (64 bytes) |
| `/Gy /O2` | 425 (13,050 bytes) | 0 |
| `/O1 /Gy` and `/Gy /O1` | 65 (2,046 bytes) | 65 (2,046 bytes) |
| `/O2 /Oi /Gy` | 14 (1,092 bytes) | 1 (48 bytes) |
| `/O2 /G5 /Gy` | 16 (608 bytes) | 0 |
| `/O2 /G6 /Oa /Gy` | 2 (303 bytes) | 0 |
| `/Od /Gy` | 6 (135 bytes) | 6 (135 bytes) |
| Total | 3,592 (201,526 bytes) | 332 (9,445 bytes) |

One further unit is a C runtime function with its own switches; it does not
build with 13.00.9466.

The 3,259 units that 13.00.9466 does not reproduce need a VC7.1 code
generator. The Rich header names one VC7.1 build, 13.10.3077, so they came
from its objects. This is the same attribution that
[versus-vc71-o2.md](versus-vc71-o2.md) made with 13.00.9176, now tested
against the exact VC7.0 build. The two tests agree on every unit but one:
`vm-rot-rand-with-angle`, which 13.00.9466 reproduces. Its VC7.1 evidence is
withdrawn and it returns to candidate status.

Units that both compilers reproduce receive no evidence: their compiler
cannot be told apart.

## Evidence recorded for VC7.1 units

A Versus unit built with 13.10.3052 receives this note as its basis when
13.00.9466, given the same switches, does not reproduce it. It names
13.10.3077 as `original_compiler`; [campaign-vc71-o2.md](campaign-vc71-o2.md)
shows that 13.10.3052 generates the same code. The switches are established
in [versus-vc71-o2.md](versus-vc71-o2.md): `/O2`, plus `/GX` for C++ units
with exception frames. Processor tuning and `/Gy` are not claimed.

## Evidence recorded for VC7.0 units

A Versus unit built with 13.00.9466 itself uses the compiler the Rich header
names, so no `original_compiler` is recorded. Its switches are claimed only
when an experiment in this directory shows that alternatives fail. Until
then, such units stay candidates.

## Reproducing

```
python pc/evidence/versus_compiler_experiments.py VS_NET_2002/Vc7/bin/cl.exe 9466 STEAM/Versus/System/SCCT_Versus.exe
```
