// campaign_leaf_2e2d30.cpp -- method at VA 0x10be2d30 of a dynamic array of 20-byte elements holding
// a dynamic array at 0x08, taking an index and a count: destroys the elements in that range (each
// inner array removes its contents through the method at VA 0x10bdf500, frees its data through
// virtual slot 2 of the allocator at VA 0x111c88a0 and clears its three words), then passes the
// index, the count and the element size to the method at VA 0x10bdb570. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10be2d30_08
{
public:
    ~UnkType_10be2d30_08()
    {
        Unk_10bdf500(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10bdf500(int Index, int Count);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be2d30_Elem
{
public:
    int unk_00;
    int unk_04;
    UnkType_10be2d30_08 unk_08;
};

class UnkType_10be2d30
{
public:
    void Unk_10be2d30(int Index, int Count);
    void Unk_10bdb570(int Index, int Count, int ElementSize);

private:
    UnkType_10be2d30_Elem* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10be2d30::Unk_10be2d30
void UnkType_10be2d30::Unk_10be2d30(int Index, int Count)
{
    for ( int Item = Index; Item < Index + Count; Item++ )
    {
        unk_00[Item].~UnkType_10be2d30_Elem();
    }
    Unk_10bdb570(Index, Count, sizeof(UnkType_10be2d30_Elem));
}
