// versus_leaf_16b520.cpp -- one accessor at file offset 0x16b520 (VA 0x10a6b520): the
// int field at 0x34 of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b520
{
    unsigned char unk_00[0x34];
    int unk_34;                   // read by GetUnk34
    unsigned char unk_38[0x3dc];   // the element stride is 0x414
};

class UnkType_10a6b520
{
public:
    int GetUnk34(int Index, int Unused);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b520 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b520::GetUnk34
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6b520::GetUnk34(int Index, int Unused)
{
    return unk_48[Index].unk_34;
}
