// Work item 0210: UGameEngine helpers around RVA 0xe7670-0xe7af4.
typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;

struct FColor {
    BYTE R, G, B, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : R(InR), G(InG), B(InB), A(InA) {}
};

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
};
struct FPlane : FVector {
    FLOAT W;
};

// UnMath.h: intersection of the line Point1-Point2 with Plane (an out-of-line copy, RVA 0xe7670).
FVector FLinePlaneIntersection(const FVector &Point1, const FVector &Point2, const FPlane &Plane)
{
    return Point1 + (Point2 - Point1) * ((Plane.W - (Point1 | Plane)) / ((Point2 - Point1) | Plane));
}

// Render device / interface reached through UViewport+0x140 (unnamed, slot 4 clears the screen).
class URenderInterface_e7720 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Clear(UBOOL UseColor, FColor Color, UBOOL UseDepth, FLOAT Depth, UBOOL UseStencil, DWORD Stencil);
};

class UViewport {
public:
    virtual void vpad00(); virtual void vpad01(); virtual void vpad02(); virtual void vpad03();
    virtual void vpad04(); virtual void vpad05(); virtual void vpad06(); virtual void vpad07();
    virtual void vpad08(); virtual void vpad09(); virtual void vpad10(); virtual void vpad11();
    virtual void vpad12(); virtual void vpad13(); virtual void vpad14(); virtual void vpad15();
    virtual void vpad16(); virtual void vpad17(); virtual void vpad18(); virtual void vpad19();
    virtual void vpad20(); virtual void vpad21(); virtual void vpad22(); virtual void vpad23();
    virtual void vpad24(); virtual void vpad25(); virtual void vpad26(); virtual void vpad27();
    virtual void vpad28(); virtual void vpad29(); virtual void vpad30(); virtual void vpad31();
    virtual void vpad32(); virtual void vpad33(); virtual void vpad34(); virtual void vpad35();
    virtual void Present(); // slot 36 (+0x90)
    BYTE Pad04[0x64];
    class UCanvas *Canvas;             // +0x68
    BYTE Pad6C[0x140 - 0x6C];
    URenderInterface_e7720 *RI;        // +0x140
};

class UClient {
public:
    BYTE Pad00[0x2C];
    UViewport **Viewports;             // +0x2C (TArray data)
    INT ViewportsNum;                  // +0x30
};

class UObject {
public:
    UObject() {}
    virtual ~UObject();
    virtual void vpad01(); virtual void vpad02(); virtual void vpad03();
    virtual void ProcessEvent(void *Function, void *Parms, void *Result, void *Extra); // slot 4
    virtual void vpad05(); virtual void vpad06(); virtual void vpad07();
    virtual void vpad08(); virtual void vpad09(); virtual void vpad10(); virtual void vpad11();
    virtual void vpad12(); virtual void vpad13(); virtual void vpad14(); virtual void vpad15();
    virtual void vpad16(); virtual void vpad17(); virtual void vpad18(); virtual void vpad19();
    virtual void vpad20(); virtual void vpad21(); virtual void vpad22(); virtual void vpad23();
    virtual void vpad24(); virtual void vpad25(); virtual void vpad26(); virtual void vpad27();
    virtual void vpad28(); virtual void vpad29(); virtual void vpad30(); virtual void vpad31();
    BYTE ObjectPad[0x24];
};

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, void *Ar);
};

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const FString &Other);      // 0x104640
    const TCHAR *operator*() const { return ArrayNum ? Data : TEXT_Empty; }
    static const TCHAR TEXT_Empty[];
    FString(const TCHAR *In);           // 0x1046c0
    FString &operator=(const FString &Other);
    ~FString();                         // 0x1048b0
};

// Inline CRT wrappers (UnFile.h).
extern "C" __declspec(dllimport) int _wcsicmp(const TCHAR *A, const TCHAR *B);
extern "C" __declspec(dllimport) int wcsncmp(const TCHAR *A, const TCHAR *B, unsigned int Count);
extern "C" __declspec(dllimport) unsigned int wcslen(const TCHAR *S);
extern "C" __declspec(dllimport) TCHAR *wcscpy(TCHAR *Dest, const TCHAR *Src);
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }
inline INT appStrncmp(const TCHAR *A, const TCHAR *B, INT Count) { return wcsncmp(A, B, Count); }
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
extern "C" __declspec(dllimport) TCHAR *wcsncpy(TCHAR *Dest, const TCHAR *Src, unsigned int Count);
inline TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT Max) { wcsncpy(Dest, Src, Max); Dest[Max - 1] = 0; return Dest; }
inline TCHAR *appStrcpy(TCHAR *Dest, const TCHAR *Src) { return wcscpy(Dest, Src); }

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize)
    :   ArrayNum(InNum), ArrayMax(InNum), Data(0)
    {
        if (ArrayMax)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"Farray::protectedcstor");
        else
            Data = 0;
    }
    INT Add(INT Count, INT ElementSize);   // 0x1044e0
};

template <class T> class TArray : public FArray {
public:
    TArray() {}
    TArray(const TArray &Other);
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};
template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}
template <class T> inline void operator delete(void *, TArray<T> &) {}

// UnTemplate.h (TArray<FString> copy: FUN_1090c550; LTCG: this on the stack, Other in EDI).
template <class T> TArray<T>::TArray(const TArray<T> &Other)
:   FArray(Other.ArrayNum, sizeof(T))
{
    ArrayNum = 0;
    for (INT i = 0; i < Other.ArrayNum; i++)
        new(*this) T(Other(i));
}

class FURL {
public:
    FString Protocol;                   // +0x00
    FString Host;                       // +0x0C
    INT Port;                           // +0x18
    FString Map;                        // +0x1C
    TArray<FString> Op;                 // +0x28
    FString Portal;                     // +0x34
    UBOOL Valid;                        // +0x40
    static FString DefaultProtocol;
    static FString DefaultHost;
    static FString DefaultMap;
    static FString DefaultPortal;
    static FString DefaultLocalMap;
    static INT DefaultPort;
    FURL(const TCHAR *LocalFilename = 0);
    FURL(FURL *Base, const TCHAR *TextURL, INT Type);  // FUN_10a33560
};

// UnURL.cpp (FUN_10a33490; LTCG: this on the stack, LocalFilename in EDI).
FURL::FURL(const TCHAR *LocalFilename)
:   Protocol(DefaultProtocol)
,   Host(DefaultHost)
,   Port(DefaultPort)
,   Map(LocalFilename ? FString(LocalFilename) : DefaultMap)
,   Op()
,   Portal(DefaultPortal)
,   Valid(1)
{}

void FURL_ParseText(FURL *URL, const TCHAR *Text, INT Index);
void FURL_AddOp(FURL *URL, const FString &Op);
void FURL_CheckBase(FURL **Base);

// Stand-in for FUN_10a33560 (retail body is about 2.4 KB of URL parsing); it only keeps the
// constructor out of line with the same LTCG convention (this and all arguments on the stack).
FURL::FURL(FURL *Base, const TCHAR *TextURL, INT Type)
:   Protocol(DefaultProtocol)
,   Host(DefaultHost)
,   Port(DefaultPort)
,   Map(DefaultMap)
,   Op()
,   Portal(DefaultPortal)
,   Valid(1)
{
    TCHAR TempURL[1024];
    appStrncpy(TempURL, TextURL, 1024);
    TCHAR *URL = TempURL;
    FURL_CheckBase(&Base);
    if (Type == 2) {
        Protocol = Base->Protocol;
        Host = Base->Host;
        Map = Base->Map;
        Portal = Base->Portal;
        Port = Base->Port;
    }
    if (Type == 2 || Type == 1) {
        for (INT i = 0; i < Base->Op.Num(); i++)
            FURL_AddOp(this, Base->Op(i));
    }
    for (INT i = 0; URL[i]; i++)
        FURL_ParseText(this, URL + i, i);
    if (Port == 0)
        Valid = 0;
}

// UnMisc.cpp (FUN_109126c0; LTCG: &Str in EAX, Result in EBX).
UBOOL ParseToken(const TCHAR *&Str, TCHAR *Result, INT MaxLen, UBOOL UseEscape)
{
    INT Len = 0;
    while (*Str == ' ' || *Str == 9)
        Str++;
    if (*Str == '"') {
        Str++;
        while (*Str && *Str != '"' && (Len + 1) < MaxLen) {
            TCHAR c = *Str++;
            if (c == '\\' && UseEscape) {
                c = *Str++;
                if (!c)
                    break;
            }
            if ((Len + 1) < MaxLen)
                Result[Len++] = c;
        }
        if (*Str == '"')
            Str++;
    } else {
        for (; *Str && *Str != ' ' && *Str != 9; Str++)
            if ((Len + 1) < MaxLen)
                Result[Len++] = *Str;
    }
    Result[Len] = 0;
    return Len != 0;
}

extern TCHAR GCmdLine[];                 // 0x10c92680
inline const TCHAR *appCmdLine() { return GCmdLine; }
extern UBOOL GIsBrowsingInitialMap_e7880; // 0x10c925f8 (neutral name)
extern const TCHAR Empty_10c92484[];     // L"" in writable .data
extern const TCHAR Empty_10c92488[];     // L"" in writable .data
// Retail keeps two unpooled copies of L"PLATFORM=" (0x10c495bc for the compare, 0x10c495a8 for the length).
extern const TCHAR PlatformPrefix_Cmp[];
extern const TCHAR PlatformPrefix_Len[];

class USubsystem : public UObject, public FExec {
public:
    USubsystem() {}
};

class UEngine : public USubsystem {
public:
    UEngine() {}
    ~UEngine();
    BYTE EnginePad2C[0x30 - 0x2C];
    UClient *Client;                   // +0x30
};

extern const TCHAR UGameEngine_EmptyURL[];  // L"" in writable .data (0x10c92480)

class UGameEngine : public UEngine {
public:
    virtual void Draw(UViewport *Viewport, UBOOL Blit, BYTE *HitData, INT *HitSize); // slot 32 (+0x80)
    virtual void gpad33(); virtual void gpad34(); virtual void gpad35(); virtual void gpad36();
    virtual void gpad37(); virtual void gpad38(); virtual void gpad39(); virtual void gpad40();
    virtual void gpad41(); virtual void gpad42(); virtual void gpad43(); virtual void gpad44();
    virtual void gpad45(); virtual void gpad46(); virtual void gpad47();
    virtual UBOOL Browse(FURL URL, const void *TravelInfo, FString &Error); // slot 48 (+0xc0)

    UGameEngine();
    DWORD HashKey_e77b0(INT Key);
    void DrawFirstViewport_e7720();
    void Tick_e77d0(void *A, void *B);
    void BrowseInitialMap_e7880();

    BYTE GamePad34[0x13C - 0x34];
    FURL LastURL;                      // +0x13C
};

UGameEngine::UGameEngine()
:   LastURL(UGameEngine_EmptyURL)
{}


class UCanvas : public UObject {
public:
    BYTE Pad28[0x34 - 0x28];
    FLOAT ClipX;                        // +0x34
    FLOAT ClipY;                        // +0x38
    BYTE Pad3C[0x58 - 0x3C];
    INT SizeX;                          // +0x58
    INT SizeY;                          // +0x5C
    BYTE Pad60[0x78 - 0x60];
    UViewport *Viewport;                // +0x78
    void Update();                      // FUN_10a00d30 (LTCG, this in ESI)
};
void *FindCanvasResetEvent(UCanvas *Canvas);
INT appFloor(FLOAT F);

// Retail body of FUN_10a00d30 is larger; this stand-in keeps it out of line with this in ESI.
void UCanvas::Update()
{
    ProcessEvent(FindCanvasResetEvent(this), 0, 0, 0);
    ClipX = (FLOAT)Viewport->Canvas->SizeX;
    SizeX = appFloor(ClipX);
    ClipY = (FLOAT)Viewport->Canvas->SizeY;
    SizeY = appFloor(ClipY);
    ProcessEvent(FindCanvasResetEvent(this), 0, 0, 0);
}

// Unnamed object at +0x40 of the first argument of slot 54 (neutral names).
class UnnamedSink_e77d0 {
public:
    virtual void vpad00(); virtual void vpad01(); virtual void vpad02(); virtual void vpad03();
    virtual void vpad04(); virtual void vpad05(); virtual void vpad06(); virtual void vpad07();
    virtual void vpad08(); virtual void vpad09(); virtual void vpad10(); virtual void vpad11();
    virtual void vpad12(); virtual void vpad13(); virtual void vpad14(); virtual void vpad15();
    virtual void vpad16(); virtual void vpad17(); virtual void vpad18(); virtual void vpad19();
    virtual void vpad20(); virtual void vpad21(); virtual void vpad22(); virtual void vpad23();
    virtual void vpad24(); virtual void vpad25(); virtual void vpad26();
    virtual void Add(INT Value);       // slot 27 (+0x6c)
    virtual void Flush();              // slot 28 (+0x70)
};
struct UnnamedOwner_e77d0 {
    BYTE Pad00[0x40];
    UnnamedSink_e77d0 *Sink;           // +0x40
};
struct UnnamedInner_e77d0 { BYTE Pad00[0x10]; INT Value; };
struct UnnamedMid_e77d0 { BYTE Pad00[0x24]; UnnamedInner_e77d0 *Inner; };
struct ALevelInfo_e77d0 { BYTE Pad00[0x4dc]; UnnamedMid_e77d0 *Mid; };
struct ULevel_e77d0 {
    BYTE Pad00[0x10];
    INT Value;                         // +0x10
    BYTE Pad14[0x2c - 0x14];
    ALevelInfo_e77d0 **Actors;         // +0x2c (Actors TArray data)
};
extern INT GCounter_e77d0;             // 0x10c925a4
void AfterTick_e77d0();                // FUN_1091b510

// Reflected vtable slot 54 (neutral names).
void UGameEngine::Tick_e77d0(void *InOwner, void *InLevel)
{
    UnnamedOwner_e77d0 *Owner = (UnnamedOwner_e77d0 *)InOwner;
    ULevel_e77d0 *Level = (ULevel_e77d0 *)InLevel;
    GCounter_e77d0++;
    Owner->Sink->Add(Level->Value);
    Owner->Sink->Add(Level->Actors[0]->Mid->Inner->Value);
    Owner->Sink->Flush();
    AfterTick_e77d0();
}

// Reflected vtable slot 24: enter the map named on the command line (neutral name).
void UGameEngine::BrowseInitialMap_e7880()
{
    FString Error;
    FURL DefaultURL;
    GIsBrowsingInitialMap_e7880 = 1;
    TCHAR Parm[4096] = { Empty_10c92484[0] };
    const TCHAR *Tmp = appCmdLine();
    if (!ParseToken(Tmp, Parm, 4096, 0)
     || (appStricmp(Parm, L"SERVER") == 0 && !ParseToken(Tmp, Parm, 4096, 0))
     || (appStrncmp(Parm, PlatformPrefix_Cmp, appStrlen(PlatformPrefix_Len)) == 0 && !ParseToken(Tmp, Parm, 4096, 0))
     || Parm[0] == '-')
        appStrcpy(Parm, *FURL::DefaultLocalMap);
    FURL URL(&DefaultURL, Parm, 1);
    if (!Browse(URL, 0, Error)) {
        if (appStricmp(*Error, Empty_10c92488) == 0 && appStricmp(Parm, *FURL::DefaultLocalMap) != 0)
            Browse(FURL(&DefaultURL, *FURL::DefaultLocalMap, 1), 0, Error);
    }
}

// Reflected vtable slot 39: scramble a 32-bit key.
DWORD UGameEngine::HashKey_e77b0(INT Key)
{
    return (Key >> 16) ^ (Key * 237) ^ (Key << 16) ^ 0x93FE92CE;
}

// Reflected vtable slot 52: clear and draw the first viewport.
void UGameEngine::DrawFirstViewport_e7720()
{
    if (Client && Client->ViewportsNum) {
        UViewport *Viewport = Client->Viewports[0];
        if (Viewport && Viewport->Canvas && Viewport->RI) {
            Viewport->Canvas->Update();
            Viewport->RI->Clear(0, FColor(0, 0, 0, 255), 1, 1.0f, 1, 0);
            Draw(Viewport, 1, 0, 0);
            Viewport->Present();
        }
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_e7720(UGameEngine *E)
{
    void (UGameEngine::*P)() = &UGameEngine::DrawFirstViewport_e7720;
    Escape(&P);
    E->DrawFirstViewport_e7720();
}
void Driver_e77d0(UGameEngine *E, void *A, void *B)
{
    void (UGameEngine::*P)(void *, void *) = &UGameEngine::Tick_e77d0;
    Escape(&P);

    E->Tick_e77d0(A, B);
}
void Driver_e7670(FVector *Out, const FVector *A, const FVector *B, const FPlane *P)
{
    Out[0] = FLinePlaneIntersection(*A, *B, *P);
    Out[1] = FLinePlaneIntersection(*B, *A, *P);
}
inline void *operator new(unsigned int, void *Mem) { return Mem; }
inline void operator delete(void *, void *) {}
UGameEngine *Driver_e7820(void *Mem)
{
    return new(Mem) UGameEngine;
}
void Driver_e7880(UGameEngine *E, const TCHAR *T)
{
    FURL U(0); FURL V(T); Escape(&U); Escape(&V);
    void (UGameEngine::*P)() = &UGameEngine::BrowseInitialMap_e7880;
    Escape(&P);
    E->BrowseInitialMap_e7880();
}
