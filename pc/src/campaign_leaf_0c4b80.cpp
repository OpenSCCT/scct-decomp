// campaign_leaf_0c4b80.cpp -- free function at VA 0x109c4b80: creates the object the global at VA
// 0x1120a9bc points to if there is none yet (0x64 bytes from the allocator at VA 0x111c88a0, tag
// "USMStreamer", constructor at VA 0x109c4600) and returns it. The function name is invented; the
// tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_1120a9bc.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

// Unk_109c4b80
UnkType_1120a9bc* Unk_109c4b80()
{
    if ( GUnk_1120a9bc == 0 )
    {
        GUnk_1120a9bc = new(L"USMStreamer") UnkType_1120a9bc;
    }
    return GUnk_1120a9bc;
}
