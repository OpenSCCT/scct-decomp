// campaign_leaf_0c1190.cpp -- method at VA 0x109c1190 of a dynamic array of 16-byte records taking
// an index and a count: destroys each record in that range (the dynamic array at 0x04 of each:
// method at VA 0x10966210 with 0, its count and the element size 1, then frees its data through
// virtual slot 2 of the allocator global at VA 0x111c88a0), then calls the method at VA 0x109bf5b0
// with the index, the count and the record size. guess: an instance of the engine's
// TArray<T>::Remove. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c1190_Array
{
public:
    ~UnkType_109c1190_Array()
    {
        Unk_10966210(0, unk_04, 1);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10966210(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_109c1190_Record
{
    int unk_00;
    UnkType_109c1190_Array unk_04;
};

class UnkType_109c1190
{
public:
    void Unk_109c1190(int Index, int Count);
    void Unk_109bf5b0(int Index, int Count, int ElementSize);

private:
    UnkType_109c1190_Record* unk_00;
    int unk_04;
};

// UnkType_109c1190::Unk_109c1190
void UnkType_109c1190::Unk_109c1190(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_109c1190_Record();
    }
    Unk_109bf5b0(Index, Count, sizeof(UnkType_109c1190_Record));
}
