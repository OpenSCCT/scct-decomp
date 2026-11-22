// versus_leaf_16b5e0.cpp -- one accessor at file offset 0x16b5e0 (VA 0x10a6b5e0): the
// int field at 0x18 of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b5e0
{
    unsigned char unk_00[0x18];
    int unk_18;                   // read by GetUnk18
    unsigned char unk_1c[0x3f8];   // the element stride is 0x414
};

class UnkType_10a6b5e0
{
public:
    int GetUnk18(int Index);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b5e0 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b5e0::GetUnk18
// The function pops its one argument (ret 4).
int UnkType_10a6b5e0::GetUnk18(int Index)
{
    return unk_48[Index].unk_18;
}
