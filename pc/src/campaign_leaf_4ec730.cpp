// campaign_leaf_4ec730.cpp -- one function at file offset 0x4ec730, preferred VA 0x10dec730. It
// returns 1 when the circular difference of two sixteen-bit values, Second's less First's, is
// positive; the inline helper brings a difference into range by adding or removing 0x10000. It
// never reads its this pointer. The class, method, structure, member and parameter names are
// invented; the offsets and the bytes are the binary's.

extern "C" int __cdecl abs(int Value);
#pragma intrinsic(abs)

struct UnkAngle
{
    int UnkDelta(const UnkAngle& Other) const
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

    unsigned short unk_0;
};

class UnkType_10dec730
{
public:
    int Unk_10dec730(const UnkAngle& First, const UnkAngle& Second) const;
};

// UnkType_10dec730::Unk_10dec730
int UnkType_10dec730::Unk_10dec730(const UnkAngle& First, const UnkAngle& Second) const
{
    return Second.UnkDelta(First) > 0;
}
