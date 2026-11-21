// Work item 0260: Versus RVA 0x61110, FD3DRenderInterface::SetRenderTarget.
// Built with /GL and linked /LTCG. Names follow Unreal Engine 2's D3D
// renderer (the allocation tag "FD3DTexture" is in retail); field offsets come
// from the retail code. 0x5b7d0 is UD3DRenderDevice::GetCachedResource (see
// item 0249), 0x68f40/0x69080 the FD3DResource/FD3DTexture constructors
// (LTCG: this in EAX), 0x691e0 FD3DTexture::Cache (LTCG: this on the stack).

typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;
typedef unsigned __int64 QWORD;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }

extern const TCHAR FD3DTextureTag_61110[];   // L"FD3DTexture" at 0x10c4dd90

struct IDirect3DSurface8;

struct IDirect3DDevice8 {
    virtual void __stdcall Slot00(); virtual void __stdcall Slot01(); virtual void __stdcall Slot02();
    virtual void __stdcall Slot03(); virtual void __stdcall Slot04(); virtual void __stdcall Slot05();
    virtual void __stdcall Slot06(); virtual void __stdcall Slot07(); virtual void __stdcall Slot08();
    virtual void __stdcall Slot09(); virtual void __stdcall Slot10(); virtual void __stdcall Slot11();
    virtual void __stdcall Slot12(); virtual void __stdcall Slot13(); virtual void __stdcall Slot14();
    virtual void __stdcall Slot15(); virtual void __stdcall Slot16(); virtual void __stdcall Slot17();
    virtual void __stdcall Slot18(); virtual void __stdcall Slot19(); virtual void __stdcall Slot20();
    virtual void __stdcall Slot21(); virtual void __stdcall Slot22(); virtual void __stdcall Slot23();
    virtual void __stdcall Slot24(); virtual void __stdcall Slot25(); virtual void __stdcall Slot26();
    virtual void __stdcall Slot27(); virtual void __stdcall Slot28(); virtual void __stdcall Slot29();
    virtual void __stdcall Slot30();
    virtual long __stdcall SetRenderTarget(IDirect3DSurface8 *RenderTarget, IDirect3DSurface8 *ZStencil); // slot 31
};

class FRenderTarget {
public:
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
};

class FD3DResource;

class UD3DRenderDevice {
public:
    char Pad00[0xb0];
    FD3DResource *ResourceList;                 // +0xb0
    FD3DResource *ResourceHash[4096];           // +0xb4
    char Pad40b4[0x46a4 - 0x40b4];
    IDirect3DDevice8 *Direct3DDevice8;          // +0x46a4

    static FD3DResource *__stdcall GetCachedResource(UD3DRenderDevice *RenDev, QWORD CacheId);   // RVA 0x5b7d0
};

#pragma pack(push, 4)
class FD3DResource {
public:
    UD3DRenderDevice *RenDev;       // +0x04
    QWORD CacheId;                  // +0x08
    INT CachedRevision;             // +0x10
    INT HashIndex;                  // +0x14
    FD3DResource *NextResource;     // +0x18
    FD3DResource *HashNext;         // +0x1c
    INT LastFrameUsed;              // +0x20

    FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId);
    virtual ~FD3DResource();
};
#pragma pack(pop)

class FD3DTexture : public FD3DResource {
public:
    IDirect3DSurface8 *RenderTargetSurface;     // +0x24
    IDirect3DSurface8 *DepthStencilSurface;     // +0x28
    void *Texture;                              // +0x2c
    void *CubeTexture;                          // +0x30
    INT CachedWidth;                            // +0x34
    INT CachedHeight;                           // +0x38
    INT Pad3c[3];
    void *Field48, *Field4c, *Field50;          // +0x48

    FD3DTexture(UD3DRenderDevice *InRenDev, QWORD InCacheId);
    static UBOOL __stdcall Cache(FD3DTexture *Texture, FRenderTarget *RenderTarget);   // RVA 0x691e0
};

struct FD3DRenderState {
    IDirect3DSurface8 *RenderTargetSurface;
    IDirect3DSurface8 *DepthStencilSurface;
    INT ViewportX, ViewportY, ViewportWidth, ViewportHeight;
};

class FD3DRenderInterface {
public:
    virtual UBOOL SetRenderTarget(FRenderTarget *RenderTarget);
    char Pad04[0x108 - 4];
    UD3DRenderDevice *RenDev;                   // +0x108
    char Pad10c[0x2af10 - 0x10c];
    FD3DRenderState *CurrentState;              // +0x2af10
};

// The constructors live in another file in retail and are not inlined here.
#pragma auto_inline(off)
// RVA 0x68f40 (LTCG helper; not reported here)
FD3DResource::FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : RenDev(InRenDev), CacheId(InCacheId)
{
    CachedRevision = 0;
    NextResource = RenDev->ResourceList;
    RenDev->ResourceList = this;
    DWORD Low = (DWORD)CacheId;
    HashIndex = (((Low >> 4) & 0xff0) + ((Low >> 16) & 0xf)) ^ (Low & 0xfff);
    HashNext = RenDev->ResourceHash[HashIndex];
    RenDev->ResourceHash[HashIndex] = this;
    LastFrameUsed = 0;
}

// RVA 0x69080 (LTCG helper; not reported here)
FD3DTexture::FD3DTexture(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : FD3DResource(InRenDev, InCacheId)
{
    Field48 = 0;
    Field4c = 0;
    Field50 = 0;
    RenderTargetSurface = 0;
    DepthStencilSurface = 0;
    Texture = 0;
    CubeTexture = 0;
}
#pragma auto_inline(on)

// RVA 0x61110
UBOOL FD3DRenderInterface::SetRenderTarget(FRenderTarget *RenderTarget)
{
    QWORD CacheId = RenderTarget->GetCacheId();
    FD3DTexture *RenderTexture = (FD3DTexture *)UD3DRenderDevice::GetCachedResource(RenDev, CacheId);
    if (!RenderTexture)
        RenderTexture = new(FD3DTextureTag_61110) FD3DTexture(RenDev, CacheId);

    if (RenderTexture->CachedRevision != RenderTarget->GetRevision() &&
        FD3DTexture::Cache(RenderTexture, RenderTarget))
        return 0;

    if (!RenderTexture->RenderTargetSurface || !RenderTexture->DepthStencilSurface)
        return 0;
    if (CurrentState->RenderTargetSurface == RenderTexture->RenderTargetSurface &&
        CurrentState->DepthStencilSurface == RenderTexture->DepthStencilSurface)
        return 0;

    RenDev->Direct3DDevice8->SetRenderTarget(RenderTexture->RenderTargetSurface, RenderTexture->DepthStencilSurface);
    CurrentState->RenderTargetSurface = RenderTexture->RenderTargetSurface;
    CurrentState->DepthStencilSurface = RenderTexture->DepthStencilSurface;
    CurrentState->ViewportX = 0;
    CurrentState->ViewportY = 0;
    CurrentState->ViewportWidth = RenderTexture->CachedWidth;
    CurrentState->ViewportHeight = RenderTexture->CachedHeight;
    return 1;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_61110(FD3DRenderInterface *RI, FRenderTarget *RT)
{
    Escape(&GMalloc);
    Escape((void *)RI->FD3DRenderInterface::SetRenderTarget(RT));
}
