# Steam 252084 Versus D3DX8 stack and buffer attribution

Microsoft's signed DirectX 8.1 SDK release library supplies exact, consecutive code for the 18 measured Steam Versus functions at file offsets `0x28d144–0x28d4e2` (exclusive end). Nine stack functions account for 679 bytes and nine buffer functions for 247, totaling 926 distinct bytes. The largest member is the 232-byte `CD3DXSzStack::GenerateStringBuffer` at `0x28d303`.

## Provenance

| Artifact | SHA-256 |
| --- | --- |
| DirectX 8.1 SDK self-extracting installer, 173,778,784 bytes | `73f6791e0ae7f8a1d74f71d8ebe517a79c0cbf03fd344424696fd7a3816d2d02` |
| `DXF/DXSDK/lib/d3dx8.lib` in that installer, 2,150,226 bytes | `39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28` |
| `obj/i386/cd3dxstack.obj` in the release library | `c408d992d338ee5ee22114334311632ef9909ca69d33ae318d3bdaef39d1ea49` |
| `obj/i386/cd3dxbuffer.obj` in the release library | `9548a984a3d527878dc5313785cce8bb1808ac2f533d5998f30b73d0204f9ae7` |
| Locked Versus image | `e3da0a152a8152af0c912e42dac8ef5378279b2ceb4f335f4efab070d45c80f3` |

Windows Authenticode verified the installer signature from Microsoft Corporation, certificate thumbprint `90c22db300f44ec79beab4662bb77ed1e81843bc`, with a VeriSign timestamp. The listed member hashes cover their complete COFF objects, including debug records. Their timestamps are October 16, 2001 at 18:00:09 and 18:00:10 UTC.

Each object's CodeView `S_COMPILE2` identifies the Microsoft x86 C++ optimizing compiler, frontend **13.00.9176**, backend **13.00.9178**. Both have COFF `@comp.id = 0x001d23da`. They record their original `NT32_Fre/multimedia/directx/dxg/d3dx8/core/obj/i386` output paths. The retail Rich record `0x001c23da` counts 78 objects under a different product identifier. The member-specific attribution comes from the two original COFF records and their linked retail contributions.

## Independent link checks

- The SDK's named buffer vtable contains seven relocations. Resolving their ordered method symbols produced one identical table in retail at VA `0x10bec2b4`. The SDK table's sixth entry references a COFF weak external for the vector deleting destructor, whose auxiliary record identifies the scalar deleting destructor at `0x10b8d467` as fallback. The SDK scalar destructor calls the base destructor at `0x10b8d3eb`.
- The signed library's separate `init.obj` defines `IID_ID3DXBuffer` and the Microsoft Windows Kits 10.0.22621 x86 `Uuid.Lib` member `unknwn_i.obj` defines `IID_IUnknown`. Their complete 16-byte values each occur exactly once in retail, at VAs `0x10bdfb00` and `0x10bf1f0c`. They independently bind QueryInterface.
- The existing Versus engine allocation/deallocation receipts identify VAs `0x109042e0` and `0x10a50880`. Both load `GMalloc` at `0x10c73bf0`. The former passes the literal UTF-16 allocation tag `new` to allocator slot zero, and the latter dispatches its pointer to the free slot at +8.
- The named VC7 runtime `ehprolog.obj` has a relocation-free 31-byte `__EH_prolog` that appears once in retail at VA `0x10bc3524`. The PE import directory names the `MSVCR70.dll!__CxxFrameHandler` IAT entry. Its unique executable jump thunk is at `0x10b83a54`. The x86 SEH-chain access is FS:[0].
- Across the retail image, one cleanup and handler pair matches the SDK `GenerateStringBuffer` frame. The cleanup starts at VA `0x10bc9f06`, pushes [ebp-0x18] and calls the global delete at `0x10a50880`. The handler at `0x10bc9f10` loads FuncInfo `0x10c1aee8` then tail-jumps to the named CRT handler. The one-state unwind map at `0x10c1aee0` reaches that cleanup from level 0 to -1. All 20 unwind-code bytes and all 36 associated unwind-data bytes independently compare after relocation. They are outside the 926 credited bytes.
- The release symbol for string-stack Push takes `char *`. The string and DWORD Pop methods share the body at `0x28d1d0`. Both GetLastError methods share the eight bytes at `0x28d2fb`. Each retail range counts once.

## Compiler and switch controls

The controls compile the reconstructed stack and buffer C++ sources with two compilers and twelve sets of flags, for 48 compilations. Every run used `/Gy` to expose individual functions. Each cell is the number of complete linked matches among nine distinct members of the indicated object. Both the Windows XP DDK compiler (frontend 9176/backend 9178) and VC7.0 RTM 9466 produced the following counts.

| Flags | Stack | Buffer |
| --- | ---: | ---: |
| `/O1 /GX` | 9 | 9 |
| `/O1` | 8 | 9 |
| `/O1 /EHsc` | 9 | 9 |
| `/O1 /EHa` | 8 | 9 |
| `/O2 /GX` | 1 | 1 |
| `/Ox /GX` | 1 | 1 |
| `/Od /GX` | 0 | 0 |
| `/O1 /Ob0 /GX` | 9 | 8 |
| `/O1 /G5 /GX` | 6 | 6 |
| `/O1 /G6 /GX` | 9 | 9 |
| `/O1 /Oy- /GX` | 6 | 3 |
| `/O2 /Os /GX` | 9 | 9 |

The member-wide signature supports **size optimization**. Both `/O1` and `/O2 /Os` reproduce it. The 232-byte stack function also requires the synchronous C++ exception behavior of `/GX` or `/EHsc`. Disabling EH yields 205 bytes. Asynchronous EH is five bytes different. The buffer member reproduces all nine functions with EH off, so it supports the optimization evidence alone. Default `/O2 /GX` and `/Ox /GX` preserve only the DWORD-stack constructor and buffer Release. VC7.0 RTM is a byte-equivalent replay compiler for this family. The signed member metadata independently identifies 9176/9178 as the producer.

The tested Windows XP DDK `cl.exe`, `c1xx.dll`, and `c2.dll` have SHA-256 values `a99939878f19e0a6404e349824c163de8188a967a22e82867af935c040d1032c`, `3a0cdfbccb2df87487da1d6c9e83ce781f7ef4eae025da35ec405cfebe7831a4`, and `99860f0499e637520df383ffac0845cf027cbecb82c9980844c76e1698579add`.

## Reproduce the comparison

Use the release `d3dx8.lib` from the DirectX 8.1 SDK and the Versus executable from Steam build 252084. With 7-Zip installed, these PowerShell commands verify the installer signature and extract the library. Supply your installer path as `$sdk`.

```powershell
Get-AuthenticodeSignature $sdk | Format-List Status,SignerCertificate,TimeStamperCertificate
7z x $sdk DXF/DXSDK/lib/d3dx8.lib
Get-FileHash DXF/DXSDK/lib/d3dx8.lib -Algorithm SHA256
```

From the repository root, pass the extracted release library and retail image to the auditor. Adding a path to a period x86 compiler runs the switch controls above. The verifier command rebuilds the 18 checked-in receipts from project source using VC7.0 RTM.

```powershell
$archive = 'DXF/DXSDK/lib/d3dx8.lib'
$retail = Join-Path $steamRoot 'Versus/System/SCCT_Versus.ex'
python pc/evidence/versus_d3dx81_stack_buffer.py $archive $retail
python pc/evidence/versus_d3dx81_stack_buffer.py $archive $retail --cl $ddkCompiler
python pc/evidence/versus_d3dx81_stack_buffer.py $archive $retail --cl $vc70Compiler
python pc/verify_build.py $steamRoot --cl $vc70Compiler --source src/d3dx_stack.cpp --source src/d3dx_buffer.cpp
```

The auditor checks the archive and member hashes, resolves the original named COFF sections with the recorded retail link bindings, and compares each complete body. For the one private exception-handler label whose name varies by compiler invocation, it locates the unique compiler-generated handler stub before applying the recorded binding.
