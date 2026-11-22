// campaign_leaf_484be0.cpp -- one function at file offset 0x484be0, preferred VA 0x10d84be0. It
// returns 1 when the circular difference of the eight-bit values at 0x0, Other's value less this
// one's, is positive; the inline helper brings a difference into range by adding or removing 0x100.
// The class, method and member names are invented; the offsets and the bytes are the binary's.

extern "C" int __cdecl abs(int Value);
#pragma intrinsic(abs)

class UnkType_10d84be0
{
public:
    int UnkDelta(const UnkType_10d84be0& Other) const
    {
        int Mine = unk_0;
        int Theirs = Other.unk_0;
        int Delta = Mine - Theirs;

        if ( abs(Delta) < 0x80 )
        {
            return Delta;
        }
        return Mine < Theirs ? Delta + 0x100 : Delta - 0x100;
    }

    int Unk_10d84be0(const UnkType_10d84be0& Other) const;

    unsigned char unk_0;
};

// UnkType_10d84be0::Unk_10d84be0
int UnkType_10d84be0::Unk_10d84be0(const UnkType_10d84be0& Other) const
{
    return Other.UnkDelta(*this) > 0;
}
