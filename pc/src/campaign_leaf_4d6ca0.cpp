// campaign_leaf_4d6ca0.cpp -- one function at file offset 0x4d6ca0, preferred VA 0x10dd6ca0.
// The constructor installs the vtable at 0x11145220 and registers the new object: in the global at
// 0x1131b2bc when the function at 0x10d98f30 returns 0, and otherwise at that index of the array
// the global at 0x1131b2b8 points to. The class, function and global names are invented; the
// offset and the bytes are the binary's.

#include "campaign_global_1131b2b8.h"
#include "campaign_global_1131b2bc.h"

int Unk_10d98f30();

class UnkType_10dd6ca0
{
public:
    UnkType_10dd6ca0();

    virtual void VirtualSlot0();
};

// UnkType_10dd6ca0::UnkType_10dd6ca0
UnkType_10dd6ca0::UnkType_10dd6ca0()
{
    int Index = Unk_10d98f30();

    if ( Index == 0 )
    {
        GUnk_1131b2bc = this;
    }
    else
    {
        GUnk_1131b2b8[Index] = this;
    }
}
