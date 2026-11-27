# Versus D3DX8 scalar matrix products

The two named C++ implementations in the `obj\i386\d3dxmath.obj` member
of the DirectX 8.1 release archive are individually identical to their
complete retail counterparts. Neither section has a relocation. The archive
hashes and the CodeView compiler producer are recorded in [the scalar math
evidence](versus-d3dx8-scalar-math.md).

| Function | Versus file offset | Bytes | XP DDK `/O2 /Gy` control size |
| --- | ---: | ---: | ---: |
| `c_D3DXMatrixMultiply` | `0x287c8a` | 566 | 576 |
| `c_D3DXMatrixMultiplyTranspose` | `0x287f33` | 566 | 576 |

The XP DDK compiler with front end 13.00.9176 and back end 13.00.9178,
and the recorded VC7.0 13.00.9466 compiler, each reproduce the complete
COMDATs under `/O1 /Gy`. Speed optimization changes both functions.
The two routines select a temporary when the destination aliases an
operand and write the sixteen row-column dot products in their respective
orientations.
