// campaign_leaf_252300.cpp -- a member function at VA 0x10b52300: when the byte at 0x3c is set it
// calls the member at VA 0x10b65820, clears the int at 0x44 and calls virtual slot 14 of the object
// the pointer at 0x40 refers to; it returns true. The class, method and member names are invented;
// the offsets, addresses and slot are the binary's.

class UnkType_10b52300_Item
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

class UnkType_10b52300
{
public:
    void Unk_10b65820();
    bool Unk_10b52300();

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[3];
    UnkType_10b52300_Item* unk_40;
    int unk_44;
};

// UnkType_10b52300::Unk_10b52300
bool UnkType_10b52300::Unk_10b52300()
{
    if ( unk_3c )
    {
        Unk_10b65820();
        unk_44 = 0;
        unk_40->VirtualSlot14();
    }
    return true;
}
