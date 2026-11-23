// campaign_leaf_258870.cpp -- a member function at VA 0x10b58870: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it passes
// the result of virtual slot 13 of the object the pointer at 0x14 refers to, called with the narrow
// string "Save_Load_PC", to virtual slot 13 of each of the objects the pointers at 0x48, 0x4c and
// 0x50 refer to, passes the argument to virtual slot 13 of the object the pointer at 0x54 refers
// to and sets the byte at 0xb6 of the object the pointer at 0x44 refers to. It stores and returns
// whether that happened. The class, method and member names are invented; the offsets, string,
// addresses and slots are the binary's.

class UnkType_10b58870_Found;

class UnkType_10b58870_Source
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
    virtual UnkType_10b58870_Found* VirtualSlot13(const char* Name);
};

class UnkType_10b58870_Target
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
    virtual void VirtualSlot13(UnkType_10b58870_Found* Found);
};

class UnkType_10b58870_Item
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

class UnkType_10b58870_Flags
{
public:
    unsigned char unk_00[0xb6];
    bool unk_b6;
};

class UnkType_10b58870
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b58870(int Value);

private:
    unsigned char unk_00[0x14];
    UnkType_10b58870_Source* unk_14;
    unsigned char unk_18[0x3c - 0x18];
    bool unk_3c;
    unsigned char unk_3d[0x44 - 0x3d];
    UnkType_10b58870_Flags* unk_44;
    UnkType_10b58870_Target* unk_48;
    UnkType_10b58870_Target* unk_4c;
    UnkType_10b58870_Target* unk_50;
    UnkType_10b58870_Item* unk_54;
};

// UnkType_10b58870::Unk_10b58870
bool UnkType_10b58870::Unk_10b58870(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b65b30(Value) )
    {
        unk_48->VirtualSlot13(unk_14->VirtualSlot13("Save_Load_PC"));
        unk_4c->VirtualSlot13(unk_14->VirtualSlot13("Save_Load_PC"));
        unk_50->VirtualSlot13(unk_14->VirtualSlot13("Save_Load_PC"));
        unk_54->VirtualSlot13(Value);
        Result = true;
        unk_44->unk_b6 = true;
    }
    unk_3c = Result;
    return Result;
}
