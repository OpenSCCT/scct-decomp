// campaign_leaf_4c2cc0.cpp -- one function at file offset 0x4c2cc0, preferred VA 0x10dc2cc0.
// It makes the virtual call in slot 17 and returns whether the method at 0x10dc2c30 then returns
// 4; the same bytes as 0x4c2ca0. The class and method names are invented; the offset and the bytes
// are the binary's.

class UnkType_10dc2cc0
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

    int Unk_10dc2c30();
    int Unk_10dc2cc0();
};

// UnkType_10dc2cc0::Unk_10dc2cc0
int UnkType_10dc2cc0::Unk_10dc2cc0()
{
    VirtualSlot17();
    return Unk_10dc2c30() == 4;
}
