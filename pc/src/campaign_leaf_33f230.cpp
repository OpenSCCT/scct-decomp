// campaign_leaf_33f230.cpp -- one function at file offset 0x33f230, preferred VA 0x10c3f230. It
// returns 0 when the method at 0x10bea5e0 fails for (First, Second); otherwise it passes First to
// virtual slot 28 of each of the objects at 0x40c, 0x424 and 0x428 that is set and returns 1. The
// class, method, member and parameter names are invented; the offsets, the slot and the bytes are
// the binary's.

class UnkType_10c3f230_Item
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
    virtual void VirtualSlot28(int First);
};

class UnkType_10c3f230
{
public:
    int Unk_10bea5e0(int First, int Second);
    int Unk_10c3f230(int First, int Second);

    unsigned char unk_0[0x40c];
    UnkType_10c3f230_Item* unk_40c;
    unsigned char unk_410[0x14];
    UnkType_10c3f230_Item* unk_424;
    UnkType_10c3f230_Item* unk_428;
};

// UnkType_10c3f230::Unk_10c3f230
int UnkType_10c3f230::Unk_10c3f230(int First, int Second)
{
    if ( Unk_10bea5e0(First, Second) )
    {
        if ( unk_40c != 0 )
        {
            unk_40c->VirtualSlot28(First);
        }
        if ( unk_424 != 0 )
        {
            unk_424->VirtualSlot28(First);
        }
        if ( unk_428 != 0 )
        {
            unk_428->VirtualSlot28(First);
        }
        return 1;
    }
    return 0;
}
