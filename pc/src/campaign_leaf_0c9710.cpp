// campaign_leaf_0c9710.cpp -- method at VA 0x109c9710: compares Value with the twelve values at
// 0x2c0-0x2ec of the object virtual slot 34 (vtable offset 0x88) returns, and returns 1, 0.5, 0.2
// or 0.1 by the group it matches, or 0. The class, member, method and parameter names are
// invented; the offsets, the slot and the constants are the binary's.

class UnkType_109c9710_Owner
{
public:
    char unk_0[0x2c0];
    int unk_2c0;
    int unk_2c4;
    int unk_2c8;
    int unk_2cc;
    int unk_2d0;
    int unk_2d4;
    int unk_2d8;
    int unk_2dc;
    int unk_2e0;
    int unk_2e4;
    int unk_2e8;
    int unk_2ec;
};

class UnkType_109c9710
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
    virtual UnkType_109c9710_Owner* VirtualSlot34();

    float Unk_109c9710(int Value);
};

// UnkType_109c9710::Unk_109c9710
float UnkType_109c9710::Unk_109c9710(int Value)
{
    UnkType_109c9710_Owner* Owner = VirtualSlot34();

    if ( Value == Owner->unk_2c0 || Value == Owner->unk_2c4 || Value == Owner->unk_2c8
        || Value == Owner->unk_2cc || Value == Owner->unk_2d8 || Value == Owner->unk_2dc )
    {
        return 1.0f;
    }
    if ( Value == Owner->unk_2d0 || Value == Owner->unk_2d4 )
    {
        return 0.5f;
    }
    if ( Value == Owner->unk_2e0 || Value == Owner->unk_2e4 )
    {
        return 0.2f;
    }
    if ( Value == Owner->unk_2e8 || Value == Owner->unk_2ec )
    {
        return 0.1f;
    }
    return 0.0f;
}
