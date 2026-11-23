// campaign_leaf_080600.cpp -- method at VA 0x10980600: when the capacity at 0x08 of an array of
// 4-byte elements (data at 0x00, count at 0x04) differs from the count, sets it to the count and
// reallocates the data through virtual slot 1 of the allocator the global at VA 0x111c88a0 points
// to, tagged "FArray::INT". The class, member and method names are invented; the offsets, the size,
// the tag and the address are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10980600
{
public:
    void Unk_10980600();

private:
    int* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10980600::Unk_10980600
void UnkType_10980600::Unk_10980600()
{
    if ( unk_08 != unk_04 )
    {
        unk_08 = unk_04;
        unk_00 = static_cast<int*>(GUnk_111c88a0->Realloc(
            unk_00, unk_04 * sizeof(int), L"FArray::INT"));
    }
}
