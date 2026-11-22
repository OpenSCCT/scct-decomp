// campaign_leaf_02d060.cpp -- one function at file offset 0x2d060, preferred VA 0x1092d060. It
// returns 0 when the three floats of this object equal the three floats of another, and 1
// otherwise. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_1092d060
{
public:
    int UnkNotEqualVector(const UnkType_1092d060 *Other) const;

private:
    float unk_00;
    float unk_04;
    float unk_08;
};

// UnkType_1092d060::UnkNotEqualVector
int UnkType_1092d060::UnkNotEqualVector(const UnkType_1092d060 *Other) const
{
    if ( unk_00 == Other->unk_00 && unk_04 == Other->unk_04 && unk_08 == Other->unk_08 )
    {
        return 0;
    }
    return 1;
}
