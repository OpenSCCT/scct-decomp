// campaign_leaf_3e4490.cpp -- a member function at VA 0x10ce4490 that calls the member at VA
// 0x10cd79f0, its own virtual slot 26 and, when the pointer at 0x28 is not null, the member at VA
// 0x10cd7aa0 of its object. The class, method and member names are invented; the offsets, addresses
// and slot are the binary's.

class UnkType_10cd7aa0
{
public:
    void Unk_10cd7aa0();
};

class UnkType_10ce4490
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

    void Unk_10cd79f0();
    void Unk_10ce4490();

private:
    unsigned char unk_04[0x28 - 4];
    UnkType_10cd7aa0* unk_28;
};

// UnkType_10ce4490::Unk_10ce4490
void UnkType_10ce4490::Unk_10ce4490()
{
    Unk_10cd79f0();
    VirtualSlot26();
    if ( unk_28 )
    {
        unk_28->Unk_10cd7aa0();
    }
}
