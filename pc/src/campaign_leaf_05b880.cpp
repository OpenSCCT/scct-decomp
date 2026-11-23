// campaign_leaf_05b880.cpp -- free function at VA 0x1095b880: returns 0 when the global at VA
// 0x111f559c is null; otherwise returns whether the free function at VA 0x10d810c0, which takes no
// arguments, returns 1. The function and global names are invented; the addresses are the binary's.

#include "campaign_global_111f559c.h"

unsigned char Unk_10d810c0();

// Unk_1095b880
int Unk_1095b880()
{
    if ( GUnk_111f559c )
    {
        return Unk_10d810c0() == 1;
    }
    return 0;
}
