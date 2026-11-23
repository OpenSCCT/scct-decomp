// campaign_leaf_6143d0.cpp -- thiscall method at VA 0x10f143d0: calls the method at VA 0x10f142a0
// with the address of one local; when that returns true, passes it to virtual slot 5 (vtable offset
// 0x14) of the object at 0x10 and returns true, otherwise returns false. The class, method and
// member names are invented; the offsets and addresses are the binary's.

class UnkType_10f143d0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int First);
};

class UnkType_10f143d0
{
public:
    bool Unk_10f143d0();
    bool Unk_10f142a0(int* First);

private:
    unsigned char unk_00[0x10];
    UnkType_10f143d0_Target* unk_10;
};

// UnkType_10f143d0::Unk_10f143d0
bool UnkType_10f143d0::Unk_10f143d0()
{
    int First;

    if ( Unk_10f142a0(&First) )
    {
        unk_10->VirtualSlot5(First);
        return true;
    }
    return false;
}
