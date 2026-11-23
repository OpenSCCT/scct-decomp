// campaign_leaf_614350.cpp -- thiscall method at VA 0x10f14350: calls the method at VA 0x10f13e50
// with the addresses of two locals; when that returns true, passes them to virtual slot 3 (vtable
// offset 0xc) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f14350_Second
{
    unsigned char unk_00[0x10];
};

class UnkType_10f14350_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(int First, UnkType_10f14350_Second* Second);
};

class UnkType_10f14350
{
public:
    bool Unk_10f14350();
    bool Unk_10f13e50(int* First, UnkType_10f14350_Second* Second);

private:
    unsigned char unk_00[0x10];
    UnkType_10f14350_Target* unk_10;
};

// UnkType_10f14350::Unk_10f14350
bool UnkType_10f14350::Unk_10f14350()
{
    int First;
    UnkType_10f14350_Second Second;

    if ( Unk_10f13e50(&First, &Second) )
    {
        unk_10->VirtualSlot3(First, &Second);
        return true;
    }
    return false;
}
