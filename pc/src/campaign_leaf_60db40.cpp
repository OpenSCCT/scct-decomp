// campaign_leaf_60db40.cpp -- thiscall method at VA 0x10f0db40: calls the method at VA 0x10f091c0
// with the addresses of two locals; when that returns true, passes them to virtual slot 11 (vtable
// offset 0x2c) of the object at 0x14 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f0db40_Target
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
    virtual void VirtualSlot11(int First, int Second);
};

class UnkType_10f0db40
{
public:
    bool Unk_10f0db40();
    bool Unk_10f091c0(int* First, int* Second);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0db40_Target* unk_14;
};

// UnkType_10f0db40::Unk_10f0db40
bool UnkType_10f0db40::Unk_10f0db40()
{
    int First;
    int Second;

    if ( Unk_10f091c0(&First, &Second) )
    {
        unk_14->VirtualSlot11(First, Second);
        return true;
    }
    return false;
}
