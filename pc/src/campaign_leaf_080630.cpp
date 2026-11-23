// campaign_leaf_080630.cpp -- method at VA 0x10980630: when the capacity at 0x08 of an array of
// 12-byte elements (data at 0x00, count at 0x04) differs from the count, sets it to the count and
// reallocates the data through virtual slot 1 of the allocator the global at VA 0x111c88a0 points
// to, tagged "FArray::FVector". The class, member and method names are invented; the offsets, the
// size, the tag and the address are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10980630_Vector
{
public:
    float X;
    float Y;
    float Z;
};

class UnkType_10980630
{
public:
    void Unk_10980630();

private:
    UnkType_10980630_Vector* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10980630::Unk_10980630
void UnkType_10980630::Unk_10980630()
{
    if ( unk_08 != unk_04 )
    {
        unk_08 = unk_04;
        unk_00 = static_cast<UnkType_10980630_Vector*>(GUnk_111c88a0->Realloc(
            unk_00, unk_04 * sizeof(UnkType_10980630_Vector), L"FArray::FVector"));
    }
}
