// campaign_leaf_1c43c0.cpp -- one function at file offset 0x1c43c0, preferred VA 0x10ac43c0. It
// returns by value the linear interpolation A + (B - A) * Alpha of its two vector arguments by its
// float argument. It has no this pointer. The class, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10ac43c0_Vector
{
public:
    float X;
    float Y;
    float Z;

    UnkType_10ac43c0_Vector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }

    UnkType_10ac43c0_Vector operator+(const UnkType_10ac43c0_Vector& Other) const
    {
        return UnkType_10ac43c0_Vector(X + Other.X, Y + Other.Y, Z + Other.Z);
    }

    UnkType_10ac43c0_Vector operator-(const UnkType_10ac43c0_Vector& Other) const
    {
        return UnkType_10ac43c0_Vector(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    UnkType_10ac43c0_Vector operator*(float Scale) const
    {
        return UnkType_10ac43c0_Vector(X * Scale, Y * Scale, Z * Scale);
    }

    static UnkType_10ac43c0_Vector Unk_10ac43c0(const UnkType_10ac43c0_Vector& A,
        const UnkType_10ac43c0_Vector& B, float Alpha);
};

// UnkType_10ac43c0_Vector::Unk_10ac43c0
UnkType_10ac43c0_Vector UnkType_10ac43c0_Vector::Unk_10ac43c0(const UnkType_10ac43c0_Vector& A,
    const UnkType_10ac43c0_Vector& B, float Alpha)
{
    return A + ( B - A ) * Alpha;
}
