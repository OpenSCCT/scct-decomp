// Item 0295: RVA 0x78390-0x787ac, Direct3D render-interface code after
// Unreal Engine 2's D3DDrv.
//   0x78390 SetWorldViewProjectionConstant: plain VC7.0 /O2 /Gy (try_match).
//           Its classes are neutral names; the 64-byte local is a D3DX matrix
//           and device slot 0x13c/4 uploads shader constants.
//   0x78400 SetVertexStreams: try_ltcg /O2 /Gy, root Driver_78400.
//   0x78630 SetDynamicStream: try_ltcg /O2 /Gy /GX, root Driver_78630.
// Both LTCG functions are reached from virtual wrappers (0x770d0, 0x77100)
// by tail jumps, so they keep a standard stack convention with the render
// interface as the first argument; the drivers take their addresses for that.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

struct D3DXMATRIX { FLOAT m[4][4]; };

D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX *Out, const D3DXMATRIX *M1, const D3DXMATRIX *M2);
D3DXMATRIX *__stdcall D3DXMatrixTranspose(D3DXMATRIX *Out, const D3DXMATRIX *M);

struct UnnamedD3DDevice {
    virtual void __stdcall Slot00(); virtual void __stdcall Slot01(); virtual void __stdcall Slot02(); virtual void __stdcall Slot03();
    virtual void __stdcall Slot04(); virtual void __stdcall Slot05(); virtual void __stdcall Slot06(); virtual void __stdcall Slot07();
    virtual void __stdcall Slot08(); virtual void __stdcall Slot09(); virtual void __stdcall Slot10(); virtual void __stdcall Slot11();
    virtual void __stdcall Slot12(); virtual void __stdcall Slot13(); virtual void __stdcall Slot14(); virtual void __stdcall Slot15();
    virtual void __stdcall Slot16(); virtual void __stdcall Slot17(); virtual void __stdcall Slot18(); virtual void __stdcall Slot19();
    virtual void __stdcall Slot20(); virtual void __stdcall Slot21(); virtual void __stdcall Slot22(); virtual void __stdcall Slot23();
    virtual void __stdcall Slot24(); virtual void __stdcall Slot25(); virtual void __stdcall Slot26(); virtual void __stdcall Slot27();
    virtual void __stdcall Slot28(); virtual void __stdcall Slot29(); virtual void __stdcall Slot30(); virtual void __stdcall Slot31();
    virtual void __stdcall Slot32(); virtual void __stdcall Slot33(); virtual void __stdcall Slot34(); virtual void __stdcall Slot35();
    virtual void __stdcall Slot36(); virtual void __stdcall Slot37(); virtual void __stdcall Slot38(); virtual void __stdcall Slot39();
    virtual void __stdcall Slot40(); virtual void __stdcall Slot41(); virtual void __stdcall Slot42(); virtual void __stdcall Slot43();
    virtual void __stdcall Slot44(); virtual void __stdcall Slot45(); virtual void __stdcall Slot46(); virtual void __stdcall Slot47();
    virtual void __stdcall Slot48(); virtual void __stdcall Slot49(); virtual void __stdcall Slot50(); virtual void __stdcall Slot51();
    virtual void __stdcall Slot52(); virtual void __stdcall Slot53(); virtual void __stdcall Slot54(); virtual void __stdcall Slot55();
    virtual void __stdcall Slot56(); virtual void __stdcall Slot57(); virtual void __stdcall Slot58(); virtual void __stdcall Slot59();
    virtual void __stdcall Slot60(); virtual void __stdcall Slot61(); virtual void __stdcall Slot62(); virtual void __stdcall Slot63();
    virtual void __stdcall Slot64(); virtual void __stdcall Slot65(); virtual void __stdcall Slot66(); virtual void __stdcall Slot67();
    virtual void __stdcall Slot68(); virtual void __stdcall Slot69(); virtual void __stdcall Slot70(); virtual void __stdcall Slot71();
    virtual void __stdcall Slot72(); virtual void __stdcall Slot73(); virtual void __stdcall Slot74(); virtual void __stdcall Slot75();
    virtual void __stdcall Slot76(); virtual void __stdcall Slot77(); virtual void __stdcall Slot78();
    virtual long __stdcall SetShaderConstant(DWORD Register, const void *Data, DWORD Count); // +0x13c
};

struct UnnamedRenderDevice {
    char Pad0[0x46a4];
    UnnamedD3DDevice *Direct3DDevice;   // +0x46a4
};

struct UnnamedTransformState {
    char Pad0[0x38];
    D3DXMATRIX World;                   // +0x38
    D3DXMATRIX View;                    // +0x78
    D3DXMATRIX Projection;              // +0xb8
};

struct UnnamedRenderInterface {
    char Pad0[0x108];
    UnnamedRenderDevice *RenDev;        // +0x108
    char Pad1[0x2af10 - 0x10c];
    UnnamedTransformState *State;       // +0x2af10
};

// RVA 0x78390
void __stdcall SetWorldViewProjectionConstant(UnnamedRenderInterface *RI)
{
    D3DXMATRIX M;
    D3DXMatrixMultiply(&M, &RI->State->World, &RI->State->View);
    D3DXMatrixMultiply(&M, &M, &RI->State->Projection);
    D3DXMatrixTranspose(&M, &M);
    RI->RenDev->Direct3DDevice->SetShaderConstant(4, &M, 4);
}

// ---------------------------------------------------------------------------
// 0x78400 and 0x78630: FD3DRenderInterface::SetVertexStreams and
// ::SetDynamicStream, after Unreal Engine 2's D3DDrv. Built with VC7.0 /GL
// and linked /LTCG (`this` on the stack, callees with register conventions).
// The 0x78390 helper above is the same class's world-view-projection upload.

#pragma pack(push, 4)

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }

extern const TCHAR FD3DVertexStream_Tag[];          // L"FD3DVertexStream"
extern const TCHAR FD3DDynamicVertexStream_Tag[];   // L"FD3DDynamicVertexStream"

struct FVertexComponent {
    DWORD Type;
    DWORD Function;
};

class FVertexStream {
public:
    virtual QWORD GetCacheId();                         // +0x00
    virtual INT GetRevision();                          // +0x04
    virtual INT GetStride();                            // +0x08
    virtual INT GetSize();                              // +0x0c
    virtual INT HintDynamic();                          // +0x10
    virtual INT UseNPatches();                          // +0x14
    virtual INT GetComponents(FVertexComponent *Components); // +0x18
    virtual void GetStreamData(void *Dest);             // +0x1c
};

struct FStreamDeclaration {
    FVertexComponent Components[8];
    INT NumComponents;
    FStreamDeclaration() { NumComponents = 0; }
    FStreamDeclaration(FVertexStream *Stream) { NumComponents = Stream->GetComponents(Components); }
};

// Retail 0x6ac30.
struct FShaderDeclaration {
    FStreamDeclaration Streams[16];
    INT NumStreams;
    FShaderDeclaration();
    ~FShaderDeclaration() {}
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
    virtual void __stdcall S24(); virtual void __stdcall S25(); virtual void __stdcall S26(); virtual void __stdcall S27();
    virtual void __stdcall S28(); virtual void __stdcall S29(); virtual void __stdcall S30(); virtual void __stdcall S31();
    virtual void __stdcall S32(); virtual void __stdcall S33(); virtual void __stdcall S34(); virtual void __stdcall S35();
    virtual void __stdcall S36(); virtual void __stdcall S37(); virtual void __stdcall S38(); virtual void __stdcall S39();
    virtual void __stdcall S40(); virtual void __stdcall S41(); virtual void __stdcall S42(); virtual void __stdcall S43();
    virtual void __stdcall S44(); virtual void __stdcall S45(); virtual void __stdcall S46(); virtual void __stdcall S47();
    virtual void __stdcall S48(); virtual void __stdcall S49(); virtual void __stdcall S50(); virtual void __stdcall S51();
    virtual void __stdcall S52(); virtual void __stdcall S53(); virtual void __stdcall S54(); virtual void __stdcall S55();
    virtual void __stdcall S56(); virtual void __stdcall S57(); virtual void __stdcall S58(); virtual void __stdcall S59();
    virtual void __stdcall S60(); virtual void __stdcall S61(); virtual void __stdcall S62(); virtual void __stdcall S63();
    virtual void __stdcall S64(); virtual void __stdcall S65(); virtual void __stdcall S66(); virtual void __stdcall S67();
    virtual void __stdcall S68(); virtual void __stdcall S69(); virtual void __stdcall S70(); virtual void __stdcall S71();
    virtual void __stdcall S72(); virtual void __stdcall S73(); virtual void __stdcall S74(); virtual void __stdcall S75();
    virtual void __stdcall S76(); virtual void __stdcall S77(); virtual void __stdcall S78(); virtual void __stdcall S79();
    virtual void __stdcall S80(); virtual void __stdcall S81(); virtual void __stdcall S82();
    virtual long __stdcall SetStreamSource(DWORD StreamNumber, IDirect3DVertexBuffer8 *StreamData, DWORD Stride);
};

void appMemcpy(void *Dest, const void *Src, INT Count);

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
    INT Num() { return ArrayNum; }
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};
struct FD3DDeferredStreamState { IDirect3DVertexBuffer8 *StreamData; INT StreamStride; };

class UD3DRenderDevice;
struct FD3DDeferredState {
    UD3DRenderDevice *RenDev;                   // +0x000
    char Pad0[0x4d4 - 4];
    FD3DDeferredStreamState StreamState[16];    // +0x4d4
    char Pad1[0xdac - 0x554];
    FD3DDeferredStreamState HardwareStream[16]; // +0xdac
    void UnSetVertexBuffer(IDirect3DVertexBuffer8 *VertexBuffer); // retail 0x6cd00
    void SetStreamSource(INT StreamIndex, IDirect3DVertexBuffer8 *StreamData, INT Stride)
    {
        StreamState[StreamIndex].StreamData = StreamData;
        StreamState[StreamIndex].StreamStride = Stride;
    }
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
    FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId); // retail 0x68f40
    virtual ~FD3DResource();
};

class FD3DVertexStream : public FD3DResource {
public:
    IDirect3DVertexBuffer8 *Direct3DVertexBuffer8; // +0x24
    INT CachedSize;                                // +0x28
    FD3DVertexStream(UD3DRenderDevice *InRenDev, QWORD InCacheId); // retail 0x69e40
    // Uncached stream (cache id 0) for dynamic streams; inlined into 0x6a020.
    FD3DVertexStream(UD3DRenderDevice *InRenDev) : FD3DResource(InRenDev, 0) { Direct3DVertexBuffer8 = 0; }
    void Cache(FVertexStream *SourceStream);                      // retail 0x69f00
};

class FD3DDynamicVertexStream : public FD3DVertexStream {
public:
    INT Tail;                                      // +0x2c
    FD3DDynamicVertexStream(UD3DRenderDevice *InRenDev); // retail 0x6a020
    void Reallocate(INT NewSize);                        // retail 0x6a0c0
    INT AddVertices(FVertexStream *Stream);              // retail 0x6a160
};

inline DWORD GetResourceHashIndex(QWORD CacheId)
{
    DWORD Lo = (DWORD)CacheId;
    DWORD H = (Lo >> 4) & 0xff0; H += (Lo >> 16) & 0xf; H ^= Lo & 0xfff; return H;
}

class UD3DRenderDevice {
public:
    char Pad0[0xb0];
    FD3DResource *ResourceList;                     // +0xb0
    FD3DResource *ResourceHash[4096];               // +0xb4
    char Pad1[0x40bc - 0x40b4];
    FD3DDynamicVertexStream *DynamicVertexStream;   // +0x40bc
    char Pad2[0x40d8 - 0x40c0];
    INT UseHardwareTL;                              // +0x40d8
    char Pad2a[0x410c - 0x40dc];
    INT UseScratch;                                 // +0x410c
    INT UseNPatches;                                // +0x4110
    char Pad2d[0x41f4 - 0x4114];
    DWORD MaxVertexIndex;                           // +0x41f4
    INT MaxStreams;                                 // +0x41f8
    char Pad2b[0x4698 - 0x41fc];
    INT FrameCounter;                               // +0x4698
    char Pad2c[0x46a4 - 0x469c];
    IDirect3DDevice8 *Direct3DDevice8;              // +0x46a4
    char Pad3[0x2fb4c - 0x46a8];
    FArray Scratch;                                 // +0x2fb4c
    FD3DDeferredState DeferredState;                // +0x2fb58

    FD3DResource *GetCachedResource(QWORD CacheId)
    {
        for (FD3DResource *R = ResourceHash[GetResourceHashIndex(CacheId)]; R; R = R->HashNext)
            if (R->CacheId == CacheId)
                return R;
        return 0;
    }
};

struct FD3DRenderState {
    char Pad0[0xfc];
    FD3DResource *Streams[16];      // +0xfc
    INT StreamStrides[16];          // +0x13c
    INT NumStreams;                 // +0x17c
};

class FD3DRenderInterface {
public:
    char Pad0[0x108];
    UD3DRenderDevice *RenDev;       // +0x108
    char Pad1[0x2af10 - 0x10c];
    FD3DRenderState *CurrentState;  // +0x2af10
};

// RVA 0x78400. In a vtable (0x30c0a4) and reached by a tail jump from the
// wrapper at 0x770d0; the interface is the first stack argument.
INT __stdcall SetVertexStreams(FD3DRenderInterface *RI, INT Shader, FVertexStream **Streams, INT NumStreams)
{
    for (INT StreamIndex = NumStreams; StreamIndex < RI->CurrentState->NumStreams; StreamIndex++) {
        if (RI->CurrentState->Streams[StreamIndex]) {
            RI->CurrentState->Streams[StreamIndex] = 0;
            RI->RenDev->DeferredState.SetStreamSource(StreamIndex, 0, 0);
        }
    }

    FShaderDeclaration ShaderDeclaration;
    ShaderDeclaration.NumStreams = NumStreams;
    for (INT StreamIndex = 0; StreamIndex < NumStreams; StreamIndex++)
        ShaderDeclaration.Streams[StreamIndex] = FStreamDeclaration(Streams[StreamIndex]);

    INT TotalSize = 0;
    for (INT StreamIndex = 0; StreamIndex < NumStreams; StreamIndex++) {
        QWORD CacheId = Streams[StreamIndex]->GetCacheId();
        FD3DVertexStream *D3DStream = (FD3DVertexStream *)RI->RenDev->GetCachedResource(CacheId);
        if (!D3DStream)
            D3DStream = new(FD3DVertexStream_Tag) FD3DVertexStream(RI->RenDev, CacheId);
        if (D3DStream->CachedRevision != Streams[StreamIndex]->GetRevision()) {
            TotalSize += Streams[StreamIndex]->GetSize();
            D3DStream->Cache(Streams[StreamIndex]);
        }
        D3DStream->LastFrameUsed = RI->RenDev->FrameCounter;
        INT Stride = Streams[StreamIndex]->GetStride();
        RI->RenDev->DeferredState.SetStreamSource(StreamIndex, D3DStream->Direct3DVertexBuffer8, Stride);
        RI->CurrentState->Streams[StreamIndex] = D3DStream;
        RI->CurrentState->StreamStrides[StreamIndex] = Stride;
    }
    RI->CurrentState->NumStreams = NumStreams;
    return TotalSize;
}

// RVA 0x78630. Reached by a tail jump from the virtual wrapper at 0x77100,
// so it keeps the standard convention: the interface is the first stack
// argument.
INT __stdcall SetDynamicStream(FD3DRenderInterface *RI, INT Shader, FVertexStream *Stream)
{
    if (!RI->RenDev->DynamicVertexStream)
        RI->RenDev->DynamicVertexStream = new(FD3DDynamicVertexStream_Tag) FD3DDynamicVertexStream(RI->RenDev);
    INT BaseVertexIndex = RI->RenDev->DynamicVertexStream->AddVertices(Stream);
    INT Stride = Stream->GetStride();
    RI->RenDev->DeferredState.SetStreamSource(0, RI->RenDev->DynamicVertexStream->Direct3DVertexBuffer8, Stride);
    RI->CurrentState->Streams[0] = RI->RenDev->DynamicVertexStream;
    RI->CurrentState->StreamStrides[0] = Stride;
    for (INT StreamIndex = 1; StreamIndex < RI->CurrentState->NumStreams; StreamIndex++) {
        RI->CurrentState->Streams[StreamIndex] = 0;
        RI->RenDev->DeferredState.SetStreamSource(StreamIndex, 0, 0);
    }
    RI->CurrentState->NumStreams = 1;

    FShaderDeclaration ShaderDeclaration;
    ShaderDeclaration.NumStreams = 1;
    ShaderDeclaration.Streams[0] = FStreamDeclaration(Stream);
    return BaseVertexIndex;
}

#pragma pack(pop)

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit. The callees get
// stand-in bodies only so the linker sees them as /GL code and picks register
// conventions as retail did.
void Escape(void *);
void __stdcall InitComponents(FVertexComponent *Components, INT Size, INT Count);
__declspec(noinline) FShaderDeclaration::FShaderDeclaration()
{
    for (INT i = 0; i < 16; i++) {
        InitComponents(Streams[i].Components, 8, 8);
        Streams[i].NumComponents = 0;
    }
    NumStreams = 0;
}
__declspec(noinline) FD3DResource::FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId)
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
__declspec(noinline) FD3DVertexStream::FD3DVertexStream(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : FD3DResource(InRenDev, InCacheId)
{
    Direct3DVertexBuffer8 = 0;
}
// Retail 0x69f00 (published from item 0276).
__declspec(noinline) void FD3DVertexStream::Cache(FVertexStream *SourceStream)
{
    INT StreamSize = SourceStream->GetSize();
    DWORD Usage = 8, LockFlags = 0;
    if (SourceStream->HintDynamic()) {
        Usage = 0x208;
        LockFlags = 0x2000;
    }
    if (SourceStream->UseNPatches() && RenDev->UseNPatches)
        Usage |= 0x100;
    if (!RenDev->UseHardwareTL)
        Usage |= 0x10;
    if (!Direct3DVertexBuffer8 || CachedSize != StreamSize) {
        if (Direct3DVertexBuffer8)
            Direct3DVertexBuffer8->Release();
        DWORD Pool = 0;
        for (INT Retry = 0; Retry < 3; Retry++) {
            if (Retry == 2)
                Pool = 2;
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
__declspec(noinline) FD3DDynamicVertexStream::FD3DDynamicVertexStream(UD3DRenderDevice *InRenDev)
    : FD3DVertexStream(InRenDev)
{
    Reallocate(0x20000);
}
inline INT Min(INT A, INT B) { return (A <= B) ? A : B; }
inline INT Max(INT A, INT B) { return (A >= B) ? A : B; }
inline INT Abs(INT A) { return (A >= 0) ? A : -A; }
// Retail 0x6a0c0 (item 0277).
void FD3DDynamicVertexStream::Reallocate(INT NewBufferSize)
{
    if (Direct3DVertexBuffer8) {
        RenDev->DeferredState.UnSetVertexBuffer(Direct3DVertexBuffer8);
        Direct3DVertexBuffer8->Release();
        Direct3DVertexBuffer8 = 0;
    }
    CachedSize = NewBufferSize;
    Tail = 0;
    DWORD Usage = 0x208;
    if (!RenDev->UseHardwareTL)
        Usage = 0x218;
    DWORD Pool = 0;
    for (INT Attempt = 0; Attempt < 3; Attempt++) {
        if (Attempt == 2)
            Pool = 2;
        if (RenDev->Direct3DDevice8->CreateVertexBuffer(CachedSize, Usage, 0, Pool, &Direct3DVertexBuffer8) >= 0)
            break;
        RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
    }
}
// Retail 0x6a160 (item 0277).
INT FD3DDynamicVertexStream::AddVertices(FVertexStream *Stream)
{
    INT Size = Abs(Stream->GetSize());
    DWORD Stride = Stream->GetStride();
    DWORD LockFlags = 0x1000;
    if (Size > CachedSize) {
        Reallocate(Size);
        LockFlags = 0x2000;
    }
    if (Stream->GetSize() < 0 || (INT)(Tail + Stride + Size) > CachedSize
        || (Tail + Stride + Size) / Stride > RenDev->MaxVertexIndex) {
        Tail = 0;
        LockFlags = 0x2000;
    }
    INT Start = ((INT)(Tail + Stride - 1) / (INT)Stride) * Stride;
    BYTE *LockedData = 0;
    Direct3DVertexBuffer8->Lock(Start, Size, &LockedData, LockFlags);
    BYTE *Dest = LockedData;
    if (RenDev->UseScratch) {
        if (Size + 4 > RenDev->Scratch.Num()) {
            RenDev->Scratch.Empty();
            RenDev->Scratch.Add(Max(Size, 0xffff) * 2, 1);
        }
        *(DWORD *)((BYTE *)RenDev->Scratch.Data + Size + 1) = 0x3221977;
        Dest = (BYTE *)RenDev->Scratch.Data;
    }
    Stream->GetStreamData(Dest);
    if (RenDev->UseScratch)
        appMemcpy(LockedData, Dest, Size);
    Direct3DVertexBuffer8->Unlock();
    Tail = Start + Size;
    return Start / (INT)Stride;
}
// Retail 0x6cd00 (item 0277).
void FD3DDeferredState::UnSetVertexBuffer(IDirect3DVertexBuffer8 *VertexBuffer)
{
    for (INT i = 0; i < Min(RenDev->MaxStreams, 16); i++) {
        if (HardwareStream[i].StreamData == VertexBuffer) {
            HardwareStream[i].StreamData = 0;
            HardwareStream[i].StreamStride = 0;
            RenDev->Direct3DDevice8->SetStreamSource(i, 0, 0);
        }
        if (StreamState[i].StreamData == VertexBuffer) {
            StreamState[i].StreamData = 0;
            StreamState[i].StreamStride = 0;
        }
    }
}
INT Driver_78400(FD3DRenderInterface *RI, INT Shader, FVertexStream **S, INT N)
{
    Escape(&GMalloc);
    Escape((void *)&SetVertexStreams);
    return SetVertexStreams(RI, Shader, S, N);
}
INT Driver_78630(FD3DRenderInterface *RI, INT Shader, FVertexStream *S)
{
    Escape(&GMalloc);
    Escape((void *)&SetDynamicStream);
    return SetDynamicStream(RI, Shader, S);
}
