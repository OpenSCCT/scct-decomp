// campaign_leaf_1ff9f0.cpp -- constructor at VA 0x10aff9f0: constructs the member at 0x00 with the
// constructor at VA 0x10aff990, then zeroes the values at 0x158 and 0x04. The class names are
// invented; the offsets and the address are the binary's.

class UnkType_10aff9f0_10aff990
{
public:
    UnkType_10aff9f0_10aff990();

private:
    int unk_00;
};

class UnkType_10aff9f0
{
public:
    UnkType_10aff9f0();

private:
    UnkType_10aff9f0_10aff990 unk_000;
    int unk_004;
    unsigned char unk_008[0x158 - 0x8];
    int unk_158;
};

// UnkType_10aff9f0::UnkType_10aff9f0
UnkType_10aff9f0::UnkType_10aff9f0()
{
    unk_158 = 0;
    unk_004 = 0;
}
