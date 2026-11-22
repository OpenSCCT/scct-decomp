// campaign_leaf_235500.cpp -- a member function at VA 0x10b35500 that calls the member at VA
// 0x10b74d30 and its own virtual slot 15 with 0, sets the byte at 0x14 of the object the pointer at
// 0x10 refers to and returns true. It does not read its two arguments. The class, method and member
// names are invented; the offsets, addresses and slot are the binary's.

class UnkType_10b35500_Item
{
public:
    unsigned char unk_00[0x14];
    bool unk_14;
};

class UnkType_10b35500
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

    void Unk_10b74d30();
    bool Unk_10b35500(int First, int Second);

private:
    int unk_04;
    int unk_08;
    int unk_0c;
    UnkType_10b35500_Item* unk_10;
};

// UnkType_10b35500::Unk_10b35500
bool UnkType_10b35500::Unk_10b35500(int First, int Second)
{
    Unk_10b74d30();
    VirtualSlot15(0);
    unk_10->unk_14 = true;
    return true;
}
