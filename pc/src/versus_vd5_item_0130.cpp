// Work item w3 0130: Versus RVA 0xbe310-0xbe861 (LTCG unit).
// Bone rotation helpers: each takes a bone FCoords, rotates it about an
// axis in its transposed (inverse-rotation) frame and writes the three axes
// back, plus the dispatcher at 0xbe620 that picks which rotations to apply.
// USkeletalMeshInstance::GetFrame calls the dispatcher once for each bone.
// The helper names and the names of the two rotation axes describe their operations.
typedef int INT;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, cos, fabs)

#define PI (3.1415926535897932f)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT appCos(FLOAT F) { return (FLOAT)cos(F); }
inline FLOAT Abs(FLOAT F) { return (FLOAT)fabs(F); }
inline FLOAT Square(FLOAT F) { return F * F; }
inline FLOAT Sgn(FLOAT A) { return A < 0.f ? -1.f : (A > 0.f ? 1.f : 0.f); }

struct FCoords;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector TransformVectorBy(const FCoords &Coords) const;
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
    FCoords Transpose() const;
    FCoords &RotateAxis_50920(const FVector &Axis, FLOAT Angle);
};

extern const FVector &GMath_Zero;   // 0x10ccacc0
extern const FVector &GMath_UnitZ;  // 0x10ccacbc

// RVA 0x40ab0 (item 0154).
void TransformVector_40ab0(const FCoords &Coords, const FVector &V, FVector &Result);

inline FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Result;
    TransformVector_40ab0(Coords, *this, Result);
    return Result;
}

// RVA 0x92c40 (restated so the LTCG link gives it its retail register form).
FCoords FCoords::Transpose() const
{
    return FCoords
    (
        -Origin.TransformVectorBy(*this),
        FVector(XAxis.X, YAxis.X, ZAxis.X),
        FVector(XAxis.Y, YAxis.Y, ZAxis.Y),
        FVector(XAxis.Z, YAxis.Z, ZAxis.Z)
    );
}

// RVA 0x50920 (restated, item 0205). The callers here only match with Axis
// before Angle in the parameter list (the argument evaluation order shows it).
FCoords &FCoords::RotateAxis_50920(const FVector &Axis, FLOAT Angle)
{
    FLOAT A = Angle - (INT)(Angle * (1.f / (2.f * PI))) * (2.f * PI);
    FLOAT C = appCos(Angle);
    FLOAT S = (Abs(A) < PI ? Sgn(A) : -Sgn(A)) * appSqrt(1.f - C * C);
    FLOAT OMC = 1.f - C;
    FCoords R;
    R.Origin = GMath_Zero;
    FLOAT XX = Square(Axis.X);
    R.XAxis.X = (1.f - XX) * C + XX;
    R.XAxis.Y = Axis.Y * Axis.X * OMC + S * Axis.Z;
    R.XAxis.Z = Axis.Z * Axis.X * OMC - S * Axis.Y;
    R.YAxis.X = Axis.Y * Axis.X * OMC - S * Axis.Z;
    FLOAT YY = Square(Axis.Y);
    R.YAxis.Y = (1.f - YY) * C + YY;
    R.YAxis.Z = Axis.Z * Axis.Y * OMC + S * Axis.X;
    R.ZAxis.X = Axis.Z * Axis.X * OMC + S * Axis.Y;
    R.ZAxis.Y = Axis.Z * Axis.Y * OMC - S * Axis.X;
    FLOAT ZZ = Square(Axis.Z);
    R.ZAxis.Z = (1.f - ZZ) * C + ZZ;
    *this *= R;
    return *this;
}

// The mesh instance keeps a bone coordinate array at 0xb4, two rotation
// axes (0x338, 0x344) and a block of angle parameters (0x2e0-0x304).
class UMesh;

class USkeletalMeshInstance
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual UMesh *GetMesh();  // vtable +0x80

    char Pad0[0xb4 - 4];
    FCoords *BonePose;        // 0xb4
    char Pad1[0x2e0 - 0xb8];
    FLOAT Param2E0;         // 0x2e0
    FLOAT Param2E4;         // 0x2e4
    FLOAT Param2E8;         // 0x2e8
    FLOAT Param2EC;         // 0x2ec
    FLOAT Param2F0;         // 0x2f0
    FLOAT Param2F4;         // 0x2f4
    FLOAT Param2F8;         // 0x2f8
    FLOAT Param2FC;         // 0x2fc
    FLOAT Param300;         // 0x300
    FLOAT Param304;         // 0x304
    char Pad2[0x338 - 0x308];
    FVector Axis338;        // 0x338
    FVector Axis344;        // 0x344

    void SetAxes(INT Index, const FCoords &C)
    {
        BonePose[Index].XAxis = C.XAxis;
        BonePose[Index].YAxis = C.YAxis;
        BonePose[Index].ZAxis = C.ZAxis;
    }
    void RotateAboutFirstAxis(INT Index, FLOAT Angle);
    void RotateAboutUnitZ(INT Index, FLOAT Angle);
    void RotateAboutAxisAndZ(INT Index, FLOAT AngleA, FLOAT AngleZ);
    void RotateAboutSecondAxis(INT Index, FLOAT Angle);
    void ApplyBoneRotations(INT Index);
};

// RVA 0xbe310 (LTCG: Index in EAX, this and Angle on the stack).
void USkeletalMeshInstance::RotateAboutFirstAxis(INT Index, FLOAT Angle)
{
    FCoords C = BonePose[Index].Transpose();
    C.RotateAxis_50920(Axis338, Angle);
    C = C.Transpose();
    SetAxes(Index, C);
}

// RVA 0xbe3d0
void USkeletalMeshInstance::RotateAboutUnitZ(INT Index, FLOAT Angle)
{
    FCoords C = BonePose[Index].Transpose();
    C.RotateAxis_50920(GMath_UnitZ, Angle);
    C = C.Transpose();
    SetAxes(Index, C);
}

// RVA 0xbe490
void USkeletalMeshInstance::RotateAboutAxisAndZ(INT Index, FLOAT AngleA, FLOAT AngleZ)
{
    FCoords C = BonePose[Index].Transpose();
    C.RotateAxis_50920(Axis338, AngleA);
    C.RotateAxis_50920(GMath_UnitZ, AngleZ);
    C = C.Transpose();
    SetAxes(Index, C);
}

// RVA 0xbe560
void USkeletalMeshInstance::RotateAboutSecondAxis(INT Index, FLOAT Angle)
{
    FCoords C = BonePose[Index].Transpose();
    C.RotateAxis_50920(Axis344, Angle);
    C = C.Transpose();
    SetAxes(Index, C);
}

// RVA 0xbe620 (LTCG: this in ESI, Index in EDI).
void USkeletalMeshInstance::ApplyBoneRotations(INT Index)
{
    GetMesh();
    switch (Index)
    {
    case 4:
        if (Param300 != 0.f || Param304 != 0.f)
            RotateAboutAxisAndZ(Index, Param304, Param300);
        // fall through
    case 5:
        if (Param2E8 != 0.f)
            RotateAboutFirstAxis(Index, Param2E8 * 0.5f);
        break;
    case 6:
        if (Param2E0 != 0.f || Param2E4 != 0.f)
            RotateAboutAxisAndZ(Index, Param2E4, Param2E0);
        else if (Param2EC != 0.f)
            RotateAboutSecondAxis(Index, Param2EC);
        else if (Param2F0 != 0.f || Param2F4 != 0.f)
            RotateAboutAxisAndZ(Index, Param2F4 * 0.5f, Param2F0 * 0.5f);
        else if (Param2F8 != 0.f || Param2FC != 0.f)
            RotateAboutAxisAndZ(Index, Param2FC * 0.5f, Param2F8 * 0.5f);
        break;
    case 21:
        if (Param2F0 != 0.f || Param2F4 != 0.f)
            RotateAboutAxisAndZ(Index, Param2F4, Param2F0);
        break;
    case 23:
        if (Param2F8 != 0.f || Param2FC != 0.f)
            RotateAboutAxisAndZ(Index, Param2FC, Param2F8 * 0.33333f);
        break;
    case 24:
        if (Param2F8 != 0.f)
            RotateAboutUnitZ(Index, Param2F8 * 0.66666f);
        break;
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_be620(USkeletalMeshInstance *O, INT Index)
{
    O->ApplyBoneRotations(Index);
}
