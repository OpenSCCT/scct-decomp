// campaign_leaf_07a610.cpp -- constructor at VA 0x1097a610 of a class whose vtable is at VA
// 0x110c0f50: runs the base constructor at VA 0x10cd7930, clears the array member at 0x28 and
// clears bit 19 of the base's flags at 0x1c. The class and member names are invented; the
// offsets, the constant and the addresses are the binary's.

class UnkType_1097a610_Base
{
public:
    UnkType_1097a610_Base();
    virtual void VirtualSlot0();

protected:
    unsigned char unk_04[0x18];
    unsigned int unk_1c;
    unsigned char unk_20[0x08];
};

class UnkType_10cd7930_07a610
{
public:
    UnkType_10cd7930_07a610()
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

class UnkType_1097a610 : public UnkType_1097a610_Base
{
public:
    UnkType_1097a610();
    virtual void VirtualSlot0();

private:
    UnkType_10cd7930_07a610 unk_28;
};

// UnkType_1097a610::UnkType_1097a610
UnkType_1097a610::UnkType_1097a610()
{
    unk_1c &= ~0x80000;
}
