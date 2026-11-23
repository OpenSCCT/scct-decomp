// campaign_leaf_0837e0.cpp -- method at VA 0x109837e0: empties an array of 0x2c-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys the array member at 0x14 of each (removes its
// 2-byte elements with the method at VA 0x10907710, frees its data through virtual slot 2 of the
// allocator the global at VA 0x111c88a0 points to and clears it), sets the capacity to its argument
// and the count to 0, and reallocates the data through virtual slot 1 of the allocator, tagged
// "FArray". The class, member and method names are invented; the offsets, the sizes, the tag and
// the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10907710_0837e0
{
public:
    ~UnkType_10907710_0837e0()
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

class UnkType_10907710_0837e0_Item
{
private:
    unsigned char unk_00[0x14];
    UnkType_10907710_0837e0 unk_14;
    unsigned char unk_20[0x0c];
};

class UnkType_109837e0
{
public:
    void Unk_109837e0(int Slack);

private:
    UnkType_10907710_0837e0_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109837e0::Unk_109837e0
void UnkType_109837e0::Unk_109837e0(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_10907710_0837e0_Item();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = static_cast<UnkType_10907710_0837e0_Item*>(GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_10907710_0837e0_Item), L"FArray"));
}
