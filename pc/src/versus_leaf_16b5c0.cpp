// versus_leaf_16b5c0.cpp -- one accessor at file offset 0x16b5c0 (VA 0x10a6b5c0): the
// int field at 0xe0 of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b5c0
{
    unsigned char unk_00[0xe0];
    int unk_e0;                   // read by GetUnkE0
    unsigned char unk_e4[0x330];   // the element stride is 0x414
};

class UnkType_10a6b5c0
{
public:
    int GetUnkE0(int Index, int Unused);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b5c0 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b5c0::GetUnkE0
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6b5c0::GetUnkE0(int Index, int Unused)
{
    return unk_48[Index].unk_e0;
}
