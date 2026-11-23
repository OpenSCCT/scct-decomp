// campaign_leaf_05d860.cpp -- free function at VA 0x1095d860: when its argument is set and is the
// object the global at VA 0x111f55a8 points to, calls virtual slot 4 (vtable offset 0x10) of each
// object in the array global at VA 0x111f5f08. The function name is invented; the slot and the
// addresses are the binary's.

#include "campaign_global_111f55a8.h"
#include "campaign_global_111f5f08.h"

// Unk_1095d860
void Unk_1095d860(void* Object)
{
    if ( Object && GUnk_111f55a8 && Object == GUnk_111f55a8 )
    {
        for ( int i = 0; i < GUnk_111f5f08.unk_04; i++ )
        {
            GUnk_111f5f08.unk_00[i]->VirtualSlot4();
        }
    }
}
