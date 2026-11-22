// versus_leaf_16ee60.cpp -- the int at index A + B * 8 of the inline array at 0xca8, at file offset 0x16ee60 (VA 0x10a6ee60).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6ee60
{
    unsigned char unk_00[0xca8];
    int unk_ca8[1];                     // the array's length is not known; GetUnk30_CA8 indexes it
};

class UnkType_10a6ee60
{
public:
    int GetUnk30_CA8(int A, int B);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6ee60 *unk_30;
};

// UnkType_10a6ee60::GetUnk30_CA8
int UnkType_10a6ee60::GetUnk30_CA8(int A, int B)
{
    return unk_30->unk_ca8[A + B * 8];
}
