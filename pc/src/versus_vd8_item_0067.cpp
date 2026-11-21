// Work item w4_0067: Versus RVA 0x139fe0-0x13a48c.
//   0x139fe0 BuildPortalVolume_139fe0 (LTCG: cdecl, 3 stack args)
//   0x13a2a0 AddProjector_13a2a0      (LTCG: this/node in EBX, 2 stack args)
//   0x13a370 AddLight_13a370          (LTCG: light in EBX, node in ESI, 1 stack arg)
// Compiled with VC7.0 /GL and linked with /LTCG.
// Neutral names are used for structs/functions without retail symbol evidence.

typedef unsigned char BYTE;
typedef signed short SWORD;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
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
extern const TCHAR MemChunk_Tag[]; // L"MemChunk"

inline void *appMalloc(INT Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template <class T> inline T Abs(const T A) { return (A < (T)0) ? -A : A; }
template <class T> inline T Square(const T A) { return A * A; }

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

extern FMemStack GSceneMem; // retail 0x10c73cac
inline void *operator new(unsigned int Size, FMemStack &Mem) { return Mem.PushBytes(Size, 8); }

extern FLOAT NEAR_CLIPPING_PLANE; // retail 0x10c73b08

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator^(const FVector &V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    __declspec(noinline) FVector SafeNormal() const;
};

__declspec(dllimport) extern const FVector GZeroVector;

inline FLOAT FDistSquared(const FVector &V1, const FVector &V2)
{
    return Square(V2.X - V1.X) + Square(V2.Y - V1.Y) + Square(V2.Z - V1.Z);
}

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
    FPlane(const FVector &InBase, const FVector &InNormal) : FVector(InNormal), W(InBase | InNormal) {}
    __declspec(noinline) FPlane(const FVector &A, const FVector &B, const FVector &C);
    FLOAT PlaneDot(const FVector &P) const { return X * P.X + Y * P.Y + Z * P.Z - W; }
    __declspec(noinline) UBOOL StraddlesBox_51dc0(const FVector *Corners) const;
};

struct FSphere : public FPlane
{
    FSphere() {}
    FSphere(const FVector &V, FLOAT InW) : FPlane(V, InW) {}
};

struct FMatrix
{
    FLOAT M[4][4];
    FPlane TransformFPlane(const FPlane &P) const; // 0x4fe60
};

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
};

class APlayerController
{
public:
    char Pad0[0x4fc];
    INT RendMap; // +0x4fc
};

class UViewport
{
public:
    char Pad0[0x30];
    APlayerController *Actor; // +0x30
};

class FSceneNode
{
public:
    void *VTable;
    UViewport *Viewport;    // +0x04
    char Pad08[0x154 - 0x08];
    FMatrix ScreenToWorld;  // +0x154
    FVector ViewOrigin;     // +0x194
    char Pad1A0[0x1c8 - 0x1a0];
    INT ViewZone;           // +0x1c8

    __declspec(noinline) FVector Deproject(const FPlane &Screen);
};

class AZoneInfo
{
public:
    char Pad0[0x310];
    DWORD bDistanceFog : 1; // +0x310
    char Pad314[0x324 - 0x314];
    FLOAT DistanceFogEnd;   // +0x324
};

struct FZoneProperties
{
    AZoneInfo *ZoneActor;
    DWORD Pad04, Pad08, Pad0C;
};

class UModel
{
public:
    char Pad0[0x114];
    TArray<FZoneProperties> Zones; // +0x114
};

class AActor
{
public:
    char Pad0[0x174];
    FLOAT LightRadius; // +0x174
};

class ULevel
{
public:
    char Pad0[0x2c];
    TArray<AActor *> Actors; // +0x2c
    char Pad38[0x13c - 0x38];
    UModel *Model;           // +0x13c
};

struct FConvexVolume
{
    FPlane Planes[32];
    INT NumPlanes;
    FConvexVolume() : NumPlanes(0) {}
};

struct FPortalPoly_139fe0
{
    FVector Base;
    FVector Normal;     // +0x0c
    FVector Vertex[16]; // +0x18
    DWORD PadD8, PadDC;
    _WORD NumVertices;  // +0xe0
};

struct FVisibilityContext_139fe0
{
    FSceneNode *SceneNode; // +0x00
    void *Field04;         // +0x04
    ULevel *Level;         // +0x08
    char Pad0C[0x288 - 0x0c];
    struct FProjectorLink_13a2a0 **ProjectorLists; // +0x288
    struct FLightLink_13a370 **LightLists;         // +0x28c
};

struct FProjectorLink_13a2a0
{
    struct FProjectorVolume_13a2a0 *Projector;
    FProjectorLink_13a2a0 *Next;
    FProjectorLink_13a2a0(struct FProjectorVolume_13a2a0 *InProjector, FProjectorLink_13a2a0 *InNext)
        : Projector(InProjector), Next(InNext) {}
};

struct FLightLink_13a370
{
    struct FDynamicLight_13a370 *Light;
    FLightLink_13a370 *Next;
    FLightLink_13a370(struct FDynamicLight_13a370 *InLight, FLightLink_13a370 *InNext)
        : Light(InLight), Next(InNext) {}
};

class UnnamedFrustum_117ca0
{
public:
    FVector Vertices[8]; // +0x00
    FPlane Planes[6];    // +0x60
    __declspec(noinline) UBOOL SphereCheck(const FSphere &S);
};

struct FProjectorVolume_13a2a0
{
    char Pad0[0x50];
    UnnamedFrustum_117ca0 Frustum; // +0x50
};

struct FBspNode_13a2a0
{
    FPlane Plane;    // +0x00
    FSphere Sphere;  // +0x10
    char Pad20[0x50 - 0x20];
    SWORD Index50;   // +0x50
};

struct FDynamicLight_13a370
{
    AActor *Actor;    // +0x00
    char Pad04[0x18 - 0x04];
    FVector Position; // +0x18
};

// 0x139fe0
__declspec(noinline) FConvexVolume *BuildPortalVolume_139fe0(
    FVisibilityContext_139fe0 *Context,
    FPortalPoly_139fe0 *Poly,
    UBOOL bUseFog)
{
    FConvexVolume *Volume = new(GSceneMem) FConvexVolume;
    Volume->Planes[Volume->NumPlanes++] = FPlane(Poly->Normal, Poly->Normal | Poly->Vertex[0]);
    for (INT i = 0; i < (INT)Poly->NumVertices && Volume->NumPlanes < 31; i++)
    {
        FPlane Plane(
            Context->SceneNode->ViewOrigin,
            Poly->Vertex[i],
            Poly->Vertex[(i + 1) % Poly->NumVertices]);
        Volume->Planes[Volume->NumPlanes++] = Plane;
    }
    if (bUseFog)
    {
        FSceneNode *SceneNode = Context->SceneNode;
        ULevel *Level = Context->Level;
        UModel *Model = Level->Model;
        AZoneInfo *ZoneInfo;
        if (SceneNode->ViewZone < Model->Zones.Num() && Model->Zones(SceneNode->ViewZone).ZoneActor)
            ZoneInfo = Model->Zones(SceneNode->ViewZone).ZoneActor;
        else
            ZoneInfo = (AZoneInfo *)Level->Actors(0);
        if (ZoneInfo->bDistanceFog &&
            SceneNode->Viewport->Actor->RendMap != 0x26 &&
            SceneNode->Viewport->Actor->RendMap != 0x24)
        {
            FLOAT FogEnd = ZoneInfo->DistanceFogEnd;
            FVector ViewNormal = (SceneNode->Deproject(FPlane(0.f, 0.f, 0.f, NEAR_CLIPPING_PLANE)) - SceneNode->ViewOrigin).SafeNormal();
            Volume->Planes[Volume->NumPlanes++] = FPlane(Context->SceneNode->ViewOrigin + ViewNormal * FogEnd, ViewNormal);
        }
    }
    return Volume;
}

// 0x13a2a0
__declspec(noinline) void AddProjector_13a2a0(
    FBspNode_13a2a0 *Node,
    FVisibilityContext_139fe0 *Context,
    FProjectorVolume_13a2a0 *Projector)
{
    if (Node->Plane.StraddlesBox_51dc0(Projector->Frustum.Vertices) &&
        Projector->Frustum.SphereCheck(Node->Sphere))
    {
        for (FProjectorLink_13a2a0 *Link = Context->ProjectorLists[Node->Index50]; Link; Link = Link->Next)
        {
            if (Link->Projector == Projector)
                return;
        }
        Context->ProjectorLists[Node->Index50] = new(GSceneMem) FProjectorLink_13a2a0(
            Projector, Context->ProjectorLists[Node->Index50]);
    }
}

// 0x13a370
__declspec(noinline) void AddLight_13a370(
    FDynamicLight_13a370 *Light,
    FBspNode_13a2a0 *Node,
    FVisibilityContext_139fe0 *Context)
{
    if (Abs(Node->Plane.PlaneDot(Light->Position)) < Light->Actor->LightRadius &&
        FDistSquared(Node->Sphere, Light->Position) < Square(Node->Sphere.W + Light->Actor->LightRadius))
    {
        for (FLightLink_13a370 *Link = Context->LightLists[Node->Index50]; Link; Link = Link->Next)
        {
            if (Link->Light == Light)
                return;
        }
        Context->LightLists[Node->Index50] = new(GSceneMem) FLightLink_13a370(
            Light, Context->LightLists[Node->Index50]);
    }
}

// Published callees reproduced here so LTCG assigns them their retail register conventions.
// 0x577c0 (FMemStack::AllocateNewChunk)
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

// 0x50d30 (FVector::SafeNormal)
FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// 0xc9c30 (FPlane::FPlane(A, B, C))
FPlane::FPlane(const FVector &A, const FVector &B, const FVector &C)
    : FVector(((B - A) ^ (C - A)).SafeNormal()),
      W(A | ((B - A) ^ (C - A)).SafeNormal())
{
}

// 0x112dd0 (FSceneNode::Deproject)
FVector FSceneNode::Deproject(const FPlane &Screen)
{
    return ScreenToWorld.TransformFPlane(FPlane(Screen.X * Screen.W, Screen.Y * Screen.W, Screen.Z * Screen.W, Screen.W));
}

// 0x51dc0 (FPlane::StraddlesBox_51dc0)
UBOOL FPlane::StraddlesBox_51dc0(const FVector *Corners) const
{
    if (PlaneDot(Corners[0]) < 0.f)
    {
        if (PlaneDot(Corners[1]) > 0.f) return 1;
        if (PlaneDot(Corners[2]) > 0.f) return 1;
        if (PlaneDot(Corners[3]) > 0.f) return 1;
        if (PlaneDot(Corners[4]) > 0.f) return 1;
        if (PlaneDot(Corners[5]) > 0.f) return 1;
        if (PlaneDot(Corners[6]) > 0.f) return 1;
        if (PlaneDot(Corners[7]) > 0.f) return 1;
    }
    else
    {
        if (PlaneDot(Corners[1]) < 0.f) return 1;
        if (PlaneDot(Corners[2]) < 0.f) return 1;
        if (PlaneDot(Corners[3]) < 0.f) return 1;
        if (PlaneDot(Corners[4]) < 0.f) return 1;
        if (PlaneDot(Corners[5]) < 0.f) return 1;
        if (PlaneDot(Corners[6]) < 0.f) return 1;
        if (PlaneDot(Corners[7]) < 0.f) return 1;
    }
    return 0;
}

// 0x117ca0 (UnnamedFrustum_117ca0::SphereCheck)
UBOOL UnnamedFrustum_117ca0::SphereCheck(const FSphere &S)
{
    FLOAT NegRadius = -S.W;
    for (INT i = 0; i < 6; i++)
        if (Planes[i].PlaneDot(S) <= NegRadius)
            return 0;
    return 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }

FConvexVolume *Driver_139fe0(
    FVisibilityContext_139fe0 *C,
    FPortalPoly_139fe0 *P,
    UBOOL B,
    FPlane *Out,
    const FVector *V0,
    const FVector *V1,
    const FVector *V2)
{
    Escape(&GSceneMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    Escape(&NEAR_CLIPPING_PLANE);
    Escape((void *)&BuildPortalVolume_139fe0);
    for (INT i = 0; i < 8; i++)
    {
        new(&Out[i]) FPlane(V0[i], V1[i], V2[i]);
        Escape(Out);
    }
    return BuildPortalVolume_139fe0(C, P, B);
}

void Driver_13a2a0(FBspNode_13a2a0 *Nodes, INT Count, FVisibilityContext_139fe0 *C, FProjectorVolume_13a2a0 *P)
{
    Escape(&GSceneMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    for (INT i = 0; i < Count; i++)
        AddProjector_13a2a0(&Nodes[i], C, P);
}

void Driver_13a370(FDynamicLight_13a370 *Lights, INT Count, FBspNode_13a2a0 *Nodes, FVisibilityContext_139fe0 *C)
{
    Escape(&GSceneMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    for (INT i = 0; i < Count; i++)
        AddLight_13a370(&Lights[i], &Nodes[i], C);
}
