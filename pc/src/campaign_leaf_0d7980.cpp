// campaign_leaf_0d7980.cpp -- method at VA 0x109d7980 taking one unused argument: zeroes the count
// at 0x04, frees the data pointer at 0x00 (when set) through virtual slot 2 of the allocator global
// at VA 0x111c88a0 and clears it. The class, member and method names are invented; the offsets and
// the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109d7980
{
public:
    void Unk_109d7980(int Unused);

private:
    void* unk_00;
    int unk_04;
};

// UnkType_109d7980::Unk_109d7980
void UnkType_109d7980::Unk_109d7980(int Unused)
{
    unk_04 = 0;
    if ( unk_00 )
    {
        GUnk_111c88a0->Free(unk_00);
    }
    unk_00 = 0;
}
