// campaign_leaf_1cde60.cpp -- function at VA 0x10acde60 with no this pointer. It returns the object
// the global at VA 0x1120a9c4 points to, creating it first if there is none (0x90 bytes from the
// allocator at VA 0x111c88a0, tag "mostCharacterManager"). The function name is invented; the tag
// is the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_1120a9c4.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

// Unk_10acde60
UnkType_1120a9c4* Unk_10acde60()
{
    if ( GUnk_1120a9c4 == 0 )
    {
        GUnk_1120a9c4 = new(L"mostCharacterManager") UnkType_1120a9c4;
    }
    return GUnk_1120a9c4;
}
