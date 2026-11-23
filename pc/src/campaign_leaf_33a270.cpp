// campaign_leaf_33a270.cpp -- one function at file offset 0x33a270, preferred VA 0x10c3a270. It
// returns 0 when the method at 0x10bea5e0 fails for (First, Second); otherwise it passes First to
// virtual slot 28 of every set object in the pointer array at 0x3fc (count at 0x400) and returns
// 1. The class, method, member and parameter names are invented; the offsets, the slot and the
// bytes are the binary's.

class UnkType_10c3a270_Item
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

class UnkType_10c3a270
{
public:
    int Unk_10bea5e0(int First, int Second);
    int Unk_10c3a270(int First, int Second);

    unsigned char unk_0[0x3fc];
    UnkType_10c3a270_Item** unk_3fc;
    int unk_400;
};

// UnkType_10c3a270::Unk_10c3a270
int UnkType_10c3a270::Unk_10c3a270(int First, int Second)
{
    int Index;

    if ( Unk_10bea5e0(First, Second) )
    {
        for ( Index = 0; Index < unk_400; Index++ )
        {
            UnkType_10c3a270_Item* Item = unk_3fc[Index];

            if ( Item != 0 )
            {
                Item->VirtualSlot28(First);
            }
        }
        return 1;
    }
    return 0;
}
