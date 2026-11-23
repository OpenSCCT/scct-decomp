// campaign_leaf_16d940.cpp -- method at VA 0x10a6d940: when the object the global at VA
// 0x111fa4e8 points to exists and the float at 0x28 is negative, replaces that float with the
// result of the object's virtual slot 44 (vtable offset 0xb0) for the value at 0x2c; returns the
// float at 0x28. The class, member and method names are invented; the offsets, the slot and the
// address are the binary's.

#include "campaign_global_111fa4e8.h"

class UnkType_10a6d940
{
public:
    float Unk_10a6d940();

private:
    char unk_0[0x28];
    float unk_28;
    int unk_2c;
};

// UnkType_10a6d940::Unk_10a6d940
float UnkType_10a6d940::Unk_10a6d940()
{
    if ( GUnk_111fa4e8 && unk_28 < 0.0f )
    {
        unk_28 = GUnk_111fa4e8->VirtualSlot44(unk_2c);
    }
    return unk_28;
}
