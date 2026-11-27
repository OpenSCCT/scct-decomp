#include "versus_stats_render_context.h"
#include "versus_scene_level_types.h"
#include "versus_canvas.h"
#include "versus_viewport_types.h"
#include "versus_scene_node_types.h"
#include "versus_canvas_util.h"
#include "versus_client_types.h"
#include "versus_hud_types.h"
#include "versus_interaction_types.h"
#include "versus_interaction_master.h"
#include "versus_canvas_materials.h"
#include "versus_solid_color_texture.h"
#include "versus_global_temp_objects.h"
#include "versus_stats_data.h"

extern FOutputDevice *GError;
#include "versus_object_factory.h"
extern UObject *GObjTransientPkg;
extern UGlobalTempObjects *GGlobalTempObjects;
extern DWORD GUglyHackFlags;
extern const FVector &GMath_One;
extern const FVector &GMath_Zero;
void UpdateVertexPools(UViewport *Viewport);

static const EName NAME_FirstPersonRender = (EName)2843;
static const EName NAME_PostRender = (EName)2844;

void APawn::eventFirstPersonRender(UCanvas *Canvas)
{
    struct { UCanvas *Canvas; } Parms;
    Parms.Canvas = Canvas;
    ProcessEvent(FindFunctionChecked(NAME_FirstPersonRender, 0), &Parms, 0);
}

void AHUD::eventPostRender(UCanvas *Canvas)
{
    struct { UCanvas *Canvas; } Parms;
    Parms.Canvas = Canvas;
    ProcessEvent(FindFunctionChecked(NAME_PostRender, 0), &Parms, 0);
}

static FLOAT ClampUnit(FLOAT Value)
{
    return Value < 0.f ? 0.f : Value < 1.f ? Value : 1.f;
}

void FPlayerSceneNode::Render(FRenderInterface *RI, UBOOL Clear)
{
    RI->PushState();
    Viewport->Canvas->Update();
    Viewport->Canvas->pCanvasUtil->Flush();
    if (Viewport->InteractionMaster)
        Viewport->InteractionMaster->MasterProcessPreRender(Viewport->Canvas);
    if (Viewport->bLetterBox) {
        RI->Clear(1, FColor(0, 0, 0), 0, 0.f, 0, 0);
        Viewport->AspectRatio = Viewport->DesiredAspectRatio;
        UpdateMatrices();
        FLOAT Height = Viewport->SizeY / Viewport->AspectRatio;
        RI->SetViewport(0, (INT)((Viewport->SizeY - Height) * 0.5f), Viewport->SizeX, (INT)Height);
    }
    FLevelSceneNode::Render(RI, 1);
    if (Viewport->Actor->Pawn)
        Viewport->Actor->Pawn->eventFirstPersonRender(Viewport->Canvas);
    Viewport->Precache();
    Viewport->Canvas->pCanvasUtil->Flush();
    if (Viewport->bLetterBox) {
        Viewport->AspectRatio = 1.f;
        UpdateMatrices();
        RI->SetViewport(0, 0, Viewport->SizeX, Viewport->SizeY);
    }

    UClient *Client = static_cast<UClient *>(Viewport->Outer);
    const FVector &Scale = Client->ScreenFlashes ? Viewport->Actor->FlashScale : GMath_One;
    const FVector &Fog = Client->ScreenFlashes ? Viewport->Actor->FlashFog : GMath_Zero;
    const FLOAT FlashScale = ClampUnit(Scale.X);
    const FVector FlashFog(ClampUnit(Fog.X), ClampUnit(Fog.Y), ClampUnit(Fog.Z));
    if (FlashScale < 1.f) {
        static FSolidColorTexture Texture(FColor(128, 128, 128));
        static UProxyBitmapMaterial *Proxy;
        static UFinalBlend *Blend;
        if (!Proxy) {
            Proxy = static_cast<UProxyBitmapMaterial *>(ConstructObject(&UProxyBitmapMaterial::PrivateStaticClass,
                                                                        GObjTransientPkg));
            GGlobalTempObjects->AddReference((UObject **)&Proxy);
            Proxy->SetTextureInterface(&Texture);
        }
        if (!Blend) {
            Blend = static_cast<UFinalBlend *>(ConstructObject(&UFinalBlend::PrivateStaticClass, GObjTransientPkg));
            GGlobalTempObjects->AddReference((UObject **)&Blend);
            Blend->FrameBufferBlending = 2;
            Blend->Material = Proxy;
            Blend->ZWrite = 0;
        }
        FCanvasUtil Canvas(&Viewport->RenderTarget, RI);
        Canvas.DrawTile(0.f, 0.f, Viewport->SizeX, Viewport->SizeY, 0.f, 0.f, 0.f, 0.f, 0.f,
                        Blend, FColor(FPlane(FlashFog, 1.f - FlashScale)));
    }
    GUglyHackFlags |= 1;
    if (Viewport->Actor->myHUD)
        Viewport->Actor->myHUD->eventPostRender(Viewport->Canvas);
    Viewport->Canvas->pCanvasUtil->Flush();
    GUglyHackFlags &= ~1;
    if (Viewport->InteractionMaster)
        Viewport->InteractionMaster->MasterProcessPostRender(Viewport->Canvas);
    GStats.Render(Viewport, Level->Engine);
    UpdateVertexPools(Viewport);
    Viewport->Canvas->pCanvasUtil->Flush();
    RI->PopState();
}
