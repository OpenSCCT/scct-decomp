// versus_leaf_16c060.cpp -- a flag test on the object at 0x30 (the int at 0x1598 equals 5), at file offset 0x16c060 (VA 0x10a6c060).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6c060
{
    unsigned char unk_00[0x1598];
    int unk_1598;                       // compared with 5 by UnkCheck1598
};

class UnkType_10a6c060
{
public:
    int UnkCheck1598();

private:
    unsigned char unk_00[0x30];         // not read by UnkCheck1598
    UnkPointee_10a6c060 *unk_30;
};

// UnkType_10a6c060::UnkCheck1598
int UnkType_10a6c060::UnkCheck1598()
{
    if ( unk_30 != 0 && unk_30->unk_1598 == 5 )
    {
        return 1;
    }
    return 0;
}
