// campaign_leaf_60e150.cpp -- thiscall method at VA 0x10f0e150: calls the method at VA 0x10f0a650
// with the addresses of three locals; when that returns true, passes them to virtual slot 24
// (vtable offset 0x60) of the object at 0x14 and returns true, otherwise returns false. Before the
// call Third is set to zero. The class, method and member names are invented; the offsets and
// addresses are the binary's.

class UnkType_10f0e150_Target
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
    virtual void VirtualSlot24(int First, int Second, int Third);
};

class UnkType_10f0e150
{
public:
    bool Unk_10f0e150();
    bool Unk_10f0a650(int* First, int* Second, int* Third);

private:
    unsigned char unk_00[0x14];
    UnkType_10f0e150_Target* unk_14;
};

// UnkType_10f0e150::Unk_10f0e150
bool UnkType_10f0e150::Unk_10f0e150()
{
    int First;
    int Second;
    int Third = 0;

    if ( Unk_10f0a650(&First, &Second, &Third) )
    {
        unk_14->VirtualSlot24(First, Second, Third);
        return true;
    }
    return false;
}
