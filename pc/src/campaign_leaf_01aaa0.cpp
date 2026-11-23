// campaign_leaf_01aaa0.cpp -- method at VA 0x1091aaa0: calls virtual slot 38 (vtable offset 0x98)
// when its argument is 0; deletes the objects at 0x4c, 0x50, 0x54 and 0x58 through their virtual
// destructors (slot 1) and clears the pointers; then passes its argument to the method at VA
// 0x10918f80. The class, member and method names are invented; the offsets, the slots and the
// address are the binary's.

class UnkType_1091aaa0_Item
{
public:
    virtual void VirtualSlot0();
    virtual ~UnkType_1091aaa0_Item();
};

class UnkType_1091aaa0
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

    void Unk_1091aaa0(int Flag);
    void Unk_10918f80(int Flag);

private:
    unsigned char unk_04[0x48];
    UnkType_1091aaa0_Item* unk_4c;
    UnkType_1091aaa0_Item* unk_50;
    UnkType_1091aaa0_Item* unk_54;
    UnkType_1091aaa0_Item* unk_58;
};

// UnkType_1091aaa0::Unk_1091aaa0
void UnkType_1091aaa0::Unk_1091aaa0(int Flag)
{
    if ( !Flag )
    {
        VirtualSlot38();
    }
    delete unk_4c;
    unk_4c = 0;
    delete unk_50;
    unk_50 = 0;
    delete unk_54;
    unk_54 = 0;
    delete unk_58;
    unk_58 = 0;
    Unk_10918f80(Flag);
}
