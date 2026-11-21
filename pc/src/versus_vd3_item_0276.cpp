// Work item 0276: Versus RVA 0x69f00 and 0x6a020.
// 0x69f00: FD3DVertexStream::Cache, after Unreal Engine 2's D3DDrv: (re)creates
//          the D3D8 vertex buffer when the source stream's size changed, then
//          locks it and copies the stream data in. FD3DVertexStream is the
//          class with vtable 0x10c0be50 (ctor 0x69e40, dtor 0x69ea0).
// 0x6a020: constructor of a dynamic vertex stream (vtable 0x10c0be28) that
//          derives from FD3DVertexStream and allocates a 128 KB buffer through
//          its Reallocate (0x6a0c0). The class name is neutral.
// Both were built with /GL /LTCG (this in ESI / on the stack, RenDev in ECX).

typedef unsigned long DWORD;
typedef int INT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

class FVertexStream {
public:
    virtual QWORD GetCacheId();
    virtual INT GetRevision();
    virtual void Slot02();              // neutral
    virtual INT GetSize();
    virtual INT HintDynamic();
    virtual INT UseNPatches();
    virtual void Slot06();              // neutral
    virtual void GetStreamData(void *Dest);
};

struct IDirect3DVertexBuffer8 {
    virtual void __stdcall S0(); virtual void __stdcall S1(); virtual long __stdcall Release();
    virtual void __stdcall S3(); virtual void __stdcall S4(); virtual void __stdcall S5();
    virtual void __stdcall S6(); virtual void __stdcall S7(); virtual void __stdcall S8();
    virtual void __stdcall S9(); virtual void __stdcall S10();
    virtual long __stdcall Lock(DWORD Offset, DWORD Size, BYTE **Data, DWORD Flags);
    virtual long __stdcall Unlock();
};

struct IDirect3DDevice8 {
    virtual void __stdcall S00(); virtual void __stdcall S01(); virtual void __stdcall S02(); virtual void __stdcall S03();
    virtual void __stdcall S04();
    virtual long __stdcall ResourceManagerDiscardBytes(DWORD Bytes);
    virtual void __stdcall S06(); virtual void __stdcall S07();
    virtual void __stdcall S08(); virtual void __stdcall S09(); virtual void __stdcall S10(); virtual void __stdcall S11();
    virtual void __stdcall S12(); virtual void __stdcall S13(); virtual void __stdcall S14(); virtual void __stdcall S15();
    virtual void __stdcall S16(); virtual void __stdcall S17(); virtual void __stdcall S18(); virtual void __stdcall S19();
    virtual void __stdcall S20(); virtual void __stdcall S21(); virtual void __stdcall S22();
    virtual long __stdcall CreateVertexBuffer(DWORD Length, DWORD Usage, DWORD FVF, DWORD Pool, IDirect3DVertexBuffer8 **VB);
};

class UD3DRenderDevice;

struct FD3DDeferredState {
    void UnSetVertexBuffer(IDirect3DVertexBuffer8 *Buffer); // retail 0x6cd00 (neutral name)
};

class FD3DResource {
public:
    UD3DRenderDevice *RenDev;   // +0x04
    QWORD CacheId;              // +0x08
    INT CachedRevision;         // +0x10
    INT HashIndex;              // +0x14
    FD3DResource *NextResource; // +0x18
    FD3DResource *HashNext;     // +0x1c
    INT LastFrameUsed;          // +0x20

    FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId);
    virtual ~FD3DResource();
};

class FD3DVertexStream : public FD3DResource {
public:
    IDirect3DVertexBuffer8 *Direct3DVertexBuffer8; // +0x24
    INT CachedSize;                                // +0x28

    FD3DVertexStream(UD3DRenderDevice *InRenDev, QWORD InCacheId)
        : FD3DResource(InRenDev, InCacheId)
    {
        Direct3DVertexBuffer8 = 0;
    }
    virtual ~FD3DVertexStream();
    void Cache(FVertexStream *SourceStream);
};

// Neutral name: vtable 0x10c0be28.
class UnnamedDynamicVertexStream_6a020 : public FD3DVertexStream {
public:
    INT Tail;                                      // +0x2c

    UnnamedDynamicVertexStream_6a020(UD3DRenderDevice *InRenDev);
    virtual ~UnnamedDynamicVertexStream_6a020();
    void Reallocate(INT NewSize);
};

class UD3DRenderDevice {
public:
    char PadA[0xb0];
    FD3DResource *ResourceList;                   // +0xb0
    FD3DResource *ResourceHash[4096];             // +0xb4
    char Pad1[0x40d8 - 0x40b4];
    INT UseHardwareTL;                            // +0x40d8 (neutral)
    char Pad1b[0x4110 - 0x40dc];
    INT UseNPatches;                              // +0x4110 (neutral)
    char Pad1c[0x46a4 - 0x4114];
    IDirect3DDevice8 *Direct3DDevice8;            // +0x46a4
    char Pad2[0x2fb58 - 0x46a8];
    FD3DDeferredState DeferredState;              // +0x2fb58
};

void FD3DVertexStream::Cache(FVertexStream *SourceStream)
{
    INT StreamSize = SourceStream->GetSize();
    DWORD Usage = 8, LockFlags = 0;                 // D3DUSAGE_WRITEONLY
    if (SourceStream->HintDynamic()) {
        Usage = 0x208;                              // | D3DUSAGE_DYNAMIC
        LockFlags = 0x2000;                         // D3DLOCK_DISCARD
    }
    if (SourceStream->UseNPatches() && RenDev->UseNPatches)
        Usage |= 0x100;                             // D3DUSAGE_NPATCHES
    if (!RenDev->UseHardwareTL)
        Usage |= 0x10;                              // D3DUSAGE_SOFTWAREPROCESSING

    if (!Direct3DVertexBuffer8 || CachedSize != StreamSize) {
        if (Direct3DVertexBuffer8)
            Direct3DVertexBuffer8->Release();
        DWORD Pool = 0;                             // D3DPOOL_DEFAULT
        for (INT Retry = 0; Retry < 3; Retry++) {
            if (Retry == 2)
                Pool = 2;                           // D3DPOOL_SYSTEMMEM
            if (RenDev->Direct3DDevice8->CreateVertexBuffer(StreamSize, Usage, 0, Pool, &Direct3DVertexBuffer8) >= 0)
                break;
            RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
        }
    }

    BYTE *Data;
    Direct3DVertexBuffer8->Lock(0, StreamSize, &Data, LockFlags);
    SourceStream->GetStreamData(Data);
    Direct3DVertexBuffer8->Unlock();
    CachedRevision = SourceStream->GetRevision();
    CachedSize = StreamSize;
}

UnnamedDynamicVertexStream_6a020::UnnamedDynamicVertexStream_6a020(UD3DRenderDevice *InRenDev)
    : FD3DVertexStream(InRenDev, 0)
{
    Reallocate(0x20000);
}

// Callees defined so the linker sees every caller and picks the retail
// conventions; their bodies are not part of this unit's match.
inline INT GetResourceHashIndex(QWORD CacheId)
{
    DWORD Lo = (DWORD)CacheId;
    return (((Lo >> 4) & 0xff0) + ((Lo >> 16) & 0xf)) ^ (Lo & 0xfff);
}

FD3DResource::FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId)
{
    RenDev = InRenDev;
    CacheId = InCacheId;
    CachedRevision = 0;
    NextResource = RenDev->ResourceList;
    RenDev->ResourceList = this;
    HashIndex = GetResourceHashIndex(CacheId);
    HashNext = RenDev->ResourceHash[HashIndex];
    RenDev->ResourceHash[HashIndex] = this;
    LastFrameUsed = 0;
}

void UnnamedDynamicVertexStream_6a020::Reallocate(INT NewSize)
{
    if (Direct3DVertexBuffer8) {
        RenDev->DeferredState.UnSetVertexBuffer(Direct3DVertexBuffer8);
        Direct3DVertexBuffer8->Release();
        Direct3DVertexBuffer8 = 0;
    }
    CachedSize = NewSize;
    Tail = 0;
    DWORD Usage = RenDev->UseHardwareTL ? 0x208 : 0x218;
    for (INT Retry = 0; Retry < 3; Retry++) {
        DWORD Pool = Retry == 2 ? 2 : 0;
        if (RenDev->Direct3DDevice8->CreateVertexBuffer(CachedSize, Usage, 0, Pool, &Direct3DVertexBuffer8) >= 0)
            break;
        RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
    }
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_69f00(FD3DVertexStream *VS, FVertexStream *S) { VS->Cache(S); }
void Driver_6a020(void *Mem, UD3DRenderDevice *R) { new (Mem) UnnamedDynamicVertexStream_6a020(R); }
