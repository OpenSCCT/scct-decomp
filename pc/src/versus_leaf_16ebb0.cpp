// versus_leaf_16ebb0.cpp -- whether the first int of the element at Index of the array at 0xc74 equals 0xb, at file offset 0x16ebb0 (VA 0x10a6ebb0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10a6ebb0
{
    int unk_00;                         // read by TestUnk30_C74_0B
    unsigned char unk_04[0x34 - 0x04];  // the element stride is 0x34
};

struct UnkPointee_10a6ebb0
{
    unsigned char unk_00[0xc74];
    UnkElement_10a6ebb0 *unk_c74;
};

class UnkType_10a6ebb0
{
public:
    int TestUnk30_C74_0B(int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6ebb0 *unk_30;
};

// UnkType_10a6ebb0::TestUnk30_C74_0B
int UnkType_10a6ebb0::TestUnk30_C74_0B(int Index)
{
    return unk_30->unk_c74[Index].unk_00 == 0xb;
}
