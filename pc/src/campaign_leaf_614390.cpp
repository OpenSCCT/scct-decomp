// campaign_leaf_614390.cpp -- thiscall method at VA 0x10f14390: calls the method at VA 0x10f14080
// with the addresses of two locals; when that returns true, passes them to virtual slot 4 (vtable
// offset 0x10) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f14390_Second
{
    unsigned char unk_00[0x10];
};

class UnkType_10f14390_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int First, UnkType_10f14390_Second* Second);
};

class UnkType_10f14390
{
public:
    bool Unk_10f14390();
    bool Unk_10f14080(int* First, UnkType_10f14390_Second* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f14390_Target* unk_10;
};

// UnkType_10f14390::Unk_10f14390
bool UnkType_10f14390::Unk_10f14390()
{
    int First;
    UnkType_10f14390_Second Second;

    if ( Unk_10f14080(&First, &Second) )
    {
        unk_10->VirtualSlot4(First, &Second);
        return true;
    }
    return false;
}
