# Versus D3DX8 math dispatch

The DirectX 8.1 release archive and its `d3dxmath.obj` CodeView compiler
record are identified in [the scalar math evidence](versus-d3dx8-scalar-math.md).
The member defines 57 public math entry points with six-byte COFF contributions.
Each uses a single DIR32 relocation against `g_D3DXFastTable` with a
distinct, four-byte-aligned member addend. Fourteen such entry points
survive in the Versus executable. Linking each complete named contribution
at its retail address reproduces every byte, including the field address.

| Public entry point | Retail offset | Table member | Rebuilding compiler and flags |
| --- | --- | --- | --- |
| D3DXVec2Transform | `0x287511` | `0x00` | 13.00.9466 `/O1 /Gy` |
| D3DXVec3Normalize | `0x287517` | `0x1c` | 13.00.9466 `/O1 /Gy` |
| D3DXVec3TransformCoord | `0x287784` | `0x28` | 13.00.9466 `/O1 /Gy` |
| D3DXMatrixMultiply | `0x287c84` | `0x0c` | 13.00.9466 `/O1 /Gy` |
| D3DXMatrixTranspose | `0x287ec0` | `0x94` | 13.00.9466 `/O1 /Gy` |
| D3DXMatrixInverse | `0x288169` | `0x48` | 13.00.9466 `/O1 /Gy` |
| D3DXMatrixRotationQuaternion | `0x288827` | `0x98` | 13.00.9466 `/O1 /Gy` |
| D3DXQuaternionRotationYawPitchRoll | `0x288c22` | `0x64` | 13.10.3052 `/O2 /Gy` |
| D3DXQuaternionMultiply | `0x288d01` | `0x4c` | 13.00.9466 `/O1 /Gy` |
| D3DXQuaternionInverse | `0x288e56` | `0xb0` | 13.00.9466 `/O1 /Gy` |
| D3DXQuaternionLn | `0x288f10` | `0xdc` | 13.00.9466 `/O1 /Gy` |
| D3DXQuaternionExp | `0x288f94` | `0xe0` | 13.00.9466 `/O1 /Gy` |
| D3DXQuaternionSlerp | `0x289035` | `0x8c` | 13.10.3052 `/O2 /Gy` |
| D3DXPlaneNormalize | `0x289200` | `0x54` | 13.00.9466 `/O1 /Gy` |

The two by-value floating-point wrappers use the VC7.1 speed builds shown
above. VC7.0 size builds copy the floating arguments, producing 39 bytes
for `D3DXQuaternionRotationYawPitchRoll` and 29 for `D3DXQuaternionSlerp`.
The 8.1 release object provides independent six-byte controls for
all fourteen entries.

`D3DXCpuOptimizations` at `0x28d067` copies 57 function pointers from
the scalar table at `0x33c060` into the active table at `0x33bf78`.
The release object defines this writable table with 55 relocations to named
initializers at the same member indices. Its last two slots are zero in both
the object and the executable. The on-disk active table contains 55 nonzero
initializer addresses, of
which 54 are distinct. The vector-four and quaternion normalization slots
share their initializer and scalar implementation. Every initializer
first enables CPU optimization, then calls or jumps directly to its
corresponding scalar function. The two linked references were checked
independently against the optimizer entry and the parallel scalar table.

All 54 initializer bodies rebuild with the XP DDK 13.00.9176/9178,
VC7.0 13.00.9466 and VC7.1 13.10.3052 using `/O1 /Gy`. The release
archive's initializer bodies dispatch through the active table. Producer
attribution for the distinct retail first-call implementation remains open.
The optimization-state enum tag comes from the decorated external global
in `cpudetect.obj`. Its enumerator spellings describe the observed selector
results.
