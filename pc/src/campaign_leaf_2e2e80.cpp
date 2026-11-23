// campaign_leaf_2e2e80.cpp -- destructor at VA 0x10be2e80 of a class holding dynamic arrays (data
// pointer, count, capacity) at 0x24 and 0x4c. The array at 0x4c removes its elements through the
// method at VA 0x10be2aa0, the one at 0x24 through the method at VA 0x10929170 with 4 as the
// element size; each then frees its data through virtual slot 2 of the allocator at VA 0x111c88a0
// and clears its three words. The class, member and method names are invented; the offsets and
// the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10be2e80_24
{
public:
    ~UnkType_10be2e80_24()
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

class UnkType_10be2e80_4c
{
public:
    ~UnkType_10be2e80_4c()
    {
        Unk_10be2aa0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10be2aa0(int Index, int Count);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be2e80
{
public:
    ~UnkType_10be2e80();

private:
    unsigned char unk_00[0x24];
    UnkType_10be2e80_24 unk_24;
    unsigned char unk_30[0x4c - 0x30];
    UnkType_10be2e80_4c unk_4c;
};

// UnkType_10be2e80::~UnkType_10be2e80
UnkType_10be2e80::~UnkType_10be2e80()
{
}
