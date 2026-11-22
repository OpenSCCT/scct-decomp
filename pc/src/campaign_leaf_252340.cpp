// campaign_leaf_252340.cpp -- a member function at VA 0x10b52340: when the member at VA 0x1095b860
// returns non-zero it calls virtual slot 15 of the object the pointer at 0x38 refers to with 1; it
// returns false. It does not read its argument. The class, method and member names are invented;
// the offsets, addresses and slot are the binary's.

class UnkType_10b52340_Item
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
    virtual void VirtualSlot15(int Value);
};

class UnkType_10b52340
{
public:
    int Unk_1095b860();
    bool Unk_10b52340(int Unused);

private:
    unsigned char unk_00[0x38];
    UnkType_10b52340_Item* unk_38;
};

// UnkType_10b52340::Unk_10b52340
bool UnkType_10b52340::Unk_10b52340(int Unused)
{
    if ( Unk_1095b860() )
    {
        unk_38->VirtualSlot15(1);
    }
    return false;
}
