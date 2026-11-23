// campaign_leaf_6fdd80.cpp -- constructor at VA 0x10ffdd80: constructs the 4-byte member at 0x00
// with the constructor at VA 0x10e119f0, clears the members at 0x04 and 0x08 and sets the one at
// 0x0c to 0x80000000. The class names are invented; the offsets and addresses are the binary's.

class UnkType_10e119f0
{
public:
    UnkType_10e119f0();

private:
    int unk_00;
};

class UnkType_10ffdd80
{
public:
    UnkType_10ffdd80();

private:
    UnkType_10e119f0 unk_00;
    int unk_04;
    int unk_08;
    unsigned int unk_0c;
};

// UnkType_10ffdd80::UnkType_10ffdd80
UnkType_10ffdd80::UnkType_10ffdd80()
{
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0x80000000;
}
