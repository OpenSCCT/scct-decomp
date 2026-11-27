// Work item 0250: Versus RVA 0x5c000-0x5c314, D3D render device helpers.
// Class name from the reflected vtable (UD3DRenderDevice@30c1f0); field names
// are inferred from use (PCI vendor/device ids, DirectDraw video memory query).

typedef unsigned long DWORD;
typedef int INT;
typedef long HRESULT;
typedef DWORD UBOOL;

#include "campaign_import_GUID.h"

struct DDSCAPS2 { DWORD dwCaps, dwCaps2, dwCaps3, dwCaps4; };
#define DDSCAPS_TEXTURE      0x00001000
#define DDSCAPS_VIDEOMEMORY  0x00004000
#define DDSCAPS_LOCALVIDMEM  0x10000000

struct IDirectDraw7 {
    virtual HRESULT __stdcall QueryInterface(const GUID &, void **);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
    virtual void __stdcall Unused03(); virtual void __stdcall Unused04();
    virtual void __stdcall Unused05(); virtual void __stdcall Unused06();
    virtual void __stdcall Unused07(); virtual void __stdcall Unused08();
    virtual void __stdcall Unused09(); virtual void __stdcall Unused10();
    virtual void __stdcall Unused11(); virtual void __stdcall Unused12();
    virtual void __stdcall Unused13(); virtual void __stdcall Unused14();
    virtual void __stdcall Unused15(); virtual void __stdcall Unused16();
    virtual void __stdcall Unused17(); virtual void __stdcall Unused18();
    virtual void __stdcall Unused19(); virtual void __stdcall Unused20();
    virtual void __stdcall Unused21(); virtual void __stdcall Unused22();
    virtual HRESULT __stdcall GetAvailableVidMem(DDSCAPS2 *Caps, DWORD *Total, DWORD *Free); // +0x5c
};

extern "C" HRESULT __stdcall DirectDrawCreateEx(GUID *lpGuid, void **lplpDD, const GUID &iid, void *pUnkOuter);
extern "C" const GUID IID_IDirectDraw7;
extern "C" void *memset(void *, int, unsigned int);
#pragma intrinsic(memset)

// Render-related config globals written by SetResolutionMode (slot 24).
extern INT GD3D_8b8c;
extern INT GD3D_8b68;
extern INT GD3D_8bac;
extern INT GD3D_8b84;
extern INT GD3D_8b74;

struct IUnknownLike {
    virtual HRESULT __stdcall QueryInterface(const GUID &, void **) = 0;
    virtual DWORD __stdcall AddRef() = 0;
    virtual DWORD __stdcall Release() = 0;
};

struct UViewport;

struct UD3DRenderDevice {
    // Vtable slots as recovered from the reflected vtable at 0x30c1f0.
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void SetResolutionMode(INT Unused, INT Mode);       // slot 24, 0x5c2a0
    virtual void Slot25();
    virtual INT GetDetailLevel(INT Unused);                      // slot 26, 0x5c150
    virtual INT GetTextureDetail(INT Unused);                    // slot 27, 0x5c270
    virtual void Slot28();
    virtual void Exit(UViewport *Viewport);                      // slot 29, 0x5c000
    virtual void Flush(UViewport *Viewport);                     // slot 30 (+0x78)
    virtual void Slot31(); virtual void Slot32(); virtual void Slot33();
    virtual void ReleaseDynamicResources();                      // slot 34 (+0x88)

    char Pad04[0x4618 - 4];
    DWORD VendorId;   // +0x4618 (0x1002 ATI, 0x10de NVIDIA)
    DWORD DeviceId;   // +0x461c
    char Pad4620[0x46a0 - 0x4620];
    IUnknownLike *Direct3D;        // +0x46a0
    IUnknownLike *Direct3DDevice;  // +0x46a4

    static DWORD __stdcall GetVideoMemoryMB(UD3DRenderDevice *Device);
    void ReleaseStateBlocks();     // 0x5f9c0 (LTCG: this in ESI)
    void ReleaseResources();       // 0x5ffe0 (LTCG: this in EAX), see item 0255
    UD3DRenderDevice();
};

// RVA 0x5c000 (UD3DRenderDevice vtable slot 29)
void UD3DRenderDevice::Exit(UViewport *Viewport)
{
    ReleaseDynamicResources();
    Flush(Viewport);
    if (Direct3DDevice) {
        ReleaseStateBlocks();
        ReleaseResources();
        Direct3DDevice->Release();
        Direct3DDevice = 0;
    }
    if (Direct3D) {
        Direct3D->Release();
        Direct3D = 0;
    }
}

// RVA 0x5c070
DWORD __stdcall UD3DRenderDevice::GetVideoMemoryMB(UD3DRenderDevice *Device)
{
    DWORD Result = 64;
    IDirectDraw7 *DD;
    DirectDrawCreateEx(0, (void **)&DD, IID_IDirectDraw7, 0);
    if (DD) {
        DWORD Total[2];
        DWORD Free;
        DDSCAPS2 Caps;
        memset(&Caps, 0, sizeof(Caps));
        Caps.dwCaps = DDSCAPS_TEXTURE;
        DD->GetAvailableVidMem(&Caps, &Total[0], &Free);
        Caps.dwCaps = DDSCAPS_LOCALVIDMEM | DDSCAPS_VIDEOMEMORY;
        DD->GetAvailableVidMem(&Caps, &Total[1], &Free);
        DD->Release();

        for (INT i = 0; i < 2; i++)
            if (Total[i] == 0)
                Total[i] = 0xffffffff;

        DWORD MB = Total[0] < Total[1] ? Total[0] : Total[1];
        if (MB == 0xffffffff)
            MB = 64 * 1024 * 1024;
        MB >>= 20;

        Result = 1;
        while (Result < MB)
            Result <<= 1;
    }
    return Result;
}

// RVA 0x5c150 (UD3DRenderDevice vtable slot 26)
INT UD3DRenderDevice::GetDetailLevel(INT Unused)
{
    DWORD MB = GetVideoMemoryMB(this);
    INT Level = 0;
    switch (VendorId) {
    case 0x1002:
        switch (DeviceId) {
        case 0x4242: case 0x4243:
        case 0x4966: case 0x4967:
        case 0x496e: case 0x496f:
        case 0x514c: case 0x516c:
        case 0x54dd:
        case 0x5940: case 0x5941:
        case 0x5960: case 0x5961:
        case 0x5964:
        case 0x5c61: case 0x5c63:
            Level = 1;
            break;
        default:
            Level = 2;
            break;
        }
        break;
    case 0x10de:
        if (DeviceId >= 0x200 && DeviceId <= 0x202)
            Level = 1;
        else
            Level = 2;
        break;
    }
    INT MemLevel;
    if (MB >= 256)
        MemLevel = 2;
    else if (MB >= 128)
        MemLevel = 2;
    else
        MemLevel = 1;
    return Level <= MemLevel ? Level : MemLevel;
}

// RVA 0x5c270 (UD3DRenderDevice vtable slot 27)
INT UD3DRenderDevice::GetTextureDetail(INT Unused)
{
    DWORD MB = GetVideoMemoryMB(this);
    if (MB >= 256)
        return 4;
    if (MB >= 128)
        return 3;
    return 2;
}

// RVA 0x5c2a0 (UD3DRenderDevice vtable slot 24)
void UD3DRenderDevice::SetResolutionMode(INT Unused, INT Mode)
{
    INT Size;
    switch (Mode) {
    case 0:  Size = 0x400; GD3D_8b8c = 0x200; break;
    case 1:  Size = 0x400; GD3D_8b8c = 0x400; break;
    case 2:  Size = 0x800; GD3D_8b8c = 0x400; break;
    default: Size = 0x200; GD3D_8b8c = 0x200; break;
    }
    GD3D_8b84 = (GD3D_8b74 != 80 ? 4 : 2) * Size;
    GD3D_8b68 = Size;
    GD3D_8bac = Mode;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link of 0x5c000, not part of the unit. The two
// callees below are approximations of 0x5f9c0 and 0x5ffe0 (only so the linker
// sees their bodies and gives them their register conventions); they are not
// matched here.
typedef HRESULT (__stdcall *DeleteFn_Scaffold)(void *Device, DWORD Handle);
#define HANDLE_AT(Off) (*(DWORD *)((char *)this + (Off)))
#define IFACE_AT(Off) (*(IUnknownLike **)((char *)this + (Off)))
#define DELETE_HANDLE(Off, Slot)     if (HANDLE_AT(Off) && HANDLE_AT(Off) != 0xffffffff) {         (*(DeleteFn_Scaffold *)(*(char **)Direct3DDevice + (Slot)))(Direct3DDevice, HANDLE_AT(Off));         HANDLE_AT(Off) = 0xffffffff; }
#define SAFE_RELEASE_AT(Off)     if (IFACE_AT(Off)) { IFACE_AT(Off)->Release(); IFACE_AT(Off) = 0; }

void UD3DRenderDevice::ReleaseStateBlocks()
{
    DELETE_HANDLE(0x30f2c, 0x138)
    DELETE_HANDLE(0x30f68, 0x168)
    DELETE_HANDLE(0x30f30, 0x168)
    DELETE_HANDLE(0x30f34, 0x168)
    DELETE_HANDLE(0x30f38, 0x168)
    DELETE_HANDLE(0x30f3c, 0x168)
    DELETE_HANDLE(0x30f40, 0x168)
    DELETE_HANDLE(0x30f44, 0x168)
    DELETE_HANDLE(0x30f48, 0x168)
    DELETE_HANDLE(0x30f4c, 0x168)
    DELETE_HANDLE(0x30f50, 0x168)
    DELETE_HANDLE(0x30f60, 0x168)
    DELETE_HANDLE(0x30f64, 0x168)
    DELETE_HANDLE(0x30f54, 0x168)
    DELETE_HANDLE(0x30f58, 0x168)
    DELETE_HANDLE(0x30f5c, 0x168)
    DELETE_HANDLE(0x30f6c, 0x168)
    DELETE_HANDLE(0x30f70, 0x168)
    DELETE_HANDLE(0x30f74, 0x168)
    DELETE_HANDLE(0x30f78, 0x168)
    DELETE_HANDLE(0x30f7c, 0x168)
    DELETE_HANDLE(0x30f80, 0x168)
    DELETE_HANDLE(0x30f84, 0x168)
    DELETE_HANDLE(0x30f88, 0x168)
    DELETE_HANDLE(0x30f8c, 0x168)
    DELETE_HANDLE(0x30f90, 0x168)
    DELETE_HANDLE(0x30f94, 0x168)
    DELETE_HANDLE(0x30f98, 0x168)
    DELETE_HANDLE(0x30f9c, 0x168)
    DELETE_HANDLE(0x30fa0, 0x168)
    DELETE_HANDLE(0x30fa4, 0x168)
    DELETE_HANDLE(0x30fa8, 0x168)
    DELETE_HANDLE(0x30fac, 0x168)
    DELETE_HANDLE(0x30fb0, 0x168)
    DELETE_HANDLE(0x30fb4, 0x168)
    DELETE_HANDLE(0x30fb8, 0x168)
    DELETE_HANDLE(0x30fbc, 0x168)
    DELETE_HANDLE(0x30e44, 0x168)
    DELETE_HANDLE(0x30e48, 0x168)
    DELETE_HANDLE(0x30e4c, 0x168)
    DELETE_HANDLE(0x30e50, 0x168)
    DELETE_HANDLE(0x30e54, 0x168)
    DELETE_HANDLE(0x30e58, 0x168)
}

void UD3DRenderDevice::ReleaseResources()
{
    SAFE_RELEASE_AT(0x30e1c)
    SAFE_RELEASE_AT(0x30e20)
    for (INT i = 0; i < 4; i++)
        SAFE_RELEASE_AT(0x30e30 + i * 4)
    SAFE_RELEASE_AT(0x30e2c)
    SAFE_RELEASE_AT(0x30ea4)
    SAFE_RELEASE_AT(0x30e68)
    SAFE_RELEASE_AT(0x30e6c)
    SAFE_RELEASE_AT(0x30e70)
    SAFE_RELEASE_AT(0x30e74)
    SAFE_RELEASE_AT(0x30e78)
    SAFE_RELEASE_AT(0x30e7c)
    SAFE_RELEASE_AT(0x30e80)
    SAFE_RELEASE_AT(0x30e84)
    SAFE_RELEASE_AT(0x30e88)
    SAFE_RELEASE_AT(0x30e28)
    SAFE_RELEASE_AT(0x30e24)
    SAFE_RELEASE_AT(0x30e40)
    SAFE_RELEASE_AT(0x30e5c)
    SAFE_RELEASE_AT(0x30e60)
    SAFE_RELEASE_AT(0x30e64)
    SAFE_RELEASE_AT(0x30e90)
    SAFE_RELEASE_AT(0x30e8c)
    for (INT j = 0; j < 2; j++)
        SAFE_RELEASE_AT(0x30e94 + j * 4)
}

UD3DRenderDevice::UD3DRenderDevice() {}
void *operator new(unsigned int);
void Escape(void *);
void Driver_5c000(UD3DRenderDevice *D, UViewport *V)
{
    Escape(new UD3DRenderDevice);
    D->Exit(V);
}
