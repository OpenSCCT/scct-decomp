// Work item w3 0106: Versus RVA 0xb0630.
// Constrains a velocity-like vector V against a pair of surface normals
// (Normal and OldNormal) and damps it by (1 - Damping); W is a reference
// direction the result must not oppose. Link-time code generated: Normal in
// ECX, OldNormal in EDX, V in ESI, W in EDI; this (unused) and Damping on the
// stack (callee pops, ret 8). Callers pass an actor-like object as this; the
// class and method names are neutral (no symbol evidence). The parameter order
// and the explicit FVector copy constructor are needed for the match.

typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    FVector SafeNormal() const; // 0x50d30
};

// Zero vector (retail 0x10ccacc0, read through a pointer).
__declspec(dllimport) extern const FVector GZeroVector;

class UnnamedClass_b0630
{
public:
    void Constrain(const FVector &W, FVector &V, const FVector &Normal, const FVector &OldNormal, FLOAT Damping);
};

// RVA 0xb0630. The owning class is not known; the method never reads this.
__declspec(noinline) void UnnamedClass_b0630::Constrain(const FVector &W, FVector &V, const FVector &Normal, const FVector &OldNormal, FLOAT Damping)
{
    if ((OldNormal | Normal) <= 0.f)
    {
        FVector Dir = Normal ^ OldNormal;
        Dir = Dir.SafeNormal();
        V = Dir * ((Dir | V) * (1.f - Damping));
        if ((V | W) < 0.f)
            V = V * -1.f;
    }
    else
    {
        V = (V - Normal * (Normal | V)) * (1.f - Damping);
        if ((V | W) <= 0.f)
            V = GZeroVector;
    }
}

// Callee, defined here so the link gives it its retail register convention.
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// Scaffolding for the link, not part of the unit.
void Driver_b0630(UnnamedClass_b0630 *A, const FVector *N, const FVector *O, FVector *V, const FVector *W, FLOAT D)
{
    A->Constrain(*W, *V, *N, *O, D);
    A->Constrain(*W, *V, *O, *N, D);
}
