// campaign_leaf_081de0.cpp -- method at VA 0x10981de0: when the capacity at 0x08 of an array of
// 416-byte elements (data at 0x00, count at 0x04) differs from the count, sets it to the count and
// reallocates the data through virtual slot 1 of the allocator the global at VA 0x111c88a0 points
// to, tagged "FArray". The class, member and method names are invented; the offsets, the size, the
// tag and the address are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10981de0_Item
{
private:
    unsigned char unk_00[0x1a0];
};

class UnkType_10981de0
{
public:
    void Unk_10981de0();

private:
    UnkType_10981de0_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10981de0::Unk_10981de0
void UnkType_10981de0::Unk_10981de0()
{
    if ( unk_08 != unk_04 )
    {
        unk_08 = unk_04;
        unk_00 = static_cast<UnkType_10981de0_Item*>(GUnk_111c88a0->Realloc(
            unk_00, unk_04 * sizeof(UnkType_10981de0_Item), L"FArray"));
    }
}
