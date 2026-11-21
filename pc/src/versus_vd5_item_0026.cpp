// Work item w3 0026: Versus RVA 0x5dd90, UD3DRenderDevice::Exec (D3DDrv).
// `this` is the FExec subobject at +0x28 of the render device. Follows UE2's
// UD3DRenderDevice::Exec: DUMPRESOURCEHASH, FIRSTCOLOREDMIP, NEARCLIP,
// D3DRESOURCES and SUPPORTEDRESOLUTION; the debugf calls are compiled out in
// this build, which leaves the walks with no visible result.
// The object was built with /GL and linked with /LTCG; callees defined under
// "stand-in" exist only so the link gives them retail's register conventions.
// Retail keeps the command strings in writable .data, so they are externs.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef long HRESULT;
typedef unsigned int size_t;
typedef char ANSICHAR;

extern "C" __declspec(dllimport) int __cdecl wcscmp(const TCHAR *A, const TCHAR *B);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR *A, const TCHAR *B, size_t Count);
extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *S);
extern "C" __declspec(dllimport) int __cdecl _wtoi(const TCHAR *S);
extern "C" __declspec(dllimport) double __cdecl atof(const ANSICHAR *S);
inline INT appStrcmp(const TCHAR *A, const TCHAR *B) { return wcscmp(A, B); }
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count) { return _wcsnicmp(A, B, Count); }
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline INT appAtoi(const TCHAR *S) { return _wtoi(S); }
ANSICHAR *appToAnsi(const TCHAR *Str, ANSICHAR *ACh = 0);   // RVA 0x14120
inline FLOAT appAtof(const TCHAR *S) { return (FLOAT)atof(appToAnsi(S)); }
inline UBOOL appIsAlnum(TCHAR c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

enum EName { NAME_None = 0 };

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);              // RVA 0x118d0 (this in EBX)
};

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class UViewport;

// UObject's vtable up to URenderDevice::Flush (slot 30); the earlier slots
// are not used here.
class UObject
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual void Flush(UViewport *Viewport);       // URenderDevice::Flush, slot 30
    INT ObjectPad[9];                              // 0x04..0x28
};

class FD3DTexture;
class FD3DVertexStream;
class FD3DIndexBuffer;

class FD3DResource
{
public:
    virtual ~FD3DResource();
    virtual FD3DTexture *GetTexture();
    virtual FD3DVertexStream *GetVertexStream();
    virtual FD3DIndexBuffer *GetIndexBuffer();
    virtual INT CalculateFootprint();
    INT Pad[5];                                    // 0x04..0x18
    FD3DResource *NextResource;                    // 0x18
    FD3DResource *HashNext;                        // 0x1c
};

// IDirect3DDevice8 (COM, stdcall).
struct IDirect3DDevice8
{
    virtual HRESULT __stdcall QueryInterface(const void *Id, void **Obj);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
    virtual HRESULT __stdcall TestCooperativeLevel();
    virtual unsigned int __stdcall GetAvailableTextureMem();
};

struct D3DDISPLAYMODE
{
    unsigned int Width;
    unsigned int Height;
    unsigned int RefreshRate;
    INT Format;
};

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class UD3DRenderDevice : public UObject, public FExec
{
public:
    INT Pad0[0x21];                                // 0x2c..0xb0
    FD3DResource *ResourceList;                    // 0xb0
    FD3DResource *ResourceHash[4096];              // 0xb4
    INT Pad1[0x1b];                                // 0x40b4..0x4120
    INT FirstColoredMip;                           // 0x4120
    INT Pad2[0x148];                               // 0x4124..0x4644
    TArray<D3DDISPLAYMODE> DisplayModes;           // 0x4644
    INT Pad3[0x15];                                // 0x4650..0x46a4
    IDirect3DDevice8 *Direct3DDevice8;             // 0x46a4
    UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);
};

extern FLOAT NEAR_CLIPPING_PLANE;                  // 0x10c73b08

extern const TCHAR TEXT_DUMPRESOURCEHASH[];        // 0x10c508f0
extern const TCHAR TEXT_FIRSTCOLOREDMIP[];         // 0x10c50914
extern const TCHAR TEXT_NEARCLIP[];                // 0x10c50934
extern const TCHAR TEXT_D3DRESOURCES[];            // 0x10c50948
extern const TCHAR TEXT_SUPPORTEDRESOLUTION[];     // 0x10c50964
extern const TCHAR TEXT_WIDTH[];                   // 0x10c5098c "WIDTH="
extern const TCHAR TEXT_HEIGHT[];                  // 0x10c5099c "HEIGHT="
extern const TCHAR TEXT_BITDEPTH[];                // 0x10c509ac "BITDEPTH="
extern const TCHAR TEXT_PercentU[];                // 0x10c509c0 "%u"
extern const TCHAR TEXT_Empty1[];                  // 0x10c9254c L""
extern const TCHAR TEXT_Empty2[];                  // 0x10c92550 L""

// ---- Stand-ins: callees from other /GL units, defined only for their
// ---- link-time calling conventions. Not part of the unit.
#pragma auto_inline(off)
UBOOL ParseCommand(const TCHAR **Stream, const TCHAR *Match)
{
    while ((**Stream == ' ') || (**Stream == 9))
        (*Stream)++;
    if (appStrnicmp(*Stream, Match, appStrlen(Match)) == 0)
    {
        *Stream += appStrlen(Match);
        if (!appIsAlnum(**Stream))
        {
            while ((**Stream == ' ') || (**Stream == 9))
                (*Stream)++;
            return 1;
        }
        else
        {
            *Stream -= appStrlen(Match);
            return 0;
        }
    }
    else return 0;
}
DWORD appStrtoi(const TCHAR *Start, TCHAR **End, INT Base);
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, DWORD &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    TCHAR *End;
    if (Temp == 0)
        return 0;
    Value = appStrtoi(Temp + appStrlen(Match), &End, 10);
    return 1;
}
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, INT &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += wcslen(Match);
    Value = _wtoi(Temp);
    return 1;
}
// RVA 0x6ada0 (format in EAX): bits per pixel of a D3DFORMAT.
INT GetFormatBPP(INT Format)
{
    switch (Format)
    {
    case 20: return 24;
    case 21: case 22: case 62: case 63: case 64: case 65: case 71: case 75: case 77: case 79: return 32;
    case 23: case 24: case 25: case 26: case 29: case 30: case 40: case 51: case 60: case 61: case 70: case 73: case 80: return 16;
    case 27: case 28: case 41: case 50: case 52: return 8;
    case 0x31545844: return 4;
    case 0x32545844: case 0x33545844: case 0x34545844: case 0x35545844: return 8;
    }
    return 0;
}
extern UBOOL GLogFilterActive;
struct FLogFilter { INT Pad[1]; DWORD Flags; };
struct FLogOwner { char Pad[0x930]; FLogFilter *Filter; };
extern FLogOwner *GLogOwner;
extern TCHAR GCmdLine[];
extern const TCHAR Text_LogFlushParam[];
extern const TCHAR Text_Logf[];
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
typedef char *va_list;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Dest, size_t Count, const TCHAR *Fmt, va_list Args);
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
        while ((Start = appStrfind(Start + 1, Param)) != 0)
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
    return 0;
}
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!GLogFilterActive || !(GLogOwner->Filter->Flags & 0x1000))
    {
        TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, Text_Logf);
        _vsnwprintf(Buffer, 0x8000, Fmt, (va_list)&Fmt + sizeof(Fmt));
        Serialize(Buffer, NAME_None);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}
#pragma auto_inline(on)

// ---- The unit: RVA 0x5dd90.
UBOOL UD3DRenderDevice::Exec(const TCHAR *Cmd, FOutputDevice &Ar)
{
    if (ParseCommand(&Cmd, TEXT_DUMPRESOURCEHASH))
    {
        for (INT BucketIndex = 0; BucketIndex < 4096; BucketIndex++)
        {
            INT NumResources = 0;
            for (FD3DResource *Resource = ResourceHash[BucketIndex]; Resource; Resource = Resource->HashNext)
                NumResources++;
        }
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_FIRSTCOLOREDMIP))
    {
        if (appStrcmp(Cmd, TEXT_Empty1) != 0)
            FirstColoredMip = appAtoi(Cmd);
        else
            FirstColoredMip = 255;
        Flush(0);
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_NEARCLIP))
    {
        if (appStrcmp(Cmd, TEXT_Empty2) != 0)
            NEAR_CLIPPING_PLANE = appAtof(Cmd);
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_D3DRESOURCES))
    {
        INT TextureBytes = 0, VertexBytes = 0, IndexBytes = 0, OtherBytes = 0;
        for (FD3DResource *Resource = ResourceList; Resource; Resource = Resource->NextResource)
        {
            if (Resource->GetTexture())
                TextureBytes += Resource->CalculateFootprint();
            else if (Resource->GetVertexStream())
                VertexBytes += Resource->CalculateFootprint();
            else if (Resource->GetIndexBuffer())
                IndexBytes += Resource->CalculateFootprint();
            else
                OtherBytes += Resource->CalculateFootprint();
        }
        Direct3DDevice8->GetAvailableTextureMem();
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_SUPPORTEDRESOLUTION))
    {
        DWORD Width = 0, Height = 0;
        INT BitDepth = 0, Supported = 0;
        if (Parse(Cmd, TEXT_WIDTH, Width) && Parse(Cmd, TEXT_HEIGHT, Height) && Parse(Cmd, TEXT_BITDEPTH, BitDepth))
        {
            for (INT ModeIndex = 0; ModeIndex < DisplayModes.Num(); ModeIndex++)
            {
                if (DisplayModes(ModeIndex).Width == Width && DisplayModes(ModeIndex).Height == Height &&
                    GetFormatBPP(DisplayModes(ModeIndex).Format) == BitDepth)
                {
                    Supported = 1;
                    break;
                }
            }
        }
        Ar.Logf(TEXT_PercentU, Supported);
        return 1;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit. Constructing the device
// in place emits its vtable so Exec keeps retail's virtual thiscall form.
void Escape(void *);
inline void *operator new(size_t, void *Mem) { return Mem; }
UBOOL Driver_5dd90(void *Mem, const TCHAR *Cmd, FOutputDevice &Ar)
{
    Escape(&NEAR_CLIPPING_PLANE); Escape(&GMalloc); Escape(&GLogFilterActive);
    FExec *E = new (Mem) UD3DRenderDevice;
    Escape(E);
    return E->Exec(Cmd, Ar);
}
