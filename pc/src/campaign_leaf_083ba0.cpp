// campaign_leaf_083ba0.cpp -- method at VA 0x10983ba0: removes the elements in the range its
// arguments give (first index, count) from an array of 0x7c-byte elements: destroys the array
// member at 0x24 of each (removes its 4-byte elements with the method at VA 0x10ccb3f0, frees its
// data through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clears its
// data and count), then passes the range and the element size to the method at VA 0x10981680. The
// class, member and method names are invented; the offsets, the sizes and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10ccb3f0_083ba0
{
public:
    ~UnkType_10ccb3f0_083ba0()
    {
        Unk_10ccb3f0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10ccb3f0_083ba0_Item
{
private:
    unsigned char unk_00[0x24];
    UnkType_10ccb3f0_083ba0 unk_24;
    unsigned char unk_30[0x4c];
};

class UnkType_10983ba0
{
public:
    void Unk_10983ba0(int Index, int Count);
    void Unk_10981680(int Index, int Count, int ElementSize);

private:
    UnkType_10ccb3f0_083ba0_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10983ba0::Unk_10983ba0
void UnkType_10983ba0::Unk_10983ba0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10ccb3f0_083ba0_Item();
    }
    Unk_10981680(Index, Count, sizeof(UnkType_10ccb3f0_083ba0_Item));
}
