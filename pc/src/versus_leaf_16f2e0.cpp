// versus_leaf_16f2e0.cpp -- the int at index Index of the inline array at 0xca0, at file offset 0x16f2e0 (VA 0x10a6f2e0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6f2e0
{
    unsigned char unk_00[0xca0];
    int unk_ca0[1];                     // the array's length is not known
};

class UnkType_10a6f2e0
{
public:
    int GetUnk30_CA0(int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6f2e0 *unk_30;
};

// UnkType_10a6f2e0::GetUnk30_CA0
int UnkType_10a6f2e0::GetUnk30_CA0(int Index)
{
    return unk_30->unk_ca0[Index];
}
