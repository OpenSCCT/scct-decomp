// Work item w4_0067: Versus RVA 0x139fe0-0x13a48c.
//   0x13a2a0 AddProjector_13a2a0      (LTCG: this/node in EBX, 2 stack args)
//   0x13a370 AddLight_13a370          (LTCG: light in EBX, node in ESI, 1 stack arg)
// Compiled with VC7.0 /GL and linked with /LTCG.
// Neutral names are used for structs/functions without retail symbol evidence.

#include "versus_mem_stack.h"

typedef signed short SWORD;
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

class FMalloc;
extern FMalloc *GMalloc;

template <class T> inline T Abs(const T A) { return (A < (T)0) ? -A : A; }
template <class T> inline T Square(const T A) { return A * A; }

#include "versus_level_trace_vector.h"

__declspec(dllimport) extern const FVector GZeroVector;

inline FLOAT FDistSquared(const FVector &V1, const FVector &V2)
{
    return Square(V2.X - V1.X) + Square(V2.Y - V1.Y) + Square(V2.Z - V1.Z);
}

#include "versus_scene_base_node.h"

struct FSphere : public FPlane {};

class AActor
{
public:
    char Pad0[0x174];
    FLOAT LightRadius; // +0x174
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
