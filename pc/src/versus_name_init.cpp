// Core name table initialization for Steam Versus. The shipped editor retains
// the FName::StaticInit guard. Its Hardcode callee handles repeated indices.
#include "versus_build.h"
#include "versus_name_registry.h"

extern "C" void *__cdecl memset(void *Destination, int Value, unsigned int Count);
#pragma intrinsic(memset)

void LoadNamesFromFile();  // Reads FNames.txt after the built-in names.

enum {
    NativeName = RF_Native | 0x800,
    NativeNameWith0400 = NativeName | 0x400,
    RF_Suppress = 0x1000,
    NAME_DevNetTraffic = 574
};

// Equal spellings can have different addresses in the writable retail name data.
#define REGISTER_NAME(symbol, index, flags, text) TCHAR NameText_##symbol[] = L##text;
#include "versus_hardcoded_names.inl"
#undef REGISTER_NAME

void FName::StaticInit()
{
    memset(FName_NameHash, 0, sizeof(FName_NameHash));
    Initialized = 1;

#define REGISTER_NAME(symbol, index, flags, text) Hardcode(AllocateNameEntry(NameText_##symbol, index, flags, 0));
#include "versus_hardcoded_names.inl"
#undef REGISTER_NAME

    LoadNamesFromFile();
    FName_Names.Shrink();

    // The release executable still compares every pair in a bucket.
    for (DWORD i = 0; i < sizeof(FName_NameHash) / sizeof(FName_NameHash[0]); ++i) {
        for (FNameEntry *first = FName_NameHash[i]; first; first = first->HashNext) {
            for (FNameEntry *other = first->HashNext; other; other = other->HashNext)
                _wcsicmp(first->Name, other->Name);
        }
    }

    FName_Names(NAME_DevNetTraffic)->Flags |= RF_Suppress;
}
