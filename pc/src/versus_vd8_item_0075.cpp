// Work item 0075: Versus RVA 0x141f40-0x142476.
// BSP model collision (UnModel.cpp), compiled with VC7.0 /GL and linked with /LTCG:
// FastLineCheck (0x141f40) and FBoxLineCheck::FBoxLineCheck (0x1423d0).

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef double DOUBLE;
typedef int UBOOL;

#define INDEX_NONE (-1)

#define NF_NotCsg          0x01
#define NF_NotVisBlocking  0x20
#define NF_IgnoreInitSolid 0x10

extern "C" DOUBLE __cdecl sqrt(DOUBLE X);
#pragma intrinsic(sqrt)

DOUBLE appSqrt(DOUBLE Value)
{
    return sqrt(Value);
}

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}

    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FLOAT Size() const;
    FVector SafeNormal() const;
};

FLOAT FVector::Size() const
{
    FLOAT Result = (FLOAT)appSqrt(X * X + Y * Y + Z * Z);
    return Result;
}

struct FMatrix;

struct FPlane : public FVector
{
    FLOAT W;

    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}

    FLOAT PlaneDot(const FVector &P) const { return X * P.X + Y * P.Y + Z * P.Z - W; }
    FPlane TransformByUsingAdjointT(const FMatrix &M, const FMatrix &TA) const;
};

struct FMatrix
{
    FLOAT M[4][4];

    static FMatrix Identity;

    FMatrix() {}
    FMatrix TransposeAdjoint() const;
    FLOAT Determinant() const;
    FPlane TransformFPlane(const FPlane &P) const;
};

extern const FVector &GMath_Zero;  // 0x10ccacc0
extern const FVector &GMath_UnitX; // 0x10ccacc4

class AActor
{
public:
    FMatrix LocalToWorld() const;
};

class UPrimitive;
class UMaterial;

struct FCheckResult
{
    FCheckResult *Next;      // +0x00
    AActor *Actor;           // +0x04
    FVector Location;        // +0x08
    FVector Normal;          // +0x14
    UPrimitive *Primitive;   // +0x20
    FLOAT Time;              // +0x24
    INT Item;                // +0x28
    UMaterial *Material;     // +0x2c
    INT BoneName;            // +0x30
};

struct FBspNode
{
    FPlane Plane;            // +0x00
    BYTE unk_10[0x20];       // +0x10
    union
    {
        struct
        {
            INT iBack;       // +0x30
            INT iFront;      // +0x34
            INT iPlane;      // +0x38
        };
        INT iChild[3];
    };
    BYTE unk_3c[0x1e];       // +0x3c
    BYTE NumVertices;        // +0x5a
    BYTE NodeFlags;          // +0x5b

    UBOOL IsCsg(DWORD ExtraFlags = 0) const
    {
        return (NumVertices > 0) && !(NodeFlags & (NF_NotCsg | NF_NotVisBlocking | ExtraFlags));
    }
    UBOOL ChildOutside(INT iChildIdx, UBOOL Outside, DWORD ExtraFlags = 0) const
    {
        return iChildIdx ? (Outside || IsCsg(ExtraFlags)) : (Outside && !IsCsg(ExtraFlags));
    }
};

template<class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;

    T &operator()(INT i) { return Data[i]; }
    const T &operator()(INT i) const { return Data[i]; }
};

class UPrimitive
{
public:
    BYTE unk_00[0x54];
};

class UModel : public UPrimitive
{
public:
    TArray<FBspNode> Nodes;  // +0x54
    BYTE unk_60[0xa4];       // +0x60
    UBOOL RootOutside;       // +0x104
};

extern UBOOL GPassedOutside; // 0x10c8bc08

// Helper at RVA 0x140e80 (scaffolding for the LTCG link, not part of this item).
// Written in loop form so LTCG assigns its retail convention (this in ECX,
// hidden return in EAX) without propagating EDX preservation across the call,
// matching the retail link's conservative caller-saved register set.
__declspec(noinline) FMatrix FMatrix::TransposeAdjoint() const
{
    FMatrix TA;
    TA.M[0][0] = M[1][1] * M[2][2] - M[2][1] * M[1][2];
    TA.M[0][1] = M[2][0] * M[1][2] - M[1][0] * M[2][2];
    TA.M[0][2] = M[1][0] * M[2][1] - M[2][0] * M[1][1];

    TA.M[1][0] = M[2][1] * M[0][2] - M[0][1] * M[2][2];
    TA.M[1][1] = M[0][0] * M[2][2] - M[2][0] * M[0][2];
    TA.M[1][2] = M[2][0] * M[0][1] - M[0][0] * M[2][1];

    TA.M[2][0] = M[0][1] * M[1][2] - M[1][1] * M[0][2];
    TA.M[2][1] = M[1][0] * M[0][2] - M[0][0] * M[1][2];
    TA.M[2][2] = M[0][0] * M[1][1] - M[1][0] * M[0][1];

    for (INT i = 0; i < 3; i++)
    {
        TA.M[i][3] = 0.f;
        TA.M[3][i] = 0.f;
    }
    TA.M[3][3] = 1.f;
    return TA;
}

// Helper at RVA 0x140f70 (defined here so LTCG assigns its retail calling convention).
__declspec(noinline) FPlane FPlane::TransformByUsingAdjointT(const FMatrix &M, const FMatrix &TA) const
{
    FVector NewNormal = ((FVector)TA.TransformFPlane(FPlane(X, Y, Z, 0.f))).SafeNormal();
    if (M.Determinant() < 0.f)
        NewNormal *= -1.f;
    FPlane NewPoint = M.TransformFPlane(FPlane(X * W, Y * W, Z * W, 1.f));
    return FPlane(NewNormal, NewPoint | NewNormal);
}

// Base class for BSP box/point collision checks (constructor at RVA 0x1410d0).
struct FCollisionCheck
{
    FCheckResult &Hit;       // +0x00
    UModel *Model;           // +0x04
    AActor *Owner;           // +0x08
    FMatrix LocalToWorld;    // +0x0c
    FVector Extent;          // +0x4c
    DWORD ExtraNodeFlags;    // +0x58
    BYTE unk_5c[0x10];       // +0x5c
    FVector UnitNormal;      // +0x6c
    FVector ZeroOrigin;      // +0x78
    BYTE unk_84[0x08];       // +0x84
    FMatrix LocalToWorldTA;  // +0x8c
    BYTE unk_cc[0x504];      // +0xcc

    FCollisionCheck(FCheckResult &InHit, UModel *InModel, AActor *InOwner, FVector InExtent, DWORD InExtraNodeFlags);
};

__declspec(noinline) FCollisionCheck::FCollisionCheck(
    FCheckResult &InHit,
    UModel *InModel,
    AActor *InOwner,
    FVector InExtent,
    DWORD InExtraNodeFlags)
    : Hit(InHit)
    , Model(InModel)
    , Owner(InOwner)
    , Extent(InExtent)
    , ExtraNodeFlags(InExtraNodeFlags)
    , UnitNormal(GMath_UnitX)
    , ZeroOrigin(GMath_Zero)
{
    if (Owner)
    {
        LocalToWorld = Owner->LocalToWorld();
        LocalToWorldTA = LocalToWorld.TransposeAdjoint();
    }
    else
    {
        LocalToWorld = LocalToWorldTA = FMatrix::Identity;
    }
}

// RVA 0x141f40: FastLineCheck
static UBOOL FastLineCheck(
    FCheckResult &Hit,
    UModel *Model,
    FMatrix *LocalToWorld,
    INT iParent,
    INT iNode,
    FVector *End,
    FVector Start,
    UBOOL Outside,
    DWORD ExtraNodeFlags)
{
    FMatrix TA = LocalToWorld ? LocalToWorld->TransposeAdjoint() : FMatrix::Identity;
    while (iNode != INDEX_NONE)
    {
        const FBspNode *Node = &Model->Nodes(iNode);
        FLOAT F1, F2;
        if (LocalToWorld)
        {
            FPlane Plane = Node->Plane.TransformByUsingAdjointT(*LocalToWorld, TA);
            F1 = Plane.PlaneDot(Start);
            F2 = Plane.PlaneDot(*End);
        }
        else
        {
            F1 = Node->Plane.PlaneDot(Start);
            F2 = Node->Plane.PlaneDot(*End);
        }

        if (F1 > -0.001f && F2 > -0.001f)
        {
            Outside |= Node->IsCsg(ExtraNodeFlags & ~NF_IgnoreInitSolid);
            iNode = Node->iFront;
        }
        else if (F1 < 0.001f && F2 < 0.001f)
        {
            Outside &= !Node->IsCsg(ExtraNodeFlags & ~NF_IgnoreInitSolid);
            iNode = Node->iBack;
        }
        else
        {
            FVector Middle = Start + (Start - *End) * (F1 / (F2 - F1));
            INT Front = F1 > 0.f;
            if (!FastLineCheck(Hit, Model, LocalToWorld, iParent, Node->iChild[Front], &Middle, Start, Node->ChildOutside(Front, Outside, ExtraNodeFlags), ExtraNodeFlags))
                return 0;
            Outside = Node->ChildOutside(1 - Front, Outside, ExtraNodeFlags);
            Start = Middle;
            iParent = iNode;
            iNode = Node->iChild[1 - Front];
        }
    }

    if (!Outside)
    {
        if (!GPassedOutside && (ExtraNodeFlags & NF_IgnoreInitSolid))
        {
            Outside = 1;
        }
        else
        {
            Hit.Location = Start;
            Hit.Normal = Model->Nodes(iParent).Plane;
            Hit.Primitive = Model;
            Hit.Item = iParent;
        }
    }
    else
    {
        GPassedOutside = 1;
    }
    return Outside;
}

// RVA 0x1423d0: FBoxLineCheck::FBoxLineCheck
struct FBoxLineCheck : public FCollisionCheck
{
    FVector End;             // +0x5d0
    FVector Start;           // +0x5dc
    FLOAT Dist;              // +0x5e8
    UBOOL bHit;              // +0x5ec
    INT BestNode;            // +0x5f0

    FBoxLineCheck(
        FCheckResult &InHit,
        UModel *InModel,
        AActor *InOwner,
        const FVector &InEnd,
        const FVector &InStart,
        const FVector &InExtent,
        DWORD InExtraNodeFlags);
};

__declspec(noinline) FBoxLineCheck::FBoxLineCheck(
    FCheckResult &InHit,
    UModel *InModel,
    AActor *InOwner,
    const FVector &InEnd,
    const FVector &InStart,
    const FVector &InExtent,
    DWORD InExtraNodeFlags)
    : FCollisionCheck(InHit, InModel, InOwner, InExtent, InExtraNodeFlags)
    , End(InEnd)
    , Start(InStart)
    , Dist((InEnd - InStart).Size())
    , bHit(0)
    , BestNode(INDEX_NONE)
{
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void ConsumeBoxLineCheck(FBoxLineCheck *Check);
void ConsumeCollisionCheck(FCollisionCheck *Check);

UBOOL Driver_141f40(FCheckResult &Hit, UModel *Model, FMatrix *LocalToWorld, FVector *End, FVector Start, UBOOL Outside, DWORD ExtraNodeFlags)
{
    Escape(&GPassedOutside);
    Escape(&FMatrix::Identity);
    return FastLineCheck(Hit, Model, LocalToWorld, 0, 0, End, Start, Outside, ExtraNodeFlags);
}

UBOOL Driver_1423d0(UModel *Model, FCheckResult &Hit, AActor *Owner, const FVector &End, const FVector &Start, const FVector &Extent, DWORD ExtraNodeFlags)
{
    Escape(&FMatrix::Identity);
    Escape((void *)&GMath_UnitX);
    Escape((void *)&GMath_Zero);
    if (Model->Nodes.ArrayNum)
    {
        if (Extent.X != GMath_Zero.X || Extent.Y != GMath_Zero.Y || Extent.Z != GMath_Zero.Z)
        {
            Hit.Time = 2.0f;
            FBoxLineCheck Check(Hit, Model, Owner, End, Start, Extent, ExtraNodeFlags);
            ConsumeBoxLineCheck(&Check);
            return 1;
        }
        FCollisionCheck Base(Hit, Model, Owner, Extent, ExtraNodeFlags);
        ConsumeCollisionCheck(&Base);
    }
    return 0;
}
