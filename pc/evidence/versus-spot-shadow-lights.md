# Versus spot shadow light collection

Steam build 252084 calls the spotlight collection routine at RVA `0x1374b0` from RenderLevel at `0x13facc`. RenderLevel constructs the view volume at `0x13f70c` from the scene node’s WorldToScreen matrix, then passes its address with the render state and two integer result pointers. The collector forwards the same view volume to the visibility test at `0x137561`. The shipped editor also forwards it. The visibility test reads the context and light and leaves the volume argument unused.

The Versus Engine.u property chain identifies AActor’s bDeleteMe and bDynamicLight at word `0x2e8`, bits 15 and 17, and UsesLightBeam at `0x2ec`, bit 17. ELightEffect entry 22 is LE_ESpotShadow. AActor::GetLightRenderData selects a 0x2a4-byte record for that effect at `0x90d2e`, with a 0x40-byte base allocation for other lights. The class and routine names for collecting spot shadow lights describe their native use.

## Compiler evidence

The native caller passes the light to IsLightVisibleInContext in ESI, the zone to FilterBounds in EAX, and the frustum in EDI. The native collector also inlines the first level of the recursive slot assignment, then passes the next entry to the out-of-line recursion at `0x1375f2`. The recorded VC7.0 speed-optimized LTCG build reproduces these relationships and the complete 347-, 240-, 121-, and 57-byte functions. The Versus image’s Rich header identifies all LTCG C++ objects as VC7.0 build 9466. Ordinary C++ objects in this image also include VC7.1, so a standalone COFF match alone cannot settle the shared 57-byte recursive body. [Retail toolchain evidence](versus-vc70-9466.md)

Fresh control builds retained the native root and the same translation units. Changing both lighting sources from VC7.0 `/O2` to `/O1` changes 309 byte positions in the collector, 228 in the visibility test and 36 in the recursive slot helper, after relocating named operands. The VC7.1 `/O2 /GL` control changes 205 positions in the collector and 222 in the visibility test. An ordinary VC7.0 `/O2 /Gy` object calls FilterBounds at offsets 88 and 209 of the visibility test. Retail calls it at offsets 71 and 188.

The recorded `/Ob1` visibility translation unit leaves the two calls to FilterBounds out of line. Compiling the visibility function separately with ordinary `/O2 /Gy /GL` and compiling FilterBounds in its own `/Ob1` translation unit also recreates the complete visibility test. These builds support `/O2` and `/GL`. They do not distinguish original file grouping or an original inline-expansion switch. [Project switch controls](versus-vc70-switches.md)

The scene-memory allocation in InsertSortedLight reads the writable GSceneMem object at 0x10c73cac and its End pointer four bytes later. The receipt checks this member as an interior address of the actual 16-byte object. Both the native and recreated allocator call FMemStack::AllocateNewChunk when the requested node exceeds End.
