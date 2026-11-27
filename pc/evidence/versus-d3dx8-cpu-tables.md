# Versus D3DX8 processor tables

The DirectX 8.1 release archive `d3dx8.lib` has SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
Its named table installers establish the calling conventions, table layout,
implementation symbols and processor family. Two original COFF sections
linked with the recorded bindings match the entire retail function.

| Complete function | File offset | Bytes | COFF relocations | Release member |
| --- | ---: | ---: | ---: | --- |
| `x86_D3DXInitFastTable` | `0x28de87` | 60 | 8 | `obj/i386/d3dxmathx86.obj` |
| `x3d_D3DXInitFastTable` | `0x28d805` | 550 | 63 | `objd/i386/d3dxmathx3d.obj` |

The x86 member SHA-256 is
`d310389042a180b5ab60fa6ea01e8433b59f42c512be4931ee1fc223778a664f`.
The 3DNow! member SHA-256 is
`aa1a061b4ef8b978209ba0e345da13086f04785ea0f748bdb18d60b8f8f2bc1d`.
Their CodeView S_COMPILE2_ST records identify the Microsoft C++ front end
13.00.9176 and back end 13.00.9178 for x86. Both the XP DDK compiler and
the recorded VC7.0 compiler reproduce the complete sections using
`/O1 /Gy`. Changing the DDK compiler to `/O2 /Gy` produces contributions
of 64 and 560 bytes, respectively. VC7.1 also reproduces the two
size-optimized sections. The release members establish the producer
independently of these recompilations.

The retail 3DNow! installer requires the MMX and 3DNow! flags and
replaces five functions on processors that also have extended MMX and
extended 3DNow!. The named COFF relocations distinguish the K7 and
baseline functions sharing those five table slots.

The retail SSE and SSE2 installers update 35 and 36 pointers. The earlier
8.1 tables each have a 272-byte installer. Retail additionally installs
matrix X and Y rotation in the SSE table, and quaternion inverse and
spherical linear interpolation in the SSE2 table. The named release
implementations corroborate these four slot identities. In particular,
`sse2_QuaternionSlerp` is the name present in the release member. The
two installer receipts are candidates because the 8.1 release installer
sections differ from these retail versions.

Both Intel shadow functions take and return a Direct3D matrix pointer.
The public table slot takes and returns a D3DX matrix pointer. The source
keeps the decorated implementation signatures and performs the pointer
conversion at the two assignments that require it.
