# FStats::Render in Steam 252084 Versus

The editor identifies the statistics display as `FStats::Render`. In the retail image, `FPlayerSceneNode::Render` calls it near the end of the viewport pass. Its frame, renderer, actor and network pages use 308 distinct UTF-16 display literals. The counters they read correspond to the stat indices initialized by `FEngineStats::Init`.

The entry is at file offset `0xce3f0` and its return ends at `0xdc265` (exclusive). The five intervals in the function map contain 53,659 bytes. Rebuilding the function also reproduces every interval between them. The public receipt compares all 56,949 consecutive bytes, with SHA-256 `66de3b5cec4ca115ac1ceab86ccf18f43245ad76288195d8553fbddbd7534e5d`. Only the renderer receives credit from this receipt.

The recorded x86 compiler is Microsoft C/C++ 13.00.9466 with `/O2 /Gy /GX /GL /GF-`. The link includes the player-scene caller, the engine-stat initializer, the string and canvas operations, counter smoothing and the writable globals. Each translation unit has its own compile command in the manifest. Enabling string pooling reduced the 308 distinct literal addresses to 35. VC7.1 reproduced the physical length with a different instruction stream. On VC7.0, both `/O2` and `/Ox` reproduced the complete body. Disabling `/GX` produced 53,007 bytes. The receipt records the tested recipe as an exact candidate.

The regular build verifies the renderer. A second check follows its installed exception handler in both images, compares all 250 unwind transitions and their calls to `FString::~FString`, and checks the initial contents of five writable globals. Run both from the repository root with the installed Steam folder and the recorded compiler.

```powershell
python pc/verify_build.py $SteamRoot --cl $Cl --source src/versus_stats_render.cpp
python pc/evidence/versus_stats_render_eh.py $SteamRoot --cl $Cl
```
