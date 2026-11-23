// campaign_leaf_615480.cpp -- thiscall method at VA 0x10f15480: calls the method at VA 0x10f15aa0
// with the addresses of two locals; when that returns true, passes them to virtual slot 3 (vtable
// offset 0xc) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f15480_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(int First, int Second);
};

class UnkType_10f15480
{
public:
    bool Unk_10f15480();
    bool Unk_10f15aa0(int* First, int* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f15480_Target* unk_10;
};

// UnkType_10f15480::Unk_10f15480
bool UnkType_10f15480::Unk_10f15480()
{
    int First;
    int Second;

    if ( Unk_10f15aa0(&First, &Second) )
    {
        unk_10->VirtualSlot3(First, Second);
        return true;
    }
    return false;
}
