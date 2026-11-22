// campaign_leaf_111c10.cpp -- method at VA 0x10a11c10: calls virtual slot 29 (vtable offset 0x74)
// of the object its first argument points to with this object and its second argument, and returns
// true. The class and method names are invented; the slot is the binary's.

class UnkType_10a11c10;

class UnkType_10a11c10_Target
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
    virtual void VirtualSlot29(UnkType_10a11c10* Source, int Value);
};

class UnkType_10a11c10
{
public:
    bool Unk_10a11c10(UnkType_10a11c10_Target* Target, int Value);
};

// UnkType_10a11c10::Unk_10a11c10
bool UnkType_10a11c10::Unk_10a11c10(UnkType_10a11c10_Target* Target, int Value)
{
    Target->VirtualSlot29(this, Value);
    return true;
}
