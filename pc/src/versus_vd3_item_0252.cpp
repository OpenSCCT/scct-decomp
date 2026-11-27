// Work item 0252: UD3DRenderDevice Lock / Unlock / Present / ReadPixels
// (vtable slots 35..38 of UD3DRenderDevice@30c1f0) and a small caps query.
// The object was built with VC7.0 /GL and linked /LTCG: Lock calls
// FD3DRenderInterface::Locked (0x60ac0) with this in ESI and the arguments in
// EAX, ECX, EDX, so Locked is defined here too so the linker sees its body.

#include "d3d8_viewport.h"

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef long HRESULT;
typedef struct HWND__ *HWND;

#define D3DERR_DEVICELOST       ((HRESULT)0x88760868L)
#define D3DERR_DEVICENOTRESET   ((HRESULT)0x88760869L)
#define D3DFMT_A8R8G8B8 21
#define D3DFMT_X8R8G8B8 22
#define D3DFMT_R5G6B5   23
#define D3DLOCK_READONLY 0x10

struct RECT { INT left, top, right, bottom; };
union LARGE_INTEGER { struct { DWORD LowPart; INT HighPart; }; __int64 QuadPart; };

extern "C" __declspec(dllimport) INT __stdcall QueryPerformanceCounter(LARGE_INTEGER *);
extern "C" __declspec(dllimport) INT __stdcall GetClientRect(HWND, RECT *);
extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD);

extern UBOOL GTimestamp;
DOUBLE appSeconds();

#pragma warning(disable : 4035)
inline DWORD appCycles()
{
    if (GTimestamp)
    {
        LARGE_INTEGER Cycles;
        QueryPerformanceCounter(&Cycles);
        return Cycles.LowPart;
    }
    __asm rdtsc
}

struct FColor
{
    BYTE B, G, R, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : R(InR), G(InG), B(InB), A(InA) {}
};

struct D3DLOCKED_RECT { INT Pitch; void *pBits; };
struct D3DSURFACE_DESC { INT Format; INT Type; DWORD Usage; INT Pool; UINT Size; INT MultiSampleType; UINT Width; UINT Height; };

struct IDirect3DSurface8
{
    virtual HRESULT __stdcall QueryInterface(void *, void **) = 0;
    virtual DWORD __stdcall AddRef() = 0;
    virtual DWORD __stdcall Release() = 0;
    virtual HRESULT __stdcall GetDevice(void **) = 0;
    virtual HRESULT __stdcall SetPrivateData(void *, const void *, DWORD, DWORD) = 0;
    virtual HRESULT __stdcall GetPrivateData(void *, void *, DWORD *) = 0;
    virtual HRESULT __stdcall FreePrivateData(void *) = 0;
    virtual HRESULT __stdcall GetContainer(void *, void **) = 0;
    virtual HRESULT __stdcall GetDesc(D3DSURFACE_DESC *) = 0;
    virtual HRESULT __stdcall LockRect(D3DLOCKED_RECT *, const RECT *, DWORD) = 0;
    virtual HRESULT __stdcall UnlockRect() = 0;
};

struct IDirect3DDevice8
{
    virtual HRESULT __stdcall QueryInterface(void *, void **) = 0;
    virtual DWORD __stdcall AddRef() = 0;
    virtual DWORD __stdcall Release() = 0;
    virtual HRESULT __stdcall TestCooperativeLevel() = 0;
    virtual UINT __stdcall GetAvailableTextureMem() = 0;
    virtual HRESULT __stdcall ResourceManagerDiscardBytes(DWORD) = 0;
    virtual HRESULT __stdcall GetDirect3D(void **) = 0;
    virtual HRESULT __stdcall GetDeviceCaps(void *) = 0;
    virtual HRESULT __stdcall GetDisplayMode(void *) = 0;
    virtual HRESULT __stdcall GetCreationParameters(void *) = 0;
    virtual HRESULT __stdcall SetCursorProperties(UINT, UINT, void *) = 0;
    virtual void __stdcall SetCursorPosition(UINT, UINT, DWORD) = 0;
    virtual INT __stdcall ShowCursor(INT) = 0;
    virtual HRESULT __stdcall CreateAdditionalSwapChain(void *, void **) = 0;
    virtual HRESULT __stdcall Reset(void *) = 0;
    virtual HRESULT __stdcall Present(const RECT *, const RECT *, HWND, const void *) = 0;
    virtual HRESULT __stdcall GetBackBuffer(UINT, INT, IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall GetRasterStatus(void *) = 0;
    virtual void __stdcall SetGammaRamp(DWORD, const void *) = 0;
    virtual void __stdcall GetGammaRamp(void *) = 0;
    virtual HRESULT __stdcall CreateTexture() = 0;
    virtual HRESULT __stdcall CreateVolumeTexture() = 0;
    virtual HRESULT __stdcall CreateCubeTexture() = 0;
    virtual HRESULT __stdcall CreateVertexBuffer() = 0;
    virtual HRESULT __stdcall CreateIndexBuffer() = 0;
    virtual HRESULT __stdcall CreateRenderTarget() = 0;
    virtual HRESULT __stdcall CreateDepthStencilSurface() = 0;
    virtual HRESULT __stdcall CreateImageSurface() = 0;
    virtual HRESULT __stdcall CopyRects() = 0;
    virtual HRESULT __stdcall UpdateTexture() = 0;
    virtual HRESULT __stdcall GetFrontBuffer(IDirect3DSurface8 *) = 0;
    virtual HRESULT __stdcall SetRenderTarget(IDirect3DSurface8 *, IDirect3DSurface8 *) = 0;
    virtual HRESULT __stdcall GetRenderTarget(IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall BeginScene() = 0;
    virtual HRESULT __stdcall EndScene() = 0;
    virtual HRESULT __stdcall Clear() = 0;
    virtual HRESULT __stdcall SetTransform() = 0;
    virtual HRESULT __stdcall GetTransform() = 0;
    virtual HRESULT __stdcall MultiplyTransform() = 0;
    virtual HRESULT __stdcall SetViewport(const D3DVIEWPORT8 *) = 0;
};

class UViewport
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
    virtual void *GetWindow();                  // slot 45
    BYTE Pad04[0xa0 - 4];
    INT SizeX;                                  // 0xa0
    INT SizeY;                                  // 0xa4
    BYTE PadA8[8];
    FLOAT ScaleX;                               // 0xb0
    FLOAT ScaleY;                               // 0xb4
};

#include "versus_d3d_render_interface.h"

// A device resource in the list at UD3DRenderDevice+0xb0.
class FD3DResource
{
public:
    virtual void v00();
    virtual UBOOL GetTexture_slot1();
    virtual UBOOL GetVertexStream_slot2();
    virtual UBOOL GetIndexBuffer_slot3();
    virtual void Flush_slot4();
    BYTE Pad04[0x18 - 4];
    FD3DResource *NextResource;                 // 0x18
    INT Pad1c;
    INT LastFrameUsed;                          // 0x20
};

class UD3DRenderDevice
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27();
    virtual UBOOL SetRes(UViewport *Viewport, INT NewX, INT NewY, UBOOL Fullscreen, INT ColorBytes, UBOOL bSaveSize); // slot 28
    virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual FRenderInterface *Lock(UViewport *Viewport, BYTE *HitData, INT *HitSize); // slot 35
    virtual void Unlock(FRenderInterface *RI);                                       // slot 36
    virtual void Present(UViewport *Viewport);                                       // slot 37
    virtual void ReadPixels(UViewport *Viewport, FColor *Pixels);                    // slot 38

    UD3DRenderDevice();

    BYTE Pad004[0xb0 - 4];
    FD3DResource *ResourceList;                 // 0xb0
    BYTE Padb4[0x467c - 0xb4];
    UBOOL ForceReset;                           // 0x467c
    UBOOL FullScreen;                           // 0x4680
    UViewport *LockedViewport;                  // 0x4684
    BYTE Pad4688[0x4698 - 0x4688];
    INT FrameCounter;                           // 0x4698
    BYTE Pad469c[0x46a4 - 0x469c];
    IDirect3DDevice8 *Direct3DDevice;           // 0x46a4
    DWORD BackBufferWidth;                      // 0x46a8
    DWORD BackBufferHeight;                     // 0x46ac
    BYTE Pad46b0[0x46d4 - 0x46b0];
    DWORD MaxFrameRate;                         // 0x46d4
    BYTE Pad46d8[4];
    FD3DRenderInterface RenderInterface;        // 0x46dc
};

// Was a local static in Present: time of the last Present.
extern DOUBLE UD3DRenderDevice_Present_LastPresentTime;

void FD3DRenderInterface::Locked(UViewport *InViewport, BYTE *InHitData, INT *InHitSize)
{
    Viewport = InViewport;
    HitCount = 0;
    HitData = InHitData;
    HitSize = InHitSize;

    IDirect3DSurface8 *RenderTarget = 0, *DepthStencilSurface = 0;
    RenderDevice->Direct3DDevice->GetRenderTarget(&RenderTarget);
    RenderDevice->Direct3DDevice->GetDepthStencilSurface(&DepthStencilSurface);

    CurrentState->ViewportX = 0;
    CurrentState->ViewportY = 0;
    CurrentState->ViewportWidth = Viewport->SizeX;
    CurrentState->ViewportHeight = Viewport->SizeY;
    CurrentState->DepthStencilSurface = DepthStencilSurface;
    CurrentState->RenderTarget = RenderTarget;

    CurrentStateIndex = 0;
    PushState();
}

FRenderInterface *UD3DRenderDevice::Lock(UViewport *Viewport, BYTE *HitData, INT *HitSize)
{
    appCycles();
    FrameCounter++;

    if (!Direct3DDevice)
    {
        ForceReset = 1;
        LockedViewport = 0;
        SetRes(Viewport, (INT)(Viewport->SizeX * Viewport->ScaleX), (INT)(Viewport->SizeY * Viewport->ScaleY), FullScreen, 0, 1);
    }

    HRESULT Result = Direct3DDevice->TestCooperativeLevel();
    if (Result < 0)
    {
        if (Result == D3DERR_DEVICELOST)
            return 0;
        if (Result == D3DERR_DEVICENOTRESET)
        {
            LockedViewport = 0;
            ForceReset = 1;
            SetRes(Viewport, (INT)(Viewport->SizeX * Viewport->ScaleX), (INT)(Viewport->SizeY * Viewport->ScaleY), FullScreen, 0, 1);
        }
    }

    LockedViewport = Viewport;

    D3DVIEWPORT8 ViewportInfo;
    ViewportInfo.Width = Viewport->SizeX;
    ViewportInfo.Height = Viewport->SizeY;
    if (!FullScreen)
    {
        RECT ClientRect;
        GetClientRect((HWND)Viewport->GetWindow(), &ClientRect);
        ViewportInfo.Width = ClientRect.right;
        ViewportInfo.Height = ClientRect.bottom;
    }
    ViewportInfo.X = 0;
    ViewportInfo.Y = 0;
    ViewportInfo.MinZ = 0.0f;
    ViewportInfo.MaxZ = 1.0f;
    if (ViewportInfo.Width > BackBufferWidth)
        ViewportInfo.Width = BackBufferWidth;
    if (ViewportInfo.Height > BackBufferHeight)
        ViewportInfo.Height = BackBufferHeight;

    if (Direct3DDevice->SetViewport(&ViewportInfo) < 0)
    {
        LockedViewport = 0;
        return 0;
    }

    Direct3DDevice->BeginScene();
    RenderInterface.Locked(Viewport, HitData, HitSize);
    return &RenderInterface;
}

void UD3DRenderDevice::Unlock(FRenderInterface *RI)
{
    for (FD3DResource *Resource = ResourceList; Resource; Resource = Resource->NextResource)
    {
        if (Resource->LastFrameUsed == FrameCounter)
        {
            if (Resource->GetTexture_slot1())
                Resource->Flush_slot4();
            else if (Resource->GetVertexStream_slot2())
                Resource->Flush_slot4();
            else if (Resource->GetIndexBuffer_slot3())
                Resource->Flush_slot4();
        }
    }

    Direct3DDevice->GetAvailableTextureMem();

    FD3DRenderInterface *D3DRI = (FD3DRenderInterface *)RI;
    if (D3DRI && D3DRI->HitSize)
        *D3DRI->HitSize = D3DRI->HitCount;

    RenderInterface.Unlocked();

    if (Direct3DDevice)
        Direct3DDevice->EndScene();

    LockedViewport = 0;
}

void UD3DRenderDevice::Present(UViewport *Viewport)
{
    appCycles();
    if (!Direct3DDevice)
        return;

    DOUBLE Elapsed = appSeconds() - UD3DRenderDevice_Present_LastPresentTime;
    DOUBLE MinFrameTime = 2.0f / MaxFrameRate - 0.001;
    if (Elapsed < MinFrameTime)
        Sleep((INT)((MinFrameTime - Elapsed) * 1000.0));

    if (!FullScreen && Viewport)
    {
        HWND Window = (HWND)Viewport->GetWindow();
        RECT SourceRect;
        SourceRect.top = 0;
        SourceRect.left = 0;
        SourceRect.right = (INT)(Viewport->SizeX * Viewport->ScaleX);
        SourceRect.bottom = (INT)(Viewport->SizeY * Viewport->ScaleY);
        Direct3DDevice->Present(&SourceRect, &SourceRect, Window, 0);
    }
    else
        Direct3DDevice->Present(0, 0, 0, 0);

    UD3DRenderDevice_Present_LastPresentTime = appSeconds();
}

void UD3DRenderDevice::ReadPixels(UViewport *Viewport, FColor *Pixels)
{
    IDirect3DSurface8 *BackBuffer;
    D3DSURFACE_DESC Desc;
    D3DLOCKED_RECT LockedRect;

    Direct3DDevice->GetBackBuffer(0, 0, &BackBuffer);
    BackBuffer->GetDesc(&Desc);

    if (Viewport && Pixels)
        BackBuffer->LockRect(&LockedRect, 0, D3DLOCK_READONLY);
    else
    {
        RECT Rect;
        Rect.top = 0;
        Rect.left = 0;
        Rect.bottom = 1;
        Rect.right = 1;
        BackBuffer->LockRect(&LockedRect, &Rect, D3DLOCK_READONLY);
    }

    if (Viewport && Pixels)
    {
        if (Desc.Format == D3DFMT_X8R8G8B8 || Desc.Format == D3DFMT_A8R8G8B8 || Desc.Format == D3DFMT_R5G6B5)
        {
            FColor *Dest = Pixels;
            for (INT Y = 0; Y < Viewport->SizeY; Y++)
            {
                BYTE *Src = (BYTE *)LockedRect.pBits + Y * LockedRect.Pitch;
                if (Desc.Format == D3DFMT_R5G6B5)
                {
                    for (INT X = 0; X < Viewport->SizeX; X++)
                    {
                        *Dest++ = FColor((((WORD *)Src)[X] >> 8) & 0xf8, (BYTE)(((WORD *)Src)[X] >> 5) << 2, ((WORD *)Src)[X] << 3);
                    }
                }
                else
                {
                    for (INT X = 0; X < Viewport->SizeX; X++)
                        *Dest++ = ((FColor *)Src)[X];
                }
            }
        }
    }

    BackBuffer->UnlockRect();
    BackBuffer->Release();
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
UD3DRenderDevice::UD3DRenderDevice() {}
void Driver_5e010(void *Mem)
{
    Escape(&GTimestamp);
    Escape(&UD3DRenderDevice_Present_LastPresentTime);
    Escape(new (Mem) UD3DRenderDevice);
}
