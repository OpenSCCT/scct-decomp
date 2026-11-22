// versus_leaf_2b7e80.cpp -- clears the ints at 0x20, 0x54 and 0x58, at file offset 0x2b7e80 (VA 0x10bb7e80).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10bb7e80
{
public:
    void ClearUnk20And54And58();

private:
    unsigned char unk_00[0x20];         // not read by this function
    int unk_20;                         // cleared by ClearUnk20And54And58
    unsigned char unk_24[0x54 - 0x24];  // not read by this function
    int unk_54;                         // cleared by ClearUnk20And54And58
    int unk_58;                         // cleared by ClearUnk20And54And58
};

// UnkType_10bb7e80::ClearUnk20And54And58
void UnkType_10bb7e80::ClearUnk20And54And58()
{
    unk_20 = unk_58 = unk_54 = 0;
}
