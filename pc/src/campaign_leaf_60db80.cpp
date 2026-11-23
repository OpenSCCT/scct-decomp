// campaign_leaf_60db80.cpp -- thiscall method at VA 0x10f0db80: calls the method at VA 0x10f09730
// with the addresses of four locals; when that returns true, passes them to virtual slot 14 (vtable
// offset 0x38) of the object at 0x14 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f0db80_Target
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
    virtual void VirtualSlot14(int First, int Second, int Third, int Fourth);
};

class UnkType_10f0db80
{
public:
    bool Unk_10f0db80();
    bool Unk_10f09730(int* First, int* Second, int* Third, int* Fourth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0db80_Target* unk_14;
};

// UnkType_10f0db80::Unk_10f0db80
bool UnkType_10f0db80::Unk_10f0db80()
{
    int First;
    int Second;
    int Third;
    int Fourth;

    if ( Unk_10f09730(&First, &Second, &Third, &Fourth) )
    {
        unk_14->VirtualSlot14(First, Second, Third, Fourth);
        return true;
    }
    return false;
}
