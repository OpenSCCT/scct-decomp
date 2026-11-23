// campaign_leaf_613960.cpp -- thiscall method at VA 0x10f13960: calls the method at VA 0x10f13070
// with the addresses of five locals; when that returns true, passes them to virtual slot 14 (vtable
// offset 0x38) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f13960_Third
{
    unsigned char unk_00[0x10];
};

struct UnkType_10f13960_Fifth
{
    unsigned char unk_00[0x84];
};

class UnkType_10f13960_Target
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
    virtual void VirtualSlot14(int First, int Second, UnkType_10f13960_Third* Third, int Fourth,
                               UnkType_10f13960_Fifth* Fifth);
};

class UnkType_10f13960
{
public:
    bool Unk_10f13960();
    bool Unk_10f13070(int* First, int* Second, UnkType_10f13960_Third* Third, int* Fourth,
                      UnkType_10f13960_Fifth* Fifth);

private:
    unsigned char unk_00[0x10];
    UnkType_10f13960_Target* unk_10;
};

// UnkType_10f13960::Unk_10f13960
bool UnkType_10f13960::Unk_10f13960()
{
    int First;
    int Second;
    UnkType_10f13960_Third Third;
    int Fourth;
    UnkType_10f13960_Fifth Fifth;

    if ( Unk_10f13070(&First, &Second, &Third, &Fourth, &Fifth) )
    {
        unk_10->VirtualSlot14(First, Second, &Third, Fourth, &Fifth);
        return true;
    }
    return false;
}
