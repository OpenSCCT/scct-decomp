// campaign_leaf_2f5230.cpp -- destructor at VA 0x10bf5230 of a class holding two dynamic arrays (data
// pointer, count, capacity) at 0x00 and 0x0c. Each array removes its elements through its own
// method (VA 0x10929170 and VA 0x10bec6b0, both called with 4 as the element size), frees its data
// through virtual slot 2 of the allocator at VA 0x111c88a0 and clears its three words. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bf5230_00
{
public:
    ~UnkType_10bf5230_00()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf5230_0c
{
public:
    ~UnkType_10bf5230_0c()
    {
        Unk_10bec6b0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10bec6b0(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf5230
{
public:
    ~UnkType_10bf5230();

private:
    UnkType_10bf5230_00 unk_00;
    UnkType_10bf5230_0c unk_0c;
};

// UnkType_10bf5230::~UnkType_10bf5230
UnkType_10bf5230::~UnkType_10bf5230()
{
}
