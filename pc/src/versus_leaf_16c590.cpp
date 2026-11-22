// versus_leaf_16c590.cpp -- whether the int at 0x600 of the object that the member at 0x30 points to is nonzero, at file offset 0x16c590 (VA 0x10a6c590).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6c590
{
    unsigned char unk_00[0x600];
    int unk_600;                        // tested by TestUnk30_600
};

class UnkType_10a6c590
{
public:
    int TestUnk30_600();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6c590 *unk_30;
};

// UnkType_10a6c590::TestUnk30_600
int UnkType_10a6c590::TestUnk30_600()
{
    return unk_30->unk_600 != 0;
}
