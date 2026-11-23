// campaign_leaf_024610.cpp -- free function at VA 0x10924610: allocates a 0x30-byte object through
// slot 0 of the allocator the global at VA 0x111c88a0 points to, tagged "FConfigCacheIni",
// constructs it with the constructor at VA 0x10922260 when the allocation succeeds and returns it.
// The class and function names are invented; the size, the tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

class UnkType_10922260_024610
{
public:
    UnkType_10922260_024610();

private:
    unsigned char unk_00[0x30];
};

// Unk_10924610
UnkType_10922260_024610* Unk_10924610()
{
    return new(L"FConfigCacheIni") UnkType_10922260_024610;
}
