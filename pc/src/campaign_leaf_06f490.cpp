// campaign_leaf_06f490.cpp -- one function at file offset 0x6f490, preferred VA 0x1096f490. It
// returns the dot product of the difference of its first two vector arguments with its third. It
// has no this pointer. The class, method and member names are invented; the offset and the bytes
// are the binary's.

struct UnkType_1096f490_Vector
{
    float X;
    float Y;
    float Z;

    UnkType_1096f490_Vector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }

    UnkType_1096f490_Vector operator-(const UnkType_1096f490_Vector& Other) const
    {
        return UnkType_1096f490_Vector(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    float operator|(const UnkType_1096f490_Vector& Other) const
    {
        return X * Other.X + Y * Other.Y + Z * Other.Z;
    }
};

class UnkType_1096f490
{
public:
    static float Unk_1096f490(const UnkType_1096f490_Vector& First,
        const UnkType_1096f490_Vector& Second, const UnkType_1096f490_Vector& Third);
};

// UnkType_1096f490::Unk_1096f490
float UnkType_1096f490::Unk_1096f490(const UnkType_1096f490_Vector& First,
    const UnkType_1096f490_Vector& Second, const UnkType_1096f490_Vector& Third)
{
    return ( First - Second ) | Third;
}
