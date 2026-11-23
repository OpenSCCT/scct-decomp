// campaign_leaf_344310.cpp -- one function at file offset 0x344310, preferred VA 0x10c44310. It
// calls the method at 0x10bed8a0 on this object, then passes each set word of 0x444, 0x43c and
// 0x440, with 0, to virtual slot 35 of the object at 0x7c. The class, method and member names are
// invented; the offsets, the slot and the bytes are the binary's.

class UnkType_10c44310_Owner
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
    virtual void VirtualSlot35(int Item, int Flag);
};

class UnkType_10c44310
{
public:
    void Unk_10bed8a0();
    void Unk_10c44310();

    unsigned char unk_0[0x7c];
    UnkType_10c44310_Owner* unk_7c;
    unsigned char unk_80[0x3bc];
    int unk_43c;
    int unk_440;
    int unk_444;
};

// UnkType_10c44310::Unk_10c44310
void UnkType_10c44310::Unk_10c44310()
{
    Unk_10bed8a0();
    if ( unk_444 != 0 )
    {
        unk_7c->VirtualSlot35(unk_444, 0);
    }
    if ( unk_43c != 0 )
    {
        unk_7c->VirtualSlot35(unk_43c, 0);
    }
    if ( unk_440 != 0 )
    {
        unk_7c->VirtualSlot35(unk_440, 0);
    }
}
