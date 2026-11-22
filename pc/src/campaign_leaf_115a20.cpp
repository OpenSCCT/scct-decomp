// campaign_leaf_115a20.cpp -- method at VA 0x10a15a20: calls virtual slot 30 (vtable offset 0x78)
// of the object its first argument points to with this object and its second argument, and returns
// the result. The class and method names are invented; the slot is the binary's.

class UnkType_10a15a20;

class UnkType_10a15a20_Target
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
    virtual int VirtualSlot30(UnkType_10a15a20* Source, int Value);
};

class UnkType_10a15a20
{
public:
    int Unk_10a15a20(UnkType_10a15a20_Target* Target, int Value);
};

// UnkType_10a15a20::Unk_10a15a20
int UnkType_10a15a20::Unk_10a15a20(UnkType_10a15a20_Target* Target, int Value)
{
    return Target->VirtualSlot30(this, Value);
}
