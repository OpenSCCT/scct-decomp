// Work item 0156: Versus RVA 0x40ff0-0x4150f.
// Core math: FCoords::operator/=(FRotator), FCoords::operator/, VRand,
// FRotator::Vector and FQuat helpers (UnMath.h / UnMath.cpp).

typedef int INT;
typedef float FLOAT;

extern "C" __declspec(dllimport) int __cdecl rand(void);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    void Set(FLOAT InX, FLOAT InY, FLOAT InZ) { X = InX; Y = InY; Z = InZ; }
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    FVector &operator+=(const FVector &V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector UnsafeNormal() const
    {
        FLOAT Scale = 1.f / (FLOAT)sqrt(X * X + Y * Y + Z * Z);
        return FVector(X * Scale, Y * Scale, Z * Scale);
    }
};

inline FVector operator*(FLOAT Scale, const FVector &V) { return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale); }

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FVector Vector();
};

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords &operator*=(const FCoords &TransformCoords);
    FCoords &operator/=(const FRotator &Rot);
    FCoords operator/(const FRotator &Rot) const;
};

// Global math table (GMath at 0x10ccac00); UnitCoords is its first member.
// RVA 0x40950 is its sine/cosine helper for Unreal rotation units.
struct FGlobalMath
{
    FCoords UnitCoords;
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;

// Constant vectors reached through references (0x10ccacc0, c4, b8, bc).
extern const FVector &ZeroVector_Ref;  // 0x10ccacc0
extern const FVector &UnitX_Ref;       // 0x10ccacc4
extern const FVector &UnitY_Ref;       // 0x10ccacb8
extern const FVector &UnitZ_Ref;       // 0x10ccacbc

// RVA 0x40ff0
FCoords &FCoords::operator/=(const FRotator &Rot)
{
    FLOAT S, C;

    // Apply inverse roll rotation.
    GMath.SinCos(Rot.Roll, &S, &C);
    *this *= FCoords(ZeroVector_Ref, UnitX_Ref, FVector(0.f, C, S), FVector(0.f, -S, C));

    // Apply inverse pitch rotation.
    GMath.SinCos(Rot.Pitch, &S, &C);
    *this *= FCoords(ZeroVector_Ref, FVector(C, 0.f, -S), UnitY_Ref, FVector(S, 0.f, C));

    // Apply inverse yaw rotation.
    GMath.SinCos(Rot.Yaw, &S, &C);
    *this *= FCoords(ZeroVector_Ref, FVector(C, -S, 0.f), FVector(S, C, 0.f), UnitZ_Ref);

    return *this;
}

// RVA 0x411a0
FCoords FCoords::operator/(const FRotator &Rot) const
{
    return FCoords(*this) /= Rot;
}

// RVA 0x41330
FVector FRotator::Vector()
{
    return (GMath.UnitCoords / *this).XAxis;
}

extern const FLOAT InvRandMax_41260; // 0x10c10a88, 1/RAND_MAX

inline FLOAT appFrand() { return rand() * InvRandMax_41260; }

// RVA 0x41260 (LTCG: result pointer in EDI)
FVector VRand()
{
    FVector Result;
    do
    {
        Result.X = appFrand() * 2.f - 1.f;
        Result.Y = appFrand() * 2.f - 1.f;
        Result.Z = appFrand() * 2.f - 1.f;
    } while (Result.SizeSquared() > 1.f);
    return Result.UnsafeNormal();
}

struct FQuat
{
    FLOAT X, Y, Z, W;
    FQuat() {}
    FQuat(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : X(InX), Y(InY), Z(InZ), W(InW) {}
    FQuat operator*(const FQuat &Q) const
    {
        return FQuat(
            W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,
            W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,
            W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W,
            W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z);
    }
    FVector RotateVector(FVector V) const;
};

// RVA 0x41370 is the out-of-line FQuat::operator* (LTCG: this in ECX,
// Q in EDX, result in EAX).

// RVA 0x413f0 (LTCG: this in ECX, result in EAX, vector by value).
FVector FQuat::RotateVector(FVector V) const
{
    // (q.W*q.W - qv.qv) v + 2 (qv.v) qv + 2 q.W (qv x v)
    FVector qv(X, Y, Z);
    FVector vOut = 2.f * W * (qv ^ V);
    vOut += ((W * W) - (qv | qv)) * V;
    vOut += (2.f * (qv | V)) * qv;
    return vOut;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_41260(FVector *Out) { *Out = VRand(); }
void Driver_41370(FQuat *Out, const FQuat *A, const FQuat *B) { *Out = *A * *B; }
void Driver_413f0(FVector *Out, const FQuat *Q, FVector *V)
{
    Out[0] = Q->RotateVector(V[0]);
    Out[1] = Q[1].RotateVector(V[1]);
}
