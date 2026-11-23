// campaign_leaf_6138b0.cpp -- thiscall method at VA 0x10f138b0: calls the method at VA 0x10f12f10
// with the addresses of two locals; when that returns true, passes them to virtual slot 12 (vtable
// offset 0x30) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f138b0_Target
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
    virtual void VirtualSlot12(int First, int Second);
};

class UnkType_10f138b0
{
public:
    bool Unk_10f138b0();
    bool Unk_10f12f10(int* First, int* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f138b0_Target* unk_10;
};

// UnkType_10f138b0::Unk_10f138b0
bool UnkType_10f138b0::Unk_10f138b0()
{
    int First;
    int Second;

    if ( Unk_10f12f10(&First, &Second) )
    {
        unk_10->VirtualSlot12(First, Second);
        return true;
    }
    return false;
}
