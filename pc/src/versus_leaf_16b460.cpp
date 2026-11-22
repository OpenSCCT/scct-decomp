// versus_leaf_16b460.cpp -- one accessor at file offset 0x16b460 (VA 0x10a6b460): the
// int field at 0x24 of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b460
{
    unsigned char unk_00[0x24];
    int unk_24;                   // read by GetUnk24
    unsigned char unk_28[0x3ec];   // the element stride is 0x414
};

class UnkType_10a6b460
{
public:
    int GetUnk24(int Index, int Unused);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b460 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b460::GetUnk24
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6b460::GetUnk24(int Index, int Unused)
{
    return unk_48[Index].unk_24;
}
