// campaign_leaf_1e68c0.cpp -- one function at file offset 0x1e68c0, preferred VA 0x10ae68c0. It
// reduces its unsigned argument modulo 40 and returns a two-bit mask: bit 0 when the first byte of
// that 8-byte entry of the array at offset 0x10 is nonzero, bit 1 when the first byte of that entry
// of the array at offset 0x164 is. The class, method and member names are invented; the offset and
// the bytes are the binary's.

struct UnkEntry
{
    unsigned char unk_0;
    unsigned char unk_1[7];
};

class UnkType_10ae68c0
{
public:
    unsigned char unk_0[0x10];
    UnkEntry unk_10[40];
    unsigned char unk_150[0x164 - 0x150];
    UnkEntry unk_164[40];

    int Unk_10ae68c0(unsigned int Index);
};

// UnkType_10ae68c0::Unk_10ae68c0
int UnkType_10ae68c0::Unk_10ae68c0(unsigned int Index)
{
    Index %= 40;
    return ( unk_10[Index].unk_0 != 0 ) | ( unk_164[Index].unk_0 ? 2 : 0 );
}
