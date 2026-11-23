// campaign_leaf_615550.cpp -- thiscall method at VA 0x10f15550: calls the method at VA 0x10f15b80
// with the addresses of two locals; when that returns true, passes them to virtual slot 7 (vtable
// offset 0x1c) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f15550_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7(int First, int Second);
};

class UnkType_10f15550
{
public:
    bool Unk_10f15550();
    bool Unk_10f15b80(int* First, int* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f15550_Target* unk_10;
};

// UnkType_10f15550::Unk_10f15550
bool UnkType_10f15550::Unk_10f15550()
{
    int First;
    int Second;

    if ( Unk_10f15b80(&First, &Second) )
    {
        unk_10->VirtualSlot7(First, Second);
        return true;
    }
    return false;
}
