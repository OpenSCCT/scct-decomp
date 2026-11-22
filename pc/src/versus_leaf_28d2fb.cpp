// versus_leaf_28d2fb.cpp -- returns the int at 0x0c and then ANDs it with zero, at file offset 0x28d2fb
// (VA 0x10b8d2fb). The class and method names are invented; the offsets are the binary's. This unit is built
// with /O1: the original keeps the AND (and dword ptr [ecx+0xc], 0), which /O2 folds into a store of zero.

class UnkType_10b8d2fb
{
public:
    int TakeAndClear();

private:
    unsigned char unk_00[0x0c];
    int unk_0c;
};

// UnkType_10b8d2fb::TakeAndClear
// The old value is returned in EAX; the member is then ANDed with zero.
int UnkType_10b8d2fb::TakeAndClear()
{
    int Old = unk_0c;
    unk_0c &= 0;
    return Old;
}
