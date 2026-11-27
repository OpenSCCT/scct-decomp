#ifndef VERSUS_D3D_RENDER_DEVICE_H
#define VERSUS_D3D_RENDER_DEVICE_H

#include "versus_native_subsystem.h"

class UViewport;
class FRenderInterface;
class FD3DDynamicVertexStream;
class FD3DResource;
class UD3DRenderDevice;
struct IDirect3DVertexBuffer8;
struct IDirect3DDevice8;

struct FD3DDeferredStreamState {
    IDirect3DVertexBuffer8 *StreamData;
    INT StreamStride;
};

struct FD3DTextureStageState {
    DWORD TexCoordIndex;
    DWORD unk_04[2];
    DWORD TextureTransformFlags;
    DWORD unk_10[9];
};

// Deferred device state embedded in the render device at +0x2fb58.
struct FD3DDeferredState {
    UD3DRenderDevice *RenDev;            // +0x000
    BYTE unk_004[0x4d4 - 4];
    FD3DDeferredStreamState StreamState[16];     // +0x4d4 (pending)
    BYTE unk_554[0x958 - 0x554];
    FD3DTextureStageState HardwareStages[8];  // +0x958, updated by 0x6cc60
    BYTE unk_af8[0xdac - 0xaf8];
    FD3DDeferredStreamState HardwareStream[16];  // +0xdac (set on the device)
    void UnSetVertexBuffer(IDirect3DVertexBuffer8 *VertexBuffer);
};

class URenderDevice : public USubsystem {
public:
    void StaticConstructor();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void UnSetRes(UViewport *Viewport);
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual FRenderInterface *Lock(UViewport *Viewport, unsigned char *HitData, int *HitSize);
    virtual void Unlock(FRenderInterface *RenderInterface);
    virtual void Present(UViewport *Viewport);

    BYTE unk_28[0x4];
    BYTE unk_2c;
    BYTE unk_2d[0x7];
    FString Description;
    INT DescFlags;
    UBOOL HighDetailActors;
    UBOOL SuperHighDetailActors;
    UBOOL DetailTextures;
    BYTE unk_50[0x8];
    UBOOL unk_58;
    UBOOL UseStencil;
    UBOOL Use16bit;
    UBOOL Use16bitTextures;
    BYTE unk_68[0x48];
};

class UD3DRenderDevice : public URenderDevice {
public:
    void StaticConstructor();

    FD3DResource *ResourceList;
    FD3DResource *ResourceHash[4096];
    BYTE unk_40b4[0x40bc - 0x40b4];
    FD3DDynamicVertexStream *DynamicVertexStream;
    BYTE unk_40c0[0x40c8 - 0x40c0];
    UBOOL UsePrecaching;
    UBOOL UseTrilinear;
    BYTE unk_40d0[0x4];
    UBOOL UseVSync;
    UBOOL UseHardwareTL;
    UBOOL UseHardwareVS;
    UBOOL UseCubemaps;
    BYTE unk_40e4[0x10];
    UBOOL UseTripleBuffering;
    UBOOL ReduceMouseLag;
    BYTE unk_40fc[0x10];
    UBOOL CheckForOverflow;
    UBOOL UseNPatches;
    UBOOL DecompressTextures;
    BYTE unk_4118[0x4];
    INT AdapterNumber;
    BYTE unk_4120[0x4];
    INT MaxPixelShaderVersion;
    INT LevelOfAnisotropy;
    FLOAT DetailTexMipBias;
    FLOAT DefaultTexMipBias;
    FLOAT TesselationFactor;
    INT DesiredRefreshRate;
    BYTE unk_413c[0x41d0 - 0x413c];
    DWORD MaxTextureBlendStages;
    BYTE unk_41d4[0x41f4 - 0x41d4];
    DWORD MaxVertexIndex;
    INT MaxStreams;
    BYTE unk_41fc[0x4698 - 0x41fc];
    INT FrameCounter;
    BYTE unk_469c[0x46a4 - 0x469c];
    IDirect3DDevice8 *Direct3DDevice8;
    BYTE unk_46a8[0x2fb4c - 0x46a8];
    TArray<BYTE> Scratch;
    FD3DDeferredState DeferredState;
};

#endif
