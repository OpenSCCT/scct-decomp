// campaign_leaf_25d830.cpp -- a member function at VA 0x10b5d830: when the byte at 0x40 is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it passes
// the argument to virtual slot 13 of the object the pointer at 0x50 refers to, calls the member at
// VA 0x10d2a530 of the object the pointer at 0x44 refers to with 1 and 1 and sets that object's
// byte at 0xb5. It stores and returns whether that happened. The class, method and member names are
// invented; the offsets, addresses and slot are the binary's.

class UnkType_10b5d830_Target
{
public:
    void Unk_10d2a530(int First, int Second);
    void Unk_10d2a830(int First, int Second, int Third);

    unsigned char unk_00[0xb5];
    bool unk_b5;
};

class UnkType_10b5d830_Item
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

class UnkType_10b5d830
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b5d830(int Value);

private:
    unsigned char unk_00[0x40];
    bool unk_40;
    unsigned char unk_41[3];
    UnkType_10b5d830_Target* unk_44;
    unsigned char unk_48[8];
    UnkType_10b5d830_Item* unk_50;
};

// UnkType_10b5d830::Unk_10b5d830
bool UnkType_10b5d830::Unk_10b5d830(int Value)
{
    if ( unk_40 )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b65b30(Value) )
    {
        unk_50->VirtualSlot13(Value);
        Result = true;
        unk_44->Unk_10d2a530(1, 1);
        unk_44->unk_b5 = true;
    }
    unk_40 = Result;
    return Result;
}
