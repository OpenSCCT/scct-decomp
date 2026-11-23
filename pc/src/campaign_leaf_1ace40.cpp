// campaign_leaf_1ace40.cpp -- thiscall method at VA 0x10aace40 of a hash map: it rebuilds the hash.
// A new table of the hash count's words is allocated through slot 0 of the allocator at VA
// 0x111c88a0 (tag L"HashMapHash") and filled with -1; every 12-byte pair of the pair array is then
// chained into the bucket its key selects, the old table is freed through slot 2 and the new one
// kept at 0x0c. The class, method and member names are invented.

#include "campaign_global_111c88a0.h"

// operator new[]
inline void* operator new[](unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

// operator delete[]
inline void operator delete[](void* Original)
{
    GUnk_111c88a0->Free(Original);
}

// GetTypeHash
inline int GetTypeHash(int Key)
{
    return Key;
}

struct UnkType_10aace40_Pair
{
    int HashNext;
    int Key;
    int Value;
};

class UnkType_10aace40
{
public:
    void Unk_10aace40();

private:
    UnkType_10aace40_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_10aace40::Unk_10aace40
void UnkType_10aace40::Unk_10aace40()
{
    int* NewHash = new(L"HashMapHash") int[unk_10];
    for ( int i = 0; i < unk_10; i++ )
    {
        NewHash[i] = -1;
    }
    for ( int i = 0; i < unk_04; i++ )
    {
        UnkType_10aace40_Pair& Pair = unk_00[i];
        int iHash = GetTypeHash(Pair.Key) & (unk_10 - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if ( unk_0c )
    {
        delete[] unk_0c;
    }
    unk_0c = NewHash;
}
