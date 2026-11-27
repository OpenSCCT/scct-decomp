#include "versus_build.h"
#include "versus_pawn_action_events.h"
#include "versus_scene_level_types.h"
#include "versus_scene_model_types.h"
#include "versus_canvas.h"
#include "versus_viewport_types.h"
#include "versus_scene_node_types.h"
#include "versus_canvas_util.h"
#include "versus_render_device.h"


FLevelSceneNode::FLevelSceneNode(UViewport *V, FRenderTarget *Target)
    : FSceneNode(V, Target)
{
    Level = V->Actor->XLevel;
    Model = Level->Model;
    ViewZone = -1;
    InvisibleZone = -1;
    ViewActor = 0;
    StencilRef = 0;
    if (!Model->Sections.ArrayNum)
        Model->BuildRenderData();
    if (!Level->unk_4ae0)
        Level->BuildRenderData();
}

FCameraSceneNode::FCameraSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget, AActor *CameraActor,
                                   const FVector &CameraLocation, const FRotator &CameraRotation, FLOAT CameraFOV)
    : FLevelSceneNode(InViewport, InRenderTarget)
{
    Model->PointRegion(CameraActor->Level, CameraLocation);
    ViewOrigin = CameraLocation;
    ViewActor = CameraActor;
    ViewZone = Viewport->Precaching ? 0 : Model->PointRegion(CameraActor->Level, ViewOrigin).ZoneNumber;
    ViewRotation = CameraRotation;
    FovAngle = CameraFOV;
    UpdateMatrices();
}

void UViewport::DrawPendingView()
{
    enum { REN_DynLight = 5, REN_Fade = 0x22, REN_Flash = 0x25 };
    if (bHitTesting || Precaching)
        return;

    if (FirstPersonActor) {
        APlayerController *A = Actor;
        AActor *ViewActor = A;
        FVector CameraLocation;
        CameraLocation.X = A->Location.X;
        CameraLocation.Y = A->Location.Y;
        CameraLocation.Z = A->Location.Z;
        FRotator CameraRotation = A->Rotation;
        const FColor Black(0, 0, 0);
        RI->Clear(0, Black, 1, 1.0f, 0, 0);
        Actor->PlayerCalcView(ViewActor, CameraLocation, CameraRotation, 1);
        {
            FActorSceneNode Node(this, &RenderTarget, ViewActor, CameraLocation, CameraRotation,
                                       Actor->FovAngle, FirstPersonActor);
            FSceneNode *Scene = &Node;
            Scene->Render(RI, 1);
        }
        FirstPersonActor = 0;
    }

    if (Actor->bCaptureRemanence) {
        RI->Effect80(SizeX, SizeY);
        Actor->bCaptureRemanence = 0;
    }
    INT Mode = Actor->RendMap;
    if (Mode != 0x24 && Mode != 0x26 && !RI->Flashing && Actor->RemanenceBlendFactor > 0.0039f)
        RI->Effect84(SizeX, SizeY, Actor->RemanenceBlendFactor);

    if (RI->Fading) {
        RI->BeginFade(SizeX, SizeY);
        RI->EffectAlpha = 0;
        RI->Fading = 0;
        Actor->RendMap = REN_Fade;
    } else if (RI->Flashing) {
        RI->BeginFlash(SizeX, SizeY);
        RI->Flashing = 0;
        Actor->RendMap = REN_Flash;
    } else {
        Mode = Actor->RendMap;
        if (Mode == REN_DynLight) {
            RI->EffectAlpha = 0;
            RI->Effect98();
        } else if (Mode == 0x24) {
            RI->Effect90(SizeX, SizeY, static_cast<ALevelInfo *>(Actor->XLevel->Actors(0))->pThermalTexture_A);
        } else if (Mode == 0x26) {
            RI->Effect94(SizeX, SizeY, static_cast<ALevelInfo *>(Actor->XLevel->Actors(0))->pThermalTexture_A);
        }
    }
    RI->SetViewport(0, 0, SizeX, SizeY);
    RenderEntries.Reset();

    Mode = Actor->RendMap;
    if ((Mode == 0x24 || Mode == 0x26 || Mode == REN_Flash) && Actor->RemanenceBlendFactor > 0.0039f)
        RI->Effect84(SizeX, SizeY, Actor->RemanenceBlendFactor);
}

void UpdateVertexPools(UViewport *Viewport);

void FCameraSceneNode::Render(FRenderInterface *RI, UBOOL Clear)
{
    RI->PushState();
    FLevelSceneNode::Render(RI, 1);
    Viewport->DrawPendingView();
    UpdateVertexPools(Viewport);
    Viewport->Canvas->pCanvasUtil->Flush();
    RI->PopState();
}

#include "versus_malloc.h"

typedef unsigned __int64 QWORD;
inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }

#pragma pack(push, 4)
class FVertexPool : public FVertexStream
{
public:
    QWORD CacheId;          // +0x04
    INT Size;               // +0x0c
    INT Revision;           // +0x10
    INT unk_14;             // +0x14
    FVertexStream *Stream;  // +0x18
    FVertexPool *NextPool;  // +0x1c
    INT UnusedFrames;       // +0x20

    ~FVertexPool()
    {
        if (NextPool)
            delete NextPool;
    }

    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual INT GetStride();
    virtual INT GetSize();
};

#pragma pack(pop)

extern FVertexPool *GFirstVertexPool;
#include "versus_vertex_pool_update.inl"
