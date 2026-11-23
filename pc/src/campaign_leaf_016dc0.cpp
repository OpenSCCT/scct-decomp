// campaign_leaf_016dc0.cpp -- method at VA 0x10916dc0: passes its argument to virtual slot 7
// (vtable offset 0x1c) of each object in the pointer array at 0x34 (count at 0x38). The class,
// member and method names are invented; the offsets and the slot are the binary's.

class UnkType_10916dc0_Item
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

class UnkType_10916dc0
{
public:
    void Unk_10916dc0(int Value);

private:
    unsigned char unk_00[0x34];
    UnkType_10916dc0_Item** unk_34;
    int unk_38;
};

// UnkType_10916dc0::Unk_10916dc0
void UnkType_10916dc0::Unk_10916dc0(int Value)
{
    for ( int i = 0; i < unk_38; i++ )
    {
        unk_34[i]->VirtualSlot7(Value);
    }
}
