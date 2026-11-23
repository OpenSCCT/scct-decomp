// campaign_leaf_05d910.cpp -- free function at VA 0x1095d910: returns 1 when its argument is 0;
// otherwise returns 0 when the global at VA 0x111f55a8 holds no object, and else sets the global at
// VA 0x111f55cc and returns, as an int, the byte result of the object's method at VA 0x10d85b70
// when its method at VA 0x10d844e0 returns true, or of its method at VA 0x10d85c20 otherwise. The
// class and function names are invented; the addresses are the binary's.

#include "campaign_global_111f55a8.h"
#include "campaign_global_111f55cc.h"

class UnkType_1095d910_111f55a8
{
public:
    bool Unk_10d844e0();
    unsigned char Unk_10d85b70();
    unsigned char Unk_10d85c20();
};

// Unk_1095d910
int Unk_1095d910(int Flag)
{
    if ( Flag )
    {
        if ( !GUnk_111f55a8 )
        {
            return 0;
        }
        GUnk_111f55cc = 1;
        if ( static_cast<UnkType_1095d910_111f55a8*>(GUnk_111f55a8)->Unk_10d844e0() )
        {
            return static_cast<UnkType_1095d910_111f55a8*>(GUnk_111f55a8)->Unk_10d85b70();
        }
        return static_cast<UnkType_1095d910_111f55a8*>(GUnk_111f55a8)->Unk_10d85c20();
    }
    return 1;
}
