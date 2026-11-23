// campaign_leaf_0690a0.cpp -- constructor at VA 0x109690a0 of a class whose vtable is at VA
// 0x110bef68: runs the inline constructor of its base class, which runs the base constructor at VA
// 0x10cd7930 and sets the values at 0x2c, 0x30 and 0x34 to 12, 0 and 1; then clears the array
// member at 0x38. The class and member names are invented; the offsets, the constants and the
// addresses are the binary's.

class UnkType_109690a0_Base
{
public:
    UnkType_109690a0_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x28];
};

class UnkType_10cd7930_0690a0 : public UnkType_109690a0_Base
{
public:
    UnkType_10cd7930_0690a0()
    : unk_2c(12)
    , unk_30(0)
    , unk_34(1)
    {
    }

    virtual void VirtualSlot0();

private:
    int unk_2c;
    int unk_30;
    int unk_34;
};

class UnkType_10cd7930_0690a0_Array
{
public:
    UnkType_10cd7930_0690a0_Array()
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

class UnkType_109690a0 : public UnkType_10cd7930_0690a0
{
public:
    UnkType_109690a0();
    virtual void VirtualSlot0();

private:
    UnkType_10cd7930_0690a0_Array unk_38;
};

// UnkType_109690a0::UnkType_109690a0
UnkType_109690a0::UnkType_109690a0()
{
}
