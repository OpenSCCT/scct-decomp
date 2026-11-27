# Versus D3DX8 quaternion logarithm and spherical interpolation

The DirectX 8.1 release `d3dx8.lib` (SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`)
contains the named `obj/i386/d3dxmath.obj` member (SHA-256
`e1be1ced1b28175c071fd8d6fda60f5b01f8d21158a45224a50d254d4c944358`).
The member's CodeView record identifies Microsoft C++ front end 13.00.9176
and back end 13.00.9178. Both original scalar sections reproduce their
complete locked Versus functions after linking through the recorded names.

| Scalar function | File offset | Bytes | Linked SHA-256 |
| --- | ---: | ---: | --- |
| `c_D3DXQuaternionLn` | `0x288f16` | 126 | `92d15763ae7102569f0533eb425a58bb116426c47c4107bb576f5de39cf8881f` |
| `c_D3DXQuaternionSlerp` | `0x28903b` | 227 | `4bbbc5dfe79bddc9d785a10863ed435822d6b8191c532ea013e82b70cab00224` |

The original logarithm section binds the read-only float 1.0, the
`MSVCR70.dll!_CIacos` import through the jump at RVA `0x283c6c`, and
the existing `WithinEpsilon` implementation at `0x287364`. The public
logarithm dispatcher's COFF relocation uses `g_D3DXFastTable + 0xdc`;
the corresponding slot in the scalar fallback table at VA `0x10c3c13c`
names the complete body. For Slerp the original COFF section identifies
the three complete floating-point constants 0.0, 1.0 and FLT_EPSILON.
The retail public dispatcher at `0x289035` uses the Slerp fast-table slot.

| Original XP DDK front end 9176/back end 9178 | Logarithm | Slerp |
| --- | ---: | ---: |
| `/O1 /Oi /Gy` | 126, exact | 227, exact |
| `/O1 /Gy` | 135 | 277 |
| `/O2 /Oi /Gy` | 176 | 240 |
| `/O2 /Os /Oi /Gy` | 126, exact | 227, exact |

The recorded VC7.0 RTM 13.00.9466 rebuild gave the same results on all
four tests. Size optimization and floating-point intrinsics account for
the code-generating choices. The original named member identifies the producer.
Rebuild with `pc/verify_build.py` and `--source src/d3dx_matrix_math.cpp`.
To replay the original independently, give the extracted COFF member and
each recorded unit to `tools/link_x86.py`'s `link_function`, using
the locked-image read-only constant reader.
