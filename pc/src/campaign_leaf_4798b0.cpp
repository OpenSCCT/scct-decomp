// campaign_leaf_4798b0.cpp -- one function at file offset 0x4798b0, preferred VA 0x10d798b0. It
// returns the cross product of the three floats at 0x0 with Other's. The class, method and
// member names are invented; the offsets and the bytes are the binary's.

struct UnkType_10d798b0_Vector
{
    UnkType_10d798b0_Vector(float X, float Y, float Z)
    {
        unk_0 = X;
        unk_4 = Y;
        unk_8 = Z;
    }

    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10d798b0
{
public:
    UnkType_10d798b0_Vector Unk_10d798b0(const UnkType_10d798b0& Other) const;

    float unk_0;
    float unk_4;
    float unk_8;
};

// UnkType_10d798b0::Unk_10d798b0
UnkType_10d798b0_Vector UnkType_10d798b0::Unk_10d798b0(const UnkType_10d798b0& Other) const
{
    UnkType_10d798b0_Vector Result(unk_4 * Other.unk_8 - Other.unk_4 * unk_8,
                     Other.unk_0 * unk_8 - unk_0 * Other.unk_8,
                     Other.unk_4 * unk_0 - unk_4 * Other.unk_0);

    return Result;
}
