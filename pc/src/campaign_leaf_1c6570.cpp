// campaign_leaf_1c6570.cpp -- thiscall method at VA 0x10ac6570 of a hash map keyed by object
// pointers: it rebuilds the hash. A new table of the hash count's words is allocated through slot 0
// of the allocator at VA 0x111c88a0 (tag L"HashMapHash") and filled with -1; every 12-byte pair is
// then chained into the bucket its key's word at 0x04 selects (0 for a null key), the old table is
// freed through slot 2 and the new one kept at 0x0c. One of three identical copies (0x10ac6570,
// 0x10aad740, 0x10aad7e0). The class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10ac6570_Key
{
public:
    int unk_0;
    int unk_4;
};

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
inline int GetTypeHash(const UnkType_10ac6570_Key* Key)
{
    return Key ? Key->unk_4 : 0;
}

struct UnkType_10ac6570_Pair
{
    int HashNext;
    UnkType_10ac6570_Key* Key;
    int Value;
};

class UnkType_10ac6570
{
public:
    void Unk_10ac6570();

private:
    UnkType_10ac6570_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_10ac6570::Unk_10ac6570
void UnkType_10ac6570::Unk_10ac6570()
{
    int* NewHash = new(L"HashMapHash") int[unk_10];
    for ( int i = 0; i < unk_10; i++ )
    {
        NewHash[i] = -1;
    }
    for ( int i = 0; i < unk_04; i++ )
    {
        UnkType_10ac6570_Pair& Pair = unk_00[i];
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
