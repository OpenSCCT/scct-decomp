// campaign_leaf_06b500.cpp -- method at VA 0x1096b500: passes its argument to virtual slot 29
// (vtable offset 0x74) of each of the seven objects at 0x48 to 0x60 that exist. The class, member
// and method names are invented; the offsets and the slot are the binary's.

class UnkType_1096b500_Item
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
    virtual void VirtualSlot29(int Value);
};

class UnkType_1096b500
{
public:
    void Unk_1096b500(int Value);

private:
    unsigned char unk_00[0x48];
    UnkType_1096b500_Item* unk_48;
    UnkType_1096b500_Item* unk_4c;
    UnkType_1096b500_Item* unk_50;
    UnkType_1096b500_Item* unk_54;
    UnkType_1096b500_Item* unk_58;
    UnkType_1096b500_Item* unk_5c;
    UnkType_1096b500_Item* unk_60;
};

// UnkType_1096b500::Unk_1096b500
void UnkType_1096b500::Unk_1096b500(int Value)
{
    if ( unk_48 )
    {
        unk_48->VirtualSlot29(Value);
    }
    if ( unk_4c )
    {
        unk_4c->VirtualSlot29(Value);
    }
    if ( unk_50 )
    {
        unk_50->VirtualSlot29(Value);
    }
    if ( unk_54 )
    {
        unk_54->VirtualSlot29(Value);
    }
    if ( unk_58 )
    {
        unk_58->VirtualSlot29(Value);
    }
    if ( unk_5c )
    {
        unk_5c->VirtualSlot29(Value);
    }
    if ( unk_60 )
    {
        unk_60->VirtualSlot29(Value);
    }
}
