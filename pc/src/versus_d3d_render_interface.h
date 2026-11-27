#ifndef VERSUS_D3D_RENDER_INTERFACE_H
#define VERSUS_D3D_RENDER_INTERFACE_H

#include "versus_render_interface.h"

// A render state: render target and depth stencil, then the viewport rectangle.
struct FD3DRenderState
{
    IDirect3DSurface8 *RenderTarget;            // 0x00
    IDirect3DSurface8 *DepthStencilSurface;     // 0x04
    INT ViewportX, ViewportY;                   // 0x08
    INT ViewportWidth, ViewportHeight;          // 0x10
};

class UD3DRenderDevice;
class FBaseTexture;
class FRenderTarget;
class FD3DTexture;
class UBitmapMaterial;
struct FD3DStageState;

class FD3DRenderInterface : public FRenderInterface
{
public:
    BYTE unk_18[0x108 - 0x18];
    UD3DRenderDevice *RenderDevice;             // 0x108
    UViewport *Viewport;                        // 0x10c
    BYTE unk_110[0x2af10 - 0x110];
    FD3DRenderState *CurrentState;              // 0x2af10
    BYTE unk_2af14[0x2b344 - 0x2af14];
    INT CurrentStateIndex;                      // 0x2b344
    BYTE unk_2b348[0x2b364 - 0x2b348];
    BYTE *HitData;                              // 0x2b364
    INT *HitSize;                               // 0x2b368
    INT HitCount;                               // 0x2b36c

    virtual UBOOL SetRenderTarget(FRenderTarget *RenderTarget);
    FD3DTexture *CacheTexture(FBaseTexture *Texture);
    void SetStageTexture(FD3DStageState *Stage, UBitmapMaterial *Texture);

    void Locked(UViewport *InViewport, BYTE *InHitData, INT *InHitSize);
    void Unlocked()
    {
        PopState();
        CurrentState->RenderTarget->Release();
        CurrentState->RenderTarget = 0;
        CurrentState->DepthStencilSurface->Release();
        CurrentState->DepthStencilSurface = 0;
    }
};

#endif
