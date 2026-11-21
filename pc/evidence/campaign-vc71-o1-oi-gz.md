# Campaign compiler and switches: VC7.1, `/O1 /Oi /Gz`

This note is the `recipe_evidence` basis for Steam 252084 Campaign units built
with Microsoft C/C++ 13.10.3052 using `/O1 /Oi /Gz /Gy`. It covers third-party
C libraries linked into the game, starting with the zlib 1.1.4 inflate code.
The game code itself uses `/O2` (see [campaign-vc71-o2.md](campaign-vc71-o2.md)).

## Compiler

The build here uses 13.10.3052, the compiler established in the `/O2` note.
For these library objects that note's link-time evidence does not apply
directly. The evidence is the byte-identical result below. It is not
established whether the objects came from the game's own build or from a
prebuilt library compiled with the same compiler.

## Switches the retail code requires

**`/Gz`.** Every retail function in these libraries uses the stdcall
convention, internal (`static`) functions included. Each ends with `ret N`
for its stack arguments, and its callers do not adjust the stack. The
library sources declare no calling convention, so only the compiler's
default-stdcall switch produces this. Without `/Gz`, nothing matches.

**`/O1`.** The retail code is optimized for size. It uses `leave` to restore
the frame and short forms such as `push -5; pop edi` to load constants. The
`/O2` builds of the same sources are larger and match nothing.

**`/Oi`.** The libraries call `memcpy`, and retail inlines it as `rep movsd` and
`rep movsb`. `/O1` alone calls the runtime function instead. Only the
functions that copy memory depend on this switch.

## Experiment

[`flag_experiments.py`](flag_experiments.py) rebuilds every source file in a
group under each alternative, as in the `/O2` note. For the 15 zlib units in
eight files, at the time of writing, these are the results:

| Switches | Units identical | Bytes identical |
| --- | --- | --- |
| `/O1 /Oi /Gz /Gy` | 15 of 15 | 2,584 of 2,584 |
| `/O1 /Gz /Gy` (no `/Oi`) | 13 | 2,260 |
| `/Ox /Os /Gz /Gy` | 11 | 1,284 |
| `/O1 /Oi /Oy- /Gz /Gy` | 6 | 1,684 |
| `/O2 /Gz /Gy` | 1 | 51 |
| `/O2 /Oy- /Gz /Gy` | 0 | 0 |
| `/O1 /Oi /Gy` (no `/Gz`) | 0 | 0 |

The two units that need `/Oi` are `inflate_flush` and
`inflate_set_dictionary`. Both copy memory with `zmemcpy`, which zlib defines
as `memcpy`.

## Sources

The units carry the library's own source text, with its license notice. Two
mechanical changes make each unit build on its own:

- Local headers are inlined, and system headers are replaced by a short list of
  C runtime declarations.
- File-scope initialized tables are declared `__declspec(selectany)` rather
  than `static`. Each table becomes its own external contribution, bound to
  its retail copy. The table contents stay in the source.
