// campaign_leaf_7640d0.cpp -- thiscall method at VA 0x110640d0: returns 0 when the pointer at 0x74 is
// null, otherwise whether the thirteenth virtual method of that object returns 0. The class and
// method names are invented.

class UnkType_110640d0_74
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

class UnkType_110640d0
{
public:
    int Unk_110640d0();

private:
    int unk_00[29];
    UnkType_110640d0_74* unk_74;
};

// UnkType_110640d0::Unk_110640d0
int UnkType_110640d0::Unk_110640d0()
{
    if ( unk_74 )
    {
        return unk_74->VirtualSlot12() == 0;
    }
    return 0;
}
