// versus_leaf_16eec0.cpp -- (n - b) * 100 / n, with n the int at 0xcb4 and b the int at 0xcb8, or -1 when n is below 10, at file offset 0x16eec0 (VA 0x10a6eec0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10a6eec0
{
    unsigned char unk_00[0xcb4];
    int unk_cb4;                        // n, read by CalcUnk30_CB4
    int unk_cb8;                        // b, read by CalcUnk30_CB4
};

class UnkType_10a6eec0
{
public:
    int CalcUnk30_CB4();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkPointee_10a6eec0 *unk_30;
};

// UnkType_10a6eec0::CalcUnk30_CB4
int UnkType_10a6eec0::CalcUnk30_CB4()
{
    int n = unk_30->unk_cb4;
    if ( n >= 10 )
    {
        return ( n - unk_30->unk_cb8 ) * 100 / n;
    }
    return -1;
}
