// campaign_leaf_1594d0.cpp -- one function at file offset 0x1594d0, preferred VA 0x10a594d0.
// It returns the distance, through the square-root function at VA 0x10ccabc0, between the vectors
// at offset 0x18 of the two 0x3c-byte entries its arguments select in the array at offset 0x68.
// The class, method and member names are invented; the offset and the bytes are the binary's.

double Unk_10ccabc0(double Value);

struct UnkType_10a594d0_Vector
{
    float X;
    float Y;
    float Z;

    UnkType_10a594d0_Vector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }

    UnkType_10a594d0_Vector operator-(const UnkType_10a594d0_Vector& Other) const
    {
        return UnkType_10a594d0_Vector(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    float SizeSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }
};

struct UnkType_10a594d0_Entry
{
    unsigned char unk_0[0x18];
    UnkType_10a594d0_Vector unk_18;
    unsigned char unk_24[0x3c - 0x24];
};

class UnkType_10a594d0
{
public:
    unsigned char unk_0[0x68];
    UnkType_10a594d0_Entry* unk_68;

    float Unk_10a594d0(int First, int Second);
};

// UnkType_10a594d0::Unk_10a594d0
float UnkType_10a594d0::Unk_10a594d0(int First, int Second)
{
    return Unk_10ccabc0(( unk_68[Second].unk_18 - unk_68[First].unk_18 ).SizeSquared());
}
