// campaign_leaf_07dfc0.cpp -- constructor at VA 0x1097dfc0 of a class whose vtable is at VA
// 0x110c16b0: runs the base constructor at VA 0x10cd7930; clears the array member at 0x2c; and
// constructs the member at 0x38, an array with a hash table, cleared with the table size at 0x10
// of it set to 8, by passing it to the method at VA 0x1097d240. The class, member and method names
// are invented; the offsets, the constant and the addresses are the binary's.

class UnkType_1097d240_07dfc0_Array
{
public:
    UnkType_1097d240_07dfc0_Array()
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

class UnkType_1097d240_07dfc0 : public UnkType_1097d240_07dfc0_Array
{
public:
    UnkType_1097d240_07dfc0()
    : unk_0c(0)
    , unk_10(8)
    {
        Unk_1097d240();
    }

    void Unk_1097d240();

private:
    int* unk_0c;
    int unk_10;
};

class UnkType_1097dfc0_Base
{
public:
    UnkType_1097dfc0_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x28];
};

class UnkType_1097dfc0 : public UnkType_1097dfc0_Base
{
public:
    UnkType_1097dfc0();
    virtual void VirtualSlot0();

private:
    UnkType_1097d240_07dfc0_Array unk_2c;
    UnkType_1097d240_07dfc0 unk_38;
};

// UnkType_1097dfc0::UnkType_1097dfc0
UnkType_1097dfc0::UnkType_1097dfc0()
{
}
