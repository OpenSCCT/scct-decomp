// campaign_leaf_021f30.cpp -- destructor at VA 0x10921f30: destroys the member at 0x0c (frees its data
// through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to when it is set,
// and clears its data and count), then runs the base destructor at VA 0x10921ec0. The class, member
// and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10921f30_Base
{
public:
    ~UnkType_10921f30_Base();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_111c88a0_021f30
{
public:
    ~UnkType_111c88a0_021f30()
    {
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

private:
    void* unk_00;
    int unk_04;
};

class UnkType_10921f30 : public UnkType_10921f30_Base
{
public:
    ~UnkType_10921f30();

private:
    UnkType_111c88a0_021f30 unk_0c;
};

// UnkType_10921f30::~UnkType_10921f30
UnkType_10921f30::~UnkType_10921f30()
{
}
