// campaign_leaf_0eb8a0.cpp -- method at VA 0x109eb8a0 of a dynamic array of 16-byte records taking
// an index and a count: destroys each record in that range (the two-word dynamic array at 0x00 of
// each: method at VA 0x10ccb3f0 with 0, its count and the element size 4, then frees its data
// through virtual slot 2 of the allocator global at VA 0x111c88a0), then calls the method at VA
// 0x10ccb3f0 with the index, the count and the record size. guess: an instance of the engine's
// TArray<T>::Remove. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109eb8a0_Array
{
public:
    ~UnkType_109eb8a0_Array()
    {
        Unk_10ccb3f0(0, unk_04, 4);
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

struct UnkType_109eb8a0_Record
{
    UnkType_109eb8a0_Array unk_00;
    int unk_08;
    int unk_0c;
};

class UnkType_109eb8a0
{
public:
    void Unk_109eb8a0(int Index, int Count);
    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    UnkType_109eb8a0_Record* unk_00;
    int unk_04;
};

// UnkType_109eb8a0::Unk_109eb8a0
void UnkType_109eb8a0::Unk_109eb8a0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_109eb8a0_Record();
    }
    Unk_10ccb3f0(Index, Count, sizeof(UnkType_109eb8a0_Record));
}
