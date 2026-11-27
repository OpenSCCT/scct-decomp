# Versus D3DX8 graphics setting lookup

The DirectX 8.1 release library `d3dx8.lib` has SHA-256
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.
Its `obj/i386/cpudetect.obj` member has SHA-256
`904acda956bf017833bc406a715811e877616ab5e1c8719e34456e859f991820`.
The CodeView `S_COMPILE2_ST` record identifies Microsoft x86 C++ front end
13.00.9176 and optimizing back end 13.00.9178.

The member's `GetD3DRegValue` section is 92 bytes. It matches the complete
Versus function at file offset `0x28ce91`. Its four COFF relocations identify
the key path and the three Windows calls, whose retail import slots are
independently named in the PE import directory.

| Operand | Retail VA | Referent |
| --- | --- | --- |
| `+0x0e` | `0x10bec270` | `Software\Microsoft\Direct3D` and its terminator |
| `+0x19` | `0x10bdf000` | `ADVAPI32!RegOpenKeyA` |
| `+0x37` | `0x10bdf004` | `ADVAPI32!RegQueryValueExA` |
| `+0x42` | `0x10bdf008` | `ADVAPI32!RegCloseKey` |

The retail D3DX CPU optimization selector at file offset `0x28d067` calls
the helper. Its type and size parameters let the caller read a DWORD setting.
Both XP DDK 13.00.9176 and VC7.0 RTM 13.00.9466 reproduce all 92 bytes
with `/O1 /Gy` or `/O2 /Os /Gy`. Both compilers emit 128 bytes at
`/O2 /Gy` and 119 at `/Od /Gy`. VC7.1 13.10.3052 also reproduces the
size-optimized body. The original COFF record identifies the compiler.

Replay with `pc/verify_build.py --source src/d3dx_settings.cpp` and the
locked Versus image.
