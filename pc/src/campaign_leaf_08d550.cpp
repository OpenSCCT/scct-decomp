// campaign_leaf_08d550.cpp -- method at VA 0x1098d550: empties an array of 0x40-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys each element with the destructor at VA
// 0x1098cac0, sets the capacity to its argument and the count to 0, and reallocates the data
// through virtual slot 1 of the allocator the global at VA 0x111c88a0 points to, tagged "FArray".
// The class, member and method names are invented; the offsets, the size, the tag and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1098d550_Item
{
public:
    ~UnkType_1098d550_Item();

private:
    unsigned char unk_00[0x40];
};

class UnkType_1098d550
{
public:
    void Unk_1098d550(int Slack);

private:
    UnkType_1098d550_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1098d550::Unk_1098d550
void UnkType_1098d550::Unk_1098d550(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_1098d550_Item();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = static_cast<UnkType_1098d550_Item*>(GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_1098d550_Item), L"FArray"));
}
