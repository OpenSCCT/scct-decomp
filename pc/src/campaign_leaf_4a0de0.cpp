// campaign_leaf_4a0de0.cpp -- one function at file offset 0x4a0de0, preferred VA 0x10da0de0.
// The constructor runs the base constructor at 0x10d84c50, installs the vtable at 0x1113e528 and
// builds the member at offset 0x2c with the constructor at 0x10d9d3c0 from the global at
// 0x1131b154. The class, member and global names are invented; the offset and the bytes are the
// binary's.

#include "campaign_global_1131b154.h"

class UnkType_10da0de0_Base
{
public:
    unsigned char unk_4[0x28];

    UnkType_10da0de0_Base();

    virtual void VirtualSlot0();
};

class UnkType_10da0de0_Member
{
public:
    int unk_0;

    UnkType_10da0de0_Member(int Value);
};

class UnkType_10da0de0 : public UnkType_10da0de0_Base
{
public:
    UnkType_10da0de0_Member unk_2c;

    UnkType_10da0de0();

    virtual void VirtualSlot0();
};

// UnkType_10da0de0::UnkType_10da0de0
UnkType_10da0de0::UnkType_10da0de0()
    : unk_2c(GUnk_1131b154)
{
}
