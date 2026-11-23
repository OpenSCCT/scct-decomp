// campaign_leaf_60d550.cpp -- thiscall method at VA 0x10f0d550: calls the method at VA 0x10f09560 with
// the addresses of 5 locals (a value, a value, a 36-byte value, a value, a value); when that returns true, passes them to virtual
// slot 3 (vtable offset 0xc) of the object at 0x14 and returns true, otherwise
// returns false. The class, method and member names are invented; the offsets and
// addresses are the binary's.

struct UnkType_10f0d550_Value2
{
    unsigned char unk_00[0x24];
};

class UnkType_10f0d550_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(int First, int Second, UnkType_10f0d550_Value2* Third, int Fourth, int Fifth);
};

class UnkType_10f0d550
{
public:
    bool Unk_10f0d550();
    bool Unk_10f09560(int* First, int* Second, UnkType_10f0d550_Value2* Third, int* Fourth, int* Fifth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0d550_Target* unk_14;
};

// UnkType_10f0d550::Unk_10f0d550
bool UnkType_10f0d550::Unk_10f0d550()
{
    int First;
    int Second;
    UnkType_10f0d550_Value2 Third;
    int Fourth;
    int Fifth;

    if ( Unk_10f09560(&First, &Second, &Third, &Fourth, &Fifth) )
    {
        unk_14->VirtualSlot3(First, Second, &Third, Fourth, Fifth);
        return true;
    }
    return false;
}
