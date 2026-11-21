// Work item 0077: Versus RVA 0x142f30-0x143487 (UModel::LineCheck, UModel::PointRegion).

typedef int INT;
typedef short SWORD;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;

#define INDEX_NONE -1

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}
// Out-of-line Clamp<FLOAT> (RVA 0x4f040), kept declared where retail declines to inline it.
FLOAT __cdecl Clamp_4f040(FLOAT X, FLOAT Min, FLOAT Max);

enum ENodeFlags
{
    NF_NotCsg           = 0x01,
    NF_IsNew            = 0x20,
};

enum ETraceFlags
{
    TRACE_Material      = 0x1000,
};

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
    FVector operator^(const FVector &V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    UBOOL operator==(const FVector &V) const { return X == V.X && Y == V.Y && Z == V.Z; }
    UBOOL operator!=(const FVector &V) const;
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    UBOOL Normalize(); // RVA 0x4f7a0
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + Y * P.Y + Z * P.Z - W;
    }
};

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *S, FLOAT *C) const; // RVA 0x40950
};
extern FGlobalMath GMath;
extern const FVector &GMath_One;   // 0x10ccabf8
extern const FVector &GMath_Zero;  // 0x10ccacc0
extern const FVector &GMath_UnitX; // 0x10ccacc4

struct FMatrix
{
    FLOAT M[4][4];

    FMatrix() {}
    FPlane TransformFPlane(const FPlane &P) const; // RVA 0x4fe60
    FPlane TransformNormal(const FVector &V) const; // RVA 0x9e330
    FMatrix TransposeAdjoint() const; // RVA 0x140e80
};
extern FMatrix GMatrixIdentity; // 0x10cc9560

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

class AActor
{
public:
    BYTE unk_00[0x80];
    FVector Location;           // 0x80
    BYTE unk_8c[0xb0 - 0x8c];
    FVector DrawScale3D;        // 0xb0
    FVector PrePivot;           // 0xbc
    BYTE unk_c8[0xe0 - 0xc8];
    FRotator Rotation;          // 0xe0
    BYTE unk_ec[0x23c - 0xec];
    FLOAT DrawScale;            // 0x23c

    FMatrix &LocalToWorld(FMatrix &Out) const; // RVA 0x9e5b0
};

class AZoneInfo;
class UPrimitive;
class UMaterial;

struct FCheckResult
{
    FCheckResult *GetNext;      // 0x00
    AActor *Actor;              // 0x04
    FVector Location;           // 0x08
    FVector Normal;             // 0x14
    UPrimitive *Primitive;      // 0x20
    FLOAT Time;                 // 0x24
    INT Item;                   // 0x28
    UMaterial *Material;        // 0x2c
};

struct FPointRegion
{
    AZoneInfo *Zone;
    INT iLeaf;
    BYTE ZoneNumber;

    FPointRegion() {}
    FPointRegion(AZoneInfo *InLevel)
        : Zone(InLevel), iLeaf(INDEX_NONE), ZoneNumber(0)
    {}
    FPointRegion(AZoneInfo *InLevel, INT InLeaf, BYTE InZoneNumber)
        : Zone(InLevel), iLeaf(InLeaf), ZoneNumber(InZoneNumber)
    {}
};

struct FZoneProperties
{
    AZoneInfo *ZoneActor;
    DWORD unk_04;
    DWORD unk_08;
    DWORD unk_0c;
};

struct FBspSurf
{
    FVector Plane;              // 0x00
    FLOAT unk_0c;               // 0x0c
    UMaterial *Material;        // 0x10
    BYTE unk_14[0x18];          // 0x14
};

struct FBspNode
{
    FPlane Plane;               // 0x00
    BYTE unk_10[0x18];          // 0x10
    INT iVertPool;              // 0x28
    INT iSurf;                  // 0x2c
    INT iChild[2];              // 0x30 (0 = Back, 1 = Front)
    INT iPlane;                 // 0x38
    BYTE unk_3c[0x10];          // 0x3c
    SWORD iLeaf[2];             // 0x4c
    BYTE unk_50[0x08];          // 0x50
    BYTE iZone[2];              // 0x58
    BYTE NumVertices;           // 0x5a
    BYTE NodeFlags;             // 0x5b

    UBOOL IsCsg(DWORD ExtraFlags = 0) const
    {
        return (NumVertices > 0) && !(NodeFlags & (NF_IsNew | NF_NotCsg | ExtraFlags));
    }
};

class UModel
{
public:
    BYTE unk_04[0x50];
    TArray<FBspNode> Nodes;         // 0x54
    BYTE unk_60[0x04];
    TArray<SWORD> Verts;            // 0x64
    BYTE unk_70[0x14];
    TArray<FVector> Points;         // 0x84
    BYTE unk_90[0x04];
    TArray<FBspSurf> Surfs;         // 0x94
    BYTE unk_a0[0x64];
    UBOOL RootOutside;              // 0x104
    BYTE unk_108[0x0c];
    TArray<FZoneProperties> Zones;  // 0x114

    AZoneInfo *GetZoneActor(INT i) const
    {
        return (i < Zones.Num()) ? Zones(i).ZoneActor : 0;
    }

    virtual UBOOL LineCheck(
        FCheckResult &Result,
        AActor *Owner,
        const FVector &End,
        const FVector &Start,
        const FVector &Extent,
        DWORD ExtraNodeFlags,
        DWORD TraceFlags
    );
    FPointRegion PointRegion(AZoneInfo *Zone, const FVector &Location) const;
};

extern UBOOL GModelLineCheckHit; // 0x10c8bc08

// RVA 0x141f40: standard __cdecl BSP fast line check.
UBOOL __cdecl FastLineCheck_141f40(
    FCheckResult *Hit,
    UModel *Model,
    FMatrix *LocalToWorld,
    INT iNode,
    INT iParent,
    const FVector &End,
    FVector Start,
    UBOOL Outside,
    DWORD ExtraNodeFlags
);

// RVA 0x142da0: coplanar polygon hit-node lookup.
INT __cdecl FindHitNode_142da0(UModel *Model, const FVector &Location, INT iNode);

struct FBoxFilter
{
    FCheckResult *Hit;          // 0x00
    UModel *Model;              // 0x04
    AActor *Owner;              // 0x08
    FMatrix LocalToWorld;       // 0x0c
    FVector Extent;             // 0x4c
    DWORD ExtraNodeFlags;       // 0x58
    BYTE unk_5c[0x10];          // 0x5c
    FVector Axis;               // 0x6c
    FVector Origin;             // 0x78
    BYTE unk_84[0x08];          // 0x84
    FMatrix LocalToWorldTA;     // 0x8c
    BYTE unk_cc[0x5d0 - 0xcc];  // 0xcc

    FBoxFilter(FCheckResult &InHit, UModel *InModel, AActor *InOwner, FVector InExtent, DWORD InExtraNodeFlags); // RVA 0x1410d0
};

struct FLineCheckFilter : public FBoxFilter
{
    FVector End;                // 0x5d0
    FVector Start;              // 0x5dc
    FLOAT Dist;                 // 0x5e8
    UBOOL bHit;                 // 0x5ec
    INT iHitNode;               // 0x5f0

    FLineCheckFilter(
        FCheckResult &InHit,
        UModel *InModel,
        AActor *InOwner,
        const FVector &InEnd,
        const FVector &InStart,
        const FVector &InExtent,
        DWORD InExtraNodeFlags
    ); // RVA 0x1423d0

    void Filter(INT iNode, INT iParent, INT iOutside, UBOOL Outside); // RVA 0x142620
};

// RVA 0x142f30: UModel::LineCheck (vtable slot 23 of UModel).
UBOOL UModel::LineCheck(
    FCheckResult &Hit,
    AActor *Owner,
    const FVector &End,
    const FVector &Start,
    const FVector &Extent,
    DWORD ExtraNodeFlags,
    DWORD TraceFlags
)
{
    if (Nodes.Num())
    {
        if (Extent == GMath_Zero)
        {
            FMatrix LocalToWorld;
            UBOOL Result;
            GModelLineCheckHit = 0;
            if (Owner)
            {
                Owner->LocalToWorld(LocalToWorld);
                Result = FastLineCheck_141f40(&Hit, this, &LocalToWorld, 0, 0, End, Start, RootOutside, ExtraNodeFlags);
            }
            else
            {
                Result = FastLineCheck_141f40(&Hit, this, 0, 0, 0, End, Start, RootOutside, ExtraNodeFlags);
            }

            if (!Result)
            {
                FVector Delta = End - Start;
                FLOAT DeltaSizeSq = Delta.SizeSquared();
                Hit.Time = ((Hit.Location - Start) | Delta) / DeltaSizeSq;
                Hit.Time = Clamp(Hit.Time - 0.5f / appSqrt(DeltaSizeSq), 0.f, 1.f);
                Hit.Location = Start + Delta * Hit.Time;
                Hit.Actor = Owner;

                INT iHitNode = FindHitNode_142da0(this, Hit.Location, Hit.Item);
                if (iHitNode != INDEX_NONE)
                {
                    Hit.Item = iHitNode;
                    Hit.Normal = Nodes(iHitNode).Plane;
                }

                if ((TraceFlags & TRACE_Material) && Hit.Item != INDEX_NONE)
                    Hit.Material = Surfs(Nodes(Hit.Item).iSurf).Material;
                else
                    Hit.Material = 0;

                if (Owner)
                {
                    Hit.Normal = LocalToWorld.TransposeAdjoint().TransformNormal(Hit.Normal);
                    if (Owner->DrawScale != 1.f || Owner->DrawScale3D != GMath_One)
                        Hit.Normal.Normalize();
                }
            }
            return Result;
        }
        else
        {
            Hit.Time = 2.f;
            FLineCheckFilter Filter(Hit, this, Owner, End, Start, Extent, ExtraNodeFlags);
            Filter.Filter(0, 0, 0, RootOutside);
            if (Filter.bHit)
            {
                Hit.Time = Clamp(Hit.Time - Clamp_4f040(0.01f, 0.01f / Filter.Dist, 0.1f / Filter.Dist), 0.f, 1.f);
                Hit.Location = Start + (End - Start) * Hit.Time;
                return Hit.Time == 1.f;
            }
            return 1;
        }
    }
    return RootOutside;
}

// RVA 0x143370: UModel::PointRegion
__declspec(noinline) FPointRegion UModel::PointRegion(AZoneInfo *Zone, const FVector &Location) const
{
    FPointRegion Result(Zone);
    if (Nodes.Num())
    {
        INT iNode = 0;
        INT iPrevNode = 0;
        INT IsFront = 0;
        UBOOL Outside = RootOutside;
        while (iNode != INDEX_NONE)
        {
            const FBspNode &Node = Nodes(iNode);
            IsFront = Node.Plane.PlaneDot(Location) >= 0.f;
            Outside = IsFront ? (Outside || Node.IsCsg()) : (Outside && !Node.IsCsg());
            iPrevNode = iNode;
            iNode = Node.iChild[IsFront];
        }

        Result.iLeaf = Nodes(iPrevNode).iLeaf[IsFront];
        Result.ZoneNumber = Zones.Num() ? Nodes(iPrevNode).iZone[IsFront] : 0;
        Result.Zone = GetZoneActor(Result.ZoneNumber) ? GetZoneActor(Result.ZoneNumber) : Zone;
    }
    return Result;
}

// ---- Out-of-line LTCG callees of UModel::LineCheck (so the linker assigns their retail conventions) ----

// RVA 0x92e40 (from versus_vd3_item_0339.cpp): LTCG this in EDX, V in ECX.
__declspec(noinline) UBOOL FVector::operator!=(const FVector &V) const
{
    return X != V.X || Y != V.Y || Z != V.Z;
}

// RVA 0x9e330 (UE2 FMatrix::TransformNormal): LTCG result in ESI, V in EAX, this on stack.
__declspec(noinline) FPlane FMatrix::TransformNormal(const FVector &V) const
{
    return TransformFPlane(FPlane(V.X, V.Y, V.Z, 0.f));
}

// RVA 0x9e5b0 (from versus_vd4_item_0361.cpp): LTCG this in EDI, Out in ESI.
__declspec(noinline) FMatrix &AActor::LocalToWorld(FMatrix &Out) const
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

// RVA 0x1410d0: FBoxFilter::FBoxFilter
__declspec(noinline) FBoxFilter::FBoxFilter(FCheckResult &InHit, UModel *InModel, AActor *InOwner, FVector InExtent, DWORD InExtraNodeFlags)
    : Hit(&InHit)
    , Model(InModel)
    , Owner(InOwner)
    , Extent(InExtent)
    , ExtraNodeFlags(InExtraNodeFlags)
    , Axis(GMath_UnitX)
    , Origin(GMath_Zero)
{
    if (Owner)
    {
        Owner->LocalToWorld(LocalToWorld);
        LocalToWorldTA = LocalToWorld.TransposeAdjoint();
    }
    else
    {
        LocalToWorldTA = GMatrixIdentity;
        LocalToWorld = LocalToWorldTA;
    }
}

// RVA 0x140e80: FMatrix::TransposeAdjoint (LTCG: this in ECX, result in EAX).
__declspec(noinline) FMatrix FMatrix::TransposeAdjoint() const
{
    FMatrix TA;
    TA.M[0][0] = M[1][1] * M[2][2] - M[1][2] * M[2][1];
    TA.M[0][1] = M[1][2] * M[2][0] - M[1][0] * M[2][2];
    TA.M[0][2] = M[1][0] * M[2][1] - M[1][1] * M[2][0];
    TA.M[0][3] = 0.f;

    TA.M[1][0] = M[2][1] * M[0][2] - M[2][2] * M[0][1];
    TA.M[1][1] = M[2][2] * M[0][0] - M[2][0] * M[0][2];
    TA.M[1][2] = M[2][0] * M[0][1] - M[2][1] * M[0][0];
    TA.M[1][3] = 0.f;

    TA.M[2][0] = M[0][1] * M[1][2] - M[0][2] * M[1][1];
    TA.M[2][1] = M[0][2] * M[1][0] - M[0][0] * M[1][2];
    TA.M[2][2] = M[0][0] * M[1][1] - M[0][1] * M[1][0];
    TA.M[2][3] = 0.f;

    TA.M[3][0] = 0.f;
    TA.M[3][1] = 0.f;
    TA.M[3][2] = 0.f;
    TA.M[3][3] = 1.f;
    return TA;
}

// RVA 0x1423d0: FLineCheckFilter::FLineCheckFilter.
__declspec(noinline) FLineCheckFilter::FLineCheckFilter(
    FCheckResult &InHit,
    UModel *InModel,
    AActor *InOwner,
    const FVector &InEnd,
    const FVector &InStart,
    const FVector &InExtent,
    DWORD InExtraNodeFlags
)
    : FBoxFilter(InHit, InModel, InOwner, InExtent, InExtraNodeFlags)
{
    End = InEnd;
    Start = InStart;
    Dist = (InEnd - InStart).Size();
    bHit = 0;
    iHitNode = INDEX_NONE;
}

// RVA 0x142da0: FindHitNode_142da0 (LTCG: Model in EAX, Location in EBX, iNode on stack).
__declspec(noinline) INT __cdecl FindHitNode_142da0(UModel *Model, const FVector &Location, INT iNode)
{
    if (iNode != INDEX_NONE)
    {
        FBspNode *Nodes = &Model->Nodes(0);
        FBspSurf *Surfs = &Model->Surfs(0);
        SWORD *Verts = &Model->Verts(0);
        FVector *Points = &Model->Points(0);

        while (iNode != INDEX_NONE)
        {
            FBspNode &Node = Nodes[iNode];
            FVector *V0 = &Points[Verts[Node.iVertPool + Node.NumVertices - 1]];
            FBspSurf &Surf = Surfs[Node.iSurf];
            FLOAT PrevDot = 0.f;
            for (INT i = 0; i < Node.NumVertices; i++)
            {
                FVector *V1 = &Points[Verts[Node.iVertPool + i]];
                FVector EdgeNormal = (*V1 - *V0) ^ Surf.Plane;
                FLOAT Dot = (EdgeNormal | Location) - (EdgeNormal | *V1);
                if ((Dot < 0.f && PrevDot > 0.f) || (Dot > 0.f && PrevDot < 0.f))
                    goto NextNode;
                PrevDot = Dot;
                V0 = V1;
            }
            return iNode;
        NextNode:
            iNode = Node.iPlane;
        }
    }
    return INDEX_NONE;
}

// Scaffolding for the LTCG link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void UseMatrix(const FMatrix &M);
void Driver_143370(const UModel *M, AZoneInfo *Z, const FVector *Loc)
{
    FPointRegion R1 = M->PointRegion(Z, *Loc);
    Escape(&R1);
    FPointRegion R2 = M[1].PointRegion(Z, Loc[1]);
    Escape(&R2);
    FPointRegion R3 = M[2].PointRegion(Z, Loc[2]);
    Escape(&R3);
}
void Driver_142f30(
    void *ModelMem,
    UModel *M,
    FCheckResult *Hit,
    AActor *Owner,
    const FVector *End,
    const FVector *Start,
    const FVector *Extent,
    DWORD ExtraNodeFlags,
    DWORD TraceFlags
)
{
    Escape(&GModelLineCheckHit);
    Escape(&GMath);
    Escape((void *)&GMath_Zero);
    Escape((void *)&GMath_One);
    Escape((void *)&GMath_UnitX);
    Escape(&GMatrixIdentity);
    Escape(new (ModelMem) UModel);
    FMatrix M1, M2;
    UseMatrix(Owner->LocalToWorld(M1));
    UseMatrix(Owner[1].LocalToWorld(M2));
    Escape((void *)(*End != *Start));
    Escape((void *)(*Start != *Extent));
    Escape((void *)(*Extent != *End));
    M->LineCheck(*Hit, Owner, *End, *Start, *Extent, ExtraNodeFlags, TraceFlags);
}
