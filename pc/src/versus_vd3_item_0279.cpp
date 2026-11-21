// Work item 0279: Versus RVA 0x6a810-0x6ab81, the Direct3D 8 index buffer
// resources of the UE2 D3D render device (D3DDrv): FD3DIndexBuffer (vtable
// 0x10c0be3c) and FD3DDynamicIndexBuffer (vtable 0x10c0be14), both derived
// from FD3DResource (vtable 0x10c0be00; constructor RVA 0x68f40, destructor
// RVA 0x68ff0). Names follow UE2's D3DDrv; the evidence is the IDirect3D8
// call pattern (CreateIndexBuffer at device slot 24 with D3DFMT_INDEX16,
// Lock/Unlock at index buffer slots 11/12, ResourceManagerDiscardBytes at
// slot 5) and the render device fields used below. The unit was built with
// VC7.0 /GL and linked with /LTCG, which gave these methods custom register
// conventions; the driver at the end reproduces the retail callers.
//
// Vtable slot 0 is the scalar deleting destructor. It is declared here as an
// explicit virtual DeletingDestructor with non-virtual destructors (as in
// item 0012): with compiler-generated virtual destructors VC7.0 /LTCG keeps
// the destructors thiscall, while retail gave ~FD3DIndexBuffer `this` on the
// stack. ~FD3DDynamicIndexBuffer (RVA 0x6a9a0, this in EAX) is implicit.
// ~FD3DIndexBuffer is never inlined in retail (callers 0x6a7e0, 0x6a9a0 and
// the constructor's unwind funclet), reproduced with auto_inline(off).
// ~FD3DResource is declared throw(): retail sets no -1 unwind state before
// calling it.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;
typedef long HRESULT;
typedef unsigned long ULONG;
typedef unsigned int UINT;

#pragma pack(push, 4)

template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }
inline void *operator new(unsigned int, void *Mem) { return Mem; }
inline void operator delete(void *, void *) {}

void appMemcpy(void *Dest, const void *Src, INT Count); // RVA 0x40a0

enum D3DFORMAT { D3DFMT_INDEX16 = 101, D3DFMT_INDEX32 = 102 };
enum D3DPOOL { D3DPOOL_DEFAULT = 0, D3DPOOL_MANAGED = 1, D3DPOOL_SYSTEMMEM = 2 };
#define D3DUSAGE_WRITEONLY          0x00000008L
#define D3DUSAGE_SOFTWAREPROCESSING 0x00000010L
#define D3DUSAGE_DYNAMIC            0x00000200L
#define D3DLOCK_NOOVERWRITE         0x00001000L
#define D3DLOCK_DISCARD             0x00002000L

struct IDirect3DIndexBuffer8
{
    virtual HRESULT __stdcall QueryInterface(void *Riid, void **Obj) = 0;
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;
    virtual HRESULT __stdcall GetDevice(void **Device) = 0;
    virtual HRESULT __stdcall SetPrivateData(void *Guid, const void *Data, DWORD Size, DWORD Flags) = 0;
    virtual HRESULT __stdcall GetPrivateData(void *Guid, void *Data, DWORD *Size) = 0;
    virtual HRESULT __stdcall FreePrivateData(void *Guid) = 0;
    virtual DWORD __stdcall SetPriority(DWORD Priority) = 0;
    virtual DWORD __stdcall GetPriority() = 0;
    virtual void __stdcall PreLoad() = 0;
    virtual INT __stdcall GetType() = 0;
    virtual HRESULT __stdcall Lock(UINT OffsetToLock, UINT SizeToLock, BYTE **Data, DWORD Flags) = 0;
    virtual HRESULT __stdcall Unlock() = 0;
};

struct IDirect3DDevice8
{
    virtual HRESULT __stdcall QueryInterface(void *Riid, void **Obj) = 0;
    virtual ULONG __stdcall AddRef() = 0;
    virtual ULONG __stdcall Release() = 0;
    virtual HRESULT __stdcall TestCooperativeLevel() = 0;
    virtual UINT __stdcall GetAvailableTextureMem() = 0;
    virtual HRESULT __stdcall ResourceManagerDiscardBytes(DWORD Bytes) = 0;
    virtual void __stdcall Slot6() = 0;
    virtual void __stdcall Slot7() = 0;
    virtual void __stdcall Slot8() = 0;
    virtual void __stdcall Slot9() = 0;
    virtual void __stdcall Slot10() = 0;
    virtual void __stdcall Slot11() = 0;
    virtual void __stdcall Slot12() = 0;
    virtual void __stdcall Slot13() = 0;
    virtual void __stdcall Slot14() = 0;
    virtual void __stdcall Slot15() = 0;
    virtual void __stdcall Slot16() = 0;
    virtual void __stdcall Slot17() = 0;
    virtual void __stdcall Slot18() = 0;
    virtual void __stdcall Slot19() = 0;
    virtual void __stdcall Slot20() = 0;
    virtual void __stdcall Slot21() = 0;
    virtual void __stdcall Slot22() = 0;
    virtual void __stdcall Slot23() = 0;
    virtual HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8 **IndexBuffer) = 0;
};

// TArray<BYTE>; Empty here frees the storage outright.
class FArray
{
public:
    INT Add(INT Count, INT ElementSize); // RVA 0x44e0
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};
template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T *GetData() { return (T *)Data; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Add(INT n = 1) { return FArray::Add(n, sizeof(T)); }
    void Empty()
    {
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

class FD3DResource;

// Only the fields these functions use; offsets from retail.
class UD3DRenderDevice
{
public:
    BYTE Pad0[0xb0];
    FD3DResource *ResourceList;                 // +0xb0
    FD3DResource *ResourceHash[4096];           // +0xb4
    BYTE Pad1[0x40d8 - 0xb4 - 4096 * 4];
    DWORD UseHardwareTL;                        // +0x40d8
    BYTE Pad2[0x410c - 0x40dc];
    DWORD ShadowIndexBuffers;                   // +0x410c (neutral name)
    BYTE Pad3[0x46a4 - 0x4110];
    IDirect3DDevice8 *Direct3DDevice8;          // +0x46a4
    BYTE Pad4[0x2fb4c - 0x46a8];
    TArray<BYTE> IndexShadow;                   // +0x2fb4c (neutral name)

    INT GetResourceHashIndex(QWORD CacheId)
    {
        DWORD Id = (DWORD)CacheId;
        return (((Id >> 4) & 0xff0) + ((Id >> 16) & 0xf)) ^ (Id & 0xfff);
    }
};

class FRenderResource
{
public:
    virtual QWORD GetCacheId() = 0;
    virtual INT GetRevision() = 0;
};
class FIndexBuffer : public FRenderResource
{
public:
    virtual INT GetSize() = 0;
    virtual void GetContents(void *Data) = 0;
};

class FD3DResource
{
public:
    UD3DRenderDevice *RenDev;                   // +0x04
    QWORD CacheId;                              // +0x08
    INT CachedRevision;                         // +0x10
    INT HashIndex;                              // +0x14
    FD3DResource *NextResource;                 // +0x18
    FD3DResource *HashNext;                     // +0x1c
    INT LastFrameUsed;                          // +0x20

    FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId);
    virtual void *DeletingDestructor(unsigned int Flags);
    ~FD3DResource() throw();                    // RVA 0x68ff0
    virtual INT CalculateFootprint();
};

class FD3DIndexBuffer : public FD3DResource
{
public:
    IDirect3DIndexBuffer8 *Direct3DIndexBuffer8; // +0x24
    INT IndexBufferSize;                         // +0x28

    FD3DIndexBuffer(UD3DRenderDevice *InRenDev, QWORD InCacheId)
        : FD3DResource(InRenDev, InCacheId)
    {
        Direct3DIndexBuffer8 = 0;
    }
    virtual void *DeletingDestructor(unsigned int Flags);
    ~FD3DIndexBuffer();
    virtual INT CalculateFootprint();

    void Cache(FIndexBuffer *SourceIndexBuffer);
};

class FD3DDynamicIndexBuffer : public FD3DIndexBuffer
{
public:
    INT Tail;                                    // +0x2c
    INT IndexSize;                               // +0x30

    FD3DDynamicIndexBuffer(UD3DRenderDevice *InRenDev, INT InIndexSize);
    virtual void *DeletingDestructor(unsigned int Flags);

    void Reallocate(INT NewSize);
    INT AddIndices(FIndexBuffer *Indices);
};

#pragma auto_inline(off)
// RVA 0x6a810: this on the stack.
FD3DIndexBuffer::~FD3DIndexBuffer()
{
    if (Direct3DIndexBuffer8)
        Direct3DIndexBuffer8->Release();
}
#pragma auto_inline(on)

// RVA 0x6a860: this on the stack, SourceIndexBuffer in EDI.
void FD3DIndexBuffer::Cache(FIndexBuffer *SourceIndexBuffer)
{
    INT NewIndexBufferSize = Max(2, SourceIndexBuffer->GetSize());

    if (!Direct3DIndexBuffer8 || IndexBufferSize != NewIndexBufferSize)
    {
        if (Direct3DIndexBuffer8)
            Direct3DIndexBuffer8->Release();
        DWORD Usage = D3DUSAGE_WRITEONLY;
        if (!RenDev->UseHardwareTL)
            Usage |= D3DUSAGE_SOFTWAREPROCESSING;
        RenDev->Direct3DDevice8->CreateIndexBuffer(
            NewIndexBufferSize,
            Usage,
            D3DFMT_INDEX16,
            D3DPOOL_MANAGED,
            &Direct3DIndexBuffer8);
    }

    if (CachedRevision != SourceIndexBuffer->GetRevision())
    {
        BYTE *IndexBufferContents = 0;
        Direct3DIndexBuffer8->Lock(0, NewIndexBufferSize, &IndexBufferContents, 0);
        SourceIndexBuffer->GetContents(IndexBufferContents);
        Direct3DIndexBuffer8->Unlock();
    }

    CachedRevision = SourceIndexBuffer->GetRevision();
    IndexBufferSize = NewIndexBufferSize;
}

// RVA 0x6a910: this on the stack, InRenDev in ECX.
FD3DDynamicIndexBuffer::FD3DDynamicIndexBuffer(UD3DRenderDevice *InRenDev, INT InIndexSize)
    : FD3DIndexBuffer(InRenDev, 0)
{
    IndexSize = InIndexSize;
    Reallocate(16384);
}

// RVA 0x6a9b0: this in ESI.
void FD3DDynamicIndexBuffer::Reallocate(INT NewSize)
{
    if (Direct3DIndexBuffer8)
    {
        Direct3DIndexBuffer8->Release();
        Direct3DIndexBuffer8 = 0;
    }

    IndexBufferSize = NewSize;
    Tail = 0;

    D3DFORMAT Format = IndexSize == 4 ? D3DFMT_INDEX32 : D3DFMT_INDEX16;
    DWORD Usage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
    if (!RenDev->UseHardwareTL)
        Usage |= D3DUSAGE_SOFTWAREPROCESSING;

    D3DPOOL Pool = D3DPOOL_DEFAULT;
    for (INT Retry = 0; Retry < 3; Retry++)
    {
        if (Retry == 2)
            Pool = D3DPOOL_SYSTEMMEM;
        HRESULT Result = RenDev->Direct3DDevice8->CreateIndexBuffer(
            IndexBufferSize, Usage, Format, Pool, &Direct3DIndexBuffer8);
        if (Result >= 0)
            break;
        RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
    }
}

// RVA 0x6aa50: this in EAX; returns the first index of the added indices.
INT FD3DDynamicIndexBuffer::AddIndices(FIndexBuffer *Indices)
{
    INT Size = Indices->GetSize();
    DWORD LockFlags = D3DLOCK_NOOVERWRITE;

    if (Size > IndexBufferSize)
    {
        Reallocate(Size);
        LockFlags = D3DLOCK_DISCARD;
    }
    if (Tail + Size > IndexBufferSize)
    {
        Tail = 0;
        LockFlags = D3DLOCK_DISCARD;
    }

    BYTE *IndexBufferContents = 0;
    INT Offset = Tail;
    Direct3DIndexBuffer8->Lock(Tail, Size, &IndexBufferContents, LockFlags);

    BYTE *Dest = IndexBufferContents;
    if (RenDev->ShadowIndexBuffers)
    {
        UD3DRenderDevice *Device = RenDev;
        if (Size + 4 > Device->IndexShadow.Num())
        {
            Device->IndexShadow.Empty();
            RenDev->IndexShadow.Add(Max(Size, 0xffff) * 2);
        }
        *(DWORD *)&RenDev->IndexShadow(Size + 1) = 0x3221977;
        Dest = RenDev->IndexShadow.GetData();
    }

    Indices->GetContents(Dest);

    if (RenDev->ShadowIndexBuffers)
        appMemcpy(IndexBufferContents, Dest, Size);

    Direct3DIndexBuffer8->Unlock();
    Tail = Offset + Size;
    return Offset / 2;
}


// RVA 0x6a970: the scalar deleting destructor (vtable slot 0).
void *FD3DDynamicIndexBuffer::DeletingDestructor(unsigned int Flags)
{
    this->~FD3DDynamicIndexBuffer();
    if (Flags & 1)
        operator delete(this);
    return this;
}

// Scaffolding for the link, not part of the unit: the base constructor
// (RVA 0x68f40, its own unit) is defined here so the linker sees it and gives
// it the same this-in-EAX, RenDev-in-ECX convention as retail.
FD3DResource::FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId)
{
    RenDev = InRenDev;
    CacheId = InCacheId;
    CachedRevision = 0;
    NextResource = RenDev->ResourceList;
    RenDev->ResourceList = this;
    HashIndex = RenDev->GetResourceHashIndex(CacheId);
    HashNext = RenDev->ResourceHash[HashIndex];
    RenDev->ResourceHash[HashIndex] = this;
    LastFrameUsed = 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_6a810(UD3DRenderDevice *R, FIndexBuffer *S, FD3DIndexBuffer *I, FD3DDynamicIndexBuffer *D, void *Mem)
{
    Escape(&GMalloc);
    I->Cache(S);
    I->Cache(S);
    FD3DDynamicIndexBuffer *N = new (Mem) FD3DDynamicIndexBuffer(R, 2);
    D->AddIndices(S);
    D->AddIndices(S);
    I->FD3DIndexBuffer::~FD3DIndexBuffer();
    D->DeletingDestructor(1);
}
#pragma pack(pop)
