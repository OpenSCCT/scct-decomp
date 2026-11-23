// campaign_leaf_05dc10.cpp -- free function at VA 0x1095dc10: stores its first argument in the byte
// at 0xb4 of the object the global at VA 0x111f55a8 points to, if any; when its second argument is
// 0 returns 1; otherwise, with no object returns 0, and else sets the global at VA 0x111f55cc and
// returns, as an int, the byte result of the object's method at VA 0x10d85b70 when its method at VA
// 0x10d844e0 returns true, or of its method at VA 0x10d85c20 otherwise. The class, member and
// function names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111f55a8.h"
#include "campaign_global_111f55cc.h"

class UnkType_1095dc10_111f55a8
{
public:
    bool Unk_10d844e0();
    unsigned char Unk_10d85b70();
    unsigned char Unk_10d85c20();

    unsigned char unk_00[0xb4];
    unsigned char unk_b4;
};

// Unk_1095dc10
int Unk_1095dc10(unsigned char Value, int Flag)
{
    if ( GUnk_111f55a8 )
    {
        static_cast<UnkType_1095dc10_111f55a8*>(GUnk_111f55a8)->unk_b4 = Value;
    }
    if ( Flag )
    {
        if ( !GUnk_111f55a8 )
        {
            return 0;
        }
        GUnk_111f55cc = 1;
        if ( static_cast<UnkType_1095dc10_111f55a8*>(GUnk_111f55a8)->Unk_10d844e0() )
        {
            return static_cast<UnkType_1095dc10_111f55a8*>(GUnk_111f55a8)->Unk_10d85b70();
        }
        return static_cast<UnkType_1095dc10_111f55a8*>(GUnk_111f55a8)->Unk_10d85c20();
    }
    return 1;
}
