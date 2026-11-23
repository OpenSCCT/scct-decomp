// campaign_leaf_60de30.cpp -- thiscall method at VA 0x10f0de30: calls the method at VA 0x10f09d20 with
// the addresses of 5 locals (a value, a value, a 16-byte value, a value, a value); when that returns true, passes them to virtual
// slot 19 (vtable offset 0x4c) of the object at 0x14 and returns true, otherwise
// returns false. The class, method and member names are invented; the offsets and
// addresses are the binary's.

struct UnkType_10f0de30_Value2
{
    unsigned char unk_00[0x10];
};

class UnkType_10f0de30_Target
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
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19(int First, int Second, UnkType_10f0de30_Value2* Third, int Fourth, int Fifth);
};

class UnkType_10f0de30
{
public:
    bool Unk_10f0de30();
    bool Unk_10f09d20(int* First, int* Second, UnkType_10f0de30_Value2* Third, int* Fourth, int* Fifth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0de30_Target* unk_14;
};

// UnkType_10f0de30::Unk_10f0de30
bool UnkType_10f0de30::Unk_10f0de30()
{
    int First;
    int Second;
    UnkType_10f0de30_Value2 Third;
    int Fourth;
    int Fifth;

    if ( Unk_10f09d20(&First, &Second, &Third, &Fourth, &Fifth) )
    {
        unk_14->VirtualSlot19(First, Second, &Third, Fourth, Fifth);
        return true;
    }
    return false;
}
