// campaign_leaf_6139d0.cpp -- thiscall method at VA 0x10f139d0: calls the method at VA 0x10f13290
// with the addresses of five locals; when that returns true, passes them to virtual slot 15 (vtable
// offset 0x3c) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f139d0_Third
{
    unsigned char unk_00[0x10];
};

struct UnkType_10f139d0_Fourth
{
    unsigned char unk_00[0x24];
};

struct UnkType_10f139d0_Fifth
{
    unsigned char unk_00[0x400];
};

class UnkType_10f139d0_Target
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
    virtual void VirtualSlot15(int First, int Second, UnkType_10f139d0_Third* Third,
                               UnkType_10f139d0_Fourth* Fourth, UnkType_10f139d0_Fifth* Fifth);
};

class UnkType_10f139d0
{
public:
    bool Unk_10f139d0();
    bool Unk_10f13290(int* First, int* Second, UnkType_10f139d0_Third* Third,
                      UnkType_10f139d0_Fourth* Fourth, UnkType_10f139d0_Fifth* Fifth);

private:
    unsigned char unk_00[0x10];
    UnkType_10f139d0_Target* unk_10;
};

// UnkType_10f139d0::Unk_10f139d0
bool UnkType_10f139d0::Unk_10f139d0()
{
    int First;
    int Second;
    UnkType_10f139d0_Third Third;
    UnkType_10f139d0_Fourth Fourth;
    UnkType_10f139d0_Fifth Fifth;

    if ( Unk_10f13290(&First, &Second, &Third, &Fourth, &Fifth) )
    {
        unk_10->VirtualSlot15(First, Second, &Third, &Fourth, &Fifth);
        return true;
    }
    return false;
}
