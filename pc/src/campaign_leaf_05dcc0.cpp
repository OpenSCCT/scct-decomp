// campaign_leaf_05dcc0.cpp -- free function at VA 0x1095dcc0: returns 0 when the global at VA
// 0x111f55a8 holds no object; otherwise copies up to seventeen values from the array its first
// argument refers to (data at 0x00, count at 0x04) into the values from 0x44 of that object, and
// then, unless its second argument is 0 (which returns 1), sets the global at VA 0x111f55cc and
// returns, as an int, the byte result of the object's method at VA 0x10d85b70 when its method at VA
// 0x10d844e0 returns true, or of its method at VA 0x10d85c20 otherwise. The class, member and
// function names are invented; the offsets, the count and the addresses are the binary's.

#include "campaign_global_111f55a8.h"
#include "campaign_global_111f55cc.h"

class UnkType_1095dcc0_Array
{
public:
    int* unk_00;
    int unk_04;
};

class UnkType_1095dcc0_111f55a8
{
public:
    bool Unk_10d844e0();
    unsigned char Unk_10d85b70();
    unsigned char Unk_10d85c20();

    unsigned char unk_00[0x44];
    int unk_44[17];
};

// Unk_1095dcc0
int Unk_1095dcc0(const UnkType_1095dcc0_Array& Values, int Flag)
{
    if ( !GUnk_111f55a8 )
    {
        return 0;
    }
    for ( int i = 0; i < 17; i++ )
    {
        if ( i >= Values.unk_04 )
        {
            break;
        }
        static_cast<UnkType_1095dcc0_111f55a8*>(GUnk_111f55a8)->unk_44[i] = Values.unk_00[i];
    }
    if ( Flag )
    {
        if ( !GUnk_111f55a8 )
        {
            return 0;
        }
        GUnk_111f55cc = 1;
        if ( static_cast<UnkType_1095dcc0_111f55a8*>(GUnk_111f55a8)->Unk_10d844e0() )
        {
            return static_cast<UnkType_1095dcc0_111f55a8*>(GUnk_111f55a8)->Unk_10d85b70();
        }
        return static_cast<UnkType_1095dcc0_111f55a8*>(GUnk_111f55a8)->Unk_10d85c20();
    }
    return 1;
}
