// campaign_leaf_08d740.cpp -- constructor at VA 0x1098d740 of a class whose vtable is at VA
// 0x110c1ff8: runs the inline constructor of its base class, which runs the base constructor at
// VA 0x10cd7930 and clears the values at 0x28-0x34; then clears the array members at 0x38, 0x44,
// 0x50 and 0x5c. The class and member names are invented; the offsets and the addresses are the
// binary's.

class UnkType_1098d740_Base
{
public:
    UnkType_1098d740_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x24];
};

class UnkType_10cd7930_08d740 : public UnkType_1098d740_Base
{
public:
    UnkType_10cd7930_08d740()
    : unk_28(0)
    , unk_2c(0)
    , unk_30(0)
    , unk_34(0)
    {
    }

    virtual void VirtualSlot0();

private:
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
};

class UnkType_10cd7930_08d740_Array
{
public:
    UnkType_10cd7930_08d740_Array()
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

class UnkType_1098d740 : public UnkType_10cd7930_08d740
{
public:
    UnkType_1098d740();
    virtual void VirtualSlot0();

private:
    UnkType_10cd7930_08d740_Array unk_38;
    UnkType_10cd7930_08d740_Array unk_44;
    UnkType_10cd7930_08d740_Array unk_50;
    UnkType_10cd7930_08d740_Array unk_5c;
};

// UnkType_1098d740::UnkType_1098d740
UnkType_1098d740::UnkType_1098d740()
{
}
