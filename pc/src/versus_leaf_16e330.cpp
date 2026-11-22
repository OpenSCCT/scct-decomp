// versus_leaf_16e330.cpp -- the int at 0x4 of the element at Index (stride 0x34) of the array at 0xc74, or -1 past the count at 0xc78, at file offset 0x16e330 (VA 0x10a6e330).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6e330
{
    unsigned char unk_00[0x4];
    int unk_04;                // read by GetUnk30_C74_04
    unsigned char unk_08[0x34 - 0x8];  // the element stride is 0x34
};

struct UnkPointee_10a6e330
{
    unsigned char unk_00[0xc74];
    UnkElement_10a6e330 *unk_c74;
    int unk_c78;                        // the count, compared with Index
};

class UnkType_10a6e330
{
public:
    int GetUnk30_C74_04(int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6e330 *unk_30;
};

// UnkType_10a6e330::GetUnk30_C74_04
int UnkType_10a6e330::GetUnk30_C74_04(int Index)
{
    if ( Index < unk_30->unk_c78 )
        return unk_30->unk_c74[Index].unk_04;
    return -1;
}
