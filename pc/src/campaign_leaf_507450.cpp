// campaign_leaf_507450.cpp -- one function at file offset 0x507450, preferred VA 0x10e07450.
// It decrements the count at offset 0x24 and, when it reaches zero, passes the object to the
// virtual method in slot 1 of the global object at 0x1131b3d8. The class, method, member and
// global names are invented; the offset and the bytes are the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10e07450
{
public:
    unsigned char unk_0[0x24];
    int unk_24;

    void Unk_10e07450();
};

// UnkType_10e07450::Unk_10e07450
void UnkType_10e07450::Unk_10e07450()
{
    if ( --unk_24 == 0 )
    {
        UnkType_1131b3d8* Owner = GUnk_1131b3d8;
        Owner->VirtualSlot1(this);
    }
}
