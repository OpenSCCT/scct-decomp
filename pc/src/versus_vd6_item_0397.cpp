// Work item 0397: Versus RVA 0x122360-0x12261c
// APlayerController::execGetPBConnectStatus, execGetServerNetworkAddress,
// execCopyToClipboard, execPasteFromClipboard;
// ALevelInfo::execDetailChange, execGetLocalURL.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef void *HANDLE;
typedef void *HWND;
typedef void *HGLOBAL;

#define RESULT_DECL void *const Result

extern "C" __declspec(dllimport) HWND __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) int __stdcall OpenClipboard(HWND);
extern "C" __declspec(dllimport) int __stdcall EmptyClipboard();
extern "C" __declspec(dllimport) int __stdcall CloseClipboard();
extern "C" __declspec(dllimport) HANDLE __stdcall SetClipboardData(unsigned int, HANDLE);
extern "C" __declspec(dllimport) HGLOBAL __stdcall GlobalAlloc(unsigned int, DWORD);
extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline TCHAR *appStrcpy(TCHAR *D, const TCHAR *S) { return wcscpy(D, S); }
inline INT appStricmp(const TCHAR *S1, const TCHAR *S2) { return _wcsicmp(S1, S2); }

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;

    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
    FString &operator=(const TCHAR *Other);
    FString &operator+=(const TCHAR *Str);
    UBOOL operator!=(const FString &Other) const;
    INT Add(INT Count, INT ElementSize);
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

// Literals retail keeps in writable .data.
extern const TCHAR GPBConnectStatusEmpty[];      // TEXT("") at 0x10c92304
extern const TCHAR GServerNetworkAddressEmpty[]; // TEXT("") at 0x10c92308

struct FFrame;

class UObject {
public:
    virtual ~UObject();
    BYTE unk_04[0x24];

    class UFunction *FindFunctionChecked(INT NameIndex, INT Strict = 0);
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    class UStruct *Node;
    UObject       *Object;
    BYTE          *Code;
    BYTE          *Locals;

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var)  FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH        Stack.Code++

enum EDetailMode {
    DM_Low       = 0,
    DM_High      = 1,
    DM_SuperHigh = 2,
};

class UNetConnection {
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual FString LowLevelGetRemoteAddress(); // slot 24, vtable +0x60
};

class UNetDriver {
public:
    BYTE            unk_00[0x38];
    UNetConnection *ServerConnection;
};

struct FURL {
    FString Protocol;
    FString Host;
    INT     Port;
    FString Map;
    FString *OpData;
    INT     OpNum;
    INT     OpMax;
    FString Portal;
    INT     Valid;

    FString String(UBOOL FullyQualified = 0) const;
};

class AActor : public UObject {
public:
    BYTE          unk_28[0x17c];
    class ULevel *XLevel;         // +0x1a4
    BYTE          unk_1a8[0x137];
    BYTE          bLightChanged;  // +0x2df
    BYTE          unk_2e0[0x18];

    class ULevel *GetLevel() const { return XLevel; }
};

class AController : public AActor {
};

class APlayerController : public AController {
public:
    void execGetPBConnectStatus(FFrame &Stack, RESULT_DECL);
    void execGetServerNetworkAddress(FFrame &Stack, RESULT_DECL);
    void execCopyToClipboard(FFrame &Stack, RESULT_DECL);
    void execPasteFromClipboard(FFrame &Stack, RESULT_DECL);
};

class AGameInfo : public AActor {
public:
    void ProcessEvent(class UFunction *Function, void *Parms, void *UnusedResult = 0);
};

class ALevelInfo : public AActor {
public:
    BYTE       unk_2f8[0x140];
    BYTE       DetailMode;        // +0x438
    BYTE       unk_439[0xa3];
    AGameInfo *Game;              // +0x4dc

    void execDetailChange(FFrame &Stack, RESULT_DECL);
    void execGetLocalURL(FFrame &Stack, RESULT_DECL);
};

class ULevel {
public:
    BYTE        unk_00[0x2c];
    AActor    **ActorsData;       // +0x2c
    INT         ActorsNum;        // +0x30
    INT         ActorsMax;        // +0x34
    BYTE        unk_38[0xb4];
    UNetDriver *NetDriver;        // +0xec
    BYTE        unk_f0[0x4];
    FURL        URL;              // +0xf4

    void DetailChange(EDetailMode NewDetailMode);
};

void appClipboardCopy(const TCHAR *Str);
FString appClipboardPaste();

// RVA 0x122360: APlayerController::execGetPBConnectStatus
void APlayerController::execGetPBConnectStatus(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = GPBConnectStatusEmpty;
}

// RVA 0x122380: APlayerController::execGetServerNetworkAddress
void APlayerController::execGetServerNetworkAddress(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (GetLevel() && GetLevel()->NetDriver && GetLevel()->NetDriver->ServerConnection)
        *(FString *)Result = GetLevel()->NetDriver->ServerConnection->LowLevelGetRemoteAddress();
    else
        *(FString *)Result = GServerNetworkAddressEmpty;
}

// RVA 0x122430: APlayerController::execCopyToClipboard
void APlayerController::execCopyToClipboard(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Text);
    P_FINISH;
    appClipboardCopy(*Text);
}

// RVA 0x1224c0: APlayerController::execPasteFromClipboard
void APlayerController::execPasteFromClipboard(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Text);
    P_FINISH;
    *(FString *)Result = appClipboardPaste();
}

// RVA 0x122560: ALevelInfo::execDetailChange
void ALevelInfo::execDetailChange(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(NewDetailMode);
    P_FINISH;
    XLevel->DetailChange((EDetailMode)NewDetailMode);
}

// RVA 0x1225b0: ALevelInfo::execGetLocalURL
void ALevelInfo::execGetLocalURL(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = XLevel->URL.String();
}

// ---------------------------------------------------------------------------
// Scaffolding for LTCG links, not part of the unit.
// Retail linked these /GL callers together with their /GL callees, so LINK
// /LTCG assigned custom calling conventions to the callees below. Defining
// the callees here (with __declspec(noinline) so retail call sites stay out
// of line) lets LINK /LTCG assign the same calling conventions.
// ---------------------------------------------------------------------------

#define GMEM_DDESHARE  0x2000
#define CF_UNICODETEXT 13

// Exact retail body of FString::operator=(const TCHAR *) (versus_ltcg1_item_9001.cpp).
__declspec(noinline) FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

// Exact retail body of appClipboardCopy (versus_vd3r_item_0055.cpp).
__declspec(noinline) void appClipboardCopy(const TCHAR *Str)
{
    if (OpenClipboard(GetActiveWindow())) {
        EmptyClipboard();
        HGLOBAL GlobalMem = GlobalAlloc(GMEM_DDESHARE, sizeof(TCHAR) * (appStrlen(Str) + 1));
        appStrcpy((TCHAR *)GlobalMem, Str);
        SetClipboardData(CF_UNICODETEXT, GlobalMem);
        CloseClipboard();
    }
}

extern void *GDetailResetTarget;
void __stdcall ResetDetailState(void *);

// Retail body of ULevel::DetailChange (RVA 0xf5660).
__declspec(noinline) void ULevel::DetailChange(EDetailMode NewDetailMode)
{
    ResetDetailState(&GDetailResetTarget);
    ALevelInfo *Info = (ALevelInfo *)ActorsData[0];
    Info->DetailMode = (BYTE)NewDetailMode;
    Info = (ALevelInfo *)ActorsData[0];
    if (Info->Game)
        Info->Game->ProcessEvent(Info->Game->FindFunctionChecked(0xc84, 0), 0, 0);
    for (INT i = 0; i < ActorsNum; i++) {
        if (ActorsData[i])
            ActorsData[i]->bLightChanged = 0;
    }
}

extern FString GDefaultProtocol;
extern FString GDefaultHost;
extern INT     GDefaultPort;
extern const TCHAR FURL_Question[];
extern const TCHAR FURL_Hash[];
FString __cdecl appItoa(INT Value);

// UE2 FURL::String body (triggers LTCG stack-passed `this` with `ret 0xc`).
static inline void AppendStr(FString &Dst, const TCHAR *Str)
{
    if (*Str) {
        if (Dst.ArrayNum) {
            INT Index = Dst.ArrayNum - 1;
            Dst.Add(appStrlen(Str), sizeof(TCHAR));
            appStrcpy(Dst.Data + Index, Str);
        } else {
            Dst.Add(appStrlen(Str) + 1, sizeof(TCHAR));
            appStrcpy(Dst.Data, Str);
        }
    }
}

__declspec(noinline) FString FURL::String(UBOOL FullyQualified) const
{
    FString Result;
    if (appStricmp(*Protocol, *GDefaultProtocol) != 0 || FullyQualified) {
        Result += *Protocol;
        Result += L":";
        if (Host != GDefaultHost)
            Result += L"//";
    }
    if (appStricmp(*Host, *GDefaultHost) != 0 || Port != GDefaultPort) {
        Result += *Host;
        if (Port != GDefaultPort) {
            Result += L":";
            Result += *appItoa(Port);
        }
        Result += L"/";
    }
    Result += *Map;
    for (INT i = 0; i < OpNum; i++) {
        AppendStr(Result, FURL_Question);
        AppendStr(Result, *OpData[i]);
    }
    if (Portal.ArrayNum) {
        AppendStr(Result, FURL_Hash);
        Result += *Portal;
    }
    return Result;
}

void Escape(void *);

void Driver_122360(APlayerController *PC, FFrame *S, void *R, FString *Str, const TCHAR *T)
{
    void (APlayerController::*Fn)(FFrame &, RESULT_DECL) = &APlayerController::execGetPBConnectStatus;
    Escape(&Fn);
    Escape(&GMalloc);
    *Str = T;
    PC->execGetPBConnectStatus(*S, R);
}

void Driver_122380(APlayerController *PC, FFrame *S, void *R, FString *Str, const TCHAR *T)
{
    void (APlayerController::*Fn)(FFrame &, RESULT_DECL) = &APlayerController::execGetServerNetworkAddress;
    Escape(&Fn);
    Escape(&GMalloc);
    *Str = T;
    PC->execGetServerNetworkAddress(*S, R);
}

void Driver_122430(APlayerController *PC, FFrame *S, void *R, const TCHAR *T)
{
    void (APlayerController::*Fn)(FFrame &, RESULT_DECL) = &APlayerController::execCopyToClipboard;
    Escape(&Fn);
    Escape(&GNatives);
    appClipboardCopy(T);
    PC->execCopyToClipboard(*S, R);
}

void Driver_122560(ALevelInfo *LI, FFrame *S, void *R, ULevel *L, EDetailMode M)
{
    void (ALevelInfo::*Fn)(FFrame &, RESULT_DECL) = &ALevelInfo::execDetailChange;
    Escape(&Fn);
    Escape(&GNatives);
    L->DetailChange(M);
    LI->execDetailChange(*S, R);
}

void Driver_1225b0(ALevelInfo *LI, FFrame *S, void *R, FURL *U, FString *Out)
{
    void (ALevelInfo::*Fn)(FFrame &, RESULT_DECL) = &ALevelInfo::execGetLocalURL;
    Escape(&Fn);
    Escape(&GMalloc);
    Escape(&GDefaultProtocol);
    Escape(&GDefaultHost);
    Escape(&GDefaultPort);
    *Out = U->String(1);
    *Out = U->String(0);
    FURL Local;
    Escape(&Local);
    *Out = Local.String(0);
    *Out = Local.String(1);
    LI->execGetLocalURL(*S, R);
}
