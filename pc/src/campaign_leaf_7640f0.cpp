// campaign_leaf_7640f0.cpp -- one function at file offset 0x7640f0, preferred VA 0x110640f0. It
// returns 1 when the thirteenth virtual method of the object at 0x78 and of each of the objects at
// 0x68 to 0x74 that are set all succeed; otherwise it returns whether that method succeeds on the
// object returned by its own tenth virtual method. The class and member names are invented; the
// offsets and the virtual slots are the binary's.

class UnkType_110640f0_Part
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
    virtual int VirtualSlot12();
};

class UnkType_110640f0
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
    virtual UnkType_110640f0_Part* VirtualSlot9();

    int Unk_110640f0();

    unsigned char unk_4[0x68 - 0x4];
    UnkType_110640f0_Part* unk_68;
    UnkType_110640f0_Part* unk_6c;
    UnkType_110640f0_Part* unk_70;
    UnkType_110640f0_Part* unk_74;
    UnkType_110640f0_Part* unk_78;
};

// UnkType_110640f0::Unk_110640f0
int UnkType_110640f0::Unk_110640f0()
{
    if ( ( unk_78->VirtualSlot12() == 0 ||
           ( unk_68 != 0 && unk_68->VirtualSlot12() == 0 ) ||
           ( unk_6c != 0 && unk_6c->VirtualSlot12() == 0 ) ||
           ( unk_70 != 0 && unk_70->VirtualSlot12() == 0 ) ||
           ( unk_74 != 0 && unk_74->VirtualSlot12() == 0 ) ) &&
         VirtualSlot9()->VirtualSlot12() == 0 )
    {
        return 0;
    }
    return 1;
}
