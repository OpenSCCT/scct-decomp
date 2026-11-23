// campaign_leaf_01ca70.cpp -- destructor at VA 0x1091ca70: destroys the member at 0x0c (frees its data
// through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to when it is set,
// and clears its data and count), then runs the base destructor at VA 0x1090dab0. The class, member
// and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1091ca70_Base
{
public:
    ~UnkType_1091ca70_Base();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_111c88a0_01ca70
{
public:
    ~UnkType_111c88a0_01ca70()
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

class UnkType_1091ca70 : public UnkType_1091ca70_Base
{
public:
    ~UnkType_1091ca70();

private:
    UnkType_111c88a0_01ca70 unk_0c;
};

// UnkType_1091ca70::~UnkType_1091ca70
UnkType_1091ca70::~UnkType_1091ca70()
{
}
