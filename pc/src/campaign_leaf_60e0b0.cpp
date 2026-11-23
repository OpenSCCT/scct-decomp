// campaign_leaf_60e0b0.cpp -- thiscall method at VA 0x10f0e0b0: calls the method at VA 0x10f0a430
// with the addresses of four locals; when that returns true, passes them to virtual slot 22 (vtable
// offset 0x58) of the object at 0x14 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

class UnkType_10f0e0b0_Target
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
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22(int First, int Second, int Third, int Fourth);
};

class UnkType_10f0e0b0
{
public:
    bool Unk_10f0e0b0();
    bool Unk_10f0a430(int* First, int* Second, int* Third, int* Fourth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0e0b0_Target* unk_14;
};

// UnkType_10f0e0b0::Unk_10f0e0b0
bool UnkType_10f0e0b0::Unk_10f0e0b0()
{
    int First;
    int Second;
    int Third;
    int Fourth;

    if ( Unk_10f0a430(&First, &Second, &Third, &Fourth) )
    {
        unk_14->VirtualSlot22(First, Second, Third, Fourth);
        return true;
    }
    return false;
}
