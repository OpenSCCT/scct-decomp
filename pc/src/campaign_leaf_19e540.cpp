// campaign_leaf_19e540.cpp -- constructor at VA 0x10a9e540: constructs the member at 0x00 with the
// constructor at VA 0x10a9e4e0, then zeroes the values at 0x158 and 0x04. The class names are
// invented; the offsets and the address are the binary's.

class UnkType_10a9e540_10a9e4e0
{
public:
    UnkType_10a9e540_10a9e4e0();

private:
    int unk_00;
};

class UnkType_10a9e540
{
public:
    UnkType_10a9e540();

private:
    UnkType_10a9e540_10a9e4e0 unk_000;
    int unk_004;
    unsigned char unk_008[0x158 - 0x8];
    int unk_158;
};

// UnkType_10a9e540::UnkType_10a9e540
UnkType_10a9e540::UnkType_10a9e540()
{
    unk_158 = 0;
    unk_004 = 0;
}
