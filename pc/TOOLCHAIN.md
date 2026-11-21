# Steam compiler and flag evidence

| Steam build 252084 program | Retail evidence | What remains to establish |
| --- | --- | --- |
| Campaign and co-op | The PE32 optional header records linker version 7.10. A scan of the DOS stub up to the PE signature found no Rich marker. REA found 150 exports. | The compiler build and options for the game translation units. The linker version identifies only one part of the build. |
| Versus | The PE32 optional header records linker version 7.00. Its Rich records include linker product `0x003d`, build 9466, count 1, along with C, C++, assembler and library producer records with multiple build numbers. REA found zero exports. | Which compiler produced each source unit, the compiler flags and the linker command line. |

Ghidra's product table associates `0x003d` with the Visual Studio .NET 2002 linker, `0x001c` and `0x001d` with its C and C++ tools, and `0x0060` with Visual Studio .NET 2003 C++. The Versus file includes all four IDs. Mixed producer records can come from several libraries and translation units. The output of `workflow.py â€¦ inspect` lists the raw product IDs, builds and counts for this exact binary. [Microsoft PE format](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format) Â· [Ghidra 12.1.4 product table](https://github.com/NationalSecurityAgency/ghidra/blob/Ghidra_12.1.4_build/Ghidra/Features/Base/data/ms_pe_rich_products.xml)

## Campaign sound catalogue

The campaign export table resolves `_SND_fn_lGetSoundTextureCount@0`, ordinal 57, to preferred VA `0x11048e10` (RVA `0x748e10`). REA export evidence is `ev_2265eec6bc83a81dc32381bb16c057ab071e61ff853f63232491831a06a3e06d`. Ghidra 12.1.4 identified a three-byte function returning zero. The independent C implementation uses the export's x86 calling convention.

| Experimental x86 compiler | Flags | Local comparison |
| --- | --- | --- |
| MSVC 19.44.35229.0 | `/O2 /c` | Three identical bytes, objdiff symbol 100% |
| MSVC 19.44.35229.0 | `/O1 /c` | Three identical bytes, objdiff symbol 100% |
| MSVC 19.44.35229.0 | `/Od /c` | Different function size |

An exact result for this constant return cannot distinguish the two optimisations. Reproducing an historical recipe requires independent evidence for the compiler version and flags. A shipped build record, debug information or a representative set of functions with differentiating code generation could advance the investigation.

## Versus vector arithmetic

The [Enhanced build annotations](../../re/ghidra/annotations/game.json) name `UObject::execDot_VectorVector` at preferred VA `0x109467f0`. The SHA-256 of that Enhanced reference is recorded in the [binary lockfile](../../re/binaries.lock.json). Ghidra 12.1.4 on the independently verified Steam payload found a 108-byte function at the same address. The complete routine has the same SHA-256 in the two binaries, `2789f485c74697821d84e0920b20249405600439c9591fe366e460f2eda95c13`. The Steam instructions dispatch two VM operands and compute the three-component dot product with x87 arithmetic. REA export evidence for this payload is `ev_017b93cbbfaa4dd81368ef0f59f67c444f3ac11a1601baa6242fa3ea4048528b`.

The function name transfers from a matching reference body. Its original translation unit, build flags and independently compiled implementation are still open. The study adds a reproducible anchor for Versus contributors.

## Period compiler experiments

The x86 optimizing compiler from Microsoft Visual C++ Toolkit 2003 identifies
itself as 13.10.3052. Its `cl.exe` has SHA-256
`9e45887874de83876ada2adc9943daa9094d1c1f1f9c3d93eac5ad57a1cbee2a`.
It reproduces the campaign audio ASCII case routines, spatial calculations
and numerous Versus script natives. In a seven-function Versus GUI comparison
covering 610 bytes, `/O2 /Gy`, `/Ox /Gy` and `/O2 /G6 /Gy` each matched
all seven. `/O1 /Gy` matched one, and x86 MSVC 19.44 matched none of the
seven in the tested profiles. The manifest records a working recipe for
each independently compiled function.

Twelve wide-string and Unicode digit functions in the campaign cover 931 bytes
and match complete, uniquely
located sections of named VC7.1 runtime objects. CodeView in the Toolkit
library identifies its C frontend and backend as 13.10.3052. The corresponding
VC7.1 RTM objects identify 13.10.3077. Across all 722 paired archive members,
the initialized non-debug section data agree. The 1,069 paired named code
contributions also agree in bytes and relocation locations. This identifies
the runtime family and explains why these twelve units still carry candidate
receipts. The campaign manifest records the per-member hashes. [CRT makefile](https://github.com/QianNangong/VC6Ultimate/blob/620bdecb834a8d59c576e20fa65086b4c654eb5b/VisualUltimate/WindowsSDKs/vc7/crt/src/makefile.sub#L38-L67)

[Campaign compiler and switches](evidence/campaign-vc71-o2.md) is the
reviewed basis for Campaign `/O2` and `/O2 /EHa` units. It names 13.10.3077
as the original compiler, shows that 13.10.3052 generates the same code, and
records the switch experiments across all 15,904 units.

## Versus actor placement

The stock AActor placement callback at RVA `0xae2f0` transfers the object in
EAX to the initializer at RVA `0x92100`. With both bodies in one C translation
unit, Microsoft C/C++ 13.10.3052 assigns EAX to the private initializer.
The full 75-byte initializer and 178 registered placement callbacks reproduce
4,037 Steam bytes using `/O2 /Gy`. The same compiler reproduced all 179 with
`/Ox /Gy` and `/O2 /G6 /Gy`, 159 with `/O1 /Gy` and zero with `/Od /Gy`.
The optimization switches used by Ubisoft remain undetermined.

An independent C declaration with `regparm(1)`
reproduces this convention using Clang 19.1.0, revision
`2cfe42ea4a7fe364dcb197beca469af8edec0ad6`, for `i686-pc-windows-msvc`.
With `-O2 -ffunction-sections`, 177 complete placement callbacks match in
both the Steam executable and the locked Enhanced reference. Rebuilding with
ordinary cdecl or with `-O0` produced zero complete matches in this group.
The compiler executable used to reproduce these candidates has SHA-256
`0d08cdd309906d6287d4791fabd3f00ad8d6bbaa550d6615bdefd5d352de0dab`.

## Linked tree removal in the Steam executables

The C function in `src/tree_unlink_node.c` reproduces the 959-byte function
at campaign RVA `0x5ed4a0` and Versus RVA `0x235f90`. Each function returns
immediately before a single NOP. The compiler's 960-byte COFF contribution
matches the body and that NOP in both executables. The tracker counts 959
bytes for each function.

The tested build uses the x86 VC6 driver and C frontend from Visual Studio 6
Service Pack 6 and the optimizing backend from the Visual C++ Processor Pack
for Service Pack 5, with `/O2 /Gy`.

| Compiler component | SHA-256 |
| --- | --- |
| `cl.exe` | `1bf99f206271ecdbd13da2829192ea2c02e2a44c740b8d72935d5d9cb753b156` |
| `c1.dll` | `fc6771ed73524417877f1263604bf8b9b9cd403c8cfb72b2e25737bdc81d592e` |
| `c2.dll` | `6c8e3988a5ccd69a9f9829b5c7512848d71c018b8d24be3928d7b00b5f79f231` |

## C++ units with exception frames

The engine is C++. Destructors whose bodies can unwind into a parent destructor
carry a Microsoft C++ exception frame: `push -1`, `push` of the frame handler,
and a link through `FS:[0]`. C cannot produce that frame, so these units are
C++ translation units built by Microsoft C/C++ 13.10.3052 with
`/O2 /Gy /GX`.

`src/versus_object_destructors.cpp` reproduces 215 complete Versus class
destructors (109 bytes each). Each runs the inlined
`UObject::ConditionalDestroy()` before its parent destructor, as the engine's
`DECLARE_CLASS` destructor does. Class names come from the registered
placement constructors that install each vtable. Parent names come from the
vtable that each parent destructor installs.
`src/versus_member_destructors.cpp` adds 39 destructors that also destroy one
member between `ConditionalDestroy()` and the parent destructor, either through
the member's out-of-line destructor or through a one-argument release helper.
Their frames have two unwind states: the member, then the parent.
`src/versus_multi_member_destructors.cpp` adds 46 destructors with two to
seventeen members, destroyed in descending offset order with one unwind state
each. VC7.1 rotates `eax`, `ecx` and `edx` when consecutive inlined member
destructors pass `this` straight to a release helper. Retail computes every
address in `eax`, which VC7.1 reproduces only when the inlined destructor first
copies `this` into a local (`Released *self = this; ReleaseMember(self);`).

`tools/link_x86.py` accepts three references that only C++ frames make.
`__except_list` is the absolute offset 0 that the C runtime defines for the
thread information block. A function's own `__ehhandler$` label in its
`.text$x` section is bound to the retail handler. A `??_7` virtual function
table is bound to the retail table. The audit verifies each handler as
`mov eax, FuncInfo; jmp`, checks the FuncInfo magic `0x19930520`, and follows
the only unwind action to a funclet that calls the same parent destructor.

### Catch blocks and `/EHa`

Node allocators of the engine's `std::list` and `std::map`/`std::set` keep a
`try`/`catch (...)` around their link construction even though nothing in it
can throw, and keep every local in the try region in memory. Only
asynchronous exception handling (`/EHa`) reproduces that: with `/GX` the
compiler removes the try block. `src/container_nodes.cpp` builds these with
`/O2 /Gy /EHa`, and `src/container_algorithms.cpp` builds the uninitialized fill
and copy loops of `std::vector` storage the same way.

MSVC places a catch block after the function's return in the same section,
under a private `$L` label. Ghidra's function body stops at the return and
nothing indexes the catch block, so each unit covers the whole section. The
linker treats a private `$L` function label at a nonzero offset as part of its
function. The audit requires the indexed body to end at that label, no indexed
function inside the catch range, and the retail FuncInfo to name the label as
the only `catch (...)` handler.

### Link-time code generation (Versus)

The Versus Rich header lists 292 objects from VC7.0 13.00.9466 built for
link-time code generation (`/GL`, product 0x2c). LINK 7.00.9466 `/LTCG`
generated their code and gave internal functions custom calling conventions:
`this` and arguments in ESI, EDI, EAX or EBX, `this` on the stack with
`ret 4`, or no prologue. An object file holds only intermediate language, so
these units are rebuilt as a linked DLL.

A unit with an `ltcg_link` record compiles its source with `/GL`.
`pc/verify_build.py` then links the object with the LINK.EXE beside the
compiler, using the fixed options in `tools/link_image.py`, the record's
scaffolding roots, and a stub object with one `int3` code section for each
external the source declares but does not define. The source ends with a
driver function, marked as scaffolding, that calls the unit the way retail
callers do. The linker picks the calling convention from those callers. The
driver also passes the address of each global the function reads to an
external function, because in the original program those globals have their
address taken elsewhere, and that stops the optimiser moving loads past stores.

The record gives the function's file offset and address in the DLL, and
every address field in it, with its kind (absolute or rel32 branch) and the
symbol it refers to. `tools/link_image.py` checks that each built field refers
to that symbol's address in the DLL, rewrites it with the retail address from
`link_bindings`, and compares source-defined string literals with retail byte
for byte. The DLL is linked at 0x10000000, so no unbound field can equal its
retail value by accident. The audit links the DLL again, re-derives the field
list from the DLL's base relocations and from rel32 branches that leave the
function, and checks the symbol names against a `/MAP` of the same link.
