// campaign_leaf_6154c0.cpp -- thiscall method at VA 0x10f154c0: calls the method at VA 0x10f15ad0
// with the addresses of two locals; when that returns true, passes them to virtual slot 4 (vtable
// offset 0x10) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f154c0_Second
{
    unsigned char unk_00[0x404];
};

class UnkType_10f154c0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int First, UnkType_10f154c0_Second* Second);
};

class UnkType_10f154c0
{
public:
    bool Unk_10f154c0();
    bool Unk_10f15ad0(int* First, UnkType_10f154c0_Second* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f154c0_Target* unk_10;
};

// UnkType_10f154c0::Unk_10f154c0
bool UnkType_10f154c0::Unk_10f154c0()
{
    int First;
    UnkType_10f154c0_Second Second;

    if ( Unk_10f15ad0(&First, &Second) )
    {
        unk_10->VirtualSlot4(First, &Second);
        return true;
    }
    return false;
}
