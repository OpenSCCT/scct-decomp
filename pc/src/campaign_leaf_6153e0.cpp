// campaign_leaf_6153e0.cpp -- thiscall method at VA 0x10f153e0: calls the method at VA 0x10f15850 with
// the addresses of 4 locals (a value, a 132-byte value, a value, a value); when that returns true, passes them to virtual
// slot 1 (vtable offset 0x4) of the object at 0x10 and returns true, otherwise
// returns false. The class, method and member names are invented; the offsets and
// addresses are the binary's.

struct UnkType_10f153e0_Value1
{
    unsigned char unk_00[0x84];
};

class UnkType_10f153e0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int First, UnkType_10f153e0_Value1* Second, int Third, int Fourth);
};

class UnkType_10f153e0
{
public:
    bool Unk_10f153e0();
    bool Unk_10f15850(int* First, UnkType_10f153e0_Value1* Second, int* Third, int* Fourth);

private:
    unsigned char unk_00[0x10];
    UnkType_10f153e0_Target* unk_10;
};

// UnkType_10f153e0::Unk_10f153e0
bool UnkType_10f153e0::Unk_10f153e0()
{
    int First;
    UnkType_10f153e0_Value1 Second;
    int Third;
    int Fourth;

    if ( Unk_10f15850(&First, &Second, &Third, &Fourth) )
    {
        unk_10->VirtualSlot1(First, &Second, Third, Fourth);
        return true;
    }
    return false;
}
