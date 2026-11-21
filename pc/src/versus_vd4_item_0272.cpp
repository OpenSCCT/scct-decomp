// Work item 0272: D3DDrv resource classes.
// 0x68ff0 FD3DResource::~FD3DResource (vtable 0x10c0be00)
// 0x69080 FD3DTexture::FD3DTexture   (vtable 0x10c0be64; callers allocate
//         0x54 bytes tagged L"FD3DTexture" and pass RenDev->+0x108 and a QWORD)
// Layout follows Unreal Engine 2's D3DDrv (FD3DResource / FD3DTexture).

#define NULL 0
typedef unsigned __int64 QWORD;
typedef int INT;

#pragma pack(push, 4)

class FD3DResource;

class UD3DRenderDevice
{
public:
    char Pad00[0xb0];
    FD3DResource *ResourceList;     // +0xb0
    FD3DResource *ResourceHash[1];  // +0xb4
};

class FD3DResource
{
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

inline INT GetResourceHashIndex(QWORD CacheId)
{
    return ((((unsigned long)CacheId) >> 4) & 0xff0) + ((((unsigned long)CacheId) >> 16) & 0xf) ^ (((unsigned long)CacheId) & 0xfff);
}

// 0x68f40, defined so the link sees retail's calling convention (item 0271).
FD3DResource::FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : RenDev(InRenDev), CacheId(InCacheId)
{
    CachedRevision = 0;
    NextResource = RenDev->ResourceList;
    RenDev->ResourceList = this;
    HashIndex = GetResourceHashIndex(CacheId);
    HashNext = RenDev->ResourceHash[HashIndex];
    RenDev->ResourceHash[HashIndex] = this;
    LastFrameUsed = 0;
}

// Near miss: block order and the hash-slot address match retail, but VC7
// caches 0 in ESI (push esi / xor esi,esi) and aligns both loops, where
// retail uses immediates and test eax,eax with unaligned loops.
FD3DResource::~FD3DResource()
{
    // Remove this resource from the device's resource list.
    if (RenDev->ResourceList != this) {
        FD3DResource *ResourcePtr = RenDev->ResourceList;
        while (ResourcePtr && ResourcePtr->NextResource != this)
            ResourcePtr = ResourcePtr->NextResource;
        if (ResourcePtr)
            ResourcePtr->NextResource = NextResource;
    } else {
        RenDev->ResourceList = NextResource;
    }
    NextResource = NULL;

    // Remove this resource from the device's resource hash.
    FD3DResource **HashPtr = &RenDev->ResourceHash[HashIndex];
    if (*HashPtr != this) {
        FD3DResource *ResourcePtr = *HashPtr;
        while (ResourcePtr && ResourcePtr->HashNext != this)
            ResourcePtr = ResourcePtr->HashNext;
        if (ResourcePtr)
            ResourcePtr->HashNext = HashNext;
    } else {
        *HashPtr = HashNext;
    }
    HashNext = NULL;
}

struct FArray
{
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(NULL), ArrayNum(0), ArrayMax(0) {}
};

class FD3DTexture : public FD3DResource
{
public:
    void *Direct3DTexture8;         // +0x24
    void *Direct3DCubeTexture8;     // +0x28
    void *RenderTargetSurface;      // +0x2c
    void *DepthStencilSurface;      // +0x30
    INT Pad34[5];                   // +0x34
    FArray Mips;                    // +0x48

    FD3DTexture(UD3DRenderDevice *InRenDev, QWORD InCacheId);
    virtual ~FD3DTexture();
};

FD3DTexture::FD3DTexture(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : FD3DResource(InRenDev, InCacheId)
{
    Direct3DTexture8 = NULL;
    Direct3DCubeTexture8 = NULL;
    RenderTargetSurface = NULL;
    DepthStencilSurface = NULL;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
class FMalloc { public: virtual void *Malloc(unsigned long Size, const unsigned short *Tag); };
extern FMalloc *GMalloc;
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_68ff0(FD3DResource *R) { R->FD3DResource::~FD3DResource(); }
FD3DTexture *Driver_69080(UD3DRenderDevice *RenDev, QWORD CacheId)
{
    void *Mem = GMalloc->Malloc(0x54, L"FD3DTexture");
    return Mem ? new(Mem) FD3DTexture(RenDev, CacheId) : NULL;
}
