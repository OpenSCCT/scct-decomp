// campaign_leaf_2733d0.cpp -- method at VA 0x10b733d0 taking an object: clears the word at 0x18,
// empties the word array at 0x0c (count at 0x10, capacity at 0x14; data shrunk to nothing through
// virtual slot 1 of the allocator at VA 0x111c88a0, tagged L"FArray::INT"), passes the word reached
// through the object at 0x08 to this object's virtual slot 9 (vtable offset 0x24) when that object
// is set, then stores at 0x18 the index of the first element equal to the argument's word at 0x50.
// The class, member and method names are invented; the offsets, the slot and the string are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b733d0_18
{
public:
    unsigned char unk_00[0x12c];
    int unk_12c;
};

class UnkType_10b733d0_08
{
public:
    unsigned char unk_00[0x18];
    UnkType_10b733d0_18* unk_18;
};

class UnkType_10b733d0_Array
{
public:
    void UnkEmpty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = (int*)GUnk_111c88a0->Realloc(unk_00, 0, L"FArray::INT");
    }

    int* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b733d0_Other
{
public:
    unsigned char unk_00[0x50];
    int unk_50;
};

class UnkType_10b733d0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9(int Value);

    void Unk_10b733d0(UnkType_10b733d0_Other* Other);

private:
    int unk_04;
    UnkType_10b733d0_08* unk_08;
    UnkType_10b733d0_Array unk_0c;
    int unk_18;
};

// UnkType_10b733d0::Unk_10b733d0
void UnkType_10b733d0::Unk_10b733d0(UnkType_10b733d0_Other* Other)
{
    unk_18 = 0;
    unk_0c.UnkEmpty();
    if ( unk_08 )
    {
        VirtualSlot9(unk_08->unk_18->unk_12c);
    }
    for ( int Index = 0; Index < unk_0c.unk_04; Index++ )
    {
        if ( unk_0c.unk_00[Index] == Other->unk_50 )
        {
            unk_18 = Index;
            return;
        }
    }
}
