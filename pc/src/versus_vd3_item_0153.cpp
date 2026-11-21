// Work item 0153: FVector / FCoords inline helpers (Unreal Engine 2 UnMath.h),
// RVA 0x40780-0x40903.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FLOAT SizeSquared() const;
    UBOOL IsZero() const;
    FVector UnsafeNormal() const;
};

#pragma auto_inline(off)
// 0x40780 (LTCG: this in EAX)
FLOAT FVector::SizeSquared() const
{
    return X * X + Y * Y + Z * Z;
}

// 0x407a0
UBOOL FVector::IsZero() const
{
    return X == 0.f && Y == 0.f && Z == 0.f;
}

// 0x407e0 (LTCG: result pointer in EAX)
FVector FVector::UnsafeNormal() const
{
    FLOAT Scale = 1.f / appSqrt(X * X + Y * Y + Z * Z);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

class FCoords
{
public:
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ);
    FCoords(const FCoords &Other);
};

// 0x40830
FCoords::FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
    : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ)
{
}

// 0x40890
FCoords::FCoords(const FCoords &Other)
    : Origin(Other.Origin), XAxis(Other.XAxis), YAxis(Other.YAxis), ZAxis(Other.ZAxis)
{
}

#pragma auto_inline(on)

// 0x408e0: integer 3-vector subtraction. Neutral name: no evidence for the
// class. LTCG: this in ECX, operand in ESI, result pointer in EAX.
struct UnnamedIntVector_408e0
{
    INT X, Y, Z;
    UnnamedIntVector_408e0() {}
    UnnamedIntVector_408e0(INT InX, INT InY, INT InZ) : X(InX), Y(InY), Z(InZ) {}
    UnnamedIntVector_408e0 operator-(const UnnamedIntVector_408e0 &V) const;
};

#pragma auto_inline(off)
UnnamedIntVector_408e0 UnnamedIntVector_408e0::operator-(const UnnamedIntVector_408e0 &V) const
{
    return UnnamedIntVector_408e0(X - V.X, Y - V.Y, Z - V.Z);
}
#pragma auto_inline(on)

// Scaffolding for the LTCG link, not part of the unit.
FLOAT Driver_40780(const FVector *V) { return V->SizeSquared(); }
void Driver_407e0(const FVector *V, FVector *Out) { *Out = V->UnsafeNormal(); }
void Driver_408e0(const UnnamedIntVector_408e0 *A, const UnnamedIntVector_408e0 *B, UnnamedIntVector_408e0 *Out) { *Out = *A - *B; }
