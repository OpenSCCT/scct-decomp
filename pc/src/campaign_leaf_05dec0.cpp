// campaign_leaf_05dec0.cpp -- free function at VA 0x1095dec0: when the global at VA 0x111f559c is
// set and the free function at VA 0x10d81890 returns an object, returns the value at 0x0c of the
// object it returns on a second call, otherwise 0. The class and function names are invented; the
// offsets and the addresses are the binary's.

#include "campaign_global_111f559c.h"

class UnkType_1095dec0_Object
{
public:
    unsigned char unk_00[0x0c];
    int unk_0c;
};

UnkType_1095dec0_Object* Unk_10d81890();

// Unk_1095dec0
int Unk_1095dec0()
{
    if ( GUnk_111f559c && Unk_10d81890() )
    {
        return Unk_10d81890()->unk_0c;
    }
    return 0;
}
