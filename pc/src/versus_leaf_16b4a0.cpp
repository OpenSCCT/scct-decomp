// versus_leaf_16b4a0.cpp -- one accessor at file offset 0x16b4a0 (VA 0x10a6b4a0): the
// char field at 0xe4 of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b4a0
{
    unsigned char unk_00[0xe4];
    char unk_e4;                  // read by GetUnkE4
    unsigned char unk_e5[0x32f];   // the element stride is 0x414
};

class UnkType_10a6b4a0
{
public:
    int GetUnkE4(int Index);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b4a0 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b4a0::GetUnkE4
// The function pops its one argument (ret 4).
int UnkType_10a6b4a0::GetUnkE4(int Index)
{
    return unk_48[Index].unk_e4;
}
