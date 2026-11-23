// campaign_leaf_01c8f0.cpp -- method at VA 0x1091c8f0: if virtual slot 18 (vtable offset 0x48)
// returns an object, calls the slot again and returns the value at 0x5c of the object it returns;
// otherwise returns 0. The class, member and method names are invented; the slot and the offset are
// the binary's.

class UnkType_1091c8f0_Result
{
public:
    unsigned char unk_00[0x5c];
    int unk_5c;
};

class UnkType_1091c8f0
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
    virtual UnkType_1091c8f0_Result* VirtualSlot18();

    int Unk_1091c8f0();
};

// UnkType_1091c8f0::Unk_1091c8f0
int UnkType_1091c8f0::Unk_1091c8f0()
{
    if ( VirtualSlot18() )
    {
        return VirtualSlot18()->unk_5c;
    }
    return 0;
}
