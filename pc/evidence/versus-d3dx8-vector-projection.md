# Versus D3DX8 vector projection

The DirectX 8.1 release archive `d3dx8.lib` (SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`)
provides the named C++ scalar implementations in `obj\i386\d3dxmath.obj`
(SHA-256 `e1be1ced1b28175c071fd8d6fda60f5b01f8d21158a45224a50d254d4c944358`).
The member's CodeView S_COMPILE2_ST record identifies the Microsoft x86 C++
front end 13.00.9176 and back end 13.00.9178. Both original COFF sections
link independently to the locked Versus image using the unit bindings.

| Function | File offset | Complete COFF bytes | Instruction bytes | XP DDK `/O2 /Gy` control bytes |
| --- | ---: | ---: | ---: | ---: |
| `c_D3DXVec3Project` | `0x2898f0` | 397 | 365 | 448 |
| `c_D3DXVec3Unproject` | `0x289a7d` | 422 | 390 | 512 |

Each section contains eight compiler-generated switch addresses after its
return. The verifier resolves every arm from COFF local symbols and compares
all 64 bytes of switch data against the locked image. The original COFF names
the public matrix multiplication, matrix inversion and homogeneous coordinate
transform dispatchers used by the scalar code.

The XP DDK x86 compiler and the recorded VC7.0 13.00.9466 compiler both
rebuild the two complete sections with `/O1 /Gy`. The speed-optimized DDK
controls in the table retain the same section option. VC7.1 also matches
both size-optimized sections. The independent release object identifies the
original producer.
