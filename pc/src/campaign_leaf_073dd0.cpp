// campaign_leaf_073dd0.cpp -- method at VA 0x10973dd0: empties an array of 0x1c-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys the array member at 0x10 of each (removes its
// 12-byte elements with the method at VA 0x10929260, frees its data through virtual slot 2 of the
// allocator the global at VA 0x111c88a0 points to and clears it), sets the capacity to its argument
// and the count to 0, and reallocates the data through virtual slot 1 of the allocator, tagged
// "FArray". The class, member and method names are invented; the offsets, the sizes, the tag and
// the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929260_073dd0
{
public:
    ~UnkType_10929260_073dd0()
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

class UnkType_10929260_073dd0_Item
{
private:
    unsigned char unk_00[0x10];
    UnkType_10929260_073dd0 unk_10;
};

class UnkType_10973dd0
{
public:
    void Unk_10973dd0(int Slack);

private:
    UnkType_10929260_073dd0_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10973dd0::Unk_10973dd0
void UnkType_10973dd0::Unk_10973dd0(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_10929260_073dd0_Item();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = static_cast<UnkType_10929260_073dd0_Item*>(GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_10929260_073dd0_Item), L"FArray"));
}
