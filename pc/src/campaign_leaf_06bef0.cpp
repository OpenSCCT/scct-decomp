// campaign_leaf_06bef0.cpp -- method at VA 0x1096bef0: returns the larger of what virtual slot 26
// (vtable offset 0x68) returns for the objects at 0x50 and 0x4c, taking 0 for one that does not
// exist. The class, member and method names are invented; the offsets and the slot are the
// binary's.

class UnkType_1096bef0_Item
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
    virtual int VirtualSlot26();
};

class UnkType_1096bef0
{
public:
    int Unk_1096bef0();

private:
    unsigned char unk_00[0x4c];
    UnkType_1096bef0_Item* unk_4c;
    UnkType_1096bef0_Item* unk_50;
};

// UnkType_1096bef0::Unk_1096bef0
int UnkType_1096bef0::Unk_1096bef0()
{
    int First = unk_50 ? unk_50->VirtualSlot26() : 0;
    int Second = unk_4c ? unk_4c->VirtualSlot26() : 0;
    return Second < First ? First : Second;
}
