// campaign_leaf_0f33e0.cpp -- method at VA 0x109f33e0 of a dynamic array of 0x30-byte records
// taking an index and a count: destroys each record in that range (the dynamic array at 0x18 of
// each: method at VA 0x10907710 with 0, its count and the element size 2, then frees its data
// through virtual slot 2 of the allocator global at VA 0x111c88a0), then calls the method at VA
// 0x10ccb3f0 with the index, the count and the record size. guess: an instance of the engine's
// TArray<T>::Remove. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109f33e0_Array
{
public:
    ~UnkType_109f33e0_Array()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_109f33e0_Record
{
    unsigned char unk_00[0x18];
    UnkType_109f33e0_Array unk_18;
    unsigned char unk_24[0x30 - 0x24];
};

class UnkType_109f33e0
{
public:
    void Unk_109f33e0(int Index, int Count);
    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    UnkType_109f33e0_Record* unk_00;
    int unk_04;
};

// UnkType_109f33e0::Unk_109f33e0
void UnkType_109f33e0::Unk_109f33e0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_109f33e0_Record();
    }
    Unk_10ccb3f0(Index, Count, sizeof(UnkType_109f33e0_Record));
}
