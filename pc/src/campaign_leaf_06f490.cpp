// campaign_leaf_06f490.cpp -- one function at file offset 0x6f490, preferred VA 0x1096f490. It
// returns the dot product of the difference of its first two vector arguments with its third. It
// has no this pointer. The class, method and member names are invented; the offset and the bytes
// are the binary's.

struct UnkVector
{
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

    float operator|(const UnkVector& Other) const
    {
        return X * Other.X + Y * Other.Y + Z * Other.Z;
    }
};

class UnkType_1096f490
{
public:
    static float Unk_1096f490(const UnkVector& First, const UnkVector& Second,
        const UnkVector& Third);
};

// UnkType_1096f490::Unk_1096f490
float UnkType_1096f490::Unk_1096f490(const UnkVector& First,
    const UnkVector& Second, const UnkVector& Third)
{
    return ( First - Second ) | Third;
}
