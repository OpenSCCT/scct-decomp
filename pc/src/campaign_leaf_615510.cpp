// campaign_leaf_615510.cpp -- thiscall method at VA 0x10f15510: calls the method at VA 0x10f15b50
// with the addresses of two locals; when that returns true, passes them to virtual slot 6 (vtable
// offset 0x18) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f15510_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6(int First, int Second);
};

class UnkType_10f15510
{
public:
    bool Unk_10f15510();
    bool Unk_10f15b50(int* First, int* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f15510_Target* unk_10;
};

// UnkType_10f15510::Unk_10f15510
bool UnkType_10f15510::Unk_10f15510()
{
    int First;
    int Second;

    if ( Unk_10f15b50(&First, &Second) )
    {
        unk_10->VirtualSlot6(First, Second);
        return true;
    }
    return false;
}
