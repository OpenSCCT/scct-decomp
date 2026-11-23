// campaign_leaf_7640b0.cpp -- one function at file offset 0x7640b0, preferred VA 0x110640b0. It
// returns whether virtual slot 12 of the object at 0x70 returns zero, or 0 when there is no
// object. The class, method and member names are invented; the offset is the binary's.

class UnkType_110640b0_Object
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

class UnkType_110640b0
{
public:
    int Unk_110640b0();

    unsigned char unk_0[0x70];
    UnkType_110640b0_Object* unk_70;
};

// UnkType_110640b0::Unk_110640b0
int UnkType_110640b0::Unk_110640b0()
{
    if ( unk_70 != 0 )
    {
        return unk_70->VirtualSlot12() == 0;
    }
    return 0;
}
