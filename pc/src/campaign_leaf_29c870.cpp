// campaign_leaf_29c870.cpp -- method at VA 0x10b9c870: makes two function-local static names on
// first use (L"s_Jump" and L"begin", through the name constructor at VA 0x10cd4790 with 2), passes
// the first and 0 to this object's virtual slot 12 (vtable offset 0x30) and the second, 0 and 0 to
// its virtual slot 13 (vtable offset 0x34), and returns 1. The class, member and method names are
// invented; the slots, the strings and the address are the binary's.

class UnkType_10b9c870_Name
{
public:
    UnkType_10b9c870_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10b9c870
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
    virtual void VirtualSlot12(UnkType_10b9c870_Name Name, int Value);
    virtual void VirtualSlot13(UnkType_10b9c870_Name Name, int Value, int Second);

    int Unk_10b9c870();
};

// UnkType_10b9c870::Unk_10b9c870
int UnkType_10b9c870::Unk_10b9c870()
{
    static UnkType_10b9c870_Name Jump(L"s_Jump", 2);
    static UnkType_10b9c870_Name Begin(L"begin", 2);
    VirtualSlot12(Jump, 0);
    VirtualSlot13(Begin, 0, 0);
    return 1;
}
