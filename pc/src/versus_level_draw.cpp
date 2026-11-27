#include "versus_build.h"
#include "versus_arrays.h"
#include "versus_pawn_action_events.h"
#include "versus_scene_level_types.h"
#include "versus_scene_node_types.h"
#include "versus_scene_model_types.h"
#include "versus_canvas_matrix.h"

#include "versus_level_render_state.h"
#include "versus_convex_volume.h"
#include "versus_viewport_types.h"
#include "versus_mem_stack.h"

struct FBspSection {
    BYTE unk_00[0x20];
    class UMaterial *Material;
    DWORD PolyFlags;
    INT iLightMapTexture;
    BYTE unk_2c[0xc];
};
enum { PF_EchelonLightFriendly = 0x80000 };

inline UBOOL IsLightFriendlyBspSection(const UModel *Model, INT Index)
{
    const FBspSection *Sections = static_cast<const FBspSection *>(Model->Sections.Data);
    return (Sections[Index].PolyFlags & PF_EchelonLightFriendly) != 0;
}

class UStaticMesh : public UPrimitive
{
  public:
    BYTE unk_50[0x140 - 0x50];
    UBOOL UseSimpleLineCollision, UseSimpleBoxCollision, UseVertexColor;
};

template <class T> struct TList {
    T Element;
    TList *Next;
};
class FBspDrawList
{
  public:
    void Render(FLevelSceneNode *SceneNode, FRenderInterface *RI, DWORD Flags);
};
struct FDynamicLightList;
struct FDynamicActor {
    AActor *Actor;
    INT Revision;
    FLOAT Determinant;
    BYTE unk_c[0xe8 - 0x0c];
    FDynamicLightList *Lights;
    DWORD unk_ec;
    FDynamicLightList *SectionLights;
    void *Projectors;
    void UpdateLightFade(FLevelSceneNode *SceneNode);
    void Render(FLevelSceneNode *SceneNode, FDynamicLightList *InLights, void *InProjectors,
                FRenderInterface *RI, INT Pass, void *PostActors);
};
struct FTranslucentListNode {
    UBOOL bIsBsp;
    union {
        INT iNode;
        FDynamicActor *DynamicActor;
    };
    BYTE unk_08[0x18 - 0x08];
    FTranslucentListNode *Next;
};

class USubsystem : public UObject
{
  public:
    virtual ~USubsystem();
    virtual void Tick(FLOAT DeltaTime);
};
class UEngine : public USubsystem
{
  public:
    BYTE unk_28[0xa4 - 0x28];
    BITFIELD UseSound : 1;
    BITFIELD UseStaticMeshBatching : 1;
};
class FRenderTransformTarget
{
  public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void SetTransform(FRenderInterface *RI, INT Type, const FMatrix &Matrix);
};
enum { DT_StaticMesh = 8 };
extern INT GRenderFlag;
extern INT GRenderMode;

inline void FLevelRenderState::DrawActor(FDynamicActor *Actor, UBOOL UpdateLights)
{
    RI->PushState();
    RI->SetCullMode(SceneNode->Determinant * Actor->Determinant < 0.f);
    if (UpdateLights && Actor->Lights)
        Actor->UpdateLightFade(SceneNode);
    Actor->Render(SceneNode, Actor->Lights, Actor->Projectors, RI, 1, &PostActors);
    RI->PopState();
}

AActor *AActor::GetLightingActor() { return bUseLightingFromBase && Base ? Base->GetLightingActor() : this; }

UBOOL FLevelSceneNode::IsBspSectionVisible(INT Section) const
{
    if (RenderState->SectionDrawLists[Section])
        return 1;
    for (FTranslucentListNode *Node = RenderState->Translucent; Node; Node = Node->Next)
        if (Node->bIsBsp && Section == RenderState->Model->Nodes(Node->iNode).iSection)
            return 1;
    return 0;
}

UBOOL FLevelSceneNode::IsActorVisible(AActor *Actor, bool UseStaticMeshLists) const
{
    if (UseStaticMeshLists && Actor->DrawType == DT_StaticMesh && Actor->bStatic &&
        !Actor->Projectors.ArrayNum && Actor->StaticMesh && !Actor->StaticMesh->UseVertexColor) {
        for (TList<FDynamicActor *> *List = RenderState->StaticActors; List; List = List->Next)
            if (List->Element->Actor == Actor)
                return 1;
    } else {
        for (TList<FDynamicActor *> *List = RenderState->Actors; List; List = List->Next)
            if (List->Element->Actor == Actor)
                return 1;
    }
    for (FTranslucentListNode *Node = RenderState->Translucent; Node; Node = Node->Next)
        if (!Node->bIsBsp && Node->DynamicActor->Actor == Actor)
            return 1;
    return 0;
}

void DrawLevelPass(FLevelRenderState &State, INT Pass, UBOOL LightFriendly, FLevelSceneNode *VisibilityScene)
{
    FRenderInterface *RI = State.RI;
    RI->PushState();
    RI->TransformTarget->SetTransform(RI, 0, GIdentityMatrix);
    if (Pass == 0) {
        if (LightFriendly) {
            for (TList<INT> *List = State.SectionList; List; List = List->Next) {
                INT Section = List->Element;
                if (VisibilityScene->IsBspSectionVisible(Section) && State.SectionProjectors[Section] &&
                    IsLightFriendlyBspSection(State.Model, Section))
                    State.SectionDrawLists[Section]->Render(State.SceneNode, RI, 1);
            }
            for (TList<FDynamicActor *> *List = State.StaticActors; List; List = List->Next) {
                FDynamicActor *Actor = List->Element;
                if (VisibilityScene->IsActorVisible(Actor->Actor,
                                                    State.Level->Engine->UseStaticMeshBatching == 1))
                    State.DrawActor(Actor, 0);
            }
            for (TList<FDynamicActor *> *List = State.LightFriendlyActors; List; List = List->Next) {
                FDynamicActor *Actor = List->Element;
                if (VisibilityScene->IsActorVisible(Actor->Actor,
                                                    State.Level->Engine->UseStaticMeshBatching == 1))
                    State.DrawActor(Actor, 0);
            }
        } else {
            for (TList<INT> *List = State.SectionList; List; List = List->Next) {
                INT Section = List->Element;
                if (VisibilityScene->IsBspSectionVisible(Section) && State.SectionProjectors[Section] &&
                    !IsLightFriendlyBspSection(State.Model, Section))
                    State.SectionDrawLists[Section]->Render(State.SceneNode, RI, 1);
            }
            for (TList<FDynamicActor *> *List = State.RegularActors; List; List = List->Next) {
                FDynamicActor *Actor = List->Element;
                if (VisibilityScene->IsActorVisible(Actor->Actor,
                                                    State.Level->Engine->UseStaticMeshBatching == 1))
                    State.DrawActor(Actor, 0);
            }
            if (State.AdditionalActors) {
                GRenderFlag = 0;
                GRenderMode = 1;
                for (TList<FDynamicActor *> *List = State.AdditionalActors; List; List = List->Next) {
                    FDynamicActor *Actor = List->Element;
                    if (VisibilityScene->IsActorVisible(Actor->Actor,
                                                        State.Level->Engine->UseStaticMeshBatching == 1))
                        State.DrawActor(Actor, 0);
                }
                GRenderMode = 2;
            }
        }
    } else if (Pass == 3) {
        for (TList<INT> *List = State.SectionList; List; List = List->Next) {
            INT Section = List->Element;
            if (State.SectionLights[Section]) {
                State.RI->SetSectionLights(State.SectionLights[Section]);
                State.SectionDrawLists[List->Element]->Render(State.SceneNode, RI, 1);
            }
        }
        for (TList<FDynamicActor *> *List = State.Actors; List; List = List->Next)
            if (List->Element->SectionLights) {
                State.RI->SetSectionLights(List->Element->SectionLights);
                State.DrawActor(List->Element, 0);
            }
        for (TList<FDynamicActor *> *List = State.LightFriendlyActors; List; List = List->Next)
            if (List->Element->SectionLights) {
                State.RI->SetSectionLights(List->Element->SectionLights);
                State.DrawActor(List->Element, 0);
            }
        for (TList<FDynamicActor *> *List = State.RegularActors; List; List = List->Next)
            if (List->Element->SectionLights) {
                State.RI->SetSectionLights(List->Element->SectionLights);
                State.DrawActor(List->Element, 0);
            }
    } else {
        if (LightFriendly) {
            for (TList<INT> *List = State.SectionList; List; List = List->Next) {
                INT Section = List->Element;
                if (State.SectionProjectors[Section] && IsLightFriendlyBspSection(State.Model, Section))
                    State.SectionDrawLists[Section]->Render(State.SceneNode, RI, 1);
            }
        } else {
            for (TList<INT> *List = State.SectionList; List; List = List->Next) {
                INT Section = List->Element;
                if (State.SectionProjectors[Section] && !IsLightFriendlyBspSection(State.Model, Section))
                    State.SectionDrawLists[Section]->Render(State.SceneNode, RI, 1);
            }
        }
        if (Pass == 1) {
            if (LightFriendly) {
                for (TList<FDynamicActor *> *List = State.LightFriendlyActors; List; List = List->Next)
                    State.DrawActor(List->Element, 1);
            } else {
                for (TList<FDynamicActor *> *List = State.RegularActors; List; List = List->Next)
                    State.DrawActor(List->Element, 1);
                if (State.AdditionalActors) {
                    GRenderFlag = 0;
                    GRenderMode = 1;
                    for (TList<FDynamicActor *> *List = State.AdditionalActors; List; List = List->Next)
                        State.DrawActor(List->Element, 1);
                    GRenderMode = 2;
                }
            }
        } else {
            for (TList<FDynamicActor *> *List = State.RegularActors; List; List = List->Next)
                State.DrawActor(List->Element, 0);
            if (State.AdditionalActors) {
                GRenderFlag = 0;
                GRenderMode = 1;
                for (TList<FDynamicActor *> *List = State.AdditionalActors; List; List = List->Next)
                    State.DrawActor(List->Element, 0);
                GRenderMode = 2;
            }
        }
    }
    RI->PopState();
}

FConvexVolume *BuildPortalVolume(
    FLevelRenderState *Context,
    FPoly *Poly,
    UBOOL bUseFog)
{
    FConvexVolume *Volume = new(GSceneMem) FConvexVolume;
    const FVector &Normal = Poly->Normal;
    const FPlane PortalPlane(Poly->Vertex[0], Normal);
    Volume->BoundingPlanes[Volume->NumPlanes++] = PortalPlane;
    for (INT i = 0; i < (INT)Poly->NumVertices && Volume->NumPlanes < FConvexVolume::MaxPlanes - 1; i++)
    {
        FPlane Plane(
            Context->SceneNode->ViewOrigin,
            Poly->Vertex[i],
            Poly->Vertex[(i + 1) % Poly->NumVertices]);
        Volume->BoundingPlanes[Volume->NumPlanes++] = Plane;
    }
    if (bUseFog)
    {
        FLevelSceneNode *SceneNode = Context->SceneNode;
        ULevel *Level = Context->Level;
        UModel *Model = Level->Model;
        AZoneInfo *ZoneInfo;
        if (SceneNode->ViewZone < Model->Zones.Num() && Model->Zones(SceneNode->ViewZone).ZoneActor)
            ZoneInfo = Model->Zones(SceneNode->ViewZone).ZoneActor;
        else
            ZoneInfo = Level->GetLevelInfo();
        if (ZoneInfo->bDistanceFog &&
            SceneNode->Viewport->Actor->RendMap != 0x26 &&
            SceneNode->Viewport->Actor->RendMap != 0x24)
        {
            FLOAT FogEnd = ZoneInfo->DistanceFogEnd;
            FVector ViewNormal = (SceneNode->Deproject(FPlane(0.f, 0.f, 0.f, NEAR_CLIPPING_PLANE)) - SceneNode->ViewOrigin).SafeNormal();
            Volume->BoundingPlanes[Volume->NumPlanes++] = FPlane(Context->SceneNode->ViewOrigin + ViewNormal * FogEnd, ViewNormal);
        }
    }
    return Volume;
}
