// campaign_leaf_11c250.cpp -- one function at file offset 0x11c250, preferred VA 0x10a1c250. It
// returns by value its vector reflected about its argument's normal: V - N * (2 * (V . N)). The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a1c250_Vector
{
public:
    float X;
    float Y;
    float Z;

    UnkType_10a1c250_Vector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }

    UnkType_10a1c250_Vector operator-(const UnkType_10a1c250_Vector& Other) const
    {
        return UnkType_10a1c250_Vector(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    UnkType_10a1c250_Vector operator*(float Scale) const
    {
        return UnkType_10a1c250_Vector(X * Scale, Y * Scale, Z * Scale);
    }

    float operator|(const UnkType_10a1c250_Vector& Other) const
    {
        return X * Other.X + Y * Other.Y + Z * Other.Z;
    }

    UnkType_10a1c250_Vector Unk_10a1c250(const UnkType_10a1c250_Vector& Normal) const;
};

// UnkType_10a1c250_Vector::Unk_10a1c250
UnkType_10a1c250_Vector UnkType_10a1c250_Vector::Unk_10a1c250(
    const UnkType_10a1c250_Vector& Normal) const
{
    return *this - Normal * ( 2.0f * ( *this | Normal ) );
}
