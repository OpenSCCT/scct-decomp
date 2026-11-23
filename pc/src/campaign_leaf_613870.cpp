// campaign_leaf_613870.cpp -- thiscall method at VA 0x10f13870: calls the method at VA 0x10f12ee0
// with the addresses of two locals; when that returns true, passes them to virtual slot 11 (vtable
// offset 0x2c) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f13870_Target
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

class UnkType_10f13870
{
public:
    bool Unk_10f13870();
    bool Unk_10f12ee0(int* First, int* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f13870_Target* unk_10;
};

// UnkType_10f13870::Unk_10f13870
bool UnkType_10f13870::Unk_10f13870()
{
    int First;
    int Second;

    if ( Unk_10f12ee0(&First, &Second) )
    {
        unk_10->VirtualSlot11(First, Second);
        return true;
    }
    return false;
}
