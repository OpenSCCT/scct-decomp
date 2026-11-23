// campaign_leaf_256e00.cpp -- a member function at VA 0x10b56e00: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it calls
// the member at VA 0x10d2a530 of the object the pointer at 0x44 refers to with 1 and 1, sets that
// object's byte at 0xb5 and passes the argument to virtual slot 13 of the object the pointer at
// 0x40 refers to. It stores and returns whether that happened. The class, method and member names
// are invented; the offsets, addresses and slot are the binary's.

class UnkType_10b56e00_Target
{
public:
    void Unk_10d2a530(int First, int Second);
    void Unk_10d2a830(int First, int Second, int Third);

    unsigned char unk_00[0xb5];
    bool unk_b5;
};

class UnkType_10b56e00_Item
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

class UnkType_10b56e00
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b56e00(int Value);

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[3];
    UnkType_10b56e00_Item* unk_40;
    UnkType_10b56e00_Target* unk_44;
};

// UnkType_10b56e00::Unk_10b56e00
bool UnkType_10b56e00::Unk_10b56e00(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b65b30(Value) )
    {
        Result = true;
        unk_44->Unk_10d2a530(1, 1);
        unk_44->unk_b5 = true;
        unk_40->VirtualSlot13(Value);
    }
    unk_3c = Result;
    return Result;
}
