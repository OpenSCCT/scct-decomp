#ifndef VERSUS_SCENE_NODE_TYPES_H
#define VERSUS_SCENE_NODE_TYPES_H

#include "versus_canvas_matrix.h"
#include "versus_scene_base_node.h"

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
