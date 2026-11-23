// campaign_leaf_018c80.cpp -- method at VA 0x10918c80 taking a value it does not read: deletes each
// object in the pointer array at 0x28 (count at 0x2c) that exists through its virtual destructor
// (slot 1), passes 0 to the method at VA 0x10918cd0 of the array, clears the value at 0x24 and
// calls virtual slot 10 (vtable offset 0x28). The class, member and method names are invented; the
// offsets, the slots and the address are the binary's.

class UnkType_10918c80_Item
{
public:
    virtual void VirtualSlot0();
    virtual ~UnkType_10918c80_Item();
};

class UnkType_10918cd0_018c80
{
public:
    void Unk_10918cd0(int Slack);

    UnkType_10918c80_Item** unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10918c80
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

    void Unk_10918c80(int);

private:
    unsigned char unk_04[0x24 - 0x04];
    int unk_24;
    UnkType_10918cd0_018c80 unk_28;
};

// UnkType_10918c80::Unk_10918c80
void UnkType_10918c80::Unk_10918c80(int)
{
    for ( int i = 0; i < unk_28.unk_04; i++ )
    {
        delete unk_28.unk_00[i];
    }
    unk_28.Unk_10918cd0(0);
    unk_24 = 0;
    VirtualSlot10();
}
