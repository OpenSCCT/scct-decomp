// campaign_leaf_47c3f0.cpp -- one function at file offset 0x47c3f0, preferred VA 0x10d7c3f0. It
// returns 1 when the floats at 0x4 and 0x8 equal the argument's. The class, method and member names are invented; the offsets and the
// bytes are the binary's.

class UnkType_10d7c3f0
{
public:
    int Unk_10d7c3f0(const UnkType_10d7c3f0& Other) const;

    int unk_0;
    float unk_4;
    float unk_8;
};

// UnkType_10d7c3f0::Unk_10d7c3f0
int UnkType_10d7c3f0::Unk_10d7c3f0(const UnkType_10d7c3f0& Other) const
{
    return unk_4 == Other.unk_4 && unk_8 == Other.unk_8;
}
