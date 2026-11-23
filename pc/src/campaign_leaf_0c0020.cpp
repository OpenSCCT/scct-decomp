// campaign_leaf_0c0020.cpp -- method at VA 0x109c0020 of a dynamic array of 40-byte records taking
// an index and a count: destroys each record in that range (the two-word dynamic array at 0x00 of
// each: method at VA 0x10ccb3f0 with 0, its count and the element size 2, then frees its data
// through virtual slot 2 of the allocator global at VA 0x111c88a0), then calls the method at VA
// 0x109bf3a0 with the index, the count and the record size. guess: an instance of the engine's
// TArray<T>::Remove. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c0020_Array
{
public:
    ~UnkType_109c0020_Array()
    {
        Unk_10ccb3f0(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
};

struct UnkType_109c0020_Record
{
    UnkType_109c0020_Array unk_00;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
};

class UnkType_109c0020
{
public:
    void Unk_109c0020(int Index, int Count);
    void Unk_109bf3a0(int Index, int Count, int ElementSize);

private:
    UnkType_109c0020_Record* unk_00;
    int unk_04;
};

// UnkType_109c0020::Unk_109c0020
void UnkType_109c0020::Unk_109c0020(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_109c0020_Record();
    }
    Unk_109bf3a0(Index, Count, sizeof(UnkType_109c0020_Record));
}
