// campaign_leaf_083c20.cpp -- method at VA 0x10983c20: removes the elements in the range its
// arguments give (first index, count) from an array of 0x2c-byte elements: destroys the array
// member at 0x14 of each (removes its 2-byte elements with the method at VA 0x10907710, frees its
// data through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clears
// it), then passes the range and the element size to the method at VA 0x10981a20. The class, member
// and method names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10907710_083c20
{
public:
    ~UnkType_10907710_083c20()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10907710_083c20_Item
{
private:
    unsigned char unk_00[0x14];
    UnkType_10907710_083c20 unk_14;
    unsigned char unk_20[0x0c];
};

class UnkType_10983c20
{
public:
    void Unk_10983c20(int Index, int Count);
    void Unk_10981a20(int Index, int Count, int ElementSize);

private:
    UnkType_10907710_083c20_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10983c20::Unk_10983c20
void UnkType_10983c20::Unk_10983c20(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10907710_083c20_Item();
    }
    Unk_10981a20(Index, Count, sizeof(UnkType_10907710_083c20_Item));
}
