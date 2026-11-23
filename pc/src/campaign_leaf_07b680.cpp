// campaign_leaf_07b680.cpp -- constructor at VA 0x1097b680 of a class whose vtable is at VA
// 0x110c1204: clears the array member at 0x04; constructs the member at 0x10, an array with a hash
// table, cleared with the table size at 0x10 of it set to 8, by passing it to the method at VA
// 0x10976230; clears the value at 0x24, sets the one at 0x28 to 7 and clears the array member at
// 0x2c. The class, member and method names are invented; the offsets, the constants and the
// addresses are the binary's.

class UnkType_10976230_07b680_Array
{
public:
    UnkType_10976230_07b680_Array()
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

class UnkType_10976230_07b680 : public UnkType_10976230_07b680_Array
{
public:
    UnkType_10976230_07b680()
    : unk_0c(0)
    , unk_10(8)
    {
        Unk_10976230();
    }

    void Unk_10976230();

private:
    int* unk_0c;
    int unk_10;
};

class UnkType_1097b680
{
public:
    UnkType_1097b680();
    virtual void VirtualSlot0();

private:
    UnkType_10976230_07b680_Array unk_04;
    UnkType_10976230_07b680 unk_10;
    int unk_24;
    int unk_28;
    UnkType_10976230_07b680_Array unk_2c;
};

// UnkType_1097b680::UnkType_1097b680
UnkType_1097b680::UnkType_1097b680()
: unk_24(0)
, unk_28(7)
{
}
