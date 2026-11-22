// versus_leaf_16ee80.cpp -- the first int of the 0x20-byte element at Index of the inline array at 0xca4, where -1 is returned as 1, at file offset 0x16ee80 (VA 0x10a6ee80).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6ee80
{
    int unk_00;                         // read by GetUnk30_CA4
    unsigned char unk_04[0x20 - 0x04];  // the element stride is 0x20
};

struct UnkPointee_10a6ee80
{
    unsigned char unk_00[0xca4];
    UnkElement_10a6ee80 unk_ca4[1];          // the array's length is not known
};

class UnkType_10a6ee80
{
public:
    int GetUnk30_CA4(int Unused, int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6ee80 *unk_30;
};

// UnkType_10a6ee80::GetUnk30_CA4
// Unused is never read; the function pops both arguments (ret 8).
int UnkType_10a6ee80::GetUnk30_CA4(int Unused, int Index)
{
    int value = unk_30->unk_ca4[Index].unk_00;
    if ( value == -1 )
    {
        value = 1;
    }
    return value;
}
