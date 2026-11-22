// campaign_leaf_2f1be0.cpp -- a member function at VA 0x10bf1be0 that calls the member at VA
// 0x10bed8a0 and then, when the pointer at 0x3fc is not null, passes it and 0 to virtual slot 35 of
// the object the pointer at 0x7c refers to. The class, method and member names are invented; the
// offsets, addresses and slot are the binary's.

class UnkType_10bf1be0_Item
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
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35(void* Item, int Value);
};

class UnkType_10bf1be0
{
public:
    void Unk_10bed8a0();
    void Unk_10bf1be0();

private:
    unsigned char unk_000[0x7c];
    UnkType_10bf1be0_Item* unk_07c;
    unsigned char unk_080[0x3fc - 0x80];
    void* unk_3fc;
};

// UnkType_10bf1be0::Unk_10bf1be0
void UnkType_10bf1be0::Unk_10bf1be0()
{
    Unk_10bed8a0();
    if ( unk_3fc )
    {
        unk_07c->VirtualSlot35(unk_3fc, 0);
    }
}
