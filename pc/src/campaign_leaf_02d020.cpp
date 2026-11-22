// campaign_leaf_02d020.cpp -- one function at file offset 0x2d020, preferred VA 0x1092d020. It
// returns 1 when the three floats of this object equal the three floats of another, and 0
// otherwise. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_1092d020
{
public:
    int UnkEqualVector(const UnkType_1092d020 *Other) const;

private:
    float unk_00;
    float unk_04;
    float unk_08;
};

// UnkType_1092d020::UnkEqualVector
int UnkType_1092d020::UnkEqualVector(const UnkType_1092d020 *Other) const
{
    if ( unk_00 == Other->unk_00 && unk_04 == Other->unk_04 && unk_08 == Other->unk_08 )
    {
        return 1;
    }
    return 0;
}
