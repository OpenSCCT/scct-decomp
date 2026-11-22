// campaign_leaf_46c220.cpp -- one function at file offset 0x46c220, preferred VA 0x10d6c220. It
// returns 1 when the floats at 0x4 and 0x8 equal those of Other and the words at 0xc are equal
// or either is 0. The class, method and member names are invented; the offsets and the bytes are
// the binary's.

class UnkType_10d6c220
{
public:
    int Unk_10d6c220(const UnkType_10d6c220& Other) const;

    int unk_0;
    float unk_4;
    float unk_8;
    int unk_c;
};

// UnkType_10d6c220::Unk_10d6c220
int UnkType_10d6c220::Unk_10d6c220(const UnkType_10d6c220& Other) const
{
    return unk_4 == Other.unk_4 && unk_8 == Other.unk_8
        && ( unk_c == Other.unk_c || unk_c == 0 || Other.unk_c == 0 );
}
