// campaign_leaf_265f80.cpp -- a member function at VA 0x10b65f80: when the byte at 0x18 is already
// set it returns true; otherwise it passes the narrow string "options_PC" to virtual slot 13 of the
// object the pointer at 0x00 refers to and, when that returns an object, passes it to virtual slot
// 13 of the objects the pointers at 0x04 to 0x14 refer to, keeping in the byte at 0x18 whether all
// of them succeed. It returns that byte, or false when no object was returned. The class, method
// and member names are invented; the offsets, string and slots are the binary's.

class UnkType_10b65f80_Found;

class UnkType_10b65f80_Source
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
    virtual UnkType_10b65f80_Found* VirtualSlot13(const char* Name);
};

class UnkType_10b65f80_Target
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
    virtual bool VirtualSlot13(UnkType_10b65f80_Found* Found);
};

class UnkType_10b65f80
{
public:
    bool Unk_10b65f80();

private:
    UnkType_10b65f80_Source* unk_00;
    UnkType_10b65f80_Target* unk_04;
    UnkType_10b65f80_Target* unk_08;
    UnkType_10b65f80_Target* unk_0c;
    UnkType_10b65f80_Target* unk_10;
    UnkType_10b65f80_Target* unk_14;
    bool unk_18;
};

// UnkType_10b65f80::Unk_10b65f80
bool UnkType_10b65f80::Unk_10b65f80()
{
    if ( unk_18 )
    {
        return true;
    }
    UnkType_10b65f80_Found* Found = unk_00->VirtualSlot13("options_PC");
    if ( !Found )
    {
        return false;
    }
    unk_18 = unk_04->VirtualSlot13(Found);
    unk_18 &= unk_08->VirtualSlot13(Found);
    unk_18 &= unk_0c->VirtualSlot13(Found);
    unk_18 &= unk_10->VirtualSlot13(Found);
    unk_18 &= unk_14->VirtualSlot13(Found);
    return unk_18;
}
