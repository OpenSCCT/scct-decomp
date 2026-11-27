# Versus array growth in the statistics renderer

The Steam image identifies VC7.0 13.00.9466 LTCG objects. [Compiler and switch evidence](versus-vc70-switches.md)

The moving average at RVA 0xce2c0 and its untyped array append at RVA 0x15400
rebuild together from the seven consecutive mesh-counter calls in the fourth
render page. VC7.0 with `/O2 /Ob1 /Gy /GL` emits the complete 301- and 90-byte
bodies. With the same caller, VC7.1 emits 314 and 70 bytes. VC7.0 with
`/O1 /Ob1` emits 257 and 77, and `/Od /Ob1` emits 559 and 88. In the VC7.0 speed
build, removing the inline expansion limit inlines the append into its caller.

The repeated zero-fill sequence in the append also appears as a standalone
Win32 routine at RVA 0x42a0. Its DWORD loop, byte remainder and register order
identify the engine header's inline assembly helper. The array append and the
integer formatter at RVA 0x11f50 use the helper inside their recovered C++
bodies. [Epic's Win32 header](https://github.com/stephank/surreal/blob/de288ffe9dd96abe9218630098cb6de8fe2b436c/Core/Inc/UnVcWin32.h#L317-L332)
