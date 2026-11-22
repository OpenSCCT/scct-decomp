// versus_leaf_16b2c0.cpp -- one accessor at file offset 0x16b2c0 (VA 0x10a6b2c0): the
// int field at 0xf4 of the element at Index in the array of 0x414-byte elements that
// the member at 0x48 points to. The class, member and method names are invented; the
// offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b2c0
{
    unsigned char unk_00[0xf4];
    int unk_f4;                   // read by GetUnkF4
    unsigned char unk_f8[0x31c];   // the element stride is 0x414
};

class UnkType_10a6b2c0
{
public:
    int GetUnkF4(int Index, int Unused);

private:
    unsigned char unk_00[0x48];     // not read by this function
    UnkElement_10a6b2c0 *unk_48;       // array of elements, indexed by Index
};

// UnkType_10a6b2c0::GetUnkF4
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6b2c0::GetUnkF4(int Index, int Unused)
{
    return unk_48[Index].unk_f4;
}
