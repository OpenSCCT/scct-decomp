// campaign_leaf_275610.cpp -- a member function at VA 0x10b75610: when the byte at 0x3c is set it
// calls the member at VA 0x10b65820 and virtual slot 14 of the object the global pointer at VA
// 0x1122e72c refers to; it returns true. The class, method, member and global names are invented;
// the offsets, addresses and slot are the binary's.

class UnkType_1122e72c
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
};

extern UnkType_1122e72c* GUnk_1122e72c;

class UnkType_10b75610
{
public:
    void Unk_10b65820();
    bool Unk_10b75610();

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
};

// UnkType_10b75610::Unk_10b75610
bool UnkType_10b75610::Unk_10b75610()
{
    if ( unk_3c )
    {
        Unk_10b65820();
        GUnk_1122e72c->VirtualSlot14();
    }
    return true;
}
