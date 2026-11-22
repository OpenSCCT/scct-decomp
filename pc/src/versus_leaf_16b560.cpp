// versus_leaf_16b560.cpp -- one accessor at file offset 0x16b560 (VA 0x10a6b560): the
// int field at 0xc of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b560
{
    unsigned char unk_00[0xc];
    int unk_c;                    // read by GetUnkC
    unsigned char unk_10[0x404];   // the element stride is 0x414
};

class UnkType_10a6b560
{
public:
    int GetUnkC(int Index, int Unused);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b560 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b560::GetUnkC
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6b560::GetUnkC(int Index, int Unused)
{
    return unk_48[Index].unk_c;
}
