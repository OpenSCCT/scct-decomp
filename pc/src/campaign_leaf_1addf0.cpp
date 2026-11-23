// campaign_leaf_1addf0.cpp -- copy constructor at VA 0x10aaddf0 of an array of 4-byte elements
// (data, count, capacity). It takes the other array's count as both count and capacity, allocates
// the data through slot 1 of the allocator at VA 0x111c88a0 with the tag "FArray::FName", and
// copies the elements one by one. The class and member names are invented; the tag is the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10aaddf0
{
public:
    UnkType_10aaddf0(const UnkType_10aaddf0& Other);

private:
    int* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10aaddf0::UnkType_10aaddf0
UnkType_10aaddf0::UnkType_10aaddf0(const UnkType_10aaddf0& Other)
{
    int Count = Other.unk_4;
    unk_4 = Count;
    unk_8 = Count;
    unk_0 = 0;
    unk_0 = (int*)GUnk_111c88a0->Realloc(unk_0, Count * sizeof(int), L"FArray::FName");
    for ( int i = 0; i < unk_4; i++ )
    {
        unk_0[i] = Other.unk_0[i];
    }
}
