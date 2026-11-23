// campaign_leaf_60d500.cpp -- thiscall method at VA 0x10f0d500: calls the method at VA 0x10f087a0
// with the addresses of three locals; when that returns true, passes them to virtual slot 10
// (vtable offset 0x28) of the object at 0x14 and returns true, otherwise returns false. The class,
// method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f0d500_Target
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
    virtual void VirtualSlot10(int First, int Second, int Third);
};

class UnkType_10f0d500
{
public:
    bool Unk_10f0d500();
    bool Unk_10f087a0(int* First, int* Second, int* Third);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0d500_Target* unk_14;
};

// UnkType_10f0d500::Unk_10f0d500
bool UnkType_10f0d500::Unk_10f0d500()
{
    int First;
    int Second;
    int Third;

    if ( Unk_10f087a0(&First, &Second, &Third) )
    {
        unk_14->VirtualSlot10(First, Second, Third);
        return true;
    }
    return false;
}
