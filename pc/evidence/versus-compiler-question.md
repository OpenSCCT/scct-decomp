# Open question: how much of Versus is VC7.0 code

This note records an open question about the Versus compiler attribution in
[versus-vc71-o2.md](versus-vc71-o2.md). It is not a `recipe_evidence` basis.

## What the retail code shows

Two instruction patterns separate VC7.0 output from VC7.1 output:

- **Float equality.** For `a == b` on floats, VC7.1 emits `fucompp`
  (`DA E9`). The VC7.0 compiler emits `fcomp` or `fcom`. Retail Campaign,
  a VC7.1 build, has 1,459 `fucompp` sites. Retail Versus has 14. The Versus
  UnrealScript float natives compare with `fcom` only.
- **Zero displacements.** Retail Versus encodes `[esp+0]` in the long form
  (`89 44 24 00`) in 219 unmatched functions. No matched Versus unit has this
  encoding, and VC7.1 never emits it.

The Rich header agrees: 121 objects from VC7.0 9466 and 164 from VC7.0
pre-release builds, against 27 C++ objects from VC7.1 3077.

## What this means for the attribution

Most unmatched Versus code is likely VC7.0 output. Units we can match with
VC7.1 may still come from the 27 VC7.1 objects. Matching selects VC7.1 code
because we build with a VC7.1 compiler.

The attribution test is weaker than it looks. The test says: if 13.00.9176
does not reproduce a unit, then VC7.1 3077 compiled it. But 9176 is an early
build. It drops placement-delete exception frames that retail code has, so
VC7.0 RTM (9466) may differ from 9176 on exactly the units the test assigns
to VC7.1. 9466 can't be tested: the only copy available legally is the
Standard edition, which refuses optimisation.

## Current handling

`checkpoint2.py` has `VERSUS_EVIDENCE = False` since 2026-11-21. New Versus
units are recorded as byte-identical candidates without compiler evidence.
The roughly 3,200 Versus units verified before that date keep their 3077
evidence.

## Link-time code generation

Versus appears to have been linked with whole-program optimisation. The function at RVA
`0xc7d0`, which removes a run of 12-byte elements from an array and which the engine lane
identifies as `TArray<FString>::Remove`, reads its index from EDI without ever setting it:

```text
1090c7d0  mov  eax, [esp+8]      ; count
1090c7d4  add  eax, edi          ; index arrives in EDI
1090c7d6  cmp  edi, eax
1090c7d8  push ebp
1090c7d9  mov  ebp, [esp+8]      ; this arrives on the stack
```

It has two callers, at RVA `0xc61c` and `0xca7b1`; the first clears EDI with `xor edi, edi`
just before it pushes the other arguments. No calling convention a programmer can write
passes an argument in EDI. The compiler does choose such a convention by itself, without
any link-time step, for a `static` function whose every caller it can see in one translation
unit ([toolchain notes](../TOOLCHAIN.md), "Versus actor placement"). That explanation does
not fit here: the two callers lie 780 KB apart in the image, and a template member has
external linkage. Across translation units the choice needs `/GL` and `/LTCG`, which the
7.00 linker has. The engine lane also found many array destructors with a private
convention, `this` on the stack and popped by the callee.

If so, two things follow. A unit compiled alone can only reproduce the functions whose
convention the link step left alone, so "compiled with `/O2`" is at most half of the Versus
recipe; and the units that reproduce a link-time convention through a stand-in are
fakematches (`TArrayLtcg` in `src/versus_ltcg.h`, marked as one). A unity build of the
engine would be the other reading, and would make the same per-file rebuilds wrong for the
same reason.

## Decision needed

1. Keep the current attribution and turn Versus evidence back on.
2. Keep new Versus units as candidates until an optimising 9466 compiler can
   be tested from a legal source.
3. Also move the units verified earlier back to candidates.
