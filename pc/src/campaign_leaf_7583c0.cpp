// campaign_leaf_7583c0.cpp -- one function at file offset 0x7583c0, preferred VA 0x110583c0. It
// does not read this. It returns whether the word at 0x14 of its argument differs from -1 when the
// word at 0x10 is non-zero, and from 0xffff otherwise. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkType_110583c0_Arg
{
    unsigned char unk_0[0x10];
    int unk_10;
    int unk_14;
};

class UnkType_110583c0
{
public:
    int Unk_110583c0(UnkType_110583c0_Arg* Arg);
};

// UnkType_110583c0::Unk_110583c0
int UnkType_110583c0::Unk_110583c0(UnkType_110583c0_Arg* Arg)
{
    if ( Arg->unk_10 != 0 )
    {
        return Arg->unk_14 != -1;
    }
    return Arg->unk_14 != 0xffff;
}
