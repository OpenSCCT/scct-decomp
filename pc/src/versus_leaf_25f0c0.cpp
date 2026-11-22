// versus_leaf_25f0c0.cpp -- returns the 16-bit field at 5 of the record, at file offset 0x25f0c0 (VA 0x10b5f0c0).
// The class, record and method names are invented; the offsets, the masks, the argument
// sizes and the __stdcall convention are the binary's.

#pragma pack(push, 1)
struct UnkBits_10b5f0c0
{
    unsigned char unk_00[0x3];
    unsigned char unk_03;               // not read by this function
    unsigned char unk_04;               // not read by this function
    unsigned short unk_05;              // read by GetUnk05Word
};
#pragma pack(pop)

class UnkType_10b5f0c0
{
public:
    static unsigned short __stdcall GetUnk05Word(UnkBits_10b5f0c0 *Value);
};

// UnkType_10b5f0c0::GetUnk05Word
// The function pops its one argument (ret 4).
unsigned short __stdcall UnkType_10b5f0c0::GetUnk05Word(UnkBits_10b5f0c0 *Value)
{
    return Value->unk_05;
}
