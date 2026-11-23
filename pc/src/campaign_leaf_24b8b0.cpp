// campaign_leaf_24b8b0.cpp -- a member function at VA 0x10b4b8b0: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it sets the
// byte at 0xb6 of the object the pointer at 0x48 refers to and passes the argument to virtual slot
// 13 of the objects the pointers at 0x4c and 0x50 refer to; when both accept it, it sets the byte
// at 0x3c and returns true, otherwise false. The class, method and member names are invented; the
// offsets, addresses and slot are the binary's.

class UnkType_10b4b8b0_Flags
{
public:
    unsigned char unk_00[0xb6];
    bool unk_b6;
};

class UnkType_10b4b8b0_Item
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
    virtual bool VirtualSlot13(int Value);
};

class UnkType_10b4b8b0
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b4b8b0(int Value);

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[0x48 - 0x3d];
    UnkType_10b4b8b0_Flags* unk_48;
    UnkType_10b4b8b0_Item* unk_4c;
    UnkType_10b4b8b0_Item* unk_50;
};

// UnkType_10b4b8b0::Unk_10b4b8b0
bool UnkType_10b4b8b0::Unk_10b4b8b0(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    if ( !Unk_10b65b30(Value) )
    {
        return false;
    }
    unk_48->unk_b6 = true;
    if ( !unk_4c->VirtualSlot13(Value) )
    {
        return false;
    }
    if ( !unk_50->VirtualSlot13(Value) )
    {
        return false;
    }
    unk_3c = true;
    return true;
}
