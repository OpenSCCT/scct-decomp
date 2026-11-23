// campaign_leaf_05d820.cpp -- free function at VA 0x1095d820: when its argument is set and is not
// the object the global at VA 0x111f55d8 points to, calls virtual slot 3 (vtable offset 0x0c) of
// each object in the array global at VA 0x111f5f08. The function name is invented; the slot and the
// addresses are the binary's.

#include "campaign_global_111f55d8.h"
#include "campaign_global_111f5f08.h"

// Unk_1095d820
void Unk_1095d820(UnkType_111f55d8* Object)
{
    if ( Object && Object != GUnk_111f55d8 )
    {
        for ( int i = 0; i < GUnk_111f5f08.unk_04; i++ )
        {
            GUnk_111f5f08.unk_00[i]->VirtualSlot3();
        }
    }
}
