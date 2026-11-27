# Versus D3DX8 box-filter initialization

The two named initializer functions come from the same DirectX 8.1 release
`obj/i386/cd3dxblt.obj` as the scalar filters. Its SHA-256 is
`2180cb784f19c5f329ba2682ab3e95ae6fed8195bd3b7ca0852c91ed0146195a`.
The object's CodeView record identifies Microsoft x86 C++ front end
13.00.9176 and back end 13.00.9178.

| Format | Retail file offset | Bytes | Writable slot VA |
| --- | --- | ---: | --- |
| A8R8G8B8 | `0x296d43` | 56 | `0x10c3e1c8` |
| X8R8G8B8 | `0x296d7b` | 47 | `0x10c3e1cc` |

Each slot in the original and rebuilt COFF data has one four-byte pointer
relocation to its format's initializer. The locked retail slots contain the
two corresponding function addresses. The X8 slot supplies an authenticated
map seed. Ghidra adds the complete 47-byte function ending at `0x296daa`.

Both initializers call the MMX query at file offset `0x28cf12`. They choose
the scalar entries at `0x296a1f` and `0x296b45` or the shared MMX entry
at `0x296c2d`. The 278-byte MMX section matches the original after binding
its sole relative call to the A8 scalar fallback. The initializer sections
match all retail instructions and all original named references.

Both XP DDK 13.00.9176 and VC7.0 RTM 13.00.9466 rebuild both functions
with `/O1 /Gy` and `/O2 /Os /Gy`. Their `/O2 /Gy` builds emit 48 bytes
per initializer and their `/Od /Gy` builds emit 89. The archived original
sections establish the producer.

Replay with the two source selectors `src/d3dx_box_filter_dispatch.cpp`
and `src/d3dx_box_filter.cpp` in `pc/verify_build.py`.
