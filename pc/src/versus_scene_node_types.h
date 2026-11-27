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
class FRenderInterface
{
public:
    virtual void PushState();                                      // +0x00
    virtual void PopState();                                       // +0x04
    virtual void Slot08();
    virtual void SetViewport(INT X, INT Y, INT Width, INT Height); // +0x0c
    virtual void Clear(UBOOL UseColor, FColor Color, UBOOL UseDepth, FLOAT Depth,
                       UBOOL UseStencil, DWORD Stencil);           // +0x10
    virtual void PushHit(const BYTE *Data, INT Count); virtual void PopHit(INT Count, UBOOL Force); virtual void Slot1c();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3c();
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5c();
    virtual void Slot60(); virtual void DrawPrimitive(INT Type, INT FirstIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); virtual void Slot68(); virtual void Slot6c();
    virtual void Slot70(); virtual void Slot74();
    virtual void UpdateEffects();                                  // +0x78
    virtual void Slot7c();
    virtual void Effect80(INT SizeX, INT SizeY);                   // +0x80
    virtual void Effect84(INT SizeX, INT SizeY, FLOAT Amount);     // +0x84
    virtual void BeginFade(INT SizeX, INT SizeY);                  // +0x88
    virtual void BeginFlash(INT SizeX, INT SizeY);                 // +0x8c
    virtual void Effect90(INT SizeX, INT SizeY, class UTexture *Texture);     // +0x90
    virtual void Effect94(INT SizeX, INT SizeY, class UTexture *Texture);     // +0x94
    virtual void Effect98();                                       // +0x98
    INT  Fading;                                                   // +0x04
    INT  Flashing;                                                 // +0x08
    BYTE EffectAlpha;                                              // +0x0c
};


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

    FSceneNode(UViewport *InViewport, FRenderTarget *InTarget)
        : Viewport(InViewport), RenderTarget(InTarget), Parent(0), Recursion(0) {}

    UViewport *Viewport;
    FRenderTarget *RenderTarget;
    FSceneNode *Parent;
    INT Recursion;
    BYTE unk_14[0x194 - 0x14];
    FVector ViewOrigin;
    BYTE unk_1a0[0x1b8 - 0x1a0];
    FLOAT Determinant;
};

class FLevelSceneNode : public FSceneNode {
public:
    virtual FLevelSceneNode *AsLevelSceneNode() { return this; }
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
    BYTE unk_1d4[4];
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
