// campaign_leaf_083b20.cpp -- method at VA 0x10983b20: removes the elements in the range its
// arguments give (first index, count) from an array of 0x10-byte elements: destroys the array
// member at 0x04 of each (removes its 12-byte elements with the method at VA 0x10929260, frees its
// data through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clears
// it), then passes the range and the element size to the method at VA 0x10981450. The class, member
// and method names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929260_083b20
{
public:
    ~UnkType_10929260_083b20()
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

class UnkType_10929260_083b20_Item
{
private:
    unsigned char unk_00[0x04];
    UnkType_10929260_083b20 unk_04;
};

class UnkType_10983b20
{
public:
    void Unk_10983b20(int Index, int Count);
    void Unk_10981450(int Index, int Count, int ElementSize);

private:
    UnkType_10929260_083b20_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10983b20::Unk_10983b20
void UnkType_10983b20::Unk_10983b20(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10929260_083b20_Item();
    }
    Unk_10981450(Index, Count, sizeof(UnkType_10929260_083b20_Item));
}
