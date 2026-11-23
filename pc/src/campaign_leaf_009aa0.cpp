// campaign_leaf_009aa0.cpp -- method at VA 0x10909aa0: returns 1 when the value virtual slot 10
// (vtable offset 0x28) returns and the value at 0x38 are both not -1 and the first is at least the
// second, otherwise 0. The class, member and method names are invented; the offsets, the constant
// and the slot are the binary's.

class UnkType_10909aa0
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
    virtual int VirtualSlot10();

    int Unk_10909aa0();

private:
    unsigned char unk_04[0x34];
    int unk_38;
};

// UnkType_10909aa0::Unk_10909aa0
int UnkType_10909aa0::Unk_10909aa0()
{
    int Value = VirtualSlot10();
    if ( Value != -1 && unk_38 != -1 && Value >= unk_38 )
    {
        return 1;
    }
    return 0;
}
