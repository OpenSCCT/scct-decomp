// campaign_leaf_6fded0.cpp -- constructor at VA 0x10ffded0: constructs the 4-byte member at 0x00
// with the constructor at VA 0x10e10d90, clears the members at 0x04 and 0x08 and sets the one at
// 0x0c to 0x80000000. The class names are invented; the offsets and addresses are the binary's.

class UnkType_10e10d90
{
public:
    UnkType_10e10d90();

private:
    int unk_00;
};

class UnkType_10ffded0
{
public:
    UnkType_10ffded0();

private:
    UnkType_10e10d90 unk_00;
    int unk_04;
    int unk_08;
    unsigned int unk_0c;
};

// UnkType_10ffded0::UnkType_10ffded0
UnkType_10ffded0::UnkType_10ffded0()
{
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0x80000000;
}
