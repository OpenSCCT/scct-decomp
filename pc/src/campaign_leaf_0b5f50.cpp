// campaign_leaf_0b5f50.cpp -- one function at file offset 0xb5f50, preferred VA 0x109b5f50. It
// returns by value the four floats of its object scaled by its argument. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_109b5f50_Plane
{
public:
    float X;
    float Y;
    float Z;
    float W;

    UnkType_109b5f50_Plane(float InX, float InY, float InZ, float InW)
        : X(InX), Y(InY), Z(InZ), W(InW)
    {
    }

    UnkType_109b5f50_Plane Unk_109b5f50(float Scale) const;
};

// UnkType_109b5f50_Plane::Unk_109b5f50
UnkType_109b5f50_Plane UnkType_109b5f50_Plane::Unk_109b5f50(float Scale) const
{
    return UnkType_109b5f50_Plane(X * Scale, Y * Scale, Z * Scale, W * Scale);
}
