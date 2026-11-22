// campaign_leaf_25b9f0.cpp -- a member function at VA 0x10b5b9f0 that calls its own virtual slot 15
// with 0 and then sets the byte at 0x14 of the object the pointer at 0x14 refers to. It does not
// read its argument. The class, method and member names are invented; the offsets and the slot are
// the binary's.

class UnkType_10b5b9f0_Item
{
public:
    unsigned char unk_00[0x14];
    bool unk_14;
};

class UnkType_10b5b9f0
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

    bool Unk_10b5b9f0(int Unused);

private:
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    UnkType_10b5b9f0_Item* unk_14;
};

// UnkType_10b5b9f0::Unk_10b5b9f0
bool UnkType_10b5b9f0::Unk_10b5b9f0(int Unused)
{
    VirtualSlot15(0);
    unk_14->unk_14 = true;
    return true;
}
