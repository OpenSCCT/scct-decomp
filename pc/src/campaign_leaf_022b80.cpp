// campaign_leaf_022b80.cpp -- method at VA 0x10922b80: rebuilds the hash of a map keyed by strings
// whose 0x1c-byte pairs (next index, key string, value) are in the array at 0x00 (count at 0x04):
// allocates a table of as many indices as the count at 0x10 through the allocator the global at VA
// 0x111c88a0 points to, tagged "HashMapHash", fills it with -1, chains each pair into the bucket
// the free function at VA 0x109013f0 picks for its key text, frees the old table at 0x0c when there
// is one and stores the new one there. The class, member and method names are invented; the
// offsets, the sizes, the tag and the address are the binary's.

#include "campaign_global_111c88a0.h"

inline void* operator new[](unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

inline void operator delete[](void* Pointer)
{
    GUnk_111c88a0->Free(Pointer);
}

class UnkType_022b80_String
{
public:
    const unsigned short* operator*() const
    {
        return unk_04 ? unk_00 : L"";
    }

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10922b80_Pair
{
public:
    int unk_00;
    UnkType_022b80_String unk_04;
    unsigned char unk_10[0xc];
};

unsigned int Unk_109013f0(const unsigned short* Text);

class UnkType_10922b80
{
public:
    void Unk_10922b80();

private:
    UnkType_10922b80_Pair* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

// UnkType_10922b80::Unk_10922b80
void UnkType_10922b80::Unk_10922b80()
{
    int* NewHash = new(L"HashMapHash") int[unk_10];
    int i;
    for ( i = 0; i < unk_10; i++ )
    {
        NewHash[i] = -1;
    }
    for ( i = 0; i < unk_04; i++ )
    {
        UnkType_10922b80_Pair& Pair = unk_00[i];
        int Bucket = Unk_109013f0(*Pair.unk_04) & (unk_10 - 1);
        Pair.unk_00 = NewHash[Bucket];
        NewHash[Bucket] = i;
    }
    if ( unk_0c )
    {
        delete[] unk_0c;
    }
    unk_0c = NewHash;
}
