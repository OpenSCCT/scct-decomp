// versus_leaf_16b280.cpp -- one accessor, at file offset 0x16b280 (VA 0x10a6b280): the field at
// 0xec of the element at Index in the 0x414-byte element array at 0x48. The class, member and
// field names are invented; the offsets, the element stride and the argument size are the binary's.

struct UnkElement_10a6b280
{
    unsigned char unk_00[0xec];
    int unk_ec;                         // read by GetUnkEC
    unsigned char unk_f0[0x414 - 0xf0]; // the element stride is 0x414
};

class UnkType_10a6b280
{
public:
    int GetUnkEC(int Index, int Unused);

private:
    unsigned char unk_00[0x48];         // not read by this function
    UnkElement_10a6b280 *unk_48;        // array of elements, indexed by Index
};

// UnkType_10a6b280::GetUnkEC
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6b280::GetUnkEC(int Index, int Unused)
{
    return unk_48[Index].unk_ec;
}
