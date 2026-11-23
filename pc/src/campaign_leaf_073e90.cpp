// campaign_leaf_073e90.cpp -- method at VA 0x10973e90: removes the elements in the range its
// arguments give (first index, count) from an array of 0x1c-byte elements: destroys the array
// member at 0x10 of each (removes its 12-byte elements with the method at VA 0x10929260, frees its
// data through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clears
// it), then passes the range and the element size to the method at VA 0x10973a40. The class, member
// and method names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929260_073e90
{
public:
    ~UnkType_10929260_073e90()
    {
        Unk_10929260(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929260(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10929260_073e90_Item
{
private:
    unsigned char unk_00[0x10];
    UnkType_10929260_073e90 unk_10;
};

class UnkType_10973e90
{
public:
    void Unk_10973e90(int Index, int Count);
    void Unk_10973a40(int Index, int Count, int ElementSize);

private:
    UnkType_10929260_073e90_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10973e90::Unk_10973e90
void UnkType_10973e90::Unk_10973e90(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10929260_073e90_Item();
    }
    Unk_10973a40(Index, Count, sizeof(UnkType_10929260_073e90_Item));
}
