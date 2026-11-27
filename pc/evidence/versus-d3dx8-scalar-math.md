# Versus D3DX8 scalar math

The DirectX 8.1 release archive `d3dx8.lib` has SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
Its member `obj\i386\d3dxmath.obj` has SHA-256
`e1be1ced1b28175c071fd8d6fda60f5b01f8d21158a45224a50d254d4c944358`.
The member's version-2 CodeView symbol section contains an `S_COMPILE2_ST`
record (kind `0x1013`, x86 machine `6`). The record identifies the Microsoft
optimizing compiler, C++ front end 13.00.9176 and back end 13.00.9178.

Each row below is a named, complete executable COFF COMDAT (flags `0x60101020`).
The original archive section, linked at the Versus address through the stated
unit bindings, agrees with every byte of the locked image. Each
`c_D3DX` symbol has C++ linkage and uses `__stdcall`. The archive gives
the separate indirect API dispatchers C linkage.

| Scalar function | Versus file offset | Bytes | COFF relocations | DDK `/O2` control bytes |
| --- | ---: | ---: | ---: | ---: |
| `c_D3DXMatrixfDeterminant` | `0x287bba` | 202 | 0 | 192 |
| `c_D3DXPlaneNormalize` | `0x289206` | 164 | 3 | 208 |
| `c_D3DXPlaneIntersectLine` | `0x2892aa` | 162 | 2 | 176 |
| `c_D3DXPlaneFromPointNormal` | `0x28934c` | 56 | 0 | 64 |
| `c_D3DXMatrixReflect` | `0x28a1ba` | 191 | 5 | 224 |

The XP DDK compiler and the recorded VC7.0 13.00.9466 compiler each rebuild
all five functions with size optimization and separate function sections
(`/O1 /Gy`). Plane normalization additionally uses `/Oi` for the inline
square root. Its DDK `/O1 /Gy` control without intrinsic expansion produces
177 bytes and a call to `sqrt`. The `/O2` controls in the table keep the
other flags fixed. These controls establish the code-generating choices
recorded in the recipes. The CodeView record identifies the producer
independently of these recompilations.

The archive's named `WithinEpsilon` call and its read-only float operands
`FLT_MIN` and `1.0f` bind the normalizer. Its dispatch entry at file offset
`0x289200` jumps through the slot initialized to the selector at `0x28a749`,
which jumps to the scalar body. Plane intersection calls the retail
`MSVCR70!_finite` thunk at `0x2c351c`. Reflection calls the public plane
normalization dispatcher and multiplies each normal component by `-2.0f`.

## Vector and quaternion normalizations

The same archive member and CodeView record cover the scalar functions below.
Each complete named COMDAT independently links through its function receipt to the
locked Versus image. The vector and quaternion normalization COMDATs at
`0x288d9d` both agree with all 185 bytes at the shared retail entry.

| Scalar function | File offset | Bytes | XP DDK `/O2` control bytes |
| --- | ---: | ---: | ---: |
| `c_D3DXVec2Normalize` | `0x2894c5` | 141 | 192 |
| `c_D3DXVec3Normalize` | `0x2896f9` | 160 | 224 |
| `c_D3DXVec4Normalize` | `0x288d9d` | 185 | 256 |
| `c_D3DXQuaternionNormalize` | `0x288d9d` | 185 | 256 |
| `c_D3DXQuaternionInverse` | `0x288e5c` | 180 | 208 |

The three vector dimensions and quaternion normalization require `/Oi` with
`/O1 /Gy` to generate the inline square root. Omitting `/Oi` introduces a
library square-root call in these builds. Quaternion inversion instead uses
the precomputed single-precision square root of `FLT_MIN` as its lower bound
and takes the reciprocal of the squared length. Both the period DDK compiler
and the recorded VC7.0 RTM compiler reproduce all five named implementations.
