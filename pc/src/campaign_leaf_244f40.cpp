// campaign_leaf_244f40.cpp -- a member function at VA 0x10b44f40: when the byte at 0x3c is set it
// calls the member at VA 0x10b75610 and virtual slot 14 of the object the pointer at 0x60 refers
// to; it returns true. The class, method and member names are invented; the offsets, addresses and
// slot are the binary's.

class UnkType_10b44f40_Item
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

class UnkType_10b44f40
{
public:
    bool Unk_10b75610();
    bool Unk_10b44f40();

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[0x60 - 0x3d];
    UnkType_10b44f40_Item* unk_60;
};

// UnkType_10b44f40::Unk_10b44f40
bool UnkType_10b44f40::Unk_10b44f40()
{
    if ( unk_3c )
    {
        Unk_10b75610();
        unk_60->VirtualSlot14();
    }
    return true;
}
