// campaign_leaf_60de90.cpp -- thiscall method at VA 0x10f0de90: calls the method at VA 0x10f09f20
// with the addresses of three locals; when that returns true, passes them to virtual slot 18
// (vtable offset 0x48) of the object at 0x14 and returns true, otherwise returns false. The class,
// method and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f0de90_Third
{
    unsigned char unk_00[0x404];
};

class UnkType_10f0de90_Target
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
    virtual void VirtualSlot18(int First, int Second, UnkType_10f0de90_Third* Third);
};

class UnkType_10f0de90
{
public:
    bool Unk_10f0de90();
    bool Unk_10f09f20(int* First, int* Second, UnkType_10f0de90_Third* Third);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0de90_Target* unk_14;
};

// UnkType_10f0de90::Unk_10f0de90
bool UnkType_10f0de90::Unk_10f0de90()
{
    int First;
    int Second;
    UnkType_10f0de90_Third Third;

    if ( Unk_10f09f20(&First, &Second, &Third) )
    {
        unk_14->VirtualSlot18(First, Second, &Third);
        return true;
    }
    return false;
}
