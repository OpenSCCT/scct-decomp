// campaign_leaf_4b4e70.cpp -- one function at file offset 0x4b4e70, preferred VA 0x10db4e70.
// The constructor installs the vtable at 0x1113fe54 and registers the new object: in the global at
// 0x1131b1ec when the function at 0x10d98f30 returns 0, and otherwise at that index of the array
// the global at 0x1131b1e8 points to. The class, function and global names are invented; the
// offset and the bytes are the binary's.

#include "campaign_global_1131b1e8.h"
#include "campaign_global_1131b1ec.h"

int Unk_10d98f30();

class UnkType_10db4e70
{
public:
    UnkType_10db4e70();

    virtual void VirtualSlot0();
};

// UnkType_10db4e70::UnkType_10db4e70
UnkType_10db4e70::UnkType_10db4e70()
{
    int Index = Unk_10d98f30();

    if ( Index == 0 )
    {
        GUnk_1131b1ec = this;
    }
    else
    {
        GUnk_1131b1e8[Index] = this;
    }
}
