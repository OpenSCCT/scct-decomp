// versus_leaf_16e2d0.cpp -- the word at 0x68 of the element at Index (stride 0x7c) of the array at 0x62c, or 0 past the count at 0x630, at file offset 0x16e2d0 (VA 0x10a6e2d0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6e2d0
{
    unsigned char unk_00[0x68];
    unsigned short unk_68;              // read by GetUnk30_62C
    unsigned char unk_6a[0x7c - 0x6a];  // the element stride is 0x7c
};

struct UnkPointee_10a6e2d0
{
    unsigned char unk_00[0x62c];
    UnkElement_10a6e2d0 *unk_62c;
    int unk_630;                        // the count, compared with Index
};

class UnkType_10a6e2d0
{
public:
    int GetUnk30_62C(int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6e2d0 *unk_30;
};

// UnkType_10a6e2d0::GetUnk30_62C
int UnkType_10a6e2d0::GetUnk30_62C(int Index)
{
    if ( Index < unk_30->unk_630 )
    {
        return unk_30->unk_62c[Index].unk_68;
    }
    return 0;
}
