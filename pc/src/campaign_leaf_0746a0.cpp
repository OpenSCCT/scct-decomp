// campaign_leaf_0746a0.cpp -- destructor at VA 0x109746a0: frees the data at 0xf4 through virtual
// slot 2 of the allocator the global at VA 0x111c88a0 points to when it is set and clears it, then
// frees the data at 0xcc the same way without the check and clears it, then runs the base
// destructor at VA 0x10cd8ea0. The class, member and method names are invented; the offsets and
// the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109746a0_Base
{
public:
    ~UnkType_109746a0_Base();

private:
    unsigned char unk_00[0xcc];
};

class UnkType_109746a0 : public UnkType_109746a0_Base
{
public:
    ~UnkType_109746a0();

private:
    void* unk_cc;
    unsigned char unk_d0[0xf4 - 0xd0];
    void* unk_f4;
};

// UnkType_109746a0::~UnkType_109746a0
UnkType_109746a0::~UnkType_109746a0()
{
    if ( unk_f4 )
    {
        GUnk_111c88a0->Free(unk_f4);
    }
    unk_f4 = 0;
    GUnk_111c88a0->Free(unk_cc);
    unk_cc = 0;
}
