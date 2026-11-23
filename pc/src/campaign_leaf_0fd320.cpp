// campaign_leaf_0fd320.cpp -- destructor at VA 0x109fd320 of a two-member array (data pointer at
// 0x00, count at 0x04): calls the method at VA 0x109f33e0 with 0 and the count, frees the data
// (when set) through virtual slot 2 of the allocator global at VA 0x111c88a0, then zeroes both
// members. The class, member and method names are invented; the offsets and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109fd320
{
public:
    ~UnkType_109fd320();
    void Unk_109f33e0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
};

// UnkType_109fd320::~UnkType_109fd320
UnkType_109fd320::~UnkType_109fd320()
{
    Unk_109f33e0(0, unk_04);
    if ( unk_00 )
    {
        GUnk_111c88a0->Free(unk_00);
    }
    unk_00 = 0;
    unk_04 = 0;
}
