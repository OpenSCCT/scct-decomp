// campaign_leaf_3e3e00.cpp -- one function at file offset 0x3e3e00, preferred VA 0x10ce3e00. It
// returns 1 unless one of the flag tests on the word at 0x38 holds: bit 0x400 alone, bit 0x800
// with the word at 0x24 of Other set, or bit 0x200000 with the word at 0x1c of Other set. The
// class, method, structure and member names are invented; the offsets and the bytes are the
// binary's.

struct UnkType_10ce3e00_Other
{
    unsigned char unk_0[0x1c];
    int unk_1c;
    unsigned char unk_20[0x4];
    int unk_24;
};

class UnkType_10ce3e00
{
public:
    int UnkTest(const UnkType_10ce3e00_Other& Other) const
    {
        return ( unk_38 & 0x400 ) != 0 || ( ( unk_38 & 0x800 ) && Other.unk_24 != 0 )
            || ( ( unk_38 & 0x200000 ) && Other.unk_1c != 0 );
    }

    int Unk_10ce3e00(const UnkType_10ce3e00_Other& Other) const;

    unsigned char unk_0[0x38];
    unsigned int unk_38;
};

// UnkType_10ce3e00::Unk_10ce3e00
int UnkType_10ce3e00::Unk_10ce3e00(const UnkType_10ce3e00_Other& Other) const
{
    return !UnkTest(Other);
}
