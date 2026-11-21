// Work item 0271: Versus RVA 0x68f40, FD3DResource::FD3DResource.
// Built with /GL and linked /LTCG (this in EAX, RenDev in ECX, CacheId on the
// stack). Names follow Unreal Engine 2's D3D renderer (UnD3DResource.cpp);
// field offsets come from the retail code. Vtable at 0x10c0be00.

typedef unsigned long DWORD;
typedef int INT;
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

class FD3DResource;

class UD3DRenderDevice {
public:
    char Pad00[0xb0];
    FD3DResource *ResourceList;                 // +0xb0
    FD3DResource *ResourceHash[4096];           // +0xb4
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

INT GetResourceHashIndex(QWORD CacheId)
{
    return ((DWORD)CacheId & 0xfff) ^ ((((DWORD)CacheId >> 16) & 0xf) + (((DWORD)CacheId >> 4) & 0xff0));
}

// RVA 0x68f40
FD3DResource::FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : RenDev(InRenDev), CacheId(InCacheId)
{
    CachedRevision = 0;

    // Add this resource to the device resource list.
    NextResource = RenDev->ResourceList;
    RenDev->ResourceList = this;

    // Add this resource to the device resource hash.
    HashIndex = GetResourceHashIndex(CacheId);
    HashNext = RenDev->ResourceHash[HashIndex];
    RenDev->ResourceHash[HashIndex] = this;

    LastFrameUsed = 0;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
extern const TCHAR FD3DResourceTag[];
void Driver_68f40(UD3DRenderDevice *RenDev, QWORD CacheId)
{
    Escape(&GMalloc);
    Escape(new(FD3DResourceTag) FD3DResource(RenDev, CacheId));
}
