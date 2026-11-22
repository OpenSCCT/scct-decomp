// versus_leaf_16e2a0.cpp -- the first int of the element at Index of the array at 0xc74, or 0 past the count at 0xc78, at file offset 0x16e2a0 (VA 0x10a6e2a0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6e2a0
{
    int unk_00;                         // read by GetUnk30_C74
    unsigned char unk_04[0x34 - 0x04];  // the element stride is 0x34
};

struct UnkPointee_10a6e2a0
{
    unsigned char unk_00[0xc74];
    UnkElement_10a6e2a0 *unk_c74;
    int unk_c78;                        // the count, compared with Index
};

class UnkType_10a6e2a0
{
public:
    int GetUnk30_C74(int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6e2a0 *unk_30;
};

// UnkType_10a6e2a0::GetUnk30_C74
int UnkType_10a6e2a0::GetUnk30_C74(int Index)
{
    if ( Index < unk_30->unk_c78 )
    {
        return unk_30->unk_c74[Index].unk_00;
    }
    return 0;
}
