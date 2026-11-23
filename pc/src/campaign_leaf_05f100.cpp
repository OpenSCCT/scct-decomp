// campaign_leaf_05f100.cpp -- free function at VA 0x1095f100: deletes the object the global at VA
// 0x111f55c4 points to, if any, and clears the global; then allocates a new 0x68-byte object with
// the constructor at VA 0x10aa3cf0, stores it in the global and calls its method at VA 0x10aa3d60
// with its argument and 0. The function names are invented; the size and the addresses are the
// binary's.

#include "campaign_global_111f55c4.h"

// Unk_1095f100
void Unk_1095f100(int Value)
{
    if ( GUnk_111f55c4 )
    {
        delete GUnk_111f55c4;
        GUnk_111f55c4 = 0;
    }
    GUnk_111f55c4 = new UnkType_111f55c4;
    GUnk_111f55c4->Unk_10aa3d60(Value, 0);
}
