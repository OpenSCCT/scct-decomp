// versus_leaf_24d0e0.cpp -- clears the ints at 8 and 0xc and returns true, at file offset 0x24d0e0 (VA 0x10b4d0e0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b4d0e0
{
public:
    bool ClearUnk08To0C();

private:
    unsigned char unk_00[0x8];          // not read by this function
    int unk_08;                         // cleared by ClearUnk08To0C
    int unk_0c;                         // cleared by ClearUnk08To0C
};

// UnkType_10b4d0e0::ClearUnk08To0C
bool UnkType_10b4d0e0::ClearUnk08To0C()
{
    unk_0c = unk_08 = 0;
    return true;
}
