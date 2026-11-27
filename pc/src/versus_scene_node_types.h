#ifndef VERSUS_SCENE_NODE_TYPES_H
#define VERSUS_SCENE_NODE_TYPES_H

class UViewport;
class FRenderTarget;
class AActor;
class ULevel;
class UModel;
class FLevelSceneNode;
class FCameraSceneNode;
class FActorSceneNode;
#include "versus_render_interface.h"
#include "versus_canvas_matrix.h"

class FSceneNode {
public:
    virtual ~FSceneNode() {}
    virtual FSceneNode *AsSceneNode() { return this; }
    virtual void Render(FRenderInterface *RI, UBOOL Clear) = 0;
    virtual FLevelSceneNode *AsLevelSceneNode() { return 0; }
    virtual FCameraSceneNode *AsCameraSceneNode() { return 0; }
    virtual FActorSceneNode *AsActorSceneNode() { return 0; }
    virtual FSceneNode *VirtualSlot6() { return 0; }
    virtual FSceneNode *VirtualSlot7() { return 0; }
    virtual FSceneNode *VirtualSlot8() { return 0; }

    FSceneNode(FSceneNode *InParent);
    FSceneNode(UViewport *InViewport, FRenderTarget *InTarget)
        : Viewport(InViewport), RenderTarget(InTarget), Parent(0), Recursion(0) {}

    UViewport *Viewport;
    FRenderTarget *RenderTarget;
    FSceneNode *Parent;
    INT Recursion;
    FMatrix WorldToCamera;
    FMatrix CameraToWorld;
    FMatrix CameraToScreen;
    FMatrix ScreenToCamera;
    FMatrix WorldToScreen;
    FMatrix ScreenToWorld;
    FVector ViewOrigin;
    FVector CameraX;
    FVector CameraY;
    FLOAT Determinant;
};

class FLevelSceneNode : public FSceneNode {
public:
    virtual FLevelSceneNode *AsLevelSceneNode() { return this; }
    FLevelSceneNode(FLevelSceneNode *InParent, INT InViewZone, FMatrix LocalToParent);
    FLevelSceneNode(UViewport *InViewport, FRenderTarget *InTarget);
    virtual void Render(FRenderInterface *RI, UBOOL Clear);
    virtual void VirtualSlot9();
    virtual UBOOL VirtualSlot10(const AActor *Actor);
    virtual UBOOL VirtualSlot11(const void *Object) { return 1; }
    virtual UBOOL VirtualSlot12(const void *Object);
    ULevel *Level;
    UModel *Model;
    AActor *ViewActor;
    INT ViewZone;
    INT InvisibleZone;
    DWORD StencilRef;
    struct FLevelRenderState *RenderState;
    UBOOL IsBspSectionVisible(INT Section) const;
    UBOOL IsActorVisible(AActor *Actor, bool UseStaticMeshLists) const;
};

class FCameraSceneNode : public FLevelSceneNode {
public:
    virtual FCameraSceneNode *AsCameraSceneNode() { return this; }
    FCameraSceneNode(UViewport *InViewport, FRenderTarget *InTarget, AActor *CameraActor,
                     const FVector &Location, const FRotator &Rotation, FLOAT FOV);
    virtual void Render(FRenderInterface *RI, UBOOL Clear);
    void UpdateMatrices();
    FRotator ViewRotation;
    FLOAT FovAngle;
};

class FActorSceneNode : public FCameraSceneNode {
public:
    virtual FActorSceneNode *AsActorSceneNode() { return this; }
    FActorSceneNode(UViewport *InViewport, FRenderTarget *InTarget, AActor *CameraActor,
                   const FVector &Location, const FRotator &Rotation, FLOAT FOV, AActor *InActor)
        : FCameraSceneNode(InViewport, InTarget, CameraActor, Location, Rotation, FOV),
          Actor(InActor) {}
    virtual void Render(FRenderInterface *RI, UBOOL Clear);
    AActor *Actor;
};
#endif
