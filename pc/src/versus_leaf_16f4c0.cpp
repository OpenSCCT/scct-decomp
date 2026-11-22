// versus_leaf_16f4c0.cpp -- whether the word at 0xd8 of the 0x414-byte element at Index of the array at 0x48 is not 0xffff, at file offset 0x16f4c0 (VA 0x10a6f4c0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6f4c0
{
    unsigned char unk_00[0xd8];
    unsigned short unk_d8;              // tested by TestUnk48_D8
    unsigned char unk_da[0x414 - 0xda]; // the element stride is 0x414
};

class UnkType_10a6f4c0
{
public:
    int TestUnk48_D8(int Index);

private:
    unsigned char unk_00[0x48];         // not read by this function
    UnkElement_10a6f4c0 *unk_48;
};

// UnkType_10a6f4c0::TestUnk48_D8
int UnkType_10a6f4c0::TestUnk48_D8(int Index)
{
    return unk_48[Index].unk_d8 != 0xffff;
}
