// campaign_leaf_074020.cpp -- constructor at VA 0x10974020 of a class whose vtable is at VA
// 0x110c0c30: runs the base constructor at VA 0x109732b0 and clears the array members at 0x54 and
// 0x60. The class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_10974020_Base
{
public:
    UnkType_10974020_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x50];
};

class UnkType_109732b0_074020
{
public:
    UnkType_109732b0_074020()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10974020 : public UnkType_10974020_Base
{
public:
    UnkType_10974020();
    virtual void VirtualSlot0();

private:
    UnkType_109732b0_074020 unk_54;
    UnkType_109732b0_074020 unk_60;
};

// UnkType_10974020::UnkType_10974020
UnkType_10974020::UnkType_10974020()
{
}
