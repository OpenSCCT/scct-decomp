// w4_item_0082.cpp -- Versus work item 0082 (RVA 0x146750-0x146a95).
// Five VC7.0 /GL + /LTCG functions:
//   0x146750  GetVertexPool (neutral name; allocates L"VertexPool")
//   0x146800  UpdateVertexPools (neutral name; ticks and frees vertex pools)
//   0x146890  FStaticMeshCollisionCheck::FStaticMeshCollisionCheck
//   0x146910  FStaticMeshPointCheck::FStaticMeshPointCheck
//   0x146a50  ExpandPlaneByCylinder (neutral name; expands FPlane by cylinder pushout)

typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned short TCHAR;
typedef unsigned __int64 QWORD;

#define NULL 0
#define MAXINT 0x7fffffff

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};

extern FMalloc *GMalloc;
extern QWORD GNextCacheID;

inline void *operator new(unsigned int Size, const TCHAR *Tag)
{
    return GMalloc->Malloc(Size, Tag);
}

inline void operator delete(void *Ptr)
{
    GMalloc->Free(Ptr);
}

// ---- Vertex pool (0x146750, 0x146800) ----

#pragma pack(push, 4)

class FVertexStream
{
public:
    virtual QWORD GetCacheId() = 0;
    virtual INT GetRevision() = 0;
    virtual INT GetStride() = 0;
    virtual INT GetSize() = 0;
};

class FVertexPool : public FVertexStream
{
public:
    QWORD CacheId;          // +0x04
    INT Size;               // +0x0c
    INT Revision;           // +0x10
    INT unk_14;             // +0x14
    FVertexStream *Stream;  // +0x18
    FVertexPool *NextPool;  // +0x1c
    INT UnusedFrames;       // +0x20

    __declspec(noinline) FVertexPool(INT InSize, FVertexPool *InNextPool);
    ~FVertexPool()
    {
        if (NextPool)
            delete NextPool;
    }

    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetStride();
    virtual INT GetSize();
};

#pragma pack(pop)

extern FVertexPool *GFirstVertexPool;
extern const TCHAR GVertexPoolTag[]; // retail 0x10c47610: L"VertexPool"

// GetVertexPool (RVA 0x146750; neutral name)
// Finds a matching or best-fit unused FVertexPool for Stream, or allocates a new one.
__declspec(noinline) FVertexPool *GetVertexPool(FVertexStream *Stream)
{
    FVertexPool *BestPool = NULL;
    INT BestSlack = MAXINT;
    INT Size = Stream->GetSize();

    for (FVertexPool *Pool = GFirstVertexPool; Pool; Pool = Pool->NextPool)
    {
        FVertexStream *PoolStream = Pool->Stream;
        INT PoolSize = Pool->GetSize();
        if (PoolSize >= Size)
        {
            if (PoolStream == NULL)
            {
                INT Slack = PoolSize - Size;
                if (!BestPool || Slack < BestSlack)
                {
                    BestPool = Pool;
                    BestSlack = Slack;
                }
            }
            else if (PoolStream == Stream)
            {
                BestPool = Pool;
                break;
            }
        }
    }

    if (!BestPool)
    {
        GFirstVertexPool = new(GVertexPoolTag) FVertexPool(Size, GFirstVertexPool);
        return GFirstVertexPool;
    }

    return BestPool;
}

class URenderDevice
{
public:
    virtual void unk_v00() = 0;
    virtual void unk_v04() = 0;
    virtual void unk_v08() = 0;
    virtual void unk_v0c() = 0;
    virtual void unk_v10() = 0;
    virtual void unk_v14() = 0;
    virtual void unk_v18() = 0;
    virtual void unk_v1c() = 0;
    virtual void unk_v20() = 0;
    virtual void unk_v24() = 0;
    virtual void unk_v28() = 0;
    virtual void unk_v2c() = 0;
    virtual void unk_v30() = 0;
    virtual void unk_v34() = 0;
    virtual void unk_v38() = 0;
    virtual void unk_v3c() = 0;
    virtual void unk_v40() = 0;
    virtual void unk_v44() = 0;
    virtual void unk_v48() = 0;
    virtual void unk_v4c() = 0;
    virtual void unk_v50() = 0;
    virtual void unk_v54() = 0;
    virtual void unk_v58() = 0;
    virtual void unk_v5c() = 0;
    virtual void unk_v60() = 0;
    virtual void unk_v64() = 0;
    virtual void unk_v68() = 0;
    virtual void unk_v6c() = 0;
    virtual void unk_v70() = 0;
    virtual void unk_v74() = 0;
    virtual void unk_v78() = 0;
    virtual void FlushResource(QWORD CacheId) = 0; // +0x7c (slot 31)
};

class UViewport
{
public:
    unsigned char unk_00[0x70];
    URenderDevice *RenDev; // +0x70
};

// UpdateVertexPools (RVA 0x146800; neutral name; LTCG: Viewport in EBX)
// Clears Stream bindings on each pool and flushes/deletes expired pools.
__declspec(noinline) void UpdateVertexPools(UViewport *Viewport);
#include "versus_vertex_pool_update.inl"

// ---- Math and StaticMesh collision (0x146890, 0x146910, 0x146a50) ----

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos) const;
};
extern FGlobalMath GMath;
__declspec(dllimport) extern const FVector GMath_Zero;
__declspec(dllimport) extern const FVector GMath_UnitX;

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix operator*(const FMatrix &Other) const;
    FPlane TransformFPlane(const FPlane &P) const; // retail 0x4fe60
    FVector TransformFVector(const FVector &P) const
    {
        return TransformFPlane(FPlane(P.X, P.Y, P.Z, 1.0f));
    }
};

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FBox
{
    FVector Min, Max;
    FBox() {}
    FBox(const FVector &InMin, const FVector &InMax); // retail 0x81ad0
    FBox &operator+=(const FVector &Other);           // retail 0x4f820
    FBox TransformBy(const FMatrix &M) const;         // retail 0x50da0
    const FVector &GetExtrema(INT i) const { return (&Min)[i]; }
    FVector GetExtent() const
    {
        return (Max - Min) * 0.5f;
    }
};

struct FCheckResult;

class AActor
{
public:
    FLOAT unk_00[16];           // +0x000
    unsigned char unk_40[0x40]; // +0x040
    FVector Location;           // +0x080
    unsigned char unk_8c[0x24]; // +0x08c
    FVector DrawScale3D;        // +0x0b0
    FVector PrePivot;           // +0x0bc
    unsigned char unk_c8[0x18]; // +0x0c8
    FRotator Rotation;          // +0x0e0
    unsigned char unk_ec[0x150];// +0x0ec
    FLOAT DrawScale;            // +0x23c

    FMatrix WorldToLocal() const;              // retail 0x9e3b0
    FMatrix &LocalToWorld(FMatrix &Out) const; // retail 0x9e5b0
};

class UStaticMesh
{
public:
    unsigned char unk_00[0x60];
    void *unk_60;
    unsigned char unk_64[0x84];
    void *unk_e8;
    void *unk_ec;
    void *unk_f0;
    void *unk_f4;
    void *unk_f8;
    unsigned char unk_fc[0x10];
    void *unk_10c;
    unsigned char unk_110[0x14];
    void *unk_124;
    void *unk_128;
    void *unk_12c;
    void *unk_130;
    void *unk_134;
};

extern INT GCollisionCheckTag;

class FStaticMeshCollisionCheck
{
public:
    FCheckResult *Result;    // +0x00
    AActor *Owner;           // +0x04
    UStaticMesh *StaticMesh; // +0x08
    void *unk_0c;            // +0x0c
    void *unk_10;            // +0x10
    void *unk_14;            // +0x14
    void *unk_18;            // +0x18

    __declspec(noinline) FStaticMeshCollisionCheck(
        FCheckResult *InResult,
        AActor *InOwner,
        UStaticMesh *InStaticMesh,
        UBOOL bInAlt);
};

// FStaticMeshCollisionCheck::FStaticMeshCollisionCheck (RVA 0x146890)
// LTCG: this in EAX, StaticMesh in ECX, bInAlt in EDX, Result & Owner on stack (ret 8).
__declspec(noinline) FStaticMeshCollisionCheck::FStaticMeshCollisionCheck(
    FCheckResult *InResult,
    AActor *InOwner,
    UStaticMesh *InStaticMesh,
    UBOOL bInAlt)
: Result(InResult)
, Owner(InOwner)
, StaticMesh(InStaticMesh)
, unk_0c(bInAlt ? InStaticMesh->unk_134 : InStaticMesh->unk_f8)
, unk_10(bInAlt ? InStaticMesh->unk_124 : InStaticMesh->unk_e8)
, unk_14(bInAlt ? InStaticMesh->unk_12c : InStaticMesh->unk_f0)
, unk_18(bInAlt ? InStaticMesh->unk_10c : InStaticMesh->unk_60)
{
    GCollisionCheckTag++;
}

class FStaticMeshPointCheck : public FStaticMeshCollisionCheck
{
public:
    FVector LocalLocation; // +0x1c
    FVector LocalExtent;   // +0x28
    FMatrix LocalToWorld;  // +0x34
    FLOAT BestDepth;       // +0x74

    __declspec(noinline) FStaticMeshPointCheck(
        FCheckResult *InResult,
        AActor *InOwner,
        UStaticMesh *InStaticMesh,
        UBOOL bInAlt,
        const FVector &InLocation,
        const FVector &InExtent);
};

// FStaticMeshPointCheck::FStaticMeshPointCheck (RVA 0x146910)
// LTCG: this in EBX, Result in EAX, StaticMesh in ECX, bInAlt in EDX,
// Owner, Location, Extent on stack (ret 0xc).
__declspec(noinline) FStaticMeshPointCheck::FStaticMeshPointCheck(
    FCheckResult *InResult,
    AActor *InOwner,
    UStaticMesh *InStaticMesh,
    UBOOL bInAlt,
    const FVector &InLocation,
    const FVector &InExtent)
: FStaticMeshCollisionCheck(InResult, InOwner, InStaticMesh, bInAlt)
{
    FMatrix WorldToLocal = InOwner->WorldToLocal();
    LocalLocation = WorldToLocal.TransformFVector(InLocation);
    LocalExtent = FBox(-InExtent, InExtent).TransformBy(WorldToLocal).GetExtent();
    InOwner->LocalToWorld(LocalToWorld);
    BestDepth = 100000.0f;
}

__declspec(noinline) FLOAT __cdecl FCylinderPushOut(
    const FVector &Normal, FLOAT Radius, FLOAT HalfHeight);

// ExpandPlaneByCylinder (RVA 0x146a50; neutral name)
// LTCG: Plane in ESI, Extent in EAX, hidden return FPlane* in EDI.
__declspec(noinline) FPlane ExpandPlaneByCylinder(const FPlane &Plane, const FVector &Extent)
{
    FPlane Result;
    Result.X = Plane.X;
    Result.Y = Plane.Y;
    Result.Z = Plane.Z;
    Result.W = Plane.W + FCylinderPushOut(Plane, Extent.X, Extent.Z);
    return Result;
}

// ---- Scaffolding for LTCG link, not part of the units ----
// Callees defined elsewhere in the LTCG program; bodies here only so the
// linker gives them their retail custom calling conventions.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);

// Retail 0x146650: this in ESI, InSize & InNextPool on stack (ret 8).
__declspec(noinline) FVertexPool::FVertexPool(INT InSize, FVertexPool *InNextPool)
{
    CacheId = (GNextCacheID++ * 0x100) + 0xe1;
    Size = InSize;
    unk_14 = 0;
    Stream = NULL;
    NextPool = InNextPool;
    UnusedFrames = 0;
}

// Retail 0x14a0b0: Normal in ECX, Radius & HalfHeight on stack (cdecl).
__declspec(noinline) FLOAT __cdecl FCylinderPushOut(
    const FVector &Normal, FLOAT Radius, FLOAT HalfHeight)
{
    FLOAT Sq = Normal.X * Normal.X + Normal.Y * Normal.Y + Normal.Z * Normal.Z;
    FLOAT Res = (Sq <= 0.0001f) ? 0.0f : (Normal.X * Radius + Normal.Z * HalfHeight);
    Escape(&Res);
    return Res;
}

#pragma auto_inline(off)
FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, Other.X);
        Min.Y = ::Min(Min.Y, Other.Y);
        Min.Z = ::Min(Min.Z, Other.Z);
        Max.X = ::Max(Max.X, Other.X);
        Max.Y = ::Max(Max.Y, Other.Y);
        Max.Z = ::Max(Max.Z, Other.Z);
    }
    else
    {
        Min = Max = Other;
    }
    return *this;
}

FBox::FBox(const FVector &InMin, const FVector &InMax)
    : Min(InMin), Max(InMax)
{
    Min = GMath_UnitX;
    Max = GMath_Zero;
    *this += InMin;
    *this += InMax;
}

FBox FBox::TransformBy(const FMatrix &M) const
{
    FBox NewBox(GMath_UnitX, GMath_Zero);
    for (INT i = 0; i < 2; i++)
        for (INT j = 0; j < 2; j++)
            for (INT k = 0; k < 2; k++)
                NewBox += FVector(M.TransformFPlane(FPlane(
                    FVector(GetExtrema(i).X, GetExtrema(j).Y, GetExtrema(k).Z), 1.f)));
    return NewBox;
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
    const AActor *A = this;
    FLOAT SinV, CosV;
    GMath.SinCos(A->Rotation.Yaw, &SinV, &CosV);
    FMatrix S, T, R, P;
    FLOAT *Out;
    INT i;
    Out = &S.M[0][0];
    for (i = 0; i < 16; i++) Out[i] = A->unk_00[i] / A->DrawScale3D.X + SinV;
    Out = &T.M[0][0];
    for (i = 0; i < 16; i++) Out[i] = A->unk_00[i] / A->DrawScale3D.Y + CosV;
    Out = &R.M[0][0];
    for (i = 0; i < 16; i++) Out[i] = A->unk_00[i] / A->DrawScale3D.Z;
    Out = &P.M[0][0];
    for (i = 0; i < 16; i++) Out[i] = -A->unk_00[i];
    return T * R * S * P;
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
#pragma auto_inline(on)

FVertexPool *Driver_146750(FVertexStream *Stream)
{
    Escape(&GMalloc);
    Escape(&GFirstVertexPool);
    Escape(&GNextCacheID);
    return GetVertexPool(Stream);
}

void Driver_146800(UViewport *Viewport)
{
    Escape(&GMalloc);
    Escape(&GFirstVertexPool);
    UpdateVertexPools(Viewport);
}

void Driver_146890(
    FStaticMeshCollisionCheck *Out,
    FCheckResult *R,
    AActor *O,
    UStaticMesh *M,
    UBOOL bAlt)
{
    Escape(&GCollisionCheckTag);
    new (Out) FStaticMeshCollisionCheck(R, O, M, bAlt);
}

AActor *GetActor();

void Driver_146910(
    FStaticMeshPointCheck *Out,
    FCheckResult *R,
    AActor *O,
    UStaticMesh *M,
    UBOOL bAlt,
    const FVector &Loc,
    const FVector &Ext)
{
    Escape(&GCollisionCheckTag);
    Escape(&GMath);
    Escape((void *)&GMath_Zero);
    Escape((void *)&GMath_UnitX);
    new (Out) FStaticMeshPointCheck(R, O, M, bAlt, Loc, Ext);
    FMatrix M1 = GetActor()->WorldToLocal();
    Escape(&M1);
    FMatrix M2 = GetActor()->WorldToLocal();
    Escape(&M2);
    FMatrix M3;
    O->LocalToWorld(M3);
    Escape(&M3);
}

FPlane Driver_146a50(const FPlane &P, const FVector &E)
{
    return ExpandPlaneByCylinder(P, E);
}
