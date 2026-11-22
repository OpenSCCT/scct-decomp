// versus_leaf_16c0b0.cpp -- the low bit of the complemented word at 0x18 of the 0x1c-byte element at Index, at file offset 0x16c0b0 (VA 0x10a6c0b0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6c0b0
{
    unsigned char unk_00[0x18];
    unsigned short unk_18;              // read by GetUnk34_18
    unsigned char unk_1a[0x1c - 0x1a];  // the element stride is 0x1c
};

class UnkType_10a6c0b0
{
public:
    int GetUnk34_18(int Index);

private:
    unsigned char unk_00[0x34];         // not read by this function
    UnkElement_10a6c0b0 *unk_34;
};

// UnkType_10a6c0b0::GetUnk34_18
int UnkType_10a6c0b0::GetUnk34_18(int Index)
{
    return ~unk_34[Index].unk_18 & 1;
}
