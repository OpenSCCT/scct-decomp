// campaign_leaf_0e4270.cpp -- constructor at VA 0x109e4270: constructs the member at 0x04 with the
// constructor at VA 0x10aa6d50, then zeroes the 16-bit values at 0x00 and 0x02. The class names are
// invented; the offsets and the address are the binary's.

class UnkType_109e4270_10aa6d50
{
public:
    UnkType_109e4270_10aa6d50();

private:
    int unk_00;
};

class UnkType_109e4270
{
public:
    UnkType_109e4270();

private:
    unsigned short unk_00;
    unsigned short unk_02;
    UnkType_109e4270_10aa6d50 unk_04;
};

// UnkType_109e4270::UnkType_109e4270
UnkType_109e4270::UnkType_109e4270()
{
    unk_00 = 0;
    unk_02 = 0;
}
