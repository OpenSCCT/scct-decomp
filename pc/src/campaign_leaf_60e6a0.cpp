// campaign_leaf_60e6a0.cpp -- thiscall method at VA 0x10f0e6a0: calls the method at VA 0x10f0b740
// with the addresses of five locals; when that returns true, passes them to virtual slot 33 (vtable
// offset 0x84) of the object at 0x14 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f0e6a0_Fifth
{
    unsigned char unk_00[0x10];
};

class UnkType_10f0e6a0_Target
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
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33(int First, int Second, int Third, int Fourth,
                               UnkType_10f0e6a0_Fifth* Fifth);
};

class UnkType_10f0e6a0
{
public:
    bool Unk_10f0e6a0();
    bool Unk_10f0b740(int* First, int* Second, int* Third, int* Fourth,
                      UnkType_10f0e6a0_Fifth* Fifth);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0e6a0_Target* unk_14;
};

// UnkType_10f0e6a0::Unk_10f0e6a0
bool UnkType_10f0e6a0::Unk_10f0e6a0()
{
    int First;
    int Second;
    int Third;
    int Fourth;
    UnkType_10f0e6a0_Fifth Fifth;

    if ( Unk_10f0b740(&First, &Second, &Third, &Fourth, &Fifth) )
    {
        unk_14->VirtualSlot33(First, Second, Third, Fourth, &Fifth);
        return true;
    }
    return false;
}
