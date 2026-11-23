// campaign_leaf_253c90.cpp -- a member function at VA 0x10b53c90: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it passes
// the argument to virtual slot 13 of the objects the pointers at 0x44, 0x48 and 0x4c refer to and
// sets the byte at 0xb6 of the object the pointer at 0x40 refers to. It stores and returns whether
// that happened. The class, method and member names are invented; the offsets, addresses and slot
// are the binary's.

class UnkType_10b53c90_Owner
{
public:
    unsigned char unk_00[0xb6];
    bool unk_b6;
};

class UnkType_10b53c90_Item
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
    virtual void VirtualSlot13(int Value);
};

class UnkType_10b53c90
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b53c90(int Value);

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[3];
    UnkType_10b53c90_Owner* unk_40;
    UnkType_10b53c90_Item* unk_44;
    UnkType_10b53c90_Item* unk_48;
    UnkType_10b53c90_Item* unk_4c;
};

// UnkType_10b53c90::Unk_10b53c90
bool UnkType_10b53c90::Unk_10b53c90(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b65b30(Value) )
    {
        unk_44->VirtualSlot13(Value);
        unk_48->VirtualSlot13(Value);
        unk_4c->VirtualSlot13(Value);
        Result = true;
        unk_40->unk_b6 = true;
    }
    unk_3c = Result;
    return Result;
}
