// campaign_leaf_4e7e60.cpp -- one function at file offset 0x4e7e60, preferred VA 0x10de7e60. It
// returns the difference between the sixteen-bit values at 0x0 of this object and of Other,
// brought into -0x8000..0x8000 by adding or removing 0x10000. The class, method and member names
// are invented; the offsets and the bytes are the binary's.

extern "C" int __cdecl abs(int Value);
#pragma intrinsic(abs)

class UnkType_10de7e60
{
public:
    int Unk_10de7e60(const UnkType_10de7e60& Other) const;

    unsigned short unk_0;
};

// UnkType_10de7e60::Unk_10de7e60
int UnkType_10de7e60::Unk_10de7e60(const UnkType_10de7e60& Other) const
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
