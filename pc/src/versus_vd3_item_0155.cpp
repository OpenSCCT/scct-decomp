// Work item 0155: Versus RVA 0x40ba0-0x40fed.
// Core math: FVector::RotateAngleAxis, FCoords::operator*= (by coords and by
// rotator) and FCoords::operator* (by rotator). These were compiled with /GL
// and linked with /LTCG, so the retail calls use register conventions.

typedef int INT;
typedef float FLOAT;

struct FCoords;
struct FRotator;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector RotateAngleAxis(const INT Angle, const FVector &Axis) const;
    FVector TransformPointBy(const FCoords &Coords) const;
    FVector TransformVectorBy(const FCoords &Coords) const;
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
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
    FCoords &operator*=(const FRotator &Rot);
    FCoords operator*(const FRotator &Rot) const;
};

// FGlobalMath at 0x10ccac00; its sine/cosine helper is RVA 0x40950.
struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;

// Constant vectors reached through references (0x10ccacb8..0x10ccacc4).
extern const FVector &GMath_UnitY;  // 0x10ccacb8
extern const FVector &GMath_UnitZ;  // 0x10ccacbc
extern const FVector &GMath_Zero;   // 0x10ccacc0
extern const FVector &GMath_UnitX;  // 0x10ccacc4

extern const FLOAT One_40ba0;       // 0x10c109fc (1.f)

// RVA 0x40a30 and 0x40ab0 (item 0154).
void TransformPoint_40a30(const FCoords &Coords, const FVector &Point, FVector &Result);
void TransformVector_40ab0(const FCoords &Coords, const FVector &V, FVector &Result);

// RVA 0x40b20 (item 0154); retail inlines it here under LTCG.
FVector FVector::TransformPointBy(const FCoords &Coords) const
{
    FVector Result;
    TransformPoint_40a30(Coords, *this, Result);
    return Result;
}

// RVA 0x40b60 (item 0154); retail inlines it here under LTCG.
FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Result;
    TransformVector_40ab0(Coords, *this, Result);
    return Result;
}

// RVA 0x40ba0
__declspec(noinline) FVector FVector::RotateAngleAxis(const INT Angle, const FVector &Axis) const
{
    FLOAT S, C;
    GMath.SinCos(Angle, &S, &C);

    FLOAT XS = Axis.X * S;
    FLOAT YS = Axis.Y * S;
    FLOAT ZS = Axis.Z * S;

    FLOAT OMC = One_40ba0 - C;

    FLOAT XY = Axis.Y * Axis.X * OMC;
    FLOAT YZ = Axis.Z * Axis.Y * OMC;
    FLOAT ZX = Axis.Z * Axis.X * OMC;

    return FVector(
        (Axis.X * Axis.X * OMC + C) * X + (XY - ZS) * Y + (ZX + YS) * Z,
        (XY + ZS) * X + (Axis.Y * Axis.Y * OMC + C) * Y + (YZ - XS) * Z,
        (ZX - YS) * X + (YZ + XS) * Y + (Axis.Z * Axis.Z * OMC + C) * Z);
}

// RVA 0x40ca0
__declspec(noinline) FCoords &FCoords::operator*=(const FCoords &TransformCoords)
{
    Origin = Origin.TransformPointBy(TransformCoords);
    XAxis = XAxis.TransformVectorBy(TransformCoords);
    YAxis = YAxis.TransformVectorBy(TransformCoords);
    ZAxis = ZAxis.TransformVectorBy(TransformCoords);
    return *this;
}

// RVA 0x40d90
__declspec(noinline) FCoords &FCoords::operator*=(const FRotator &Rot)
{
    FLOAT S, C;

    // Apply yaw rotation.
    GMath.SinCos(Rot.Yaw, &S, &C);
    *this *= FCoords(GMath_Zero, FVector(+C, +S, 0.f), FVector(-S, +C, 0.f), GMath_UnitZ);

    // Apply pitch rotation.
    GMath.SinCos(Rot.Pitch, &S, &C);
    *this *= FCoords(GMath_Zero, FVector(+C, 0.f, +S), GMath_UnitY, FVector(-S, 0.f, +C));

    // Apply roll rotation.
    GMath.SinCos(Rot.Roll, &S, &C);
    *this *= FCoords(GMath_Zero, GMath_UnitX, FVector(0.f, +C, -S), FVector(0.f, +S, +C));

    return *this;
}

// RVA 0x40f40
__declspec(noinline) FCoords FCoords::operator*(const FRotator &Rot) const
{
    return FCoords(*this) *= Rot;
}

// Scaffolding for the link, not part of the unit.
// __declspec(noinline) above stands in for retail call sites the LTCG inliner declined.
void Escape(void *);
void Driver_40ba0(FVector *Out, const FVector *V, INT Angle, const FVector *Axis)
{
    Escape(&GMath);
    *Out = V->RotateAngleAxis(Angle, *Axis);
}
void Driver_40f40(FCoords *Out, const FCoords *C, const FRotator *R)
{
    Escape(&GMath);
    *Out = *C * *R;
}
typedef FCoords &(FCoords::*CoordsMul_40ca0)(const FCoords &);
void EscapeMember(CoordsMul_40ca0);
void Driver_40ca0(FCoords *A, const FCoords *B)
{
    EscapeMember(&FCoords::operator*=);
    *A *= *B;
}
