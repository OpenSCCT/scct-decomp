// campaign_leaf_082890.cpp -- method at VA 0x10982890: removes the elements in the range its
// arguments give (first index, count) from an array of 0x18-byte elements: destroys the array
// member at 0x04 of each (removes its 1-byte elements with the method at VA 0x10ccb3f0, frees its
// data through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clears its
// data and count), then passes the range and the element size to the method at VA 0x109817e0. The
// class, member and method names are invented; the offsets, the sizes and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10ccb3f0_082890
{
public:
    ~UnkType_10ccb3f0_082890()
    {
        Unk_10ccb3f0(0, unk_04, 1);
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

class UnkType_10ccb3f0_082890_Item
{
private:
    unsigned char unk_00[0x04];
    UnkType_10ccb3f0_082890 unk_04;
    unsigned char unk_10[0x08];
};

class UnkType_10982890
{
public:
    void Unk_10982890(int Index, int Count);
    void Unk_109817e0(int Index, int Count, int ElementSize);

private:
    UnkType_10ccb3f0_082890_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10982890::Unk_10982890
void UnkType_10982890::Unk_10982890(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10ccb3f0_082890_Item();
    }
    Unk_109817e0(Index, Count, sizeof(UnkType_10ccb3f0_082890_Item));
}
