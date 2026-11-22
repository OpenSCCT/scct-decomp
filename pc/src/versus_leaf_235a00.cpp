// versus_leaf_235a00.cpp -- returns the byte at 0x0c of the record that the pointer at 0x58 of the argument names,
// or zero for a null argument, at file offset 0x235a00 (VA 0x10b35a00). The class, record and method names are
// invented; the offsets, the argument size and the __stdcall convention are the binary's.

struct UnkInner_10b35a00
{
    unsigned char unk_00[0xc];
    unsigned char unk_0c;               // read by GetUnk58Byte0c
};

struct UnkOuter_10b35a00
{
    unsigned char unk_00[0x58];
    UnkInner_10b35a00 *unk_58;          // followed by GetUnk58Byte0c
};

class UnkType_10b35a00
{
public:
    static unsigned char __stdcall GetUnk58Byte0c(UnkOuter_10b35a00 *Value);
};

// UnkType_10b35a00::GetUnk58Byte0c
// The function pops its one argument (ret 4).
unsigned char __stdcall UnkType_10b35a00::GetUnk58Byte0c(UnkOuter_10b35a00 *Value)
{
    if (Value != 0)
    {
        return Value->unk_58->unk_0c;
    }
    return 0;
}
