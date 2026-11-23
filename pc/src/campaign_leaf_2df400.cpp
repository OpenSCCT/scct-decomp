// campaign_leaf_2df400.cpp -- method at VA 0x10bdf400 of a dynamic array of 0xc-byte elements
// holding a dynamic array at 0x00, taking an index and a count: destroys the elements in that range
// (each inner array removes its contents through the method at VA 0x10929170 (element size 4),
// frees its data through virtual slot 2 of the allocator at VA 0x111c88a0 and clears its three
// words), then passes the index, the count and the element size to the method at VA 0x10bdb3c0. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bdf400_Inner
{
public:
    ~UnkType_10bdf400_Inner()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bdf400_Elem
{
public:
    UnkType_10bdf400_Inner unk_00;
};

class UnkType_10bdf400
{
public:
    void Unk_10bdf400(int Index, int Count);
    void Unk_10bdb3c0(int Index, int Count, int ElementSize);

private:
    UnkType_10bdf400_Elem* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10bdf400::Unk_10bdf400
void UnkType_10bdf400::Unk_10bdf400(int Index, int Count)
{
    for ( int Item = Index; Item < Index + Count; Item++ )
    {
        unk_00[Item].~UnkType_10bdf400_Elem();
    }
    Unk_10bdb3c0(Index, Count, sizeof(UnkType_10bdf400_Elem));
}
