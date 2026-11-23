// campaign_leaf_0e0c70.cpp -- method at VA 0x109e0c70 of a dynamic array of 12-byte records taking
// an index and a count: frees the pointer at 0x08 of each record in that range through virtual slot
// 2 of the allocator global at VA 0x111c88a0, then calls the method at VA 0x109da290 with the
// index, the count and the record size. guess: an instance of the engine's TArray<T>::Remove. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109e0c70_Record
{
public:
    ~UnkType_109e0c70_Record()
    {
        GUnk_111c88a0->Free(unk_08);
    }

private:
    int unk_00;
    int unk_04;
    void* unk_08;
};

class UnkType_109e0c70
{
public:
    void Unk_109e0c70(int Index, int Count);
    void Unk_109da290(int Index, int Count, int ElementSize);

private:
    UnkType_109e0c70_Record* unk_00;
    int unk_04;
};

// UnkType_109e0c70::Unk_109e0c70
void UnkType_109e0c70::Unk_109e0c70(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_109e0c70_Record();
    }
    Unk_109da290(Index, Count, sizeof(UnkType_109e0c70_Record));
}
