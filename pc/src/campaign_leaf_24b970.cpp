// campaign_leaf_24b970.cpp -- a member function at VA 0x10b4b970 that clears the byte at 0x54, sets
// the global at VA 0x111f55dc to 1 and calls virtual slot 15 of the object the pointer at 0x50
// refers to with 1. The class, method, member and global names are invented; the offsets, addresses
// and slot are the binary's.

#include "campaign_global_111f55dc.h"

class UnkType_10b4b970_Item
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
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15(int Value);
};

class UnkType_10b4b970
{
public:
    void Unk_10b4b970();

private:
    unsigned char unk_00[0x50];
    UnkType_10b4b970_Item* unk_50;
    unsigned char unk_54;
};

// UnkType_10b4b970::Unk_10b4b970
void UnkType_10b4b970::Unk_10b4b970()
{
    unk_54 = 0;
    GUnk_111f55dc = 1;
    unk_50->VirtualSlot15(1);
}
