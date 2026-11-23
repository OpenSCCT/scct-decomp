// campaign_leaf_6ee6b0.cpp -- thiscall method at VA 0x10fee6b0 of an array of 12-byte elements
// (data at 0x00, count at 0x04, capacity at 0x08): passes the pointer at the start of every element
// to virtual slot 1 of the global at VA 0x1131b3d8, then, when the capacity's top bit is clear, passes
// the data, the capacity in bytes and 0x12 to slot 5. The class, method and member names are
// invented; the offsets and addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10fee6b0_Element
{
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10fee6b0
{
public:
    void Unk_10fee6b0();

private:
    UnkType_10fee6b0_Element* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10fee6b0::Unk_10fee6b0
void UnkType_10fee6b0::Unk_10fee6b0()
{
    int i;

    for ( i = 0; i < unk_4; i++ )
    {
        GUnk_1131b3d8->VirtualSlot1(unk_0[i].unk_0);
    }
    if ( ( unk_8 & 0x80000000 ) == 0 )
    {
        GUnk_1131b3d8->VirtualSlot5(unk_0, ( unk_8 & 0x7fffffff ) * sizeof(UnkType_10fee6b0_Element), 0x12);
    }
}
