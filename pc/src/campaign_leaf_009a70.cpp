// campaign_leaf_009a70.cpp -- method at VA 0x10909a70: returns 1 when the value virtual slot 10
// (vtable offset 0x28) returns is not -1 and is at least the value virtual slot 11 (offset 0x2c)
// returns, otherwise 0. The class and method names are invented; the constant and the slots are the
// binary's.

class UnkType_10909a70
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
    virtual int VirtualSlot11();

    int Unk_10909a70();
};

// UnkType_10909a70::Unk_10909a70
int UnkType_10909a70::Unk_10909a70()
{
    int Value = VirtualSlot10();
    if ( Value != -1 && Value >= VirtualSlot11() )
    {
        return 1;
    }
    return 0;
}
