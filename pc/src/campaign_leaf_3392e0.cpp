// campaign_leaf_3392e0.cpp -- one function at file offset 0x3392e0, preferred VA 0x10c392e0. It
// returns 0 when the method at 0x10bea5e0 fails for (First, Second); otherwise it passes First to
// virtual slot 28 of each of the objects at 0x428, 0x42c, 0x430 and 0x434 that is set and returns
// 1. The class, method, member and parameter names are invented; the offsets, the slot and the
// bytes are the binary's.

class UnkType_10c392e0_Item
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

class UnkType_10c392e0
{
public:
    int Unk_10bea5e0(int First, int Second);
    int Unk_10c392e0(int First, int Second);

    unsigned char unk_0[0x428];
    UnkType_10c392e0_Item* unk_428;
    UnkType_10c392e0_Item* unk_42c;
    UnkType_10c392e0_Item* unk_430;
    UnkType_10c392e0_Item* unk_434;
};

// UnkType_10c392e0::Unk_10c392e0
int UnkType_10c392e0::Unk_10c392e0(int First, int Second)
{
    if ( Unk_10bea5e0(First, Second) )
    {
        if ( unk_428 != 0 )
        {
            unk_428->VirtualSlot28(First);
        }
        if ( unk_42c != 0 )
        {
            unk_42c->VirtualSlot28(First);
        }
        if ( unk_430 != 0 )
        {
            unk_430->VirtualSlot28(First);
        }
        if ( unk_434 != 0 )
        {
            unk_434->VirtualSlot28(First);
        }
        return 1;
    }
    return 0;
}
