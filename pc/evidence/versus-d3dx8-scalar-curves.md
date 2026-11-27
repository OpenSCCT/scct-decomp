# Versus D3DX8 scalar interpolation, matrix and quaternion functions

The DirectX 8.1 release library `d3dx8.lib` has SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
Its `obj/i386/d3dxmath.obj` member has SHA-256
`e1be1ced1b28175c071fd8d6fda60f5b01f8d21158a45224a50d254d4c944358`.
The CodeView `S_COMPILE2_ST` record identifies the Microsoft x86 C++ front
end 13.00.9176 and optimizing back end 13.00.9178.

The seventeen original executable sections below reproduce all 2,379 bytes in
the locked Versus image. The object names the C++ scalar functions with a
`c_` prefix and contains a separate six-byte public C dispatcher for each API.
`WithinEpsilon` is the shared C++ comparison helper.

| Name | Versus file offset | Bytes | Scalar table displacement |
| --- | ---: | ---: | ---: |
| WithinEpsilon | `0x287364` | 45 |  |
| D3DXVec2Hermite | `0x287391` | 142 | `0x44` |
| D3DXVec2CatmullRom | `0x28741f` | 175 | `0xbc` |
| D3DXVec2BaryCentric | `0x2874ce` | 67 | `0xc0` |
| D3DXVec3Hermite | `0x28751d` | 174 | `0xc4` |
| D3DXVec3CatmullRom | `0x2875cb` | 209 | `0xc8` |
| D3DXVec3BaryCentric | `0x28769c` | 93 | `0xcc` |
| D3DXVec4Cross | `0x2877f0` | 240 | `0x40` |
| D3DXVec4Hermite | `0x2878e0` | 209 | `0xd0` |
| D3DXVec4CatmullRom | `0x2879b1` | 243 | `0xd4` |
| D3DXVec4BaryCentric | `0x287aa4` | 119 | `0xd8` |
| D3DXMatrixTranspose | `0x287ec6` | 109 | `0x94` |
| D3DXMatrixScaling | `0x2884fc` | 92 | `0x84` |
| D3DXMatrixTranslation | `0x288558` | 92 | `0x68` |
| D3DXMatrixRotationQuaternion | `0x28882d` | 226 | `0x98` |
| D3DXQuaternionSquad | `0x28911e` | 87 | `0xac` |
| D3DXMatrixRotationYawPitchRoll | `0x289dcd` | 57 | `0xa0` |

Each dispatcher has a single original relocation to `g_D3DXFastTable`.
Its displacement picks the same entry in the scalar table at VA
`0x10c3c060`, where the locked executable records the function address
listed above. QuaternionSquad calls the QuaternionSlerp dispatcher at
file offset `0x289035` three times. MatrixRotationYawPitchRoll calls
QuaternionRotationYawPitchRoll at `0x288c22` and MatrixRotationQuaternion
at `0x288827`. The three retail dispatchers have the six original
instruction bytes after applying the table base VA `0x10c3bf78`.

For sections containing relocations, bind the original call targets and
floating-point constants using the unit records. The original COFF uses
private labels for some constants. Identify those labels by the identical
four-byte read-only values at the bound addresses. Seven sections compare
directly without relocations.

XP DDK 13.00.9176 and VC7.0 RTM 13.00.9466 each rebuild all seventeen
with both `/O1 /Gy` and `/O2 /Os /Gy`. None match with `/O2 /Gy` or
`/Od /Gy`. VC7.1 13.10.3052 produces the same results under these four
settings. The release member's CodeView record establishes the original
compiler. The source controls establish the size-optimized recipe.

Replay with `pc/verify_build.py` and the two source selectors
`src/d3dx_curve_math.cpp` and `src/d3dx_matrix_math.cpp`.
