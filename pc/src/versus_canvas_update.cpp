#include "versus_build.h"
#include "versus_canvas.h"
#include "versus_canvas_util.h"
#include "versus_canvas_viewport.h"

void UCanvas::Update()
{
    const EName NAME_Reset = (EName)542;
    ProcessEvent(FindFunctionChecked(NAME_Reset, 0), 0, 0);
    SizeX = (INT)(ClipX = (FLOAT)Viewport->SizeX);
    SizeY = (INT)(ClipY = (FLOAT)Viewport->SizeY);
    pCanvasUtil->SetTransforms(Viewport->RI, (FLOAT)Viewport->SizeX, (FLOAT)Viewport->SizeY);
}

class FRenderInterface {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Clear(UBOOL UseColor, FColor Color, UBOOL UseDepth, FLOAT Depth, UBOOL UseStencil, DWORD Stencil);
};

class UClient : public UObject {
public:
    BYTE unk_28[0x2c - 0x28];
    TArray<UViewport *> Viewports;
};

class USubsystem : public UObject {
public:
    virtual void Tick(FLOAT Delta);
};
class UEngine : public USubsystem {
public:
    virtual void Init();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void Draw(UViewport *Viewport, UBOOL Blit, BYTE *HitData, INT *HitSize);
    BYTE unk_28[8];
    UClient *Client;
};
class UGameEngine : public UEngine {
public:
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void PaintProgress();
};
void UGameEngine::PaintProgress()
{
    if (Client && Client->Viewports.Num()) {
        UViewport *Viewport = Client->Viewports(0);
        if (Viewport && Viewport->Canvas && Viewport->RI) {
            Viewport->Canvas->Update();
            const FColor Black = {0, 0, 0, 255};
            Viewport->RI->Clear(0, Black, 1, 1.0f, 1, 0);
            Draw(Viewport, 1, 0, 0);
            Viewport->Present();
        }
    }
}

void FCanvasUtil::SetTransforms(FRenderInterface* InRI, FLOAT SizeX, FLOAT SizeY)
{
    RI = InRI;
    CanvasToScreen = FTranslationMatrix(FVector(-SizeX / 2.0f - 0.5f, -SizeY / 2.0f - 0.5f, 0.0f))
                   * FScaleMatrix(FVector(2.0f / SizeX, -2.0f / SizeY, 1.0f));
    ScreenToCanvas = CanvasToScreen.Inverse();
}

FScaleMatrix::FScaleMatrix(const FVector& Scale)
    : FMatrix(FPlane(Scale.X, 0, 0, 0), FPlane(0, Scale.Y, 0, 0), FPlane(0, 0, Scale.Z, 0), FPlane(0, 0, 0, 1)) {}

FTranslationMatrix::FTranslationMatrix(const FVector& Delta)
    : FMatrix(FPlane(1, 0, 0, 0), FPlane(0, 1, 0, 0), FPlane(0, 0, 1, 0), FPlane(Delta.X, Delta.Y, Delta.Z, 1)) {}

FMatrix GIdentityMatrix(
    FPlane(1.f, 0.f, 0.f, 0.f),
    FPlane(0.f, 1.f, 0.f, 0.f),
    FPlane(0.f, 0.f, 1.f, 0.f),
    FPlane(0.f, 0.f, 0.f, 1.f));

#include "versus_matrix_determinant.inl"
#include "versus_matrix_inverse.inl"
#include "versus_matrix_product.inl"
