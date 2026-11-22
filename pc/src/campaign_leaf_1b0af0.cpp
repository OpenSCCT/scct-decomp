// campaign_leaf_1b0af0.cpp -- constructor at VA 0x10ab0af0: runs the base class constructor at VA
// 0x1097b7f0, then constructs the 12-byte member at 0x64, whose inline constructor zeroes its three
// values. The same class's destructor is at VA 0x10ab0b10. The class names are invented; the
// offsets and the address are the binary's.

class UnkType_1090ba70
{
public:
    UnkType_1090ba70()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
    }

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097b7f0
{
public:
    UnkType_1097b7f0();

private:
    unsigned char unk_00[0x64];
};

class UnkType_10ab0af0 : public UnkType_1097b7f0
{
public:
    UnkType_10ab0af0();

private:
    UnkType_1090ba70 unk_64;
};

// UnkType_10ab0af0::UnkType_10ab0af0
UnkType_10ab0af0::UnkType_10ab0af0()
{
}
