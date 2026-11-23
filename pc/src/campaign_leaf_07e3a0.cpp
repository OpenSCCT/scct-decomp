// campaign_leaf_07e3a0.cpp -- method at VA 0x1097e3a0: clears the count at 0x04, frees the data at
// 0x00 through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to when it is
// set, and clears it. The class, member and method names are invented; the offsets and the address
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1097e3a0
{
public:
    void Unk_1097e3a0();

private:
    void* unk_00;
    int unk_04;
};

// UnkType_1097e3a0::Unk_1097e3a0
void UnkType_1097e3a0::Unk_1097e3a0()
{
    unk_04 = 0;
    if ( unk_00 )
    {
        GUnk_111c88a0->Free(unk_00);
    }
    unk_00 = 0;
}
