// versus_leaf_16eea0.cpp -- the first int of the 0x20-byte element at Index of the inline array at 0xcbc, at file offset 0x16eea0 (VA 0x10a6eea0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6eea0
{
    int unk_00;                         // read by GetUnk30_CBC
    unsigned char unk_04[0x20 - 0x04];  // the element stride is 0x20
};

struct UnkPointee_10a6eea0
{
    unsigned char unk_00[0xcbc];
    UnkElement_10a6eea0 unk_cbc[1];          // the array's length is not known
};

class UnkType_10a6eea0
{
public:
    int GetUnk30_CBC(int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6eea0 *unk_30;
};

// UnkType_10a6eea0::GetUnk30_CBC
int UnkType_10a6eea0::GetUnk30_CBC(int Index)
{
    return unk_30->unk_cbc[Index].unk_00;
}
