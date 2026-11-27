# Versus D3DX8 plane through three points

The DirectX 8.1 release library `d3dx8.lib` has SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
Its `obj/i386/d3dxmath.obj` member has SHA-256
`e1be1ced1b28175c071fd8d6fda60f5b01f8d21158a45224a50d254d4c944358`.
The CodeView `S_COMPILE2_ST` record identifies Microsoft x86 C++ front end
13.00.9176 and back end 13.00.9178.

The 162-byte `c_D3DXPlaneFromPoints` section spans the entire retail function
at file offset `0x289384`. It subtracts the second and third points from the
first, computes the cross product and normalizes it in the first three plane
components. It stores the negative dot product with the first point in the
fourth component.

The only COFF relocation is a relative call at `+0x7b` to
`_D3DXVec3Normalize@8`. The original object names its six-byte dispatcher.
Relocating the dispatcher to the locked image's table base VA `0x10c3bf78`
with its original member displacement `0x1c` reproduces its bytes at file
offset `0x287517`. The scalar table at VA `0x10c3c060` independently
points to `c_D3DXVec3Normalize` at file offset `0x2896f9` for this slot.

Both XP DDK C++ 13.00.9176 and VC7.0 RTM 13.00.9466 reproduce the
complete original section with `/O1 /Gy` and `/O2 /Os /Gy`. Their
`/O2 /Gy` and `/Od /Gy` builds produce 192 and 151 bytes respectively.
VC7.1 13.10.3052 also matches with size optimization. The original member
provides the compiler identification.

Replay with `pc/verify_build.py --source src/d3dx_plane_math.cpp` and the
locked Versus image.
