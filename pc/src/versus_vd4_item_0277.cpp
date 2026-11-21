// Work item 0277: Versus RVA 0x6a0c0 and 0x6a160.
// FD3DDynamicVertexStream::Reallocate and ::AddVertices, after Unreal Engine 2's
// D3DDrv dynamic vertex stream (D3D8 CreateVertexBuffer is vtable slot 23,
// Lock 11, Unlock 12). Built with /GL /LTCG: Reallocate takes this in ESI,
// AddVertices takes this in EAX. Offsets come from the retail code.

typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;

#pragma pack(push, 4)

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

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

class FVertexStream {
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual INT GetStride();
    virtual INT GetSize();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
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

class UD3DRenderDevice;

struct FD3DStreamState {
    IDirect3DVertexBuffer8 *StreamData;
    INT StreamStride;
};

// Deferred device state embedded in the render device at +0x2fb58.
struct FD3DDeferredState {
    UD3DRenderDevice *RenDev;            // +0x000
    char Pad[0x4d4 - 4];
    FD3DStreamState StreamState[16];     // +0x4d4 (pending)
    char Pad2[0xdac - 0x554];
    FD3DStreamState HardwareStream[16];  // +0xdac (set on the device)
    void UnSetVertexBuffer(IDirect3DVertexBuffer8 *VertexBuffer);
};

class UD3DRenderDevice {
public:
    char Pad0[0x40d8];
    INT UseHardwareTL;                   // +0x40d8 (neutral)
    char Pad1[0x410c - 0x40dc];
    INT UseScratch;                      // +0x410c (neutral)
    char Pad2[0x41f4 - 0x4110];
    DWORD MaxVertexIndex;                // +0x41f4 (neutral)
    INT MaxStreams;                      // +0x41f8 (neutral)
    char Pad3[0x46a4 - 0x41fc];
    IDirect3DDevice8 *Direct3DDevice8;   // +0x46a4
    char Pad4[0x2fb4c - 0x46a8];
    FArray Scratch;                      // +0x2fb4c (neutral)
    FD3DDeferredState DeferredState;     // +0x2fb58
};

class FD3DResource {
public:
    UD3DRenderDevice *RenDev;            // +0x04
    char Pad[0x24 - 8];
    virtual ~FD3DResource();
};

class FD3DDynamicVertexStream : public FD3DResource {
public:
    IDirect3DVertexBuffer8 *Direct3DVertexBuffer8; // +0x24
    INT BufferSize;                      // +0x28
    INT Tail;                            // +0x2c

    void Reallocate(INT NewBufferSize);
    INT AddVertices(FVertexStream *Stream);
};

inline INT Min(INT A, INT B) { return (A <= B) ? A : B; }
inline INT Max(INT A, INT B) { return (A >= B) ? A : B; }
inline INT Abs(INT A) { return (A >= 0) ? A : -A; }

void FD3DDynamicVertexStream::Reallocate(INT NewBufferSize)
{
    if (Direct3DVertexBuffer8) {
        RenDev->DeferredState.UnSetVertexBuffer(Direct3DVertexBuffer8);
        Direct3DVertexBuffer8->Release();
        Direct3DVertexBuffer8 = 0;
    }
    BufferSize = NewBufferSize;
    Tail = 0;
    DWORD Usage = 0x208;
    if (!RenDev->UseHardwareTL)
        Usage = 0x218;
    DWORD Pool = 0;
    for (INT Attempt = 0; Attempt < 3; Attempt++) {
        if (Attempt == 2)
            Pool = 2;
        if (RenDev->Direct3DDevice8->CreateVertexBuffer(BufferSize, Usage, 0, Pool, &Direct3DVertexBuffer8) >= 0)
            break;
        RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
    }
}

INT FD3DDynamicVertexStream::AddVertices(FVertexStream *Stream)
{
    INT Size = Abs(Stream->GetSize());
    DWORD Stride = Stream->GetStride();
    DWORD LockFlags = 0x1000;
    if (Size > BufferSize) {
        Reallocate(Size);
        LockFlags = 0x2000;
    }
    if (Stream->GetSize() < 0 || (INT)(Tail + Stride + Size) > BufferSize
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

// Callee defined so the linker sees its callers and picks the retail
// convention (this in EBX); its body is not part of this unit's match.
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

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
INT Driver_6a160(FD3DDynamicVertexStream *VS, FVertexStream *S)
{
    Escape(&GMalloc);
    return VS->AddVertices(S);
}
