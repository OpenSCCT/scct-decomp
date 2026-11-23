// campaign_leaf_24b910.cpp -- a member function at VA 0x10b4b910 taking an int it does not read
// and a float: when the byte at 0x54 is 1, it lowers the float at 0x50 by the float argument while
// that float is above zero; once it is not, it passes the pointer at 0x38, 0, 0 and 0 to the
// member at VA 0x10ad5820 of the object the pointer at 0x0c refers to, clears the bytes at 0x54
// and 0x4c, sets the global at VA 0x111f55dc to 1 and calls virtual slot 15 of the object the
// pointer at 0x48 refers to with 1. It returns false. guess: counts down a delay. The class,
// method, member, parameter and global names are invented; the offsets, addresses and slot are the
// binary's.

#include "campaign_global_111f55dc.h"

class UnkType_10b4b910_Page;

class UnkType_10b4b910_Menu
{
public:
    void Unk_10ad5820(UnkType_10b4b910_Page* Page, int First, int Second, int Third);
};

class UnkType_10b4b910_Target
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

class UnkType_10b4b910
{
public:
    bool Unk_10b4b910(int Unused, float Delta);

private:
    unsigned char unk_00[0x0c];
    UnkType_10b4b910_Menu* unk_0c;
    unsigned char unk_10[0x38 - 0x10];
    UnkType_10b4b910_Page* unk_38;
    unsigned char unk_3c[0x48 - 0x3c];
    UnkType_10b4b910_Target* unk_48;
    bool unk_4c;
    float unk_50;
    unsigned char unk_54;
};

// UnkType_10b4b910::Unk_10b4b910
bool UnkType_10b4b910::Unk_10b4b910(int Unused, float Delta)
{
    if ( unk_54 == 1 )
    {
        if ( 0.0f < unk_50 )
        {
            unk_50 -= Delta;
            return false;
        }
        unk_0c->Unk_10ad5820(unk_38, 0, 0, 0);
        unk_54 = 0;
        unk_4c = false;
        GUnk_111f55dc = 1;
        unk_48->VirtualSlot15(1);
    }
    return false;
}
