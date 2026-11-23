// campaign_leaf_2f52d0.cpp -- destructor at VA 0x10bf52d0 of a class holding two dynamic arrays (data
// pointer, count, capacity) at 0x00 and 0x0c. The array at 0x0c removes its elements through the
// method at VA 0x1090d050, the one at 0x00 through the method at VA 0x10966210 with 1 as the
// element size; each then frees its data through virtual slot 2 of the allocator at VA 0x111c88a0
// and clears its three words. The class, member and method names are invented; the offsets and
// the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bf52d0_00
{
public:
    ~UnkType_10bf52d0_00()
    {
        Unk_10966210(0, unk_04, 1);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10966210(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf52d0_0c
{
public:
    ~UnkType_10bf52d0_0c()
    {
        Unk_1090d050(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1090d050(int Index, int Count);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf52d0
{
public:
    ~UnkType_10bf52d0();

private:
    UnkType_10bf52d0_00 unk_00;
    UnkType_10bf52d0_0c unk_0c;
};

// UnkType_10bf52d0::~UnkType_10bf52d0
UnkType_10bf52d0::~UnkType_10bf52d0()
{
}
