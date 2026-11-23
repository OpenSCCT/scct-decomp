// campaign_leaf_05e610.cpp -- constructor at VA 0x1095e610 taking a byte: constructs the member at
// 0x08 with the constructor at VA 0x10d7ce90, then stores the byte at 0x00, clears the value at
// 0x04 and sets the one at 0x0c to 1. The class and member names are invented; the offsets, the
// constant and the address are the binary's.

class UnkType_10d7ce90_05e610
{
public:
    UnkType_10d7ce90_05e610();
};

class UnkType_1095e610
{
public:
    UnkType_1095e610(unsigned char Value);

private:
    unsigned char unk_00;
    int unk_04;
    UnkType_10d7ce90_05e610 unk_08;
    int unk_0c;
};

// UnkType_1095e610::UnkType_1095e610
UnkType_1095e610::UnkType_1095e610(unsigned char Value)
{
    unk_00 = Value;
    unk_04 = 0;
    unk_0c = 1;
}
