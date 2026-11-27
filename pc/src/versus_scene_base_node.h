#ifndef VERSUS_SCENE_BASE_NODE_H
#define VERSUS_SCENE_BASE_NODE_H

class UViewport;
class FRenderTarget;
class AActor;
class ULevel;
class UModel;
class FLevelSceneNode;
class FCameraSceneNode;
class FActorSceneNode;
#include "versus_render_interface.h"
#include "versus_matrix_types.h"

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

    FVector Deproject(const FPlane &Screen);

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

#endif
