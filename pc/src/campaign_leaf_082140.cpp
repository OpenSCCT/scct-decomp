// campaign_leaf_082140.cpp -- method at VA 0x10982140: empties an array of 0x18-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys the array member at 0x04 of each (removes its
// 1-byte elements with the method at VA 0x10ccb3f0, frees its data through virtual slot 2 of the
// allocator the global at VA 0x111c88a0 points to and clears its data and count), sets the capacity
// to its argument and the count to 0, and reallocates the data through virtual slot 1 of the
// allocator, tagged "FArray". The class, member and method names are invented; the offsets, the
// sizes, the tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10ccb3f0_082140
{
public:
    ~UnkType_10ccb3f0_082140()
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

class UnkType_10ccb3f0_082140_Item
{
private:
    unsigned char unk_00[0x04];
    UnkType_10ccb3f0_082140 unk_04;
    unsigned char unk_10[0x08];
};

class UnkType_10982140
{
public:
    void Unk_10982140(int Slack);

private:
    UnkType_10ccb3f0_082140_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10982140::Unk_10982140
void UnkType_10982140::Unk_10982140(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_10ccb3f0_082140_Item();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = static_cast<UnkType_10ccb3f0_082140_Item*>(GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_10ccb3f0_082140_Item), L"FArray"));
}
