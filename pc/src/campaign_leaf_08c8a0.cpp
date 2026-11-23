// campaign_leaf_08c8a0.cpp -- method at VA 0x1098c8a0: empties an array of 0x14-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08): destroys the string at 0x04 of each element (empties
// it, reallocating its data through virtual slot 1 of the allocator the global at VA 0x111c88a0
// points to, tagged "FArray::_WORD", removes its 2-byte characters with the method at VA
// 0x10907710, frees its data through slot 2 and clears it), sets the capacity to its argument and
// the count to 0, and reallocates the data through slot 1 of the allocator, tagged "FArray". The
// class, member and method names are invented; the offsets, the sizes, the tags and the address are
// the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10907710_08c8a0
{
public:
    ~UnkType_10907710_08c8a0()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = static_cast<unsigned short*>(GUnk_111c88a0->Realloc(unk_00, 0,
                                                                       L"FArray::_WORD"));
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_08c8a0_String : public UnkType_10907710_08c8a0
{
public:
    ~UnkType_08c8a0_String()
    {
        Empty();
    }
};

class UnkType_08c8a0_Item
{
private:
    int unk_00;
    UnkType_08c8a0_String unk_04;
    unsigned char unk_10[0x14 - 0x10];
};

class UnkType_1098c8a0
{
public:
    void Unk_1098c8a0(int Slack);

private:
    UnkType_08c8a0_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1098c8a0::Unk_1098c8a0
void UnkType_1098c8a0::Unk_1098c8a0(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_08c8a0_Item();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = static_cast<UnkType_08c8a0_Item*>(
        GUnk_111c88a0->Realloc(unk_00, Slack * sizeof(UnkType_08c8a0_Item), L"FArray"));
}
