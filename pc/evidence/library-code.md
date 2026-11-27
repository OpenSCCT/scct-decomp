# Library code named by other Windows builds

Other Windows programs that shipped with a PDB or a link map name the static library code they
link. Where Chaos Theory links the same library object, the function is the same bytes apart
from link-time operands, and its name, library and object file transfer.
[library_matches.py](library_matches.py) makes the comparison;
[library-functions.tsv](library-functions.tsv) lists the result.

**No game code transfers.** The collection compared (the Windows set of the Debugging.Games
archive, 317 entries) holds no Splinter Cell build and no Unreal Engine 2 build. What transfers
is Microsoft library code: 701 functions, 118,147 bytes.

| Program | Library | Functions | Bytes | Already units |
| --- | --- | ---: | ---: | ---: |
| Campaign | C and C++ runtime, objects of the Visual Studio .NET 2003 `LIBCMT.lib` and `libcpmt.lib` | 449 | 82,245 | 61 |
| Campaign | C runtime, named only by builds of other compiler versions | 54 | 4,306 | 0 |
| Campaign | D3DX | 107 | 18,170 | 2 |
| Versus | D3DX | 66 | 10,787 | 0 |
| Versus | Microsoft Layer for Unicode (`unicows.lib`) | 13 | 1,822 | 0 |
| Versus | C runtime | 12 | 817 | 0 |

638 of the 701 are not units yet: 96,752 Campaign bytes and 13,426 Versus bytes whose identity
is now known without reading them.

## Method

For every named function of a source build, the bytes are taken with link-time operands masked:
relative call and jump targets, and 32-bit operands that point into the source image. The
masked pattern is searched in the code of each Steam executable. A hit must agree on every
unmasked byte, and each masked operand must point into the Steam image. Functions shorter than
24 bytes, or with fewer than 18 unmasked bytes, are not compared.

A location is kept only when all three hold:

1. exactly one address in the executable matches;
2. the name comes from a library the game itself links (the C and C++ runtime, D3DX, the
   Microsoft Layer for Unicode), as the source build's module record or map says;
3. the match covers the longest function any build names at that address.

1,412 other locations matched only game objects or libraries the game does not link, and 225
matched library code at several addresses. Neither is in the list.

## Source builds

Twenty-two symbol sets from thirteen programs were compared. These supply the names:

| Build | Compiler | Supplies | SHA-256 of the image |
| --- | --- | --- | --- |
| *Boiling Point: Road to Hell*, 2005-07, five modules with PDBs | Microsoft C/C++ 13.10.3077, static runtime | the VC7.1 runtime: its `LIBCMT.lib` objects are the ones Campaign links | `Xenus.exe` `743aed256d8438bee0eb0e2457277f370a1bd7b78e08c7dccf8e7cd0461b475a` |
| *Star Trek: Armada II* 1.1, 2002-01, PDB and map | VC6 | D3DX8 objects by name (`D3DX8:d3dxmath.obj`) | `f9e283deb68506a779feceecac144d1c035f6e4fe79c636e5207437780fecb28` |
| *Tomb Raider: The Angel of Darkness*, 2003-09, PDB | VC6 | D3DX9 objects, including its private zlib | `0be26792c46a7bfddd232f8fbe5ad18110d9e6de0d031ce71d0e68a26559e68f` |
| *World of Warcraft* alpha 1.0.0.3368, 2003-12, PDB | VC6 | `unicows.lib` | `861875776ce14a05fb49d4bb09f673d8a8939e2753372c3673ae6d43ac1a1c1f` |
| *Tomb Raider: Legend*, 2006-05, PDB | 13.10.3077 | 47 further runtime and D3DX functions | `a1ed2cd21b03764935f3a12f9be89b6ff3d0d5d2849caefe2e15282ca0b2731e` |

*Plants vs. Zombies*, *Bejeweled Blitz*, *Bejeweled 3*, *Royal Quest*, *MapleStory*,
*Pac-Man All-Stars*, *Soul Reaver* and *Thief 2* confirm names the builds above already give,
mostly the runtime's hand-written assembly, and add eight of their own. 457 of the 610 Campaign
locations are named by two or more symbol sets.

## What it shows

### Campaign links the VC7.1 static runtime, object for object

449 functions from 179 runtime objects sit in Campaign as *Boiling Point*'s PDB records them,
in link order: `tzset.obj` gives `_tzset_lk`, `cvtdate`, `_isindst_lk` and `_isindst` at
consecutive addresses from RVA `0x6418d1`. This agrees with the
[Campaign basis](campaign-vc71-o2.md) and extends it from twelve functions to 449. The list
names each function's object, so runtime units can be grouped as the library was.

The 61 runtime units already recorded agree with these names apart from a `steam_` prefix the
sources add (`_steam_sprintf` for `sprintf`). A recorded name is kept verbatim (R7).

### Versus does not link that runtime

Only twelve runtime functions match in Versus, all compiler support routines (`_chkstk`,
`_ftol2`, `_alldiv`, `__SEH_prolog`, the vector destructor iterator). Its other runtime code is a
different build, consistent with its 7.00 linker. Names for it need a Visual C++ 7.0 library.

### The Versus "Windows dispatch" units are the Microsoft Layer for Unicode

Versus links `unicows.lib`. Its loader matches from RVA `0x22125c`: `GetOrdinal`,
`GetProcAddressInternal`, `LoadGodot` and `ResolveThunk` of `resolve.obj`, then the `GodotFail…`
stubs of `failure.obj`. Each Unicode thunk passes its DLL name, export name, writable
dispatch slot, optional override function pointer and `GodotFail` routine to `ResolveThunk`
at RVA `0x221737`. The slot initially points to the thunk itself. If the fourth parameter is
nonzero on the legacy platform path, the resolver installs that function in the slot.

| Library name | Object |
| --- | --- |
| `<dll>_<Api>_Thunk`, for example `user32_DispatchMessageW_Thunk` | `thunk_<dll>_<Api>.obj` |
| `GodotFail<Api>` | `failure.obj` |
| `ResolveThunk` | `resolve.obj` |

The two contiguous dispatch ranges contain 74 thunks. Both begin at four-byte-aligned
addresses, RVA `0x220e50` and RVA `0x2840f0`; each thunk occupies 37 bytes without
intervening alignment. Seventeen currently have candidate receipts from MSVC 19.44.
The others reproduce with a period compiler. These library receipts supply no compiler
attribution for the game's own code.

### D3DX carries its own zlib

The D3DX matches include `huft_build`, `inflate_blocks_reset`, `d3dx_inflate_fast` and
`jzero_far`, in D3DX's own objects and namespace: the inflate and JPEG code found in the executables
belongs, at least in part, to D3DX and not to separately linked libraries. The matches come
from D3DX8 and a 2003 D3DX9, so only functions unchanged between SDK releases match; the SDK
release the game was built with would name the rest.

### 945 existing units are compiler-shaped code, not hand-written functions

Outside the list, 945 recorded units (34,792 bytes) are byte-identical to functions of
unrelated programs. Their names there say what kind of code they are:

| Kind, by the other program's name | Units | Bytes |
| --- | ---: | ---: |
| scalar deleting destructor, which the compiler generates | 437 | 13,869 |
| destructor | 233 | 10,318 |
| standard container or string member | 246 | 9,377 |
| constructor | 29 | 1,228 |

No name transfers here, but the kind does. A unit written as
`void __fastcall delete_record_05b9b0( … )` is the deleting destructor the compiler emits for a
class with a virtual destructor: its source is that class, not a C function (R12, R17).

## Limits and next steps

- A masked match is evidence of identical code, not of identity, for short generic functions.
  That is why names from game objects are never taken and why several-address matches are left
  out.
- Further names follow from the list without new evidence: 100 Campaign and 15 Versus functions
  are called by listed functions at operands the source build names, and 399 and 24 data
  objects are referenced the same way. They are leads to confirm, not part of the list.
- The libraries themselves are a better source than other programs' PDBs: `LIBCMT.lib` and
  `libcpmt.lib` of Visual Studio .NET 2003, the DirectX SDK's `d3dx9.lib` of the release the
  game used, and the Platform SDK's `unicows.lib` name every object, not only those some other
  program happened to link.
- The archive's Xbox builds of the same years (x86, the same compiler family) were not compared.
