# Versus scalar D3DX8 vector transforms and shadow matrix

The DirectX 8.1 archive member and its CodeView compiler record are identified
in [the scalar math evidence](versus-d3dx8-scalar-math.md). The release
object names the six scalar implementations below. Linking each complete
executable COMDAT to the retail address reproduces every byte.

| Scalar function | File offset | Bytes | DDK `/O2 /Gy` control size |
| --- | ---: | ---: | ---: |
| `c_D3DXVec3Transform` | `0x2876f9` | 139 | 176 |
| `c_D3DXVec3TransformNormal` | `0x28778a` | 102 | 128 |
| `c_D3DXVec4Transform` | `0x287b1b` | 159 | 192 |
| `c_D3DXVec2Transform` | `0x2895d2` | 107 | 144 |
| `c_D3DXVec2TransformNormal` | `0x2896bd` | 60 | 80 |
| `c_D3DXMatrixShadow` | `0x28a0e0` | 218 | 256 |

The five vector transforms have no relocations. The initialized scalar
dispatch table points to `c_D3DXVec3TransformNormal` at file offset
`0x33c078`. A direct fallback jump at `0x2898eb` confirms the entry.
The shadow matrix has one relative call to the public plane-normalization
dispatcher at `0x289200`. The named COFF relocation and the executable?s
callee agree.

The DDK compiler that matches the original 13.00.9176/9178 producer and the
recorded VC7.0 13.00.9466 compiler both rebuild all six complete functions
with `/O1 /Gy`. All six DDK `/O2 /Gy` controls produce different code.
