// campaign_leaf_4ec4d0.cpp -- one function at file offset 0x4ec4d0, preferred VA 0x10dec4d0. It
// returns 1 when the circular difference of the sixteen-bit values at 0x0, this value less Other's,
// is positive; the inline helper brings a difference into range by adding or removing 0x10000. The
// class, method and member names are invented; the offsets and the bytes are the binary's.

extern "C" int __cdecl abs(int Value);
#pragma intrinsic(abs)

class UnkType_10dec4d0
{
public:
    int UnkDelta(const UnkType_10dec4d0& Other) const
    {
        int Mine = unk_0;
        int Theirs = Other.unk_0;
        int Delta = Mine - Theirs;

        if ( abs(Delta) < 0x8000 )
        {
            return Delta;
        }
        return Mine < Theirs ? Delta + 0x10000 : Delta - 0x10000;
    }

    int Unk_10dec4d0(const UnkType_10dec4d0& Other) const;

    unsigned short unk_0;
};

// UnkType_10dec4d0::Unk_10dec4d0
int UnkType_10dec4d0::Unk_10dec4d0(const UnkType_10dec4d0& Other) const
{
    return UnkDelta(Other) > 0;
}
