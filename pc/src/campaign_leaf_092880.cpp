// campaign_leaf_092880.cpp -- method at VA 0x10992880 of a dynamic array of 20-byte records taking
// an index and a count: destroys each record in that range (the dynamic array at 0x08 of each:
// method at VA 0x10929170 with 0, its count and the element size 4, then frees its data through
// virtual slot 2 of the allocator global at VA 0x111c88a0), then calls the method at VA 0x10991e40
// with the index, the count and the record size. guess: an instance of the engine's
// TArray<T>::Remove. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10992880_Array
{
public:
    ~UnkType_10992880_Array()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_10992880_Record
{
    int unk_00;
    int unk_04;
    UnkType_10992880_Array unk_08;
};

class UnkType_10992880
{
public:
    void Unk_10992880(int Index, int Count);
    void Unk_10991e40(int Index, int Count, int ElementSize);

private:
    UnkType_10992880_Record* unk_00;
    int unk_04;
};

// UnkType_10992880::Unk_10992880
void UnkType_10992880::Unk_10992880(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10992880_Record();
    }
    Unk_10991e40(Index, Count, sizeof(UnkType_10992880_Record));
}
