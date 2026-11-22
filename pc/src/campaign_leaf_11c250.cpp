// campaign_leaf_11c250.cpp -- one function at file offset 0x11c250, preferred VA 0x10a1c250. It
// returns by value its vector reflected about its argument's normal: V - N * (2 * (V . N)). The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkVector
{
public:
    float X;
    float Y;
    float Z;

    UnkVector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }

    UnkVector operator-(const UnkVector& Other) const
    {
        return UnkVector(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    UnkVector operator*(float Scale) const
    {
        return UnkVector(X * Scale, Y * Scale, Z * Scale);
    }

    float operator|(const UnkVector& Other) const
    {
        return X * Other.X + Y * Other.Y + Z * Other.Z;
    }

    UnkVector Unk_10a1c250(const UnkVector& Normal) const;
};

// UnkVector::Unk_10a1c250
UnkVector UnkVector::Unk_10a1c250(const UnkVector& Normal) const
{
    return *this - Normal * ( 2.0f * ( *this | Normal ) );
}
