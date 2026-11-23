// campaign_leaf_07d240.cpp -- method at VA 0x1097d240: rebuilds the hash of a map whose 8-byte
// pairs (next index, 16-bit key, 16-bit value) are in the array at 0x00 (count at 0x04): allocates
// a table of as many indices as the count at 0x10 through the allocator the global at VA 0x111c88a0
// points to, tagged "HashMapHash", fills it with -1, chains each pair into the bucket its key
// selects, frees the old table at 0x0c when there is one and stores the new one there. The class,
// member and method names are invented; the offsets, the sizes and the tag are the binary's.

#include "campaign_global_111c88a0.h"

inline void* operator new[](unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

inline void operator delete[](void* Pointer)
{
    GUnk_111c88a0->Free(Pointer);
}

class UnkType_1097d240_Pair
{
public:
    int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
};

class UnkType_1097d240
{
public:
    void Unk_1097d240();

private:
    UnkType_1097d240_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_1097d240::Unk_1097d240
void UnkType_1097d240::Unk_1097d240()
{
    int* NewHash = new(L"HashMapHash") int[unk_10];
    int i;
    for ( i = 0; i < unk_10; i++ )
    {
        NewHash[i] = -1;
    }
    for ( i = 0; i < unk_04; i++ )
    {
        UnkType_1097d240_Pair& Pair = unk_00[i];
        int Bucket = Pair.unk_04 & (unk_10 - 1);
        Pair.unk_00 = NewHash[Bucket];
        NewHash[Bucket] = i;
    }
    if ( unk_0c )
    {
        delete[] unk_0c;
    }
    unk_0c = NewHash;
}
