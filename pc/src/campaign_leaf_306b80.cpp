// campaign_leaf_306b80.cpp -- one function at file offset 0x306b80, preferred VA 0x10c06b80. It
// removes Count 0x34-byte elements from Index of the array at 0x0, destroying each first: each
// element holds at 0x24 an array, which the method at 0x10c069e0 empties before its data is freed
// through the allocator at 0x111c88a0 and it is cleared. Then the method at 0x10c05e70 removes the
// elements. The class, method, member, local and parameter names are invented; the offsets and the
// bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c069e0
{
public:
    ~UnkType_10c069e0()
    {
        Unk_10c069e0(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c069e0(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c06b80_Element
{
public:
    unsigned char unk_0[0x24];
    UnkType_10c069e0 unk_24;
    unsigned char unk_30[0x4];
};

class UnkType_10c06b80
{
public:
    ~UnkType_10c06b80()
    {
        Unk_10c06b80(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c05e70(int Index, int Count, int Size);
    void Unk_10c06b80(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10c06b80::Unk_10c06b80
void UnkType_10c06b80::Unk_10c06b80(int Index, int Count)
{
    int Element;

    for ( Element = Index; Element < Index + Count; Element++ )
    {
        ((UnkType_10c06b80_Element*)unk_0)[Element].~UnkType_10c06b80_Element();
    }
    Unk_10c05e70(Index, Count, sizeof(UnkType_10c06b80_Element));
}
