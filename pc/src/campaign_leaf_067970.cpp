// campaign_leaf_067970.cpp -- method at VA 0x10967970: empties an array of 0x28-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys the member at 0x10 of each, an object whose
// vtable is at VA 0x110bec68 (passes it to virtual slot 18, vtable offset 0x48, of the object at
// 0x04 of it when that is set, then destroys its array member at 0x0c: removes its 1-byte elements
// with the method at VA 0x10966210, frees its data through virtual slot 2 of the allocator the
// global at VA 0x111c88a0 points to and clears it), sets the capacity to its argument and the count
// to 0, and reallocates the data through virtual slot 1 of the allocator, tagged "FArray". The
// class, member and method names are invented; the offsets, the slots, the sizes, the tag and the
// addresses are the binary's.

#include "campaign_leaf_110bec68.h"

class UnkType_110bec68_067970_Item
{
private:
    unsigned char unk_00[0x10];
    UnkType_110bec68 unk_10;
};

class UnkType_10967970
{
public:
    void Unk_10967970(int Slack);

private:
    UnkType_110bec68_067970_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10967970::Unk_10967970
void UnkType_10967970::Unk_10967970(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_110bec68_067970_Item();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = static_cast<UnkType_110bec68_067970_Item*>(GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_110bec68_067970_Item), L"FArray"));
}
