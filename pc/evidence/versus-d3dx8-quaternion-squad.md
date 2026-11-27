# Versus D3DX8 quaternion squad control points

The DirectX 8.1 release library `d3dx8.lib` has SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
It contains `obj/i386/d3dxmath.obj` (SHA-256
`e1be1ced1b28175c071fd8d6fda60f5b01f8d21158a45224a50d254d4c944358`).
Its CodeView `S_COMPILE2_ST` record identifies the original Microsoft x86
optimizing compiler, C++ front end 13.00.9176 and back end 13.00.9178.

The member names `c_D3DXQuaternionSquadSetup`. Its first three parameters
are output quaternions and the remaining four are read-only input
quaternions. The entire 986-byte executable section reproduces the
locked retail image at file offset `0x28a341`, including the two calls
to QuaternionInverse, six to QuaternionMultiply, four to QuaternionLn
and two to QuaternionExp. Both references to the tangent factor resolve
to the complete read-only constant `-0.25f` at VA `0x10c10c10`.

Each public API dispatcher is a separate six-byte original COFF function.
Its named relocation targets `g_D3DXFastTable` with the member displacement
listed below. All four retail jumps locate the same table at VA
`0x10c3bf78`; the corresponding scalar function table starts at
`0x10c3c060`. These tables independently establish the four call targets.

| API | Retail dispatcher RVA | Member displacement | Scalar fallback RVA |
| --- | ---: | ---: | ---: |
| QuaternionInverse | `0x288e56` | `0xb0` | `0x288e5c` |
| QuaternionMultiply | `0x288d01` | `0x4c` | `0x288d07` |
| QuaternionLn | `0x288f10` | `0xdc` | `0x288f16` |
| QuaternionExp | `0x288f94` | `0xe0` | `0x288f9a` |

Relocating the original scalar COFF section through these four APIs and
its tangent factor produces SHA-256
`3986fca6462dffabaceae47bbed437cea412b1b8040c93d5786b4275c04dde24`.
Both XP DDK 13.00.9176 and VC7.0 RTM 13.00.9466 reproduce that digest
with `/O1 /Gy`. Their `/O2 /Gy` builds emit 1,504 bytes and their
`/Od /Gy` builds emit 866. The two compilers also reproduce the original
with `/O2 /Os /Gy`, establishing size optimization. VC7.1 13.10.3052
emits 986 bytes with `/O1 /Gy` and differs in instruction operands.

For the source replay, use `pc/verify_build.py` with
`--source src/d3dx_quaternion_squad.cpp`. For the original member,
extract `obj/i386/d3dxmath.obj` from the matching library and use
`tools/link_x86.py`'s `link_function` with the same unit's symbol,
length, retail virtual address and bindings. The stock read-only-data
reader checks the complete floating-point constant as well.
