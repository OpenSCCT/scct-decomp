// Work item 0291: UCanvas::execDrawTile (RVA 0x101360).
// Retail compiled this with VC7.0 /GL and linked with /LTCG: UCanvas::DrawTile
// (retail 0xff300) takes `this` in ESI and the material in EAX, and
// FOutputDevice::Logf (retail 0x118d0) takes `this` in EBX. This SCCT build
// passes no fog plane to DrawTile and does not add SpaceX to CurX.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

#define RESULT_DECL void *const Result

class UObject;
struct FFrame;
typedef void (UObject::*Native)(FFrame &TheStack, RESULT_DECL);
extern Native GNatives[];

class UObject
{
public:
    void *VfTable_Dummy;
};

struct FOutputDevice
{
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);
};

struct FFrame : public FOutputDevice
{
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_FLOAT(v) FLOAT v = 0.f; Stack.Step(Stack.Object, &v);
#define P_GET_OBJECT(cls, v) cls *v = 0; Stack.Step(Stack.Object, &v);
#define P_FINISH Stack.Code++;

template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FColor
{
    BYTE B, G, R, A;
};

class UMaterial;

class UCanvas : public UObject
{
public:
    BYTE Pad04[0x2c - 0x04];
    FLOAT OrgX;      // 0x2c
    FLOAT OrgY;      // 0x30
    FLOAT ClipX;     // 0x34
    FLOAT ClipY;     // 0x38
    FLOAT CurX;      // 0x3c
    FLOAT CurY;      // 0x40
    FLOAT Z;         // 0x44
    BYTE Style;      // 0x48
    FLOAT CurYL;     // 0x4c
    FColor DrawColor; // 0x50

    void DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color);
    void execDrawTile(FFrame &Stack, RESULT_DECL);
};

extern const TCHAR Text_DrawTileMissingMaterial[];

void UCanvas::execDrawTile(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UMaterial, Mat);
    P_GET_FLOAT(XL);
    P_GET_FLOAT(YL);
    P_GET_FLOAT(U);
    P_GET_FLOAT(V);
    P_GET_FLOAT(UL);
    P_GET_FLOAT(VL);
    P_FINISH;
    if (!Mat)
    {
        Stack.Logf(Text_DrawTileMissingMaterial);
        return;
    }
    if (Style)
        DrawTile(Mat, OrgX + CurX, OrgY + CurY, XL, YL, U, V, UL, VL, Z, DrawColor);
    CurX += XL;
    CurYL = Max(CurYL, YL);
}

// Scaffolding for the link, not part of the unit: stand-in bodies so the
// linker gives the callees retail's register conventions (approximations;
// only their conventions matter here).
typedef char *va_list;
typedef unsigned int size_t;
struct FLogFilter { INT Pad[1]; DWORD Flags; };
struct FLogOwner { BYTE Pad[0x930]; FLogFilter *Filter; };
extern UBOOL GLogFilterActive;
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
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Dest, size_t Count, const TCHAR *Fmt, va_list Args);
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);
#pragma auto_inline(off)
// UE2 ParseParam (retail 0x121c0: Stream in EDI, Param in ESI).
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!GLogFilterActive || !(GLogOwner->Filter->Flags & 0x1000))
    {
        TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, Text_Logf);
        _vsnwprintf(Buffer, 0x8000, Fmt, (va_list)&Fmt + sizeof(Fmt));
        Serialize(Buffer, 0x24c);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}
void ExtPrepare(UCanvas *, UMaterial *);
void ExtTile(UCanvas *, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FColor);
void UCanvas::DrawTile(UMaterial *Material, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL,
                  FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, FLOAT Z, FColor Color)
{
    ExtPrepare(this, Material);
    ExtTile(this, X, Y, XL, YL, U, V, UL, VL, Z, Color);
    ExtPrepare(this, 0);
}
#pragma auto_inline(on)
void Escape(void *);
void Driver_101360(UCanvas *C, FFrame *S, void *R)
{
    Escape(&GNatives);
    void (UCanvas::*P)(FFrame &, void *const) = &UCanvas::execDrawTile;
    Escape(&P);
    (C->*P)(*S, R);
}
