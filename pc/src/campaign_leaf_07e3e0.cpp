// campaign_leaf_07e3e0.cpp -- destructor at VA 0x1097e3e0: frees the data at 0x00 through virtual
// slot 2 of the allocator the global at VA 0x111c88a0 points to when it is set, then clears it and
// the count at 0x04. The class and member names are invented; the offsets and the address are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1097e3e0
{
public:
    ~UnkType_1097e3e0();

private:
    void* unk_00;
    int unk_04;
};

// UnkType_1097e3e0::~UnkType_1097e3e0
UnkType_1097e3e0::~UnkType_1097e3e0()
{
    if ( unk_00 )
    {
        GUnk_111c88a0->Free(unk_00);
    }
    unk_00 = 0;
    unk_04 = 0;
}
