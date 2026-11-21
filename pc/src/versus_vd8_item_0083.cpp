// Work item 0083: Versus RVA 0x147e00-0x148087 (2 functions, 645 bytes).
// UnStaticMeshCollision.cpp (Unreal Engine 2), compiled with VC7.0 /GL and linked /LTCG:
//   0x147e00: FLinePlaneIntersection (out-of-line copy)
//   0x147e80: FStaticMeshLineCheck::FStaticMeshLineCheck

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline FLOAT appFabs(FLOAT F) { return (FLOAT)fabs(F); }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FPlane TransformFPlane(const FPlane &P) const;
    FVector TransformFVector(const FVector &V) const
    {
        return FVector(TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.0f)));
    }
    FMatrix operator*(const FMatrix &Other) const;
};

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *S, FLOAT *C);
};
extern FGlobalMath GMath;

class AActor
{
public:
    BYTE unk_0[0x80];
    FVector Location;          // +0x80
    BYTE unk_8c[0xb0 - 0x8c];
    FVector DrawScale3D;       // +0xb0
    FVector PrePivot;          // +0xbc
    BYTE unk_c8[0xe0 - 0xc8];
    FRotator Rotation;         // +0xe0
    BYTE unk_ec[0x23c - 0xec];
    FLOAT DrawScale;           // +0x23c
    FMatrix &LocalToWorld(FMatrix &Out) const;
    FMatrix WorldToLocal() const;
};

class UStaticMesh
{
public:
    BYTE unk_0[0x60];
    void *CollisionData0;      // +0x60
    BYTE unk_64[0xe8 - 0x64];
    void *Triangles0;          // +0xe8
    BYTE unk_ec[0xf0 - 0xec];
    void *Vertices0;           // +0xf0
    BYTE unk_f4[0xf8 - 0xf4];
    void *Nodes0;              // +0xf8
    BYTE unk_fc[0x10c - 0xfc];
    void *CollisionData1;      // +0x10c
    BYTE unk_110[0x124 - 0x110];
    void *Triangles1;          // +0x124
    BYTE unk_128[0x12c - 0x128];
    void *Vertices1;           // +0x12c
    BYTE unk_130[0x134 - 0x130];
    void *Nodes1;              // +0x134
};

struct FCheckResult
{
    FCheckResult *GetNext;     // +0x00
    AActor *Actor;             // +0x04
    FVector Location;          // +0x08
    FVector Normal;            // +0x14
    void *Primitive;           // +0x20
    FLOAT Time;                // +0x24
};

extern INT GStaticMeshCollisionCounter; // retail 0x10c92294

struct FStaticMeshCollisionCheck
{
    FCheckResult *Result;      // +0x00
    AActor *Owner;             // +0x04
    UStaticMesh *StaticMesh;   // +0x08
    void *Nodes;               // +0x0c
    void *Triangles;           // +0x10
    void *Vertices;            // +0x14
    void *CollisionData;       // +0x18

    FStaticMeshCollisionCheck(FCheckResult *InResult, AActor *InOwner, UStaticMesh *InStaticMesh, UBOOL InUseAlt);
};

struct FStaticMeshLineCheck : public FStaticMeshCollisionCheck
{
    FVector LocalStart;        // +0x1c
    FVector LocalEnd;          // +0x28
    FVector LocalDir;          // +0x34
    FVector LocalOneOverDir;   // +0x40
    FMatrix LocalToWorld;      // +0x4c

    FStaticMeshLineCheck(
        FCheckResult *InResult,
        AActor *InOwner,
        UStaticMesh *InStaticMesh,
        const FVector &InStart,
        const FVector &InEnd,
        UBOOL InUseAlt
    );
};

// RVA 0x147e00: FLinePlaneIntersection (UnMath.h out-of-line copy)
FVector FLinePlaneIntersection(const FVector &Point1, const FVector &Point2, const FPlane &Plane)
{
    FVector Delta = Point2 - Point1;
    return Point1 + Delta * ((Plane.W - (Point1 | Plane)) / (Delta | Plane));
}

// RVA 0x147e80: FStaticMeshLineCheck::FStaticMeshLineCheck
FStaticMeshLineCheck::FStaticMeshLineCheck(
    FCheckResult *InResult,
    AActor *InOwner,
    UStaticMesh *InStaticMesh,
    const FVector &InStart,
    const FVector &InEnd,
    UBOOL InUseAlt
)
    : FStaticMeshCollisionCheck(InResult, InOwner, InStaticMesh, InUseAlt)
{
    InResult->Time = 1.0f;

    InOwner->LocalToWorld(LocalToWorld);
    FMatrix WorldToLocal = InOwner->WorldToLocal();

    LocalStart = WorldToLocal.TransformFVector(InStart);
    LocalEnd = WorldToLocal.TransformFVector(InEnd);
    LocalDir = LocalEnd - LocalStart;

    if (appFabs(LocalDir.X) < 0.000001f)
        LocalDir.X = (LocalDir.X < 0.0f) ? -0.000001f : 0.000001f;
    if (appFabs(LocalDir.Y) < 0.000001f)
        LocalDir.Y = (LocalDir.Y < 0.0f) ? -0.000001f : 0.000001f;
    if (appFabs(LocalDir.Z) < 0.000001f)
        LocalDir.Z = (LocalDir.Z < 0.0f) ? -0.000001f : 0.000001f;

    LocalOneOverDir = FVector(1.0f / LocalDir.X, 1.0f / LocalDir.Y, 1.0f / LocalDir.Z);
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

#pragma auto_inline(off)
FStaticMeshCollisionCheck::FStaticMeshCollisionCheck(
    FCheckResult *InResult,
    AActor *InOwner,
    UStaticMesh *InStaticMesh,
    UBOOL InUseAlt
)
{
    Result = InResult;
    Owner = InOwner;
    StaticMesh = InStaticMesh;
    Nodes = InUseAlt ? InStaticMesh->Nodes1 : InStaticMesh->Nodes0;
    Triangles = InUseAlt ? InStaticMesh->Triangles1 : InStaticMesh->Triangles0;
    Vertices = InUseAlt ? InStaticMesh->Vertices1 : InStaticMesh->Vertices0;
    CollisionData = InUseAlt ? InStaticMesh->CollisionData1 : InStaticMesh->CollisionData0;
    GStaticMeshCollisionCounter++;
}

FMatrix &AActor::LocalToWorld(FMatrix &Out) const
{
    FLOAT SY, CY, SP, CP, SR, CR;
    GMath.SinCos(Rotation.Yaw, &SY, &CY);
    GMath.SinCos(Rotation.Pitch, &SP, &CP);
    GMath.SinCos(Rotation.Roll, &SR, &CR);

    FLOAT LX = Location.X, LY = Location.Y, LZ = Location.Z;
    FLOAT PX = PrePivot.X, PY = PrePivot.Y, PZ = PrePivot.Z;
    FLOAT DX = DrawScale3D.X * DrawScale,
          DY = DrawScale3D.Y * DrawScale,
          DZ = DrawScale3D.Z * DrawScale;

    Out.M[0][3] = 0.f;
    FLOAT CPSY = CP * SY, CPCY = CP * CY;
    Out.M[0][0] = CPCY * DX;
    Out.M[0][1] = CPSY * DX;
    Out.M[0][2] = SP * DX;

    FLOAT CRSY = CR * SY, CRCY = CR * CY, SRCP = SR * CP;
    FLOAT SRCY = SR * CY, SRCYSP = SRCY * SP;
    FLOAT YY = SR * SP * SY + CRCY;
    Out.M[1][0] = (SRCYSP - CRSY) * DY;
    Out.M[1][1] = YY * DY;
    Out.M[1][2] = -(SRCP * DY);
    Out.M[1][3] = 0.f;

    FLOAT SRSY = SR * SY, CRCYSP = CRCY * SP, CRSYSP = CRSY * SP, CRCP = CR * CP;
    FLOAT ZX = CRCYSP + SRSY;
    FLOAT ZY = SRCY - CRSYSP;
    Out.M[2][0] = -(ZX * DZ);
    Out.M[2][1] = ZY * DZ;
    Out.M[2][2] = CRCP * DZ;
    Out.M[2][3] = 0.f;
    Out.M[3][3] = 1.f;

    FLOAT TX = DX * PX, TY = DY * PY, TZ = DZ * PZ;
    Out.M[3][0] = (LX - TX * CPCY) + (CRSY - SRCYSP) * TY + ZX * TZ;
    Out.M[3][1] = LY - (ZY * TZ + YY * TY + TX * CPSY);
    Out.M[3][2] = LZ - ((TX * SP - TY * SRCP) + TZ * CRCP);
    return Out;
}

FMatrix MakeMatrix(const FPlane &X, const FPlane &Y, const FPlane &Z, const FPlane &W);
FMatrix FTranslationMatrix(const FVector &V)
{
    return MakeMatrix(FPlane(1.f, 0.f, 0.f, 0.f), FPlane(0.f, 1.f, 0.f, 0.f), FPlane(0.f, 0.f, 1.f, 0.f), FPlane(V.X, V.Y, V.Z, 1.f));
}
FMatrix FScaleMatrix(const FVector &V)
{
    return MakeMatrix(FPlane(V.X, 0.f, 0.f, 0.f), FPlane(0.f, V.Y, 0.f, 0.f), FPlane(0.f, 0.f, V.Z, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
}
FMatrix FInverseRotationMatrix(const FRotator &R)
{
    FLOAT S, C;
    GMath.SinCos(-R.Yaw, &S, &C);
    FMatrix M = MakeMatrix(FPlane(C, -S, 0.f, 0.f), FPlane(S, C, 0.f, 0.f), FPlane(0.f, 0.f, 1.f, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
    GMath.SinCos(-R.Pitch, &S, &C);
    M = M * MakeMatrix(FPlane(C, 0.f, -S, 0.f), FPlane(0.f, 1.f, 0.f, 0.f), FPlane(S, 0.f, C, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
    GMath.SinCos(-R.Roll, &S, &C);
    M = M * MakeMatrix(FPlane(1.f, 0.f, 0.f, 0.f), FPlane(0.f, C, S, 0.f), FPlane(0.f, -S, C, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
    return M;
}
FMatrix FMatrix::operator*(const FMatrix &Other) const
{
    FMatrix Result;
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            Result.M[i][j] = M[i][0] * Other.M[0][j] + M[i][1] * Other.M[1][j]
                           + M[i][2] * Other.M[2][j] + M[i][3] * Other.M[3][j];
    return Result;
}
FMatrix AActor::WorldToLocal() const
{
    return FTranslationMatrix(FVector(-Location.X, -Location.Y, -Location.Z))
        * FInverseRotationMatrix(Rotation)
        * FScaleMatrix(FVector(1.f / DrawScale3D.X / DrawScale, 1.f / DrawScale3D.Y / DrawScale, 1.f / DrawScale3D.Z / DrawScale))
        * FTranslationMatrix(PrePivot);
}
#pragma auto_inline(on)

void Driver_147e00(FVector *Out, FStaticMeshLineCheck *C, const FPlane *P, INT Cond)
{
    Escape(C);
    if (Cond)
        Out[0] = FLinePlaneIntersection(C->LocalStart, C->LocalEnd, *P);
    else
        Out[1] = FLinePlaneIntersection(C->LocalStart, C->LocalEnd, *P);
}

void Driver_147e80(FCheckResult *Res, AActor *Owner, UStaticMesh *Mesh, const FVector *Start, const FVector *End, UBOOL UseAlt, INT Cond)
{
    Escape(&GStaticMeshCollisionCounter);
    Escape(&GMath);
    if (Cond)
    {
        FStaticMeshLineCheck C(Res, Owner, Mesh, *Start, *End, UseAlt);
        Escape(&C);
    }
    else
    {
        FStaticMeshLineCheck C(Res, Owner, Mesh, *End, *Start, UseAlt);
        Escape(&C);
    }
}
