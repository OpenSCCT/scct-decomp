// versus_leaf_16b420.cpp -- one accessor at file offset 0x16b420 (VA 0x10a6b420): the
// int field at 0x1c of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b420
{
    unsigned char unk_00[0x1c];
    int unk_1c;                   // read by GetUnk1C
    unsigned char unk_20[0x3f4];   // the element stride is 0x414
};

class UnkType_10a6b420
{
public:
    int GetUnk1C(int Index, int Unused);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b420 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b420::GetUnk1C
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6b420::GetUnk1C(int Index, int Unused)
{
    return unk_48[Index].unk_1c;
}
