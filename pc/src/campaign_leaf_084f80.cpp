// campaign_leaf_084f80.cpp -- method at VA 0x10984f80: removes the elements in the range its
// arguments give (first index, count) from an array of 0x80-byte elements: destroys the array
// member at 0x70 of each (removes its elements with the method at VA 0x10983b20, frees its data
// through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clears it),
// then passes the range and the element size to the method at VA 0x109814e0. The class, member and
// method names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10983b20_084f80
{
public:
    ~UnkType_10983b20_084f80()
    {
        Unk_10983b20(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10983b20(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10983b20_084f80_Item
{
private:
    unsigned char unk_00[0x70];
    UnkType_10983b20_084f80 unk_70;
    unsigned char unk_7c[0x04];
};

class UnkType_10984f80
{
public:
    void Unk_10984f80(int Index, int Count);
    void Unk_109814e0(int Index, int Count, int ElementSize);

private:
    UnkType_10983b20_084f80_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10984f80::Unk_10984f80
void UnkType_10984f80::Unk_10984f80(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10983b20_084f80_Item();
    }
    Unk_109814e0(Index, Count, sizeof(UnkType_10983b20_084f80_Item));
}
