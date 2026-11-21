# Code rules

Source here has to match the retail bytes **and** read like the original. These files say what
that means:

- [rules.md](rules.md): the catalogue, R1 to R37, with examples, the fakematch table and the
  rows a checker tests.
- [style-defaults.md](style-defaults.md): naming and layout tables to start from where a
  module's own style is unknown.
- [AGENTS.md](../../AGENTS.md): this project's profile. It names the compilers and dialect, the
  evidence sources, the naming style of each module and the commands, and it overrides the
  catalogue where it says so.
- [tools/rules](../../tools/rules/README.md): the checker that computes "matched under the rules".

The catalogue and the style tables are the `decomp-code-rules` references, included here
unchanged with their author's permission so rule numbers stay stable. Change a rule for this
project in `AGENTS.md`, never by editing the catalogue.

## The reader test

> Would a programmer on the original team, writing in that codebase's style and dialect, have
> typed this? And can a reader see what it does, and why, without opening the disassembly?

A **fakematch** fails this test while producing the right bytes: a dummy temporary, a `volatile`
carrier, an empty block, a reused variable, an offset cast. It is a clue to the real source, not
a match.

## The two laws

1. **The bytes win.** A change made for style must not change what the compiler emits. When a
   rule and the bytes disagree, keep the bytes and write
   `// RULE-EXCEPTION: <rule>, <reason the bytes give>` at the code. An exception bends a style
   rule. It never licenses fake code.
2. **Identical bytes alone are not a match.** A function counts as matched only when its bytes
   match *and* it passes every **[match]** rule: R1 and R2 (one declaration per type and global),
   R4 (no offset casts), R13 (real vtables), R17 (no fake code), R18 (no assembly bodies).
   Byte-identical but failing is `MATCH-PENDING`. Report it, and don't count it.
