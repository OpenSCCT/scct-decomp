// versus_leaf_16f4f0.cpp -- whether the word at 0x5f8 of the object that the member at 0x30 points to is not 0xffff, at file offset 0x16f4f0 (VA 0x10a6f4f0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6f4f0
{
    unsigned char unk_00[0x5f8];
    unsigned short unk_5f8;             // tested by TestUnk30_5F8
};

class UnkType_10a6f4f0
{
public:
    int TestUnk30_5F8();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6f4f0 *unk_30;
};

// UnkType_10a6f4f0::TestUnk30_5F8
int UnkType_10a6f4f0::TestUnk30_5F8()
{
    return unk_30->unk_5f8 != 0xffff;
}
