// campaign_leaf_559bc0.cpp -- thiscall method at VA 0x10e59bc0: when the seventh virtual method of
// the object at 0x3c returns 6, returns the result of the method at VA 0x10e68500 on that object;
// otherwise 0. The class and method names are invented.

class UnkType_10e59bc0_3c
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual int VirtualSlot6();

    int Unk_10e68500();
};

class UnkType_10e59bc0
{
public:
    int Unk_10e59bc0();

private:
    int unk_00[15];
    UnkType_10e59bc0_3c* unk_3c;
};

// UnkType_10e59bc0::Unk_10e59bc0
int UnkType_10e59bc0::Unk_10e59bc0()
{
    if ( unk_3c->VirtualSlot6() == 6 )
    {
        return unk_3c->Unk_10e68500();
    }
    return 0;
}
