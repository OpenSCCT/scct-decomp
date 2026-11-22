// versus_leaf_25f090.cpp -- returns the byte at 4 of the record, at file offset 0x25f090 (VA 0x10b5f090).
// The class, record and method names are invented; the offsets, the masks, the argument
// sizes and the __stdcall convention are the binary's.

struct UnkBits_10b5f090
{
    unsigned char unk_00[0x3];
    unsigned char unk_03;               // read by the helper
    unsigned char unk_04;               // read by the helper
    unsigned char unk_05;               // read by the helper
};

class UnkType_10b5f090
{
public:
    static unsigned char __stdcall GetUnk04(UnkBits_10b5f090 *Value);
};

// UnkType_10b5f090::GetUnk04
// The function pops its one argument (ret 4).
unsigned char __stdcall UnkType_10b5f090::GetUnk04(UnkBits_10b5f090 *Value)
{
    return Value->unk_04;
}
