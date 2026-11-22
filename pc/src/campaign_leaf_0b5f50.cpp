// campaign_leaf_0b5f50.cpp -- one function at file offset 0xb5f50, preferred VA 0x109b5f50. It
// returns by value the four floats of its object scaled by its argument. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkPlane
{
public:
    float X;
    float Y;
    float Z;
    float W;

    UnkPlane(float InX, float InY, float InZ, float InW)
        : X(InX), Y(InY), Z(InZ), W(InW)
    {
    }

    UnkPlane Unk_109b5f50(float Scale) const;
};

// UnkPlane::Unk_109b5f50
UnkPlane UnkPlane::Unk_109b5f50(float Scale) const
{
    return UnkPlane(X * Scale, Y * Scale, Z * Scale, W * Scale);
}
