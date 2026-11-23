// campaign_leaf_4f2550.cpp -- method at VA 0x10df2550: if the pointer at 0x00 is null it reports
// the code 0xa0030004 through the function at VA 0x10d977f0 and returns false; otherwise it looks
// up an object from bits 22-31 of the pointee's member at 0x2c (function at VA 0x10d83ac0), calls
// its virtual slot 15 with the global at VA 0x1131b388, and on a false result reports 0xe003000c
// and returns false. The class, method and member names are invented; the codes, slot and addresses
// are the binary's.

#include "campaign_global_1131b388.h"

class UnkType_10df2550_Target
{
public:
    unsigned char unk_00[0x2c];
    unsigned int unk_2c;
};

class UnkType_10df2550_Found
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
    virtual bool VirtualSlot15(UnkType_1131b388* Value);
};

void Unk_10d977f0(int Arg0, int Arg1, unsigned int Code, int Arg3);
UnkType_10df2550_Found* Unk_10d83ac0(unsigned int Index);

class UnkType_10df2550
{
public:
    bool Unk_10df2550();

    UnkType_10df2550_Target* unk_00;
};

// UnkType_10df2550::Unk_10df2550
bool UnkType_10df2550::Unk_10df2550()
{
    if ( unk_00 == 0 )
    {
        Unk_10d977f0(0, 0, 0xa0030004, 0);
        return false;
    }
    if ( !Unk_10d83ac0(unk_00->unk_2c >> 22)->VirtualSlot15(GUnk_1131b388) )
    {
        Unk_10d977f0(0, 0, 0xe003000c, 0);
        return false;
    }
    return true;
}
