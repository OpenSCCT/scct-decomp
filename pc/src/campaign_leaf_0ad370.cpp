// campaign_leaf_0ad370.cpp -- constructor at VA 0x109ad370: sets the value at 0x04 to -1 and the
// value at 0x08 to 0, then constructs the member at 0x0c with the constructor at VA 0x10aa6d50. The
// class names are invented; the offsets, the constants and the address are the binary's.

class UnkType_109ad370_10aa6d50
{
public:
    UnkType_109ad370_10aa6d50();

private:
    int unk_00;
};

class UnkType_109ad370
{
public:
    UnkType_109ad370();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_109ad370_10aa6d50 unk_0c;
};

// UnkType_109ad370::UnkType_109ad370
UnkType_109ad370::UnkType_109ad370()
: unk_04(-1)
, unk_08(0)
{
}
