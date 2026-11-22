// campaign_leaf_10dac0.cpp -- method at VA 0x10a0dac0: if the pointer at 0x40 is set, calls virtual
// slot 5 (vtable offset 0x14) on the object it points to; returns 1. The class, member and method
// names are invented; the offsets are the binary's.

class UnkType_10a0dac0_40
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
};

class UnkType_10a0dac0
{
public:
    int Unk_10a0dac0();

private:
    unsigned char unk_00[0x40];
    UnkType_10a0dac0_40* unk_40;
};

// UnkType_10a0dac0::Unk_10a0dac0
int UnkType_10a0dac0::Unk_10a0dac0()
{
    UnkType_10a0dac0_40* Unk40 = unk_40;
    if ( Unk40 )
    {
        Unk40->VirtualSlot5();
    }
    return 1;
}
