# UNIAudio native property registration

The Steam 252084 Versus package registrar gives UClass the UUNIAudioSubsystem static constructor at file offset 0x202b90. Its complete 1,090-byte body ends at the return instruction at 0x202fd1. Each of 14 reflected properties supplies its hardcoded name and its field offset. Each category argument calls the FName text constructor with FNAME_Add on its own copy of the terminated UTF-16 string UNIAudio. The 14 initialized writable objects start at 0x343280 and occur at intervals of 20 bytes. Each string occupies 18 bytes including its terminator.

The candidate source uses ordinary string literals. Microsoft C/C++ 13.00.9466 and its linker reproduce the entire callback with /O2 /Gy /GL /GF-. The full receipt checks 84 address operands and every distinct string object. The native property constructors and the text-to-FName constructor are genuine linked callees. The latter's recorded root is the retail MakeUniqueObjectName caller.

| Control | Callback size | Distinct category strings |
| --- | ---: | ---: |
| VC7.0, /O2 /Gy /GL /GF- | 1,090 | 14 |
| VC7.1, same audio options | 1,062 | 14 |
| VC7.0, /O1 instead of /O2 | 844 | 14 |
| VC7.0, /O2 string pooling | 1,090 | 1 |

The Rich header and linked register conventions identify VC7.0 whole-program code generation. The size controls distinguish /O2 from /O1 and VC7.0 from VC7.1 for this callback. The distinct writable objects establish disabled string pooling. /Gy is part of the build recipe. [Versus compiler and switch evidence](versus-vc70-switches.md)
