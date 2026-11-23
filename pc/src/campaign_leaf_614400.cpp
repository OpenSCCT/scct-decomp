// campaign_leaf_614400.cpp -- thiscall method at VA 0x10f14400: calls the method at VA 0x10f14310
// with the address of one local; when that returns true, passes it to virtual slot 6 (vtable offset
// 0x18) of the object at 0x10 and returns true, otherwise returns false. The class, method and
// member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f14400_First
{
    unsigned char unk_00[0x10];
};

class UnkType_10f14400_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6(UnkType_10f14400_First* First);
};

class UnkType_10f14400
{
public:
    bool Unk_10f14400();
    bool Unk_10f14310(UnkType_10f14400_First* First);

private:
    unsigned char unk_00[0x10];
    UnkType_10f14400_Target* unk_10;
};

// UnkType_10f14400::Unk_10f14400
bool UnkType_10f14400::Unk_10f14400()
{
    UnkType_10f14400_First First;

    if ( Unk_10f14310(&First) )
    {
        unk_10->VirtualSlot6(&First);
        return true;
    }
    return false;
}
