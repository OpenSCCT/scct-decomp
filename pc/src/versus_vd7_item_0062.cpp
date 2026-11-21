// Work item w4_0062: Versus RVA 0x135da0-0x136234 (VC7.0 /GL, linked /LTCG).
// Unreal Engine 2 antiportal visibility helpers (UnRenderVisibility.cpp):
//   0x135da0  BuildAntiPortalVolume
//   0x136100  AddAntiPortals (neutral function/class names)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR MemChunk_Tag[];

inline void *appMalloc(INT Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// FMemStack (UE2 Core/UnMem.h).
struct FTaggedMemory
{
    FTaggedMemory *Next;
    INT DataSize;
    BYTE Data[1];
};

class FMemStack
{
public:
    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;
    static FTaggedMemory *UnusedChunks;

    __declspec(noinline) BYTE *AllocateNewChunk(INT MinSize);
    BYTE *PushBytes(INT AllocSize, INT Align)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
        Top = Result + AllocSize;
        if (Top > End)
        {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

extern FMemStack GSceneMem;

enum { DEFAULT_ALIGNMENT = 8 };

inline void *operator new(unsigned int Size, FMemStack &Mem, INT Count = 1, INT Align = DEFAULT_ALIGNMENT)
{
    return Mem.PushBytes(Size * Count, Align);
}

template <class T> inline T *New(FMemStack &Mem, INT Count = 1, INT Align = DEFAULT_ALIGNMENT)
{
    return (T *)Mem.PushBytes(Count * sizeof(T), Align);
}

// FArray / TArray (UE2 Core/UnTemplate.h).
class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

// Math types (UE2 Core/UnMath.h).
struct FMatrix;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FVector operator^(const FVector &V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    __declspec(noinline) FVector SafeNormal() const;
};

__declspec(dllimport) extern const FVector GZeroVector;

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &InBase, const FVector &InNormal) : FVector(InNormal), W(InBase | InNormal) {}
    __declspec(noinline) FPlane(const FVector &A, const FVector &B, const FVector &C);

    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + (Y * P.Y + Z * P.Z) - W;
    }

    __declspec(noinline) FPlane TransformByUsingAdjointT(const FMatrix &M, const FMatrix &TA) const;
};

struct FMatrix
{
    union
    {
        struct { FPlane XPlane, YPlane, ZPlane, WPlane; };
        FLOAT M[4][4];
    };
    FMatrix() {}
    FPlane TransformFPlane(const FPlane &P) const;
    FVector TransformFVector(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.0f));
    }
    FVector TransformNormal(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 0.0f));
    }
    __declspec(noinline) FMatrix TransposeAdjoint() const;
    FLOAT Determinant() const;
};

struct FBox
{
    FVector Min;
    FVector Max;
    BYTE IsValid;
    __declspec(noinline) void GetCenterAndExtents(FVector &Center, FVector &Extents) const;
};

// Convex volume (UE2 UnMath.h / UnRenderVisibility.h).
struct FConvexVolume
{
    FPlane BoundingPlanes[32];
    INT NumPlanes;

    FConvexVolume() : NumPlanes(0) {}
    __declspec(noinline) BYTE ClipBox(const FVector &Origin, const FVector &Extent) const;
};

struct FConvexVolumeList
{
    FConvexVolume *Volume;
    FConvexVolumeList *Next;

    FConvexVolumeList(FConvexVolume *InVolume, FConvexVolumeList *InNext)
        : Volume(InVolume), Next(InNext)
    {}
};

struct FZoneVisibility
{
    FConvexVolumeList *Portals;
    FConvexVolumeList *AntiPortals;

    __declspec(noinline) UBOOL BoxIsVisible(const FBox &Box);
};

struct FConvexVolumeFace
{
    FPlane Plane;
    TArray<FVector> Vertices;
};

struct FConvexVolumeEdge
{
    INT Faces[2];
    INT Vertices[2];
};

class UConvexVolume
{
public:
    BYTE unk_00[0x50];
    TArray<FConvexVolumeFace> Faces;    // 0x50
    TArray<FConvexVolumeEdge> Edges;    // 0x5c
};

class AActor;

class FDynamicActor
{
public:
    AActor *Actor;                      // 0x00
    INT Revision;                       // 0x04
    INT unk_08;                         // 0x08
    INT VisibilityTag;                  // 0x0c
    FMatrix LocalToWorld;               // 0x10
    FMatrix WorldToLocal;               // 0x50
    FBox BoundingBox;                   // 0x90
};

class AActor
{
public:
    BYTE unk_00[0x12c];
    FDynamicActor *ActorRenderData;     // 0x12c
    BYTE unk_130[0x134 - 0x130];
    INT Revision;                       // 0x134
    BYTE unk_138[0x250 - 0x138];
    UConvexVolume *AntiPortal;          // 0x250
    FLOAT CullDistance;                 // 0x254

    __declspec(noinline) FDynamicActor *GetActorRenderData();
    __declspec(noinline) void RebuildActorRenderData();
};

class APlayerController
{
public:
    BYTE unk_00[0x308];
    FLOAT FovAngle;                     // 0x308
    BYTE unk_30c[0x4fc - 0x30c];
    INT RendMap;                        // 0x4fc
};

class UViewport
{
public:
    BYTE unk_00[0x30];
    APlayerController *Actor;           // 0x30
    BYTE unk_34[0x14c - 0x34];
    INT unk_14c;                        // 0x14c
};

class FLevelSceneNode
{
public:
    BYTE unk_00[0x04];
    UViewport *Viewport;                // 0x04
    BYTE unk_08[0x194 - 0x08];
    FVector ViewOrigin;                 // 0x194
};

class ULevel
{
public:
    BYTE unk_00[0x4a8c];
    TArray<TArray<AActor *> > ZoneAntiPortals; // 0x4a8c
};

class FLevelVisibility
{
public:
    FLevelSceneNode *SceneNode;         // 0x00
    INT unk_04;                         // 0x04
    ULevel *Level;                      // 0x08
    BYTE unk_0c[0x24 - 0x0c];
    FZoneVisibility Zones[64];          // 0x24
};

extern INT GVisibilityTag;              // retail 0x10c92298

__declspec(noinline) UBOOL CheckCullDistance(FDynamicActor *DynamicActor, const FVector &ViewOrigin, UViewport *Viewport);
__declspec(noinline) void AddAntiPortals(FLevelVisibility *Vis, INT ZoneIndex);

// RVA 0x135da0: BuildAntiPortalVolume
__declspec(noinline) FConvexVolume *BuildAntiPortalVolume(const FVector &ViewOrigin, FDynamicActor *DynamicActor)
{
    UConvexVolume *AntiPortal = DynamicActor->Actor->AntiPortal;
    FConvexVolume *Result = new(GSceneMem) FConvexVolume;
    FLOAT *FaceSide = New<FLOAT>(GSceneMem, AntiPortal->Faces.Num());

    for (INT FaceIndex = 0; FaceIndex < AntiPortal->Faces.Num() && Result->NumPlanes < 32; FaceIndex++)
    {
        FMatrix TA = DynamicActor->LocalToWorld.TransposeAdjoint();
        FPlane Plane = AntiPortal->Faces(FaceIndex).Plane.TransformByUsingAdjointT(DynamicActor->LocalToWorld, TA);
        FLOAT Side = Plane.PlaneDot(ViewOrigin);
        if (Side > 0.0f)
            Result->BoundingPlanes[Result->NumPlanes++] = Plane;
        FaceSide[FaceIndex] = Side;
    }

    for (INT EdgeIndex = 0; EdgeIndex < AntiPortal->Edges.Num() && Result->NumPlanes < 32; EdgeIndex++)
    {
        FConvexVolumeEdge &Edge = AntiPortal->Edges(EdgeIndex);
        if (FaceSide[Edge.Faces[0]] * FaceSide[Edge.Faces[1]] < 0.0f)
        {
            INT FrontFace = (FaceSide[Edge.Faces[1]] > 0.0f) ? 1 : 0;
            FVector V1 = DynamicActor->LocalToWorld.TransformFVector(
                AntiPortal->Faces(Edge.Faces[1 - FrontFace]).Vertices(Edge.Vertices[1 - FrontFace]));
            FVector V2 = DynamicActor->LocalToWorld.TransformFVector(
                AntiPortal->Faces(Edge.Faces[FrontFace]).Vertices(Edge.Vertices[FrontFace]));
            Result->BoundingPlanes[Result->NumPlanes++] = FPlane(ViewOrigin, V2, V1);
        }
    }

    return Result;
}

// RVA 0x136100: AddAntiPortals (neutral function/class names)
void AddAntiPortals(FLevelVisibility *Vis, INT ZoneIndex)
{
    if (!Vis->SceneNode->Viewport->unk_14c &&
        ZoneIndex < Vis->Level->ZoneAntiPortals.Num() &&
        Vis->SceneNode->Viewport->Actor->RendMap != 0x24 &&
        Vis->SceneNode->Viewport->Actor->RendMap != 0x26)
    {
        for (INT ActorIndex = 0; ActorIndex < Vis->Level->ZoneAntiPortals(ZoneIndex).Num(); ActorIndex++)
        {
            FDynamicActor *DynamicActor = Vis->Level->ZoneAntiPortals(ZoneIndex)(ActorIndex)->GetActorRenderData();
            if (DynamicActor->VisibilityTag != GVisibilityTag &&
                Vis->Zones[ZoneIndex].BoxIsVisible(DynamicActor->BoundingBox) &&
                CheckCullDistance(DynamicActor, Vis->SceneNode->ViewOrigin, Vis->SceneNode->Viewport))
            {
                FConvexVolume *Volume = BuildAntiPortalVolume(Vis->SceneNode->ViewOrigin, DynamicActor);
                Vis->Zones[ZoneIndex].AntiPortals = new(GSceneMem) FConvexVolumeList(Volume, Vis->Zones[ZoneIndex].AntiPortals);
                DynamicActor->VisibilityTag = GVisibilityTag;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: out-of-line callees so LTCG
// assigns their retail register conventions, plus the driver.

void Escape(void *);
INT Sink(INT, INT, INT, INT);
extern INT GScratch1, GScratch2;

__declspec(noinline) FDynamicActor *CreateDynamicActor(AActor *Owner);
FDynamicActor *AActor::GetActorRenderData()
{
    if (!ActorRenderData)
        ActorRenderData = CreateDynamicActor(this);
    if (ActorRenderData->Revision != Revision)
        RebuildActorRenderData();
    return ActorRenderData;
}

void FBox::GetCenterAndExtents(FVector &Center, FVector &Extents) const
{
    Extents = FVector((Max.X - Min.X) * 0.5f, (Max.Y - Min.Y) * 0.5f, (Max.Z - Min.Z) * 0.5f);
    Center = FVector(Min.X + Extents.X, Min.Y + Extents.Y, Min.Z + Extents.Z);
}

BYTE FConvexVolume::ClipBox(const FVector &Origin, const FVector &Extent) const
{
    BYTE Result = 3;
    INT a = Sink(1, 2, 3, 4), b = Sink(5, 6, 7, 8);
    for (INT i = 0; i < NumPlanes; i++)
    {
        FLOAT Dist = BoundingPlanes[i].PlaneDot(Origin);
        FLOAT Push = BoundingPlanes[i].X * Extent.X + BoundingPlanes[i].Y * Extent.Y + BoundingPlanes[i].Z * Extent.Z;
        if (Dist > Push) return (BYTE)(a & b & 0);
        if (Dist > -Push) Result &= ~2;
    }
    return Result;
}

UBOOL FZoneVisibility::BoxIsVisible(const FBox &Box)
{
    FVector Origin, Extent;
    Box.GetCenterAndExtents(Origin, Extent);
    INT k = Sink(1, 2, 3, 4), m = Sink(5, 6, 7, 8), n = Sink(9, 10, 11, 12);
    FConvexVolumeList *List = Portals;
    while (List)
    {
        if (List->Volume->ClipBox(Origin, Extent) & 1)
            goto Visible;
        List = List->Next;
    }
    return (UBOOL)(k & m & n & 0);
Visible:
    for (List = AntiPortals; List; List = List->Next)
        if (!(List->Volume->ClipBox(Origin, Extent) & 2))
            return 0;
    return 1;
}

extern "C" double tan(double);
#pragma intrinsic(tan)

__declspec(noinline) FLOAT BoxDistSquared(FDynamicActor *DynamicActor, const FVector &ViewOrigin)
{
    FBox Box = DynamicActor->BoundingBox;
    FLOAT DistSq = 0.0f;
    if (ViewOrigin.X < Box.Min.X)
        DistSq += (ViewOrigin.X - Box.Min.X) * (ViewOrigin.X - Box.Min.X);
    else if (ViewOrigin.X > Box.Max.X)
        DistSq += (ViewOrigin.X - Box.Max.X) * (ViewOrigin.X - Box.Max.X);
    if (ViewOrigin.Y < Box.Min.Y)
        DistSq += (ViewOrigin.Y - Box.Min.Y) * (ViewOrigin.Y - Box.Min.Y);
    else if (ViewOrigin.Y > Box.Max.Y)
        DistSq += (ViewOrigin.Y - Box.Max.Y) * (ViewOrigin.Y - Box.Max.Y);
    if (ViewOrigin.Z < Box.Min.Z)
        DistSq += (ViewOrigin.Z - Box.Min.Z) * (ViewOrigin.Z - Box.Min.Z);
    else if (ViewOrigin.Z > Box.Max.Z)
        DistSq += (ViewOrigin.Z - Box.Max.Z) * (ViewOrigin.Z - Box.Max.Z);
    if (GScratch1) Escape(DynamicActor);
    return DistSq;
}

UBOOL CheckCullDistance(FDynamicActor *DynamicActor, const FVector &ViewOrigin, UViewport *Viewport)
{
    if (DynamicActor->Actor->CullDistance != 0.0f && Viewport->unk_14c != 1)
    {
        if (GScratch1) GScratch2 = GScratch1 + (INT)Viewport->Actor;
        FLOAT Factor = (FLOAT)tan(Viewport->Actor->FovAngle * 0.0087266462f);
        FLOAT DistSq = BoxDistSquared(DynamicActor, ViewOrigin) * Factor * Factor;
        FLOAT Cull = DynamicActor->Actor->CullDistance;
        FLOAT CullSq = Cull * Cull;
        if (Cull > 0.0f)
        {
            if (DistSq > CullSq)
                return 0;
        }
        else
        {
            if (DistSq <= -CullSq)
                return 0;
        }
    }
    return 1;
}

BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next)
    {
        if ((*Link)->DataSize >= MinSize)
        {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk)
    {
        INT DataSize = Max(MinSize, DefaultChunkSize - (INT)sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)appMalloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

FPlane::FPlane(const FVector &A, const FVector &B, const FVector &C)
    : FVector(((B - A) ^ (C - A)).SafeNormal()),
      W(A | ((B - A) ^ (C - A)).SafeNormal())
{
}

FMatrix FMatrix::TransposeAdjoint() const
{
    FMatrix TA;
    TA.M[0][0] = this->M[1][1] * this->M[2][2] - this->M[1][2] * this->M[2][1];
    TA.M[0][1] = this->M[1][2] * this->M[2][0] - this->M[1][0] * this->M[2][2];
    TA.M[0][2] = this->M[1][0] * this->M[2][1] - this->M[1][1] * this->M[2][0];
    TA.M[0][3] = 0.f;

    TA.M[1][0] = this->M[2][1] * this->M[0][2] - this->M[2][2] * this->M[0][1];
    TA.M[1][1] = this->M[2][2] * this->M[0][0] - this->M[2][0] * this->M[0][2];
    TA.M[1][2] = this->M[2][0] * this->M[0][1] - this->M[2][1] * this->M[0][0];
    TA.M[1][3] = 0.f;

    TA.M[2][0] = this->M[0][1] * this->M[1][2] - this->M[0][2] * this->M[1][1];
    TA.M[2][1] = this->M[0][2] * this->M[1][0] - this->M[0][0] * this->M[1][2];
    TA.M[2][2] = this->M[0][0] * this->M[1][1] - this->M[0][1] * this->M[1][0];
    TA.M[2][3] = 0.f;

    TA.M[3][0] = 0.f;
    TA.M[3][1] = 0.f;
    TA.M[3][2] = 0.f;
    TA.M[3][3] = 1.f;
    if (GScratch1) GScratch2 = GScratch1 + (INT)this;
    return TA;
}

FPlane FPlane::TransformByUsingAdjointT(const FMatrix &M, const FMatrix &TA) const
{
    FVector NewNormal = TA.TransformNormal(*this).SafeNormal();
    if (M.Determinant() < 0.0f)
        NewNormal *= -1.0f;
    return FPlane(M.TransformFVector(*this * W), NewNormal);
}

FConvexVolume *Driver_135da0(const FVector *V, FDynamicActor *A, FMatrix *OutM, const FMatrix *InM, INT N)
{
    Escape(&GMalloc);
    Escape(&GSceneMem);
    Escape(&FMemStack::UnusedChunks);
    FConvexVolume *R = BuildAntiPortalVolume(*V, A);
    Escape(R);
    FConvexVolume *R2 = BuildAntiPortalVolume(V[1], A + 1);
    INT a = Sink(1, 2, 3, 4), b = Sink(5, 6, 7, 8), c = Sink(9, 10, 11, 12);
    for (INT i = 0; i < N; i++)
    {
        FMatrix T = InM[i].TransposeAdjoint();
        OutM[i] = T;
        Sink(a, b, c, i);
    }
    return R2;
}

void Driver_136100(FLevelVisibility *Vis, INT ZoneIndex, FMemStack *M, unsigned int S, INT C, INT A, FDynamicActor *DA, const FVector *V)
{
    Escape(&GMalloc);
    Escape(&GSceneMem);
    Escape(&GVisibilityTag);
    Escape(&FMemStack::UnusedChunks);
    void *P = operator new(S, *M, C, A);
    Escape(P);
    Escape(operator new(S + 4, *M, C + 1, A * 2));
    AddAntiPortals(Vis, ZoneIndex);
    AddAntiPortals(Vis, ZoneIndex + 1);
    Escape(Vis);
    if (Vis->Zones[ZoneIndex].BoxIsVisible(DA->BoundingBox))
        Sink(CheckCullDistance(DA, *V, Vis->SceneNode->Viewport), 0, 0, 0);
}
