// campaign_leaf_06f3e0.cpp -- one function at file offset 0x6f3e0, preferred VA 0x1096f3e0. It
// returns the dot product of its argument with the three floats of this object, less the float at
// offset 0xc. The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_1096f3e0
{
public:
    float UnkDistance(const float *Point) const;

private:
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0c;
};

// UnkType_1096f3e0::UnkDistance
float UnkType_1096f3e0::UnkDistance(const float *Point) const
{
    return ( Point[2] * unk_08 + Point[1] * unk_04 ) + Point[0] * unk_00 - unk_0c;
}
