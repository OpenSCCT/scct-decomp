// campaign_leaf_1b6c00.cpp -- function at VA 0x10ab6c00 with no this pointer. It deletes every
// object in the global pointer array at VA 0x111fa7f8 through its virtual destructor, then empties
// the array: count and capacity cleared and the data reallocated to zero bytes through slot 1 of the
// allocator at VA 0x111c88a0 (tag "FArray"). The function name is invented; the tag is the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_111fa7f8.h"

// Unk_10ab6c00
void Unk_10ab6c00()
{
    for ( int i = 0; i < GUnk_111fa7f8.unk_4; i++ )
    {
        delete GUnk_111fa7f8.unk_0[i];
    }
    GUnk_111fa7f8.unk_4 = 0;
    GUnk_111fa7f8.unk_8 = 0;
    GUnk_111fa7f8.unk_0 =
        (UnkType_111fa7f8_Item**)GUnk_111c88a0->Realloc(GUnk_111fa7f8.unk_0, 0, L"FArray");
}
