// campaign_leaf_0d9110.cpp -- method at VA 0x109d9110 of a hash table: a dynamic array of 8-byte
// pairs at 0x00 (next index at 0x00, a byte key at 0x04), a hash array at 0x0c and the hash size at
// 0x10. Allocates a new hash array of that size through virtual slot 0 of the allocator global at
// VA 0x111c88a0 with the tag "HashMapHash", fills it with -1, links every pair into the bucket its
// key masked by the hash size minus one selects, frees the old hash array through slot 2 and keeps
// the new one. guess: an instance of the engine's TMap<K, V>::Rehash. The class, member and method
// names are invented; the offsets and the address are the binary's.

#include "campaign_global_111c88a0.h"

// Allocate
inline void* Allocate(unsigned long Count, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Count, Tag);
}

struct UnkType_109d9110_Pair
{
    int unk_00;
    unsigned char unk_04;
};

class UnkType_109d9110
{
public:
    void Unk_109d9110();

private:
    UnkType_109d9110_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_109d9110::Unk_109d9110
void UnkType_109d9110::Unk_109d9110()
{
    int* NewHash = (int*)Allocate(unk_10 * sizeof(int), L"HashMapHash");
    for ( int i = 0; i < unk_10; i++ )
    {
        NewHash[i] = -1;
    }
    for ( int i = 0; i < unk_04; i++ )
    {
        UnkType_109d9110_Pair& Pair = unk_00[i];
        int Bucket = Pair.unk_04 & (unk_10 - 1);
        Pair.unk_00 = NewHash[Bucket];
        NewHash[Bucket] = i;
    }
    if ( unk_0c )
    {
        GUnk_111c88a0->Free(unk_0c);
    }
    unk_0c = NewHash;
}
