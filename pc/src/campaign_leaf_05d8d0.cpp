// campaign_leaf_05d8d0.cpp -- free function at VA 0x1095d8d0: returns 0 when its first argument is
// 0; otherwise passes it to the method at VA 0x10d7cfa0 of the member at 0xd0 of the object the
// global at VA 0x111f55a8 points to, when there is one, and returns what the free function at VA
// 0x1095b950 returns when the second is set, otherwise 1. The class and function names are
// invented; the offset and the addresses are the binary's.

#include "campaign_global_111f55a8.h"

class UnkType_10d7cfa0_05d8d0
{
public:
    void Unk_10d7cfa0(int Value);
};

class UnkType_1095d8d0_111f55a8
{
public:
    unsigned char unk_00[0xd0];
    UnkType_10d7cfa0_05d8d0 unk_d0;
};

int Unk_1095b950();

// Unk_1095d8d0
int Unk_1095d8d0(int Value, int Flag)
{
    if ( !Value )
    {
        return 0;
    }
    if ( GUnk_111f55a8 )
    {
        static_cast<UnkType_1095d8d0_111f55a8*>(GUnk_111f55a8)->unk_d0.Unk_10d7cfa0(Value);
    }
    if ( Flag )
    {
        return Unk_1095b950();
    }
    return 1;
}
