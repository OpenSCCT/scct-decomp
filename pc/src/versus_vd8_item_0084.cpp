// Work item 0084: Versus RVA 0x148700-0x148bdf (3 functions, 1230 bytes)
// Static mesh extent-line collision helpers and constructor (LTCG).

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

inline FLOAT appFabs(FLOAT Value)
{
    return (FLOAT)fabs(Value);
}

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT Component(INT Index) const { return (&X)[Index]; }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FLOAT PlaneDot(const FVector &P) const { return X * P.X + Y * P.Y + Z * P.Z - W; }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FMatrix
{
    FLOAT M[4][4];
    FPlane TransformFPlane(const FPlane &P) const;  // RVA 0x4fe60
    FVector TransformFVector(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.f));
    }
    FMatrix operator*(const FMatrix &Other) const;
};

__declspec(dllimport) extern const FVector GMath_Zero;   // 0x10ccacc0
__declspec(dllimport) extern const FVector GMath_UnitX;  // 0x10ccacc4

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;

struct FBox
{
    FVector Min, Max;
    FBox() {}
    FBox(const FVector &InMin, const FVector &InMax);    // RVA 0x81ad0
    FBox &operator+=(const FVector &Other);              // RVA 0x4f820
    FBox TransformBy(const FMatrix &M) const;            // RVA 0x50da0
    FVector GetExtent() const { return (Max - Min) * 0.5f; }
};

struct FCheckResult
{
    char unk_00[0x24];
    FLOAT Time;                                          // 0x24
};

class AActor
{
public:
    char unk_00[0x80];
    FVector Location;                                    // 0x80
    char unk_8c[0x24];
    FVector DrawScale3D;                                 // 0xb0
    FVector PrePivot;                                    // 0xbc
    char unk_c8[0x18];
    FRotator Rotation;                                   // 0xe0
    char unk_ec[0x150];
    FLOAT DrawScale;                                     // 0x23c

    FMatrix WorldToLocal() const;                        // RVA 0x9e3b0
    FMatrix &LocalToWorld(FMatrix &Out) const;           // RVA 0x9e5b0
};

class UStaticMesh
{
public:
    char unk_00[0x60];
    void *MeshDataA;                                     // 0x60
    char unk_64[0x84];
    void *TrianglesA;                                    // 0xe8
    char unk_ec[0x04];
    void *VerticesA;                                     // 0xf0
    char unk_f4[0x04];
    void *NodesA;                                        // 0xf8
    char unk_fc[0x10];
    void *MeshDataB;                                     // 0x10c
    char unk_110[0x14];
    void *TrianglesB;                                    // 0x124
    char unk_128[0x04];
    void *VerticesB;                                     // 0x12c
    char unk_130[0x04];
    void *NodesB;                                        // 0x134
    UBOOL bUseAlternateCollision;                        // 0x138
};

extern INT GStaticMeshCollisionCounter;                  // 0x10c92294

struct FStaticMeshCollisionCheck
{
    FCheckResult *Result;                                // 0x00
    AActor *Owner;                                       // 0x04
    UStaticMesh *StaticMesh;                             // 0x08
    void *Nodes;                                         // 0x0c
    void *Triangles;                                     // 0x10
    void *Vertices;                                      // 0x14
    void *MeshData;                                      // 0x18

    FStaticMeshCollisionCheck(
        FCheckResult *InResult,
        AActor *InOwner,
        UStaticMesh *InStaticMesh,
        UBOOL InUseAlt);                                 // RVA 0x146890
};

struct FStaticMeshExtentLineCheck : public FStaticMeshCollisionCheck
{
    FVector LocalStart;                                  // 0x1c
    FVector LocalEnd;                                    // 0x28
    FVector LocalDir;                                    // 0x34
    FVector LocalOneOverDir;                             // 0x40
    FVector LocalExtent;                                 // 0x4c
    FVector Start;                                       // 0x58
    FVector Extent;                                      // 0x64
    FVector Delta;                                       // 0x70
    FMatrix LocalToWorld;                                // 0x7c

    FStaticMeshExtentLineCheck(
        FCheckResult *InResult,
        AActor *InOwner,
        UStaticMesh *InStaticMesh,
        UBOOL InUseAlt,
        const FVector &InStart,
        const FVector &InEnd,
        const FVector &InExtent);                        // RVA 0x148850

    UBOOL LineCheck();                                   // RVA 0x1494b0
};

// Axis-aligned clip planes (retail 0x10c73bf8 and 0x10c73c28, 3 FPlanes each).
extern FPlane PositiveAxisPlanes[3];
extern FPlane NegativeAxisPlanes[3];

extern FLOAT appSqrt(FLOAT Value);
FLOAT CylinderPushOut(const FVector &Normal, FLOAT Radius, FLOAT Height); // RVA 0x14a0b0

// RVA 0x148700 (329 bytes): test a swept cylinder against a single plane.
// Neutral name: not in symbol table.
__declspec(noinline) UBOOL TestSeparatingPlane(
    const FPlane &Plane,
    const FVector &Start,
    const FVector &Delta,
    const FVector &Extent,
    FLOAT &T0,
    FLOAT &T1,
    FVector &HitNormal,
    UBOOL &bHit)
{
    FLOAT PushOut = CylinderPushOut(Plane, Extent.X, Extent.Z);
    FLOAT StartDist = Plane.PlaneDot(Start);
    FLOAT EndDist = Plane.PlaneDot(Start + Delta);
    FLOAT Diff = StartDist - PushOut;

    if (StartDist > EndDist && Diff >= -PushOut && Diff < 0.f)
    {
        Diff = 0.f;
    }

    FLOAT Denom = StartDist - EndDist;
    if (Denom > 0.00001f)
    {
        FLOAT T = Diff / Denom;
        if (T > T0)
        {
            T0 = T;
            HitNormal = Plane;
            bHit = 1;
        }
    }
    else if (Denom < -0.00001f)
    {
        FLOAT T = Diff / Denom;
        if (T < T1)
        {
            T1 = T;
        }
    }
    else
    {
        if (StartDist > PushOut && EndDist > PushOut)
            return 0;
    }

    if (T0 < T1)
        return 1;
    return 0;
}

// RVA 0x148850 (742 bytes): FStaticMeshExtentLineCheck constructor.
__declspec(noinline) FStaticMeshExtentLineCheck::FStaticMeshExtentLineCheck(
    FCheckResult *InResult,
    AActor *InOwner,
    UStaticMesh *InStaticMesh,
    UBOOL InUseAlt,
    const FVector &InStart,
    const FVector &InEnd,
    const FVector &InExtent)
    : FStaticMeshCollisionCheck(InResult, InOwner, InStaticMesh, InUseAlt)
    , Start(InStart)
    , Extent(InExtent)
    , Delta(InEnd - InStart)
{
    InResult->Time = 1.f;

    FMatrix WorldToLocal = InOwner->WorldToLocal();
    InOwner->LocalToWorld(LocalToWorld);

    LocalExtent = FBox(-InExtent, InExtent).TransformBy(WorldToLocal).GetExtent();

    LocalStart = WorldToLocal.TransformFVector(InStart);
    LocalEnd = WorldToLocal.TransformFVector(InEnd);
    LocalDir = LocalEnd - LocalStart;

    if (appFabs(LocalDir.X) < 0.000001f)
        LocalDir.X = (LocalDir.X < 0.f) ? -0.000001f : 0.000001f;
    if (appFabs(LocalDir.Y) < 0.000001f)
        LocalDir.Y = (LocalDir.Y < 0.f) ? -0.000001f : 0.000001f;
    if (appFabs(LocalDir.Z) < 0.000001f)
        LocalDir.Z = (LocalDir.Z < 0.f) ? -0.000001f : 0.000001f;

    LocalOneOverDir = FVector(1.f / LocalDir.X, 1.f / LocalDir.Y, 1.f / LocalDir.Z);
}

// RVA 0x148b40 (159 bytes): test a swept cylinder against 3 box face planes.
// Neutral name: not in symbol table.
__declspec(noinline) UBOOL TestBoxAxes(
    const FVector &Start,
    const FVector &Delta,
    const FVector &Extent,
    const FBox &Box,
    const FVector &StartToCenter,
    FLOAT &T0,
    FLOAT &T1,
    FVector &HitNormal,
    UBOOL &bHit)
{
    for (INT i = 0; i < 3; i++)
    {
        FPlane *Plane;
        if (StartToCenter.Component(i) > 0.f)
        {
            PositiveAxisPlanes[i].W = Box.Max.Component(i);
            Plane = &PositiveAxisPlanes[i];
        }
        else
        {
            NegativeAxisPlanes[i].W = -Box.Min.Component(i);
            Plane = &NegativeAxisPlanes[i];
        }
        if (!TestSeparatingPlane(*Plane, Start, Delta, Extent, T0, T1, HitNormal, bHit))
            return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// Out-of-item LTCG callee definitions and link scaffolding, not part of the unit.
// ---------------------------------------------------------------------------

// Helper RVA 0x14a0b0 (not part of this item), defined noinline so LTCG uses
// its retail convention (Normal in ECX, Radius and Height on the stack, ret).
__declspec(noinline) FLOAT CylinderPushOut(const FVector &Normal, FLOAT Radius, FLOAT Height)
{
    FLOAT X2 = Normal.X * Normal.X;
    FLOAT Y2 = Normal.Y * Normal.Y;
    FLOAT Z2 = Normal.Z * Normal.Z;
    if (X2 + Y2 + Z2 < 0.0001f)
        return 0.f;
    FLOAT AbsZ = Normal.Z < 0.f ? -Normal.Z : Normal.Z;
    if (AbsZ >= 0.9999f)
        return Height;
    FLOAT InvXY = 1.f / appSqrt(X2 + Y2);
    return (X2 * InvXY + Y2 * InvXY) * Radius + AbsZ * Height;
}

// RVA 0x4f820 (published in versus_vd3_item_0307.cpp).
__declspec(noinline) FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, Other.X); Min.Y = ::Min(Min.Y, Other.Y); Min.Z = ::Min(Min.Z, Other.Z);
        Max.X = ::Max(Max.X, Other.X); Max.Y = ::Max(Max.Y, Other.Y); Max.Z = ::Max(Max.Z, Other.Z);
    }
    else
    {
        Min = Max = Other;
    }
    return *this;
}

// RVA 0x81ad0 (published in versus_vd3_item_0307.cpp).
__declspec(noinline) FBox::FBox(const FVector &InMin, const FVector &InMax)
    : Min(InMin), Max(InMax)
{
    Min = GMath_UnitX;
    Max = GMath_Zero;
    *this += InMin;
    *this += InMax;
}

// RVA 0x50da0 (FBox::TransformBy): defined so LTCG gives it retail's stack-args ret 0xc convention.
__declspec(noinline) FBox FBox::TransformBy(const FMatrix &M) const
{
    FBox NewBox;
    NewBox.Min = GMath_UnitX;
    NewBox.Max = GMath_Zero;
    for (INT x = 0; x < 2; x++)
        for (INT y = 0; y < 2; y++)
            for (INT z = 0; z < 2; z++)
                NewBox += M.TransformFVector(FVector((&Min)[x].X, (&Min)[y].Y, (&Min)[z].Z));
    return NewBox;
}

// RVA 0x146890 (FStaticMeshCollisionCheck ctor): defined so LTCG gives it retail's convention.
__declspec(noinline) FStaticMeshCollisionCheck::FStaticMeshCollisionCheck(
    FCheckResult *InResult,
    AActor *InOwner,
    UStaticMesh *InStaticMesh,
    UBOOL InUseAlt)
{
    Result = InResult;
    Owner = InOwner;
    StaticMesh = InStaticMesh;
    Nodes = InUseAlt ? InStaticMesh->NodesB : InStaticMesh->NodesA;
    Triangles = InUseAlt ? InStaticMesh->TrianglesB : InStaticMesh->TrianglesA;
    Vertices = InUseAlt ? InStaticMesh->VerticesB : InStaticMesh->VerticesA;
    MeshData = InUseAlt ? InStaticMesh->MeshDataB : InStaticMesh->MeshDataA;
    GStaticMeshCollisionCounter++;
}

// Stand-in for RVA 0x9e3b0 (AActor::WorldToLocal): this in EAX, hidden return on stack (ret 4).
extern FMatrix MakeTranslationMatrix(const FVector &V);
extern FMatrix MakeScaleMatrix(const FVector &V);
extern FMatrix MakeInverseRotationMatrix(const FRotator &R);
__declspec(noinline) FMatrix AActor::WorldToLocal() const
{
    FVector InvScale(1.f / DrawScale3D.X, 1.f / DrawScale3D.Y, 1.f / DrawScale3D.Z);
    FLOAT InvDrawScale = 1.f / DrawScale;
    InvScale = InvScale * InvDrawScale;
    FMatrix T1 = MakeTranslationMatrix(-Location);
    FMatrix R = MakeInverseRotationMatrix(Rotation);
    FMatrix S = MakeScaleMatrix(InvScale);
    FMatrix T2 = MakeTranslationMatrix(PrePivot);
    return T1 * R * S * T2;
}

// Stand-in for RVA 0x9e5b0 (AActor::LocalToWorld): this in EDI, Out in ESI (ret).
__declspec(noinline) FMatrix &AActor::LocalToWorld(FMatrix &Result) const
{
    FLOAT SY, CY, SP, CP, SR, CR;
    GMath.SinCos(Rotation.Yaw, &SY, &CY);
    GMath.SinCos(Rotation.Pitch, &SP, &CP);
    GMath.SinCos(Rotation.Roll, &SR, &CR);
    FVector Scale = DrawScale3D * DrawScale;
    Result.M[0][0] = CP * CY * Scale.X;
    Result.M[0][1] = CP * SY * Scale.X;
    Result.M[0][2] = SP * Scale.X;
    Result.M[0][3] = 0.f;
    Result.M[1][0] = (SR * SP * CY - CR * SY) * Scale.Y;
    Result.M[1][1] = (SR * SP * SY + CR * CY) * Scale.Y;
    Result.M[1][2] = -SR * CP * Scale.Y;
    Result.M[1][3] = 0.f;
    Result.M[2][0] = -(CR * SP * CY + SR * SY) * Scale.Z;
    Result.M[2][1] = (CY * SR - CR * SP * SY) * Scale.Z;
    Result.M[2][2] = CR * CP * Scale.Z;
    Result.M[2][3] = 0.f;
    Result.M[3][0] = Location.X - PrePivot.X;
    Result.M[3][1] = Location.Y - PrePivot.Y;
    Result.M[3][2] = Location.Z - PrePivot.Z;
    Result.M[3][3] = 1.f;
    return Result;
}

void Escape(void *);

UBOOL Driver_148700(
    const FVector *V0,
    const FVector *V1,
    const FVector *Start,
    const FVector *Delta,
    const FVector *Extent,
    const FPlane *Planes,
    FLOAT *T0,
    FLOAT *T1,
    FVector *HitNormal)
{
    Escape(PositiveAxisPlanes);
    Escape(NegativeAxisPlanes);
    FBox Box;
    Box.Min = *V0;
    Box.Max = *V1;
    FVector Center((Box.Min.X + Box.Max.X) * 0.5f, (Box.Min.Y + Box.Max.Y) * 0.5f, (Box.Min.Z + Box.Max.Z) * 0.5f);
    FVector StartToCenter = *Start - Center;
    UBOOL bHit = 0;
    if (!TestBoxAxes(*Start, *Delta, *Extent, Box, StartToCenter, *T0, *T1, *HitNormal, bHit))
        return 0;
    for (INT i = 0; i < 6; i++)
    {
        if (!TestSeparatingPlane(Planes[i], *Start, *Delta, *Extent, *T0, *T1, *HitNormal, bHit))
            return 0;
    }
    return bHit;
}

UBOOL Driver_148850(
    FCheckResult *Result,
    AActor *Owner,
    UStaticMesh *StaticMesh,
    const FVector *Start,
    const FVector *End,
    const FVector *Extent)
{
    Escape((void *)&GMath_Zero);
    Escape((void *)&GMath_UnitX);
    Escape(&GMath);
    Escape(&GStaticMeshCollisionCounter);
    FStaticMeshExtentLineCheck Check(
        Result,
        Owner,
        StaticMesh,
        StaticMesh->bUseAlternateCollision,
        *Start,
        *End,
        *Extent);
    return Check.LineCheck();
}
