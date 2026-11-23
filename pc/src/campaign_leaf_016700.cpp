// campaign_leaf_016700.cpp -- method at VA 0x10916700: counts the links from the object at 0x0c,
// following the pointer at 0x0c of each, until it reaches the object virtual slot 57 (vtable offset
// 0xe4) of the object at 0x08 returns, asking again at each step. The class, member and method
// names are invented; the offsets and the slot are the binary's.

class UnkType_10916700_Link
{
public:
    unsigned char unk_00[0x0c];
    UnkType_10916700_Link* unk_0c;
};

class UnkType_10916700_08
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
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual UnkType_10916700_Link* VirtualSlot57();
};

class UnkType_10916700
{
public:
    int Unk_10916700();

private:
    unsigned char unk_00[0x08];
    UnkType_10916700_08* unk_08;
    UnkType_10916700_Link* unk_0c;
};

// UnkType_10916700::Unk_10916700
int UnkType_10916700::Unk_10916700()
{
    UnkType_10916700_Link* Link = unk_0c;
    int Count = 0;
    while ( Link != unk_08->VirtualSlot57() )
    {
        Link = Link->unk_0c;
        Count++;
    }
    return Count;
}
