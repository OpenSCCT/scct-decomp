// Work item w3 0396: Versus RVA 0x121d70-0x122359 (Engine, AActor / APlayerController).
//   0x121d70 AActor::execConsoleCommand
//   0x121e60 AActor::execError
//   0x121f00 APlayerController::execresetConnectionPing
//   0x121f30 APlayerController::execClientTravel
//   0x122210 APlayerController::execGetPlayerNetworkAddress
//   0x122270 APlayerController::GetPlayerNetworkAddress

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned int size_t;

enum EName {
    NAME_None = 0,
    NAME_ScriptWarning = 0x24c,
    NAME_TravelError = 0x1411
};

enum ETravelType {
    TRAVEL_Absolute = 0,
    TRAVEL_Partial  = 1,
    TRAVEL_Relative = 2
};

extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);
TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT Max);
DOUBLE appSeconds();

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline INT appStricmp(const TCHAR *S1, const TCHAR *S2) { return _wcsicmp(S1, S2); }

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

inline void *operator new(size_t Size)
{
    return GMalloc->Malloc((DWORD)Size, L"new");
}

inline void operator delete(void *Ptr)
{
    GMalloc->Free(Ptr);
}

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize);
    ~FArray();
    INT Num() const { return ArrayNum; }
};

class FString : public FArray {
public:
    FString() {}
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    FString &operator=(const TCHAR *Other);
    const TCHAR *operator*() const { return Num() ? (const TCHAR *)Data : L""; }
    UBOOL operator!=(const TCHAR *Other) const;
};

template <class T> class TArray : public FArray {
public:
    TArray() {}
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

struct FNameEntry {
    INT   Index;
    DWORD Flags;
};

struct FName {
    INT Index;
    FName() {}
    FName(EName InIndex) : Index(InIndex) {}

    static UBOOL Initialized;
    static FNameEntry **Names;
    static UBOOL SafeSuppressed(EName Index)
    {
        return Initialized && (Names[Index]->Flags & 0x1000);
    }
};

// Strings kept in writable .data in retail VC7.0 output.
extern const TCHAR StrEmpty_DefaultOutput[];   // 0x10c922fc L""
extern const TCHAR StrEmpty_NetAddr[];         // 0x10c92300 L""
extern const TCHAR StrMap_entry[];             // 0x10c47974 L"entry"
extern const TCHAR StrMap_Entry[];             // 0x10c47980 L"Entry"
extern const TCHAR StrMap_Lobby[];             // 0x10c4798c L"Lobby"
extern const TCHAR StrMap_TME30[];             // 0x10c47998 L"TME30"
extern const TCHAR StrMap_TSP20[];             // 0x10c479a4 L"TSP20"
extern const TCHAR StrMap_EntrySdc[];          // 0x10c479b0 L"Entry.sdc"
extern const TCHAR StrMap_EntrySds[];          // 0x10c479c4 L"Entry.sds"

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush() {}
    void Log(const TCHAR *S);
};

class FStringOutputDevice : public FOutputDevice, public FString {
public:
    FStringOutputDevice(const TCHAR *InStr = StrEmpty_DefaultOutput) : FString(InStr) {}
    void Serialize(const TCHAR *Data, EName Event);
};

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

struct FGuid;
struct FFrame;
class UClass;
class UFunction;

#define RESULT_DECL void *const Result

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *UnusedResult = 0);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
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

    INT     Index;
    BYTE    unk_8[0x1c];
    UClass *Class;

    inline UBOOL IsA(UClass *SomeBase) const;
    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class UField : public UObject {
public:
    UField *SuperField;
};

class UClass : public UField {
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    void    *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(Var) UBOOL Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_BYTE(Var)  BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var)   FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH         Stack.Code++

struct FURL {
    FString Protocol;
    FString Host;
    INT Port;
    FString Map;
    TArray<FString> Op;
    FString Portal;
    UBOOL Valid;

    static FString DefaultProtocol;
    static FString DefaultHost;
    static FString DefaultMap;
    static FString DefaultPortal;
    static INT DefaultPort;

    FURL(FURL *Base, const TCHAR *TextURL, ETravelType Type);
    ~FURL();
};

class UEngine : public UObject, public FExec {
public:
    BYTE unk_2c[0x110];
    FURL LastURL;   // +0x13c
};

struct UNetConnectionChannelPad {
    BYTE unk_0[0x1d8];
    INT Field1D8;
    BYTE unk_1dc[0x34];
    INT Field210;
};

class UNetDriver : public UObject {
public:
    BYTE unk_28[4];
    TArray<UNetConnectionChannelPad *> ClientConnections; // +0x2c
    BYTE unk_38[0x58];
    INT MaxPing;        // +0x90
    BYTE unk_94[0x5c];
    DOUBLE ResetTime;   // +0xf0

    void ResetConnectionPing();
};

class AActor;

class ULevel : public UObject {
public:
    BYTE unk_28[0xc4];
    UNetDriver *NetDriver;  // +0xec
    UEngine    *Engine;     // +0xf0

    UBOOL DestroyActor(AActor *ThisActor, UBOOL bNetForce = 0);
};

class UPlayer : public UObject {
public:
    BYTE unk_28[8];
    void *Actor; // +0x30
};

class UNetConnection : public UPlayer {
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual FString LowLevelGetRemoteAddress(); // slot 24 (+0x60)

    static UClass PrivateStaticClass; // 0x10cbc5e8
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

// Neutral name: manager at *(0x10c923c4) + 0x184 holding scanned map names and current map.
struct FMapListManager {
    BYTE unk_0[0x28];
    TArray<FString> Maps;       // +0x28
    FString CurrentMap;         // +0x34
    INT Field40;                // +0x40

    void LoadMaps();
};

struct FGlobalContext {
    BYTE unk_0[0x184];
    FMapListManager *MapList;   // +0x184
};

class UTravelNotify : public UObject {
public:
    void eventTravelError(BYTE Reason)
    {
        struct { BYTE Reason; } Parms;
        Parms.Reason = Reason;
        ProcessEvent(FindFunctionChecked(NAME_TravelError, 0), &Parms, 0);
    }
};

extern FGlobalContext *GGlobalContext;  // 0x10c923c4
extern UTravelNotify  *GTravelNotifyObject; // 0x10c9253c

// Neutral name: 0x48-byte travel launcher object constructed in execClientTravel (0x10a84060).
class FTravelLauncher {
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();

    INT      Field04;       // +0x04
    void    *Actor;         // +0x08
    UPlayer *Player;        // +0x0c
    FString  URL;           // +0x10
    UBOOL    bItems;        // +0x1c
    INT      TravelType;    // +0x20
    UEngine *Engine;        // +0x24
    UBOOL    bExtraFlag;    // +0x28
    BYTE     Field2C;       // +0x2c
    BYTE     Field2D;       // +0x2d
    BYTE     unk_2e[0xe];
    INT      Field3C;       // +0x3c
    BYTE     Field40;       // +0x40
    BYTE     unk_41[3];
    INT      Field44;       // +0x44

    FTravelLauncher(UPlayer *InPlayer, FString InURL, UBOOL bInItems, ETravelType InTravelType, UEngine *InEngine, UBOOL bExtra);
};

extern FTravelLauncher *GTravelLauncher; // 0x10c8bbf4

class AActor : public UObject {
public:
    BYTE unk_28[0x17c];
    ULevel *XLevel;         // +0x1a4

    ULevel *GetLevel() const { return XLevel; }

    void execConsoleCommand(FFrame &Stack, RESULT_DECL);
    void execError(FFrame &Stack, RESULT_DECL);
};

class APlayerController : public AActor {
public:
    BYTE unk_1a8[0x2fc];
    UPlayer *Player;        // +0x4a4

    void execresetConnectionPing(FFrame &Stack, RESULT_DECL);
    void execClientTravel(FFrame &Stack, RESULT_DECL);
    void execGetPlayerNetworkAddress(FFrame &Stack, RESULT_DECL);
    FString GetPlayerNetworkAddress();
};

// 0x121d70: AActor::execConsoleCommand
void AActor::execConsoleCommand(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Command);
    P_FINISH;

    FStringOutputDevice StrOut;
    GetLevel()->Engine->Exec(*Command, StrOut);
    *(FString *)Result = *StrOut;
}

// 0x121e60: AActor::execError
void AActor::execError(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;

    Stack.Log(*S);
    GetLevel()->DestroyActor(this);
}

// 0x121f00: APlayerController::execresetConnectionPing
void APlayerController::execresetConnectionPing(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    if (XLevel && XLevel->NetDriver)
        XLevel->NetDriver->ResetConnectionPing();
}

// 0x121f30: APlayerController::execClientTravel
void APlayerController::execClientTravel(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(URL);
    P_GET_BYTE(TravelType);
    P_GET_UBOOL(bItems);
    P_FINISH;

    FMapListManager *MapMgr = GGlobalContext->MapList;
    if (Player && appStricmp(*MapMgr->CurrentMap, StrMap_entry) != 0)
    {
        FURL TempURL(&GetLevel()->Engine->LastURL, *URL, (ETravelType)TravelType);
        bool bValidMap = true;
        if (appStricmp(*TempURL.Map, StrMap_Entry) != 0 &&
            appStricmp(*TempURL.Map, StrMap_Lobby) != 0 &&
            TempURL.Map != StrMap_TME30 &&
            TempURL.Map != StrMap_TSP20 &&
            TempURL.Map != StrMap_EntrySdc &&
            TempURL.Map != StrMap_EntrySds)
        {
            if (MapMgr->Maps.Num() == 0)
                MapMgr->LoadMaps();
            INT i;
            for (i = 0; i < MapMgr->Maps.Num(); i++)
            {
                if (appStricmp(*MapMgr->Maps(i), *TempURL.Map) == 0)
                    break;
            }
            bValidMap = (i != MapMgr->Maps.Num());
        }

        if (bValidMap)
        {
            GTravelLauncher = new FTravelLauncher(Player, URL, bItems, (ETravelType)TravelType, GetLevel()->Engine, 0);
        }
        else
        {
            GTravelNotifyObject->eventTravelError(10);
        }
    }
}

// 0x122210: APlayerController::execGetPlayerNetworkAddress
void APlayerController::execGetPlayerNetworkAddress(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    *(FString *)Result = GetPlayerNetworkAddress();
}

// 0x122270: APlayerController::GetPlayerNetworkAddress
FString APlayerController::GetPlayerNetworkAddress()
{
    FString Ret;
    if (Player && Player->IsA(UNetConnection::StaticClass()))
        Ret = Cast<UNetConnection>(Player)->LowLevelGetRemoteAddress();
    else
        Ret = StrEmpty_NetAddr;
    return Ret;
}

// =========================================================================
// Scaffolding for the LTCG link (out-of-line LTCG callees and link drivers).
// Not part of the matched functions above.
// =========================================================================

// 0x4750: FString::operator=(const TCHAR *) (published unit versus-vd-4750)
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data) {
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

// 0x15460: FString::operator!=(const TCHAR *) const (published unit versus-vd-15460)
__declspec(noinline) UBOOL FString::operator!=(const TCHAR *Other) const
{
    return _wcsicmp(**this, Other) != 0;
}

// 0x117a0: FOutputDevice::Log(const TCHAR *) (LTCG: this in EBX, S on stack)
extern BYTE GLogHelperA[16];
extern BYTE GLogHelperB[16];
INT ExternalLogCheck(void *A, void *B);

__declspec(noinline) INT LogHelperCall(BYTE *A, BYTE *B)
{
    if (!A || !B)
        return 0;
    if (ExternalLogCheck(A, B))
        return ExternalLogCheck(B, A);
    return ExternalLogCheck(A + 1, B + 1) + *A + *B;
}

__declspec(noinline) void FOutputDevice::Log(const TCHAR *S)
{
    if (!FName::SafeSuppressed(NAME_ScriptWarning))
        Serialize(S, NAME_ScriptWarning);
    if (!LogHelperCall(GLogHelperA, GLogHelperB))
        Flush();
}

// 0x11a790: ULevel::DestroyActor (LTCG: all args on stack, ret 0xc)
INT ExternalDestroyStep(void *A, void *B, void *C, void *D);
__declspec(noinline) UBOOL ULevel::DestroyActor(AActor *ThisActor, UBOOL bNetForce)
{
    INT A = ExternalDestroyStep(ThisActor, &ThisActor, &bNetForce, 0);
    INT B = ExternalDestroyStep(ThisActor, (void *)A, (void *)bNetForce, 0);
    INT C = ExternalDestroyStep((void *)A, (void *)B, ThisActor, 0);
    INT D = ExternalDestroyStep((void *)B, (void *)C, (void *)A, 0);
    for (INT i = 0; i < A; i++)
        D += ExternalDestroyStep((void *)i, (void *)B, (void *)C, (void *)D);
    if (D)
        ExternalDestroyStep(this, ThisActor, (void *)bNetForce, (void *)D);
    return D != 0;
}

// 0xef0a0: UNetDriver::ResetConnectionPing (LTCG: this in ESI, ret)
__declspec(noinline) void UNetDriver::ResetConnectionPing()
{
    ResetTime = appSeconds();
    if (ClientConnections.Num() != 0)
    {
        MaxPing = 999999;
        for (INT i = 0; i < ClientConnections.Num(); i++)
        {
            ClientConnections(i)->Field1D8 = 0;
            ClientConnections(i)->Field210 = 0;
        }
    }
}

// 0x133560: FURL::FURL (LTCG: all args on stack, ret 0x10)
void FURL_ParseText(FURL *URL, const TCHAR *Text, INT Index);
void FURL_AddOp(FURL *URL, const FString &Op);
void FURL_CheckBase(FURL **Base);

__declspec(noinline) FURL::FURL(FURL *Base, const TCHAR *TextURL, ETravelType Type)
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
    if (Type == TRAVEL_Relative) {
        Protocol = Base->Protocol;
        Host = Base->Host;
        Map = Base->Map;
        Portal = Base->Portal;
        Port = Base->Port;
    }
    if (Type == TRAVEL_Relative || Type == TRAVEL_Partial) {
        for (INT i = 0; i < Base->Op.Num(); i++)
            FURL_AddOp(this, Base->Op(i));
    }
    for (INT i = 0; URL[i]; i++)
        FURL_ParseText(this, URL + i, i);
    if (Port == 0)
        Valid = 0;
}

// 0xa7d70: FURL::~FURL (LTCG: this on stack, ret 4)
__declspec(noinline) FURL::~FURL()
{
}

// 0xe31b0: FMapListManager::LoadMaps (LTCG: this on stack, ret 4)
void ExternalLoadMaps(FMapListManager *Mgr);
__declspec(noinline) void FMapListManager::LoadMaps()
{
    TCHAR Buf[512];
    appStrncpy(Buf, L"System\\", 512);
    ExternalLoadMaps(this);
}

// 0x184060: FTravelLauncher::FTravelLauncher (LTCG: InPlayer in ECX, this + rest on stack, ret 0x20)
void ExternalTravelInit(FTravelLauncher *Self, UPlayer *P, const TCHAR *S, INT *OutA, INT *OutB);
__declspec(noinline) FTravelLauncher::FTravelLauncher(UPlayer *InPlayer, FString InURL, UBOOL bInItems, ETravelType InTravelType, UEngine *InEngine, UBOOL bExtra)
{
    Field2C = 0;
    Field2D = 0;
    Player = InPlayer;
    URL = InURL;
    bItems = bInItems;
    TravelType = InTravelType;
    Engine = InEngine;
    bExtraFlag = bExtra;
    Actor = InPlayer->Actor;
    Field3C = 0;
    Field40 = 0;
    Field44 = 0;
    Field04 = 0;
    while (InPlayer)
    {
        InPlayer->VirtualSlot5();
        InPlayer->VirtualSlot6();
        InPlayer = (UPlayer *)InPlayer->Actor;
    }
    ExternalTravelInit(this, 0, *InURL, (INT *)&bInItems, (INT *)&InEngine);
    ExternalTravelInit(this, 0, *URL, (INT *)&InTravelType, (INT *)&bExtra);
}

void Escape(void *);

void Driver_121d70(AActor *A, FFrame *S, void *R, FString *Str, const TCHAR *T)
{
    Escape(&GMalloc);
    void (AActor::*Fn)(FFrame &, void *const) = &AActor::execConsoleCommand;
    Escape(&Fn);
    *Str = T;
    A->execConsoleCommand(*S, R);
}

void Driver_121e60(AActor *A, FFrame *S, void *R)
{
    Escape(&GMalloc);
    Escape(&FName::Initialized);
    Escape(&FName::Names);
    Escape(GLogHelperA);
    Escape(GLogHelperB);
    void (AActor::*Fn)(FFrame &, void *const) = &AActor::execError;
    Escape(&Fn);
    A->execError(*S, R);
}

void Driver_121f00(APlayerController *PC, FFrame *S, void *R)
{
    void (APlayerController::*Fn)(FFrame &, void *const) = &APlayerController::execresetConnectionPing;
    Escape(&Fn);
    PC->execresetConnectionPing(*S, R);
}

void Driver_121f30(APlayerController *PC, FFrame *S, void *R, FString *Str, const TCHAR *T)
{
    Escape(&GMalloc);
    Escape(&GGlobalContext);
    Escape(&GTravelNotifyObject);
    Escape(&GTravelLauncher);
    Escape((void *)(*Str != T));
    Escape(new FTravelLauncher(PC->Player, *Str, 1, TRAVEL_Absolute, PC->XLevel->Engine, 1));
    void (APlayerController::*Fn)(FFrame &, void *const) = &APlayerController::execClientTravel;
    Escape(&Fn);
    PC->execClientTravel(*S, R);
}

void Driver_122210(APlayerController *PC, FFrame *S, void *R, FString *Str, const TCHAR *T)
{
    Escape(&GMalloc);
    *Str = T;
    void (APlayerController::*Fn)(FFrame &, void *const) = &APlayerController::execGetPlayerNetworkAddress;
    Escape(&Fn);
    PC->execGetPlayerNetworkAddress(*S, R);
}
