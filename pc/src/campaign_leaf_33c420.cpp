// campaign_leaf_33c420.cpp -- one function at file offset 0x33c420, preferred VA 0x10c3c420. It
// returns the word at 0x284 of the object at 0x5a8 when bit 5 of Other's word at 0x2c and bit 2
// of the word at 0x4b8 are set, or bit 6 of Other's word and bit 0 of the word at 0x5b4; else,
// when the word at 0x404 or 0x408 is set, the method at 0x10befe30's nonzero result for Other;
// else that same word at 0x284. The class, method, member, local and parameter names are
// invented; the offsets and the bytes are the binary's.

class UnkType_10c3c420_Other
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
};

class UnkType_10c3c420_Target
{
public:
    unsigned char unk_0[0x284];
    int unk_284;
};

class UnkType_10c3c420
{
public:
    int Unk_10befe30(UnkType_10c3c420_Other* Other);
    int Unk_10c3c420(UnkType_10c3c420_Other* Other);

    unsigned char unk_0[0x404];
    int unk_404;
    int unk_408;
    unsigned char unk_40c[0xac];
    int unk_4b8;
    unsigned char unk_4bc[0xec];
    UnkType_10c3c420_Target* unk_5a8;
    unsigned char unk_5ac[0x8];
    int unk_5b4;
};

// UnkType_10c3c420::Unk_10c3c420
int UnkType_10c3c420::Unk_10c3c420(UnkType_10c3c420_Other* Other)
{
    int Result;

    if ( (Other->unk_2c & 0x20) && (unk_4b8 & 4) )
    {
        return unk_5a8->unk_284;
    }
    if ( (Other->unk_2c & 0x40) && (unk_5b4 & 1) )
    {
        return unk_5a8->unk_284;
    }
    if ( unk_404 != 0 || unk_408 != 0 )
    {
        Result = Unk_10befe30(Other);
        if ( Result != 0 )
        {
            return Result;
        }
    }
    return unk_5a8->unk_284;
}
