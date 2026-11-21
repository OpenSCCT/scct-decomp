// Work item 0262: Versus RVA 0x62370.
// FD3DRenderInterface::SetDynamicStream, after Unreal Engine 2's D3D render
// interface: lazily creates the render device's dynamic vertex stream, adds
// the stream's vertices to it and binds it as stream 0. Built with /GL /LTCG
// (the callees take `this` in EAX or on the stack). Field offsets come from the
// retail code; names follow UE2's D3DDrv where the shape fits.

typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size) { return GMalloc->Malloc(Size, L"new"); }
inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }

class FVertexStream {
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual INT GetSize();
    virtual void GetStreamData(void *Dest);
};

typedef unsigned char BYTE;
void appMemcpy(void *Dest, const void *Src, INT Count);
struct IDirect3DVertexBuffer8 {
    virtual void __stdcall S0(); virtual void __stdcall S1(); virtual long __stdcall Release();
    virtual void __stdcall S3(); virtual void __stdcall S4(); virtual void __stdcall S5();
    virtual void __stdcall S6(); virtual void __stdcall S7(); virtual void __stdcall S8();
    virtual void __stdcall S9(); virtual void __stdcall S10();
    virtual long __stdcall Lock(DWORD Offset, DWORD Size, BYTE **Data, DWORD Flags);
    virtual long __stdcall Unlock();
};
struct FScratch { BYTE *Data; INT ArrayNum; INT ArrayMax; void Empty(INT Slack); };
class UD3DRenderDevice;
class FD3DResource;
struct IDirect3DDevice8 {
    virtual void __stdcall S00(); virtual void __stdcall S01(); virtual void __stdcall S02(); virtual void __stdcall S03();
    virtual void __stdcall S04(); virtual void __stdcall S05(); virtual void __stdcall S06(); virtual void __stdcall S07();
    virtual void __stdcall S08(); virtual void __stdcall S09(); virtual void __stdcall S10(); virtual void __stdcall S11();
    virtual void __stdcall S12(); virtual void __stdcall S13(); virtual void __stdcall S14(); virtual void __stdcall S15();
    virtual void __stdcall S16(); virtual void __stdcall S17(); virtual void __stdcall S18(); virtual void __stdcall S19();
    virtual void __stdcall S20(); virtual void __stdcall S21(); virtual void __stdcall S22(); virtual void __stdcall S23();
    virtual long __stdcall CreateVertexBuffer(DWORD Length, DWORD Usage, DWORD FVF, DWORD Pool, IDirect3DVertexBuffer8 **VB);
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

class FD3DDynamicVertexStream : public FD3DResource {
public:
    IDirect3DVertexBuffer8 *Direct3DVertexBuffer8; // +0x24
    INT BufferSize;             // +0x28
    INT Tail;                   // +0x2c
    INT Type;                   // +0x30

    FD3DDynamicVertexStream(UD3DRenderDevice *InRenDev, INT InType);
    void Reallocate(INT NewBufferSize);
    INT AddVertices(FVertexStream *Stream);
};

struct FD3DStreamState {
    IDirect3DVertexBuffer8 *StreamData; // +0x554 from the deferred state
    INT StreamStride;                   // +0x558
};

struct FD3DDeferredState {
    char Pad[0x554];
    FD3DStreamState StreamState[16];
    void SetStreamSource(INT StreamIndex, IDirect3DVertexBuffer8 *StreamData, INT StreamStride);
};

class UD3DRenderDevice {
public:
    char PadA[0xb0];
    FD3DResource *ResourceList;                   // +0xb0
    FD3DResource *ResourceHash[4096];             // +0xb4
    char Pad0[0x40c0 - 0x40b4];
    FD3DDynamicVertexStream *DynamicVertexStream; // +0x40c0
    char Pad1[0x40d8 - 0x40c4];
    INT UseHardwareTL;                            // +0x40d8 (neutral)
    char Pad1b[0x410c - 0x40dc];
    INT UseScratch;                               // +0x410c (neutral)
    char Pad1c[0x46a4 - 0x4110];
    IDirect3DDevice8 *Direct3DDevice8;            // +0x46a4
    char Pad2[0x2fb4c - 0x46a8];
    FScratch Scratch;                             // +0x2fb4c (neutral)
    FD3DDeferredState DeferredState;              // +0x2fb58
};

// Neutral: state block reached from the render interface at +0x2af10.
struct FUnnamedState_62370 {
    char Pad[0x180];
    FD3DDynamicVertexStream *Stream; // +0x180
    INT Stride;                      // +0x184
};

class FD3DRenderInterface {
public:
    char Pad0[0x104];
    UD3DRenderDevice *RenDev;          // +0x108
    char Pad1[0x2af10 - 0x10c];
    FUnnamedState_62370 *State;        // +0x2af10

    virtual INT SetDynamicStream(FVertexStream *Stream, INT Stride);
};

INT FD3DRenderInterface::SetDynamicStream(FVertexStream *Stream, INT Stride)
{
    // Retail's unwind map has an unused state 0 ahead of the new-expression
    // (its cleanup runs as state 1): a compiled-out block that also created a
    // dynamic stream. Reproduced with a constant-false branch.
    if (0)
        RenDev->DynamicVertexStream = new FD3DDynamicVertexStream(RenDev, 1);
    if (!RenDev->DynamicVertexStream)
        RenDev->DynamicVertexStream = new FD3DDynamicVertexStream(RenDev, 2);
    FD3DDynamicVertexStream *DynamicStream = RenDev->DynamicVertexStream;
    INT BaseVertexIndex = DynamicStream->AddVertices(Stream);
    State->Stream = DynamicStream;
    State->Stride = Stride;
    RenDev->DeferredState.SetStreamSource(0, DynamicStream->Direct3DVertexBuffer8, Stride);
    return BaseVertexIndex;
}

void FD3DDeferredState::SetStreamSource(INT StreamIndex, IDirect3DVertexBuffer8 *StreamData, INT StreamStride)
{
    StreamState[StreamIndex].StreamData = StreamData;
    StreamState[StreamIndex].StreamStride = StreamStride;
}

inline INT GetResourceHashIndex(QWORD CacheId)
{
    DWORD Lo = (DWORD)CacheId;
    return (((Lo >> 4) & 0xff0) + ((Lo >> 16) & 0xf)) ^ (Lo & 0xfff);
}

// Callees defined so the linker sees every caller and picks the retail
// conventions; their bodies are not part of this unit's match.
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

void FD3DDynamicVertexStream::Reallocate(INT NewBufferSize)
{
    if (Direct3DVertexBuffer8) {
        Direct3DVertexBuffer8->Release();
        Direct3DVertexBuffer8 = 0;
    }
    BufferSize = NewBufferSize;
    Tail = 0;
    DWORD Usage = RenDev->UseHardwareTL ? 0x208 : 0x218;
    RenDev->Direct3DDevice8->CreateVertexBuffer(BufferSize, Usage, 0x65 + (Type == 4), 0, &Direct3DVertexBuffer8);
}

FD3DDynamicVertexStream::FD3DDynamicVertexStream(UD3DRenderDevice *InRenDev, INT InType)
    : FD3DResource(InRenDev, 0)
{
    Direct3DVertexBuffer8 = 0;
    Type = InType;
    Reallocate(0x4000);
}

INT FD3DDynamicVertexStream::AddVertices(FVertexStream *Stream)
{
    INT Size = Stream->GetSize();
    if (Size > BufferSize)
        Reallocate(Size);
    if (Tail + Size > BufferSize)
        Tail = 0;
    INT Start = Tail;
    BYTE *Data = 0;
    Direct3DVertexBuffer8->Lock(Start, Size, &Data, Start ? 0x1000 : 0x2000);
    if (RenDev->UseScratch) {
        if (Size + 4 > RenDev->Scratch.ArrayMax) {
            RenDev->Scratch.Empty(Size < 0xffff ? 0xffff * 2 : Size * 2);
        }
        *(DWORD *)(RenDev->Scratch.Data + Size + 1) = 0x3221977;
        Data = RenDev->Scratch.Data;
    }
    Stream->GetStreamData(Data);
    if (RenDev->UseScratch)
        appMemcpy(Data, Data, Size);
    Direct3DVertexBuffer8->Unlock();
    Tail = Start + Size;
    return Start / 2;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
INT Driver_62370(FD3DRenderInterface *RI, FVertexStream *S, INT Stride)
{
    Escape(&GMalloc);
    return RI->FD3DRenderInterface::SetDynamicStream(S, Stride);
}
