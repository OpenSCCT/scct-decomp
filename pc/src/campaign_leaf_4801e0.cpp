// campaign_leaf_4801e0.cpp -- thiscall method at VA 0x10d801e0. With no object at 0x00 it calls
// the function at 0x10d977f0 with the code 0xa0030004 and returns false. Otherwise it looks up an
// object by the top ten bits of the word at 0x2c of the object at 0x00 (function at 0x10d83ac0)
// and calls its sixteenth virtual method with the global at 0x1131b194; when that fails it
// reports the code 0xe003000c the same way and returns false, else true. The class and method
// names are invented.

#include "campaign_global_1131b194.h"

class UnkType_10d801e0_Lookup
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
    virtual bool VirtualSlot15(int Value);
};

struct UnkType_10d801e0_Item
{
    unsigned char unk_0[0x2c];
    unsigned int unk_2c;
};

void Unk_10d977f0(int First, int Second, unsigned int Code, int Fourth);
UnkType_10d801e0_Lookup* Unk_10d83ac0(unsigned int Index);

class UnkType_10d801e0
{
public:
    bool Unk_10d801e0();

private:
    UnkType_10d801e0_Item* unk_0;
};

// UnkType_10d801e0::Unk_10d801e0
bool UnkType_10d801e0::Unk_10d801e0()
{
    if ( unk_0 == 0 )
    {
        Unk_10d977f0(0, 0, 0xa0030004, 0);
        return false;
    }
    if ( !Unk_10d83ac0(unk_0->unk_2c >> 22)->VirtualSlot15(GUnk_1131b194) )
    {
        Unk_10d977f0(0, 0, 0xe003000c, 0);
        return false;
    }
    return true;
}
