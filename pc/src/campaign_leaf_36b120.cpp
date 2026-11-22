// campaign_leaf_36b120.cpp -- a member function at VA 0x10c6b120 that passes its argument to the
// member at VA 0x1099e020 and then passes this and 0 to virtual slot 35 of the object the pointer
// at 0x7c refers to. The class, method and member names are invented; the offsets, addresses and
// slot are the binary's.

class UnkType_10c6b120_Item
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

class UnkType_10c6b120
{
public:
    void Unk_1099e020(int Value);
    void Unk_10c6b120(int Value);

private:
    unsigned char unk_00[0x7c];
    UnkType_10c6b120_Item* unk_7c;
};

// UnkType_10c6b120::Unk_10c6b120
void UnkType_10c6b120::Unk_10c6b120(int Value)
{
    Unk_1099e020(Value);
    unk_7c->VirtualSlot35(this, 0);
}
