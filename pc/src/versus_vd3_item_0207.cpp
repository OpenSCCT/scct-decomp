// Work item 0207: Versus RVA 0x50ed0-0x511d0.
// Core math (UnMath.h), compiled with /GL and linked with /LTCG:
// an inverse rotation matrix built from a rotator, and the projection
// range of four points onto an axis.

typedef int INT;
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
    FPlane(const FVector &V, FLOAT InW) { X = V.X; Y = V.Y; Z = V.Z; W = InW; }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FMatrix
{
    union
    {
        struct { FPlane XPlane, YPlane, ZPlane, WPlane; };
        FLOAT M[4][4];
    };
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    void operator*=(const FMatrix &Other);
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

// RVA 0x4fbc0 (item 0202).
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}

// RVA 0x4fc30 (item 0202, copied so LTCG gives it its retail convention).
__declspec(noinline) void FMatrix::operator*=(const FMatrix &Other)
{
    FMatrix Result;
    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];

    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];

    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];

    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
    *this = Result;
}

struct FInverseRotationMatrix : public FMatrix
{
    FInverseRotationMatrix(const FRotator &Rot);
};

// RVA 0x50ed0 (LTCG: this in EBX, Rot on the stack). The W plane is one
// local shared by the three matrices, as the retail code builds it once.
__declspec(noinline) FInverseRotationMatrix::FInverseRotationMatrix(const FRotator &Rot)
{
    FLOAT S, C;
    GMath.SinCos(-Rot.Yaw, &S, &C);
    FPlane W(GMath_Zero, 1.f);
    *(FMatrix *)this = FMatrix(FPlane(+C, +S, 0.f, 0.f), FPlane(-S, +C, 0.f, 0.f), FPlane(GMath_UnitZ, 0.f), W);
    GMath.SinCos(-Rot.Pitch, &S, &C);
    *this *= FMatrix(FPlane(+C, 0.f, +S, 0.f), FPlane(GMath_UnitY, 0.f), FPlane(-S, 0.f, +C, 0.f), W);
    GMath.SinCos(-Rot.Roll, &S, &C);
    *this *= FMatrix(FPlane(GMath_UnitX, 0.f), FPlane(0.f, +C, -S, 0.f), FPlane(0.f, +S, +C, 0.f), W);
}

// RVA 0x510f0 (LTCG: Axis in ECX, Points in EAX, Min in EDX, Max in ESI).
// Neutral name: the range of four points projected onto an axis. The mixed
// dot-product spellings reproduce retail's x87 operand order.
__declspec(noinline) void ProjectPoints_510f0(const FVector &Axis, const FVector *Points, FLOAT &Min, FLOAT &Max)
{
    FLOAT Dots[4];
    Dots[0] = Points[0] | Axis;
    Dots[1] = Points[1].X * Axis.X + Points[1].Y * Axis.Y + Points[1].Z * Axis.Z;
    Dots[2] = Points[2].X * Axis.X + Points[2].Y * Axis.Y + Points[2].Z * Axis.Z;
    Dots[3] = Points[3] | Axis;
    Max = Min = Dots[0];
    for (INT i = 1; i < 4; i++)
    {
        if (Dots[i] < Min)
            Min = Dots[i];
        else if (Dots[i] > Max)
            Max = Dots[i];
    }
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_50ed0(FMatrix *Out, const FRotator *R)
{
    Escape(&GMath);
    new (Out) FInverseRotationMatrix(*R);
}
void Driver_510f0(const FVector *P, const FVector *A, FLOAT *Mn, FLOAT *Mx)
{
    ProjectPoints_510f0(*A, P, *Mn, *Mx);
}
