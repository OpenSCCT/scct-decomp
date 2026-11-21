# Resolved question: how much of Versus is VC7.0 code

**Resolved 2026-11-21.** The optimising VC7.0 RTM compiler, 13.00.9466, is now
available. Tested against it, the VC7.1 attribution holds for every unit but
one; see [versus-vc70-9466.md](versus-vc70-9466.md). Versus evidence is on
again, and new VC7.1 units cite that note. The rest of this note is the
original question.

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

## Decision needed

1. Keep the current attribution and turn Versus evidence back on.
2. Keep new Versus units as candidates until an optimising 9466 compiler can
   be tested from a legal source.
3. Also move the units verified earlier back to candidates.
