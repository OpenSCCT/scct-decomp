// campaign_leaf_6138f0.cpp -- thiscall method at VA 0x10f138f0: calls the method at VA 0x10f12f40
// with the addresses of six locals; when that returns true, passes them to virtual slot 13 (vtable
// offset 0x34) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f138f0_First
{
    unsigned char unk_00[0x10];
};

struct UnkType_10f138f0_Third
{
    unsigned char unk_00[0x24];
};

struct UnkType_10f138f0_Sixth
{
    unsigned char unk_00[0x84];
};

class UnkType_10f138f0_Target
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
    virtual void VirtualSlot13(UnkType_10f138f0_First* First, int Second,
                               UnkType_10f138f0_Third* Third, int Fourth, int Fifth,
                               UnkType_10f138f0_Sixth* Sixth);
};

class UnkType_10f138f0
{
public:
    bool Unk_10f138f0();
    bool Unk_10f12f40(UnkType_10f138f0_First* First, int* Second, UnkType_10f138f0_Third* Third,
                      int* Fourth, int* Fifth, UnkType_10f138f0_Sixth* Sixth);

private:
    unsigned char unk_00[0x10];
    UnkType_10f138f0_Target* unk_10;
};

// UnkType_10f138f0::Unk_10f138f0
bool UnkType_10f138f0::Unk_10f138f0()
{
    UnkType_10f138f0_First First;
    int Second;
    UnkType_10f138f0_Third Third;
    int Fourth;
    int Fifth;
    UnkType_10f138f0_Sixth Sixth;

    if ( Unk_10f12f40(&First, &Second, &Third, &Fourth, &Fifth, &Sixth) )
    {
        unk_10->VirtualSlot13(&First, Second, &Third, Fourth, Fifth, &Sixth);
        return true;
    }
    return false;
}
