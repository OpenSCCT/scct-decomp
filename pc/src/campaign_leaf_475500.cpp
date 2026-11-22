// campaign_leaf_475500.cpp -- one function at file offset 0x475500, preferred VA 0x10d75500. It
// returns whichever of the words at 0x80 and 0x84 also appears at 0x80 or 0x84 of Other, the
// first one checked first, or 0. The class, method and member names are invented; the offsets
// and the bytes are the binary's.

class UnkType_10d75500
{
public:
    int Unk_10d75500(const UnkType_10d75500& Other) const;

    unsigned char unk_0[0x80];
    int unk_80;
    int unk_84;
};

// UnkType_10d75500::Unk_10d75500
int UnkType_10d75500::Unk_10d75500(const UnkType_10d75500& Other) const
{
    if ( unk_80 == Other.unk_80 || unk_80 == Other.unk_84 )
    {
        return unk_80;
    }
    if ( unk_84 == Other.unk_80 || unk_84 == Other.unk_84 )
    {
        return unk_84;
    }
    return 0;
}
