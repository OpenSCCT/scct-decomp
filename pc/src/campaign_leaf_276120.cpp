// campaign_leaf_276120.cpp -- method at VA 0x10b76120: deletes every object in the pointer array at
// 0x04 (count at 0x08) through its virtual destructor, then clears the count and capacity and
// shrinks the array to nothing through the allocator at VA 0x111c88a0, tagged L"FArray". The
// class, member and method names are invented; the offsets are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b76120_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual ~UnkType_10b76120_Item();
};

class UnkType_10b76120_Owner
{
public:
    void Unk_10b76120();

private:
    int unk_00;
    UnkType_10b76120_Item** unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10b76120_Owner::Unk_10b76120
void UnkType_10b76120_Owner::Unk_10b76120()
{
    for ( int Index = 0; Index < unk_08; Index++ )
    {
        delete unk_04[Index];
    }
    unk_08 = 0;
    unk_0c = 0;
    unk_04 = (UnkType_10b76120_Item**)GUnk_111c88a0->Realloc(unk_04, 0, L"FArray");
}
