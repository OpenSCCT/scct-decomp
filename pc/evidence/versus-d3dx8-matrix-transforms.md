# Versus D3DX8 scalar matrix transformations

The DirectX 8.1 release archive `d3dx8.lib` (SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`)
contains the named `obj/i386/d3dxmath.obj` member (SHA-256
`e1be1ced1b28175c071fd8d6fda60f5b01f8d21158a45224a50d254d4c944358`).
Its CodeView compiler record `S_COMPILE2_ST` reports the Microsoft x86
optimizing compiler, front end 13.00.9176 and back end 13.00.9178.
The member contains the two complete C++ `__stdcall` scalar functions.

| Scalar function | Versus file offset | Bytes | Relative calls | Linked SHA-256 |
| --- | ---: | ---: | ---: | --- |
| `c_D3DXMatrixAffineTransformation` | `0x28890f` | 230 | 3 | `ef45703f25b515bf82e54003fd910f5ce6a02d8a2141dfd6a152fb68412a07b4` |
| `c_D3DXMatrixTransformation` | `0x289e06` | 692 | 11 | `946a0a91ea1762f12abd0e2b6f8588fcbd0b69ba9324cc8e75752a5b71e0db06` |

All fourteen COFF relocations refer to named public D3DX matrix APIs.
The locked Versus image resolves each API through a six-byte indirect jump
and an initialized slot. Each slot initially names a selector that ends
with a direct jump to the corresponding scalar implementation.

| Matrix API | Dispatcher RVA | Slot VA | Initial selector VA | Scalar fallback RVA |
| --- | ---: | ---: | ---: | ---: |
| Multiply | `0x287c84` | `0x10c3bf84` | `0x10b89cc7` | `0x287c8a` |
| Transpose | `0x287ec0` | `0x10c3c00c` | `0x10b89cd3` | `0x287ec6` |
| RotationQuaternion | `0x288827` | `0x10c3c010` | `0x10b89dc1` | `0x28882d` |

Relocating the two original Microsoft member sections through these three
dispatcher addresses reproduces both complete retail ranges. The C++ builds
stack matrices with 16-byte alignment, also visible in both retail prologues.
Both functions contain the same inlined rotation around an optional center.
The general transform additionally rotates into the scaling axes, scales,
and rotates back before applying the final rotation and translation.

Both the XP DDK compiler and VC7.0 RTM 13.00.9466 reproduce all 922 bytes
with `/O1 /Gy`. The DDK's `/O2 /Gy` produces 224 and 608 bytes respectively.
With `/Od /Gy` it produces 116 and 483 bytes. The original toolchain is
identified by the archive member. The tests establish size optimization.
`/O2 /Os /Gy` also reproduces both functions. Processor tuning remains
unspecified because the default and `/G6` produce the same bytes.

Rebuild the two recorded source units with `pc/verify_build.py` and
`--source src/d3dx_matrix_transforms.cpp`. To repeat the archive check,
extract `obj/i386/d3dxmath.obj` from the release library and give the member
to `tools/link_x86.py`'s `link_function` with each unit's recorded symbol,
size, retail VA and `link_bindings`. Both returned byte strings must hash
to the values above.
