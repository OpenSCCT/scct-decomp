// campaign_leaf_4b4400.cpp -- one function at file offset 0x4b4400, preferred VA 0x10db4400.
// The constructor runs the base constructor at 0x10da2720, installs the vtable at 0x1113e7d0 and
// builds the member at offset 0x2c with the constructor at 0x10d9d3c0 from the global at
// 0x1131b19c. The class, member and global names are invented; the offset and the bytes are the
// binary's.

#include "campaign_global_1131b19c.h"

class UnkType_10db4400_Base
{
public:
    unsigned char unk_4[0x28];

    UnkType_10db4400_Base();

    virtual void VirtualSlot0();
};

class UnkType_10db4400_Member
{
public:
    int unk_0;

    UnkType_10db4400_Member(int Value);
};

class UnkType_10db4400 : public UnkType_10db4400_Base
{
public:
    UnkType_10db4400_Member unk_2c;

    UnkType_10db4400();

    virtual void VirtualSlot0();
};

// UnkType_10db4400::UnkType_10db4400
UnkType_10db4400::UnkType_10db4400()
    : unk_2c(GUnk_1131b19c)
{
}
