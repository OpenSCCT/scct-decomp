// campaign_leaf_3e9610.cpp -- a member function at VA 0x10ce9610 that passes the wide string
// L"class %s*" and the result of virtual slot 34 of the object the pointer at 0x54 refers to to the
// free function at VA 0x10cce100, together with its first argument. It does not read its second
// argument. guess: an object property writing its C++ type. The class, method and member names are
// invented; the offsets, addresses, slot and string are the binary's.

class UnkType_10cce100;

void Unk_10cce100(UnkType_10cce100& Out, const unsigned short* Format, ...);

class UnkType_10ce9610_Item
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
    virtual const unsigned short* VirtualSlot34();
};

class UnkType_10ce9610
{
public:
    void Unk_10ce9610(UnkType_10cce100& Out, int Flags);

private:
    unsigned char unk_00[0x54];
    UnkType_10ce9610_Item* unk_54;
};

// UnkType_10ce9610::Unk_10ce9610
void UnkType_10ce9610::Unk_10ce9610(UnkType_10cce100& Out, int Flags)
{
    Unk_10cce100(Out, L"class %s*", unk_54->VirtualSlot34());
}
