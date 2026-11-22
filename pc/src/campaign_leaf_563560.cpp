// campaign_leaf_563560.cpp -- constructor at VA 0x10e63560: constructs the 0x18-byte member at 0x00
// with the constructor at VA 0x10e63530, then sets the byte at 0x18 to 1 and the 16-bit value at
// 0x1a to 0xffff. The class names are invented; the offsets and addresses are the binary's.

class UnkType_10e63530
{
public:
    UnkType_10e63530();

private:
    int unk_00[6];
};

class UnkType_10e63560
{
public:
    UnkType_10e63560();

private:
    UnkType_10e63530 unk_00;
    unsigned char unk_18;
    unsigned short unk_1a;
};

// UnkType_10e63560::UnkType_10e63560
UnkType_10e63560::UnkType_10e63560()
{
    unk_18 = 1;
    unk_1a = 0xffff;
}
