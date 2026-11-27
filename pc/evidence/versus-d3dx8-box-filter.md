# Versus D3DX8 scalar texture box filters

The DirectX 8.1 release library `d3dx8.lib` has SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
Its `obj/i386/cd3dxblt.obj` member has SHA-256
`2180cb784f19c5f329ba2682ab3e95ae6fed8195bd3b7ca0852c91ed0146195a`.
The CodeView `S_COMPILE2_ST` record names Microsoft x86 C++ front end
13.00.9176 and optimizing back end 13.00.9178.

| Scalar function | Retail file offset | Complete COFF size |
| --- | ---: | ---: |
| `c_BoxFilter2D_A8R8G8B8` | `0x296a1f` | 294 |
| `c_BoxFilter2D_X8R8G8B8` | `0x296b45` | 232 |

Both original executable sections match the locked retail image byte for byte
without relocations. The functions average four source texels for each output
texel and round the color channels. The A8 format includes alpha. Its high
channel pair is shifted before addition to fit the sum in 32 bits. The X8
format writes the red, green and blue channels and clears the high byte.

Both XP DDK 13.00.9176 and VC7.0 RTM 13.00.9466 reproduce all 526 bytes
with `/O1 /Gy` and `/O2 /Os /Gy`. Their `/O2 /Gy` builds produce 368
and 288 bytes. Their `/Od /Gy` builds produce 292 and 276 bytes.
VC7.1 13.10.3052 also matches under size optimization. The original
object's compiler record establishes the producer.

Replay both source receipts with `pc/verify_build.py --source
src/d3dx_box_filter.cpp` and the locked Versus image.
