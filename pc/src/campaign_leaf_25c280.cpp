// campaign_leaf_25c280.cpp -- a member function at VA 0x10b5c280 taking a flag: it passes 1 when
// the flag is set, otherwise 0, to virtual slot 7 of the object the pointer at 0x6c refers to, and
// then passes the pointer at 0x38, the global at VA 0x1122e28c, L"MenuSettings", L"YES" or L"NO",
// L"Localization\\PreGame_PC" and 1 to the free function at VA 0x10b71f10. The class, function,
// method, member, parameter and global names are invented; the offsets, strings, addresses and slot
// are the binary's.

#include "campaign_global_1122e28c.h"

void Unk_10b71f10(void* Owner, int Name, const unsigned short* Section, const unsigned short* Value,
                  const unsigned short* File, int Flags);

class UnkType_10b5c280_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(int Value);
};

class UnkType_10b5c280
{
public:
    void Unk_10b5c280(int Flag);

private:
    unsigned char unk_00[0x38];
    void* unk_38;
    unsigned char unk_3c[0x6c - 0x3c];
    UnkType_10b5c280_Item* unk_6c;
};

// UnkType_10b5c280::Unk_10b5c280
void UnkType_10b5c280::Unk_10b5c280(int Flag)
{
    if ( Flag )
    {
        unk_6c->VirtualSlot7(1);
        Unk_10b71f10(unk_38, GUnk_1122e28c, L"MenuSettings", L"YES", L"Localization\\PreGame_PC",
                     1);
    }
    else
    {
        unk_6c->VirtualSlot7(0);
        Unk_10b71f10(unk_38, GUnk_1122e28c, L"MenuSettings", L"NO", L"Localization\\PreGame_PC", 1);
    }
}
