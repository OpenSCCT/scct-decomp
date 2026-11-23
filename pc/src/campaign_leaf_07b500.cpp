// campaign_leaf_07b500.cpp -- method at VA 0x1097b500: passes its argument to the method at VA
// 0x1097b390 of its base class, then to virtual slot 29 (vtable offset 0x74) of each of the six
// objects at 0xe4-0xf8 that exist. The class, member and method names are invented; the offsets,
// the slot and the address are the binary's.

class UnkType_1097b500_Item
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

class UnkType_1097b500_Base
{
public:
    void Unk_1097b390(int Value);

private:
    unsigned char unk_00[0xe4];
};

class UnkType_1097b500 : public UnkType_1097b500_Base
{
public:
    void Unk_1097b500(int Value);

private:
    UnkType_1097b500_Item* unk_e4[6];
};

// UnkType_1097b500::Unk_1097b500
void UnkType_1097b500::Unk_1097b500(int Value)
{
    Unk_1097b390(Value);
    for ( int i = 0; i < 6; i++ )
    {
        if ( unk_e4[i] )
        {
            unk_e4[i]->VirtualSlot29(Value);
        }
    }
}
