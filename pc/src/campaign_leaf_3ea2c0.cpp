// campaign_leaf_3ea2c0.cpp -- a member function at VA 0x10cea2c0 taking two arguments it does not
// read: it stores 1 in the 16-bit value at 0x36 and the result of virtual slot 22 of the object the
// pointer at 0x18 refers to in the 16-bit value at 0x44. The class, method and member names are
// invented; the offsets and the slot are the binary's.

class UnkType_10cea2c0_Item
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
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual short VirtualSlot22();
};

class UnkType_10cea2c0
{
public:
    void Unk_10cea2c0(int First, int Second);

private:
    unsigned char unk_00[0x18];
    UnkType_10cea2c0_Item* unk_18;
    unsigned char unk_1c[0x36 - 0x1c];
    short unk_36;
    unsigned char unk_38[0x44 - 0x38];
    short unk_44;
};

// UnkType_10cea2c0::Unk_10cea2c0
void UnkType_10cea2c0::Unk_10cea2c0(int First, int Second)
{
    unk_36 = 1;
    unk_44 = unk_18->VirtualSlot22();
}
