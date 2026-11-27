# Versus D3DX8 quaternion conversion and interpolation

The release `d3dx8.lib` archive and its `obj\i386\d3dxmath.obj` member have
the identities and CodeView producer documented in [the scalar math
evidence](versus-d3dx8-scalar-math.md). The compiler's front end is
13.00.9176 and its back end is 13.00.9178. All three complete `c_D3DX`
sections have COMDAT flags `0x60101020`. With every archive relocation
resolved using the reconstruction's named retail bindings they reproduce
the locked Versus image.

| Scalar function | File offset | Bytes | Relocations | XP DDK `/O2` size |
| --- | ---: | ---: | ---: | ---: |
| `c_D3DXQuaternionBaryCentric` | `0x289175` | 139 | 4 | 192 |
| `c_D3DXQuaternionToAxisAngle` | `0x2889f5` | 157 | 3 | 176 |
| `c_D3DXQuaternionRotationMatrix` | `0x288a92` | 308 | 7 | 304 |

The period XP DDK compiler and the VC7.0 RTM compiler recorded in the
recipes both match all three complete functions with `/O1 /Gy`. The matrix
and axis-angle conversions use `/Oi` for intrinsic math. Recompiling
either without `/Oi`, or compiling any of the three with `/O2`, changes
its code. Barycentric interpolation sees the recovered `WithinEpsilon`
definition and calls the public spherical interpolation dispatcher three
times. Axis-angle conversion calls the `MSVCR70!_CIacos` thunk. The matrix
conversion takes the square root of the trace or a selected diagonal term
and uses the corresponding indexed quaternion component.
