// campaign_leaf_325fe0.cpp -- one function at file offset 0x325fe0, preferred VA 0x10c25fe0. It
// removes Count 0x10-byte elements from Index of the array at 0x0, destroying each first: each
// element holds at 0x4 an array, whose 4-byte elements the method at 0x10929170 removes before its
// data is freed through the allocator at 0x111c88a0 and it is cleared. Then the method at
// 0x10c25a30 removes the elements. The class, method, member, local and parameter names are
// invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929170
{
public:
    ~UnkType_10929170()
    {
        Unk_10929170(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10929170(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c25fe0_Element
{
public:
    unsigned char unk_0[0x4];
    UnkType_10929170 unk_4;
};

class UnkType_10c25fe0
{
public:
    ~UnkType_10c25fe0()
    {
        Unk_10c25fe0(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c25a30(int Index, int Count, int Size);
    void Unk_10c25fe0(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10c25fe0::Unk_10c25fe0
void UnkType_10c25fe0::Unk_10c25fe0(int Index, int Count)
{
    int Element;

    for ( Element = Index; Element < Index + Count; Element++ )
    {
        ((UnkType_10c25fe0_Element*)unk_0)[Element].~UnkType_10c25fe0_Element();
    }
    Unk_10c25a30(Index, Count, sizeof(UnkType_10c25fe0_Element));
}
