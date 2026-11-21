// Work item 0151: FVector operators (Unreal Engine 2 UnMath.h).
typedef float FLOAT;

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator^(const FVector &V) const;
    FVector operator+(const FVector &V) const;
    FVector operator-(const FVector &V) const;
    FVector operator*(FLOAT Scale) const;
    FVector operator/(FLOAT Scale) const;
    friend FVector operator*(FLOAT Scale, const FVector &V);
};

// 0x40540: cross product (LTCG: this in EDX, V in ECX, result in EAX).
__declspec(noinline) FVector FVector::operator^(const FVector &V) const
{
    return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
}

// 0x40570
FVector operator*(FLOAT Scale, const FVector &V)
{
    return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale);
}

// 0x405a0
FVector FVector::operator+(const FVector &V) const
{
    return FVector(X + V.X, Y + V.Y, Z + V.Z);
}

// 0x405d0
FVector FVector::operator-(const FVector &V) const
{
    return FVector(X - V.X, Y - V.Y, Z - V.Z);
}

// 0x40600
FVector FVector::operator*(FLOAT Scale) const
{
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// 0x40630 (LTCG: result pointer in EAX).
__declspec(noinline) FVector FVector::operator/(FLOAT Scale) const
{
    FLOAT RScale = 1.f / Scale;
    return FVector(X * RScale, Y * RScale, Z * RScale);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_40540(FVector *R, const FVector *A, const FVector *B) { *R = *A ^ *B; Escape(R); }
void Driver_40630(FVector *R, const FVector *A, FLOAT S) { *R = *A / S; Escape(R); }
