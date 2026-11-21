// Work item 0211: Versus RVA 0xe7b00, UGameEngine::Init (UE2 UnGame.cpp).
// Compiled with VC7.0 /GL + /LTCG (/O2 /Gy /GX).
// Stand-in bodies for /GL callees give the linker the same custom calling
// conventions as retail; their call targets bind to retail addresses.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

enum { INDEX_NONE = -1 };

enum EName
{
    NAME_None = 0,
    NAME_Engine = 0x15,
    NAME_Console = 0x18,
    NAME_Unknown_B8 = 0xb8,
    NAME_Unknown_B9 = 0xb9,
    NAME_Unknown_BF = 0xbf,
    NAME_Unknown_C0 = 0xc0,
    NAME_Unknown_C1 = 0xc1,
    NAME_Unknown_C6 = 0xc6,
    NAME_Unknown_C8 = 0xc8,
    NAME_Unknown_CA = 0xca,
    NAME_Unknown_CF = 0xcf,
    NAME_Unknown_E7 = 0xe7,
    NAME_Unknown_252 = 0x252,
    NAME_Unknown_469 = 0x469,
    NAME_Unknown_7D2 = 0x7d2,
    NAME_Unknown_7ED = 0x7ed,
    NAME_Unknown_C84 = 0xc84,
    NAME_Initialized = 0x13d8,
    NAME_AddInteraction = 0x13f4,
    NAME_Unknown_CC052 = 0xcc052,
};

enum ETravelType
{
    TRAVEL_Absolute = 0,
    TRAVEL_Partial = 1,
    TRAVEL_Relative = 2,
};

enum ENetRole
{
    ROLE_None = 0,
    ROLE_DumbProxy = 1,
    ROLE_SimulatedProxy = 2,
    ROLE_AutonomousProxy = 3,
    ROLE_Authority = 4,
};

enum EDetailMode
{
    DM_Low = 0,
    DM_High = 1,
    DM_SuperHigh = 2,
};

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const TCHAR *A, const TCHAR *B, unsigned int Count);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *S);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *Dest, const TCHAR *Src);

inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }
inline INT appStrncmp(const TCHAR *A, const TCHAR *B, INT Count) { return wcsncmp(A, B, Count); }
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline TCHAR *appStrcpy(TCHAR *Dest, const TCHAR *Src) { return wcscpy(Dest, Src); }

template<class T> inline void Exchange(T &A, T &B)
{
    T Temp = A;
    A = B;
    B = Temp;
}

class FName
{
public:
    FName() {}
    FName(EName N) : Index(N) {}
    INT Index;
};

extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);
extern const TCHAR Text_FStringEq[];

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const FString &Other);           // RVA 0x4640
    FString(const TCHAR *In);                // RVA 0x46c0
    FString(const ANSICHAR *In);             // RVA 0xee0c0
    ~FString();                              // RVA 0x48b0
    FString &operator=(const TCHAR *Other);  // RVA 0x4750
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern const TCHAR Text_FArray[];

inline void *operator new(unsigned int, void *Mem) { return Mem; }
inline void operator delete(void *, void *) {}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = ArrayNum ? GMalloc->Malloc(ArrayNum * ElementSize, Text_FArray) : 0;
    }
    ~FArray();
    INT Add(INT Count, INT ElementSize);
};

class TArray_FString : public FArray
{
public:
    TArray_FString() : FArray() {}
    TArray_FString(const TArray_FString &Other);
    ~TArray_FString();
};

// Stand-in for TArray<FString>::TArray(const TArray<FString>&) (RVA 0xc550: Other in EDI, this on stack).
#pragma auto_inline(off)
__declspec(noinline) TArray_FString::TArray_FString(const TArray_FString &Other)
    : FArray(Other.ArrayNum, sizeof(FString))
{
    ArrayNum = 0;
    for (INT i = 0; i < Other.ArrayNum; i++)
    {
        INT Idx = Add(1, sizeof(FString));
        FString *Slot = &((FString *)Data)[Idx];
        if (Slot)
            new (Slot) FString(((FString *)Other.Data)[i]);
    }
}
#pragma auto_inline(on)

class FURL
{
public:
    FString Protocol;         // 0x00
    FString Host;             // 0x0c
    INT Port;                 // 0x18
    FString Map;              // 0x1c
    TArray_FString Op;        // 0x28
    FString Portal;           // 0x34
    INT Valid;                // 0x40

    static FString DefaultProtocol;
    static FString DefaultHost;
    static FString DefaultMap;
    static FString DefaultLocalMap;
    static FString DefaultPortal;
    static INT DefaultPort;

    FURL(const TCHAR *Filename = 0);
    FURL(FURL *Base, const TCHAR *TextURL, ETravelType Type);
    FURL(const FURL &Other);
    ~FURL();
};

// Stand-in for FURL::FURL(const TCHAR*) (RVA 0x133490: this on stack, Filename in EDI).
#pragma auto_inline(off)
FURL::FURL(const TCHAR *Filename)
    : Protocol(DefaultProtocol)
    , Host(DefaultHost)
    , Port(DefaultPort)
    , Map(Filename ? FString(Filename) : DefaultMap)
    , Portal(DefaultPortal)
    , Valid(1)
{
}

// Stand-in for FURL::FURL(FURL*, const TCHAR*, ETravelType) (RVA 0x133560: all 4 args on stack, ret 0x10).
FURL::FURL(FURL *Base, const TCHAR *TextURL, ETravelType Type)
    : Protocol(DefaultProtocol)
    , Host(DefaultHost)
    , Port(DefaultPort)
    , Map(DefaultMap)
    , Portal(DefaultPortal)
    , Valid(1)
{
    if (Base && TextURL && Type == TRAVEL_Partial)
        Port = Base->Port;
}

// Stand-in for FURL::FURL(const FURL&) (RVA 0xca9b0: this on stack, Other in EBX).
FURL::FURL(const FURL &Other)
    : Protocol(Other.Protocol)
    , Host(Other.Host)
    , Port(Other.Port)
    , Map(Other.Map)
    , Op(Other.Op)
    , Portal(Other.Portal)
    , Valid(Other.Valid)
{
}

// Stand-in for FURL::~FURL() (RVA 0xa7d70: this on stack, ret 4).
FURL::~FURL()
{
}
#pragma auto_inline(on)

class FOutputDevice;
class UClass;
class UFunction;

class UObject
{
public:
    virtual void VirtualSlot00();
    virtual void VirtualSlot04();
    virtual void VirtualSlot08();
    virtual ~UObject();                      // 0x0c
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // 0x10

    INT Index;                               // 0x04
    DWORD Pad08[7];
    UClass *Class;                           // 0x24

    UFunction *FindFunction(FName InName, UBOOL Global = 0); // RVA 0x16830
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject
{
public:
    UClass *SuperField;                      // 0x28
    BYTE Pad2C[0xd8];
    void (*ClassConstructor)(void *);        // 0x104
    UClass *GetSuperClass() const { return SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

class UConsole : public UObject
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    void eventInitialized()
    {
        ProcessEvent(FindFunction(NAME_Initialized, 0), 0, 0);
    }
};

// Stand-in for Cast<UConsole> (RVA 0xedc80: Src in EAX).
#pragma auto_inline(off)
template<class T> __declspec(noinline) T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}
#pragma auto_inline(on)

class UPlayer;
class UViewport;
class UClient;
class UEngine;
class UGameEngine;
class ULevel;

class UInteraction : public UObject
{
public:
    DWORD bActive : 1;                       // 0x28 bit 0
    DWORD bVisible : 1;                      // 0x28 bit 1
    DWORD bRequiresTick : 1;                 // 0x28 bit 2
    DWORD bNativeEvents : 1;                 // 0x28 bit 3
    UViewport *ViewportOwner;                // 0x2c
    DWORD Field30;                           // 0x30
    DWORD Bit34_0 : 1;                       // 0x34 bit 0
    DWORD Bit34_1 : 1;                       // 0x34 bit 1
};

class UInteractionMaster : public UObject
{
public:
    UClient *Client;                         // 0x28
    DWORD Field2C;                           // 0x2c
    UInteraction *BaseConsole;               // 0x30
    UInteraction **GlobalInteractionsData;   // 0x34 (TArray<UInteraction*>.Data)

    UInteraction *eventAddInteraction(FName PackageName, FName InteractionName, UPlayer *AttachTo);
};

// Stand-in for UInteractionMaster::eventAddInteraction (RVA 0xee1c0: this in ESI, AttachTo in EDX).
#pragma auto_inline(off)
UInteraction *UInteractionMaster::eventAddInteraction(FName PackageName, FName InteractionName, UPlayer *AttachTo)
{
    struct UInteractionMaster_eventAddInteraction_Parms
    {
        FName PackageName;
        FName InteractionName;
        UPlayer *AttachTo;
        UInteraction *ReturnValue;
    } Parms;
    Parms.PackageName = PackageName;
    Parms.InteractionName = InteractionName;
    Parms.AttachTo = AttachTo;
    Parms.ReturnValue = 0;
    ProcessEvent(FindFunction(NAME_AddInteraction, 0), &Parms, 0);
    return Parms.ReturnValue;
}
#pragma auto_inline(on)

class UInput : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual void Init(UViewport *Viewport);  // 0x5c
};

class URenderDevice : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual UBOOL Init();                    // 0x5c

    BYTE Pad28[0x1c];
    UBOOL HighDetailActors;                  // 0x44
    UBOOL SuperHighDetailActors;             // 0x48
};

class UViewport : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual void Slot5C();
    virtual void Slot60();
    virtual void Slot64();
    virtual void Slot68();
    virtual void Slot6C();
    virtual void Slot70();
    virtual void Slot74();
    virtual void Slot78();
    virtual void Slot7C();
    virtual void Slot80();
    virtual void Slot84();
    virtual void Slot88();
    virtual void Slot8C();
    virtual void Slot90();
    virtual void Slot94();
    virtual void Slot98();
    virtual void Slot9C();
    virtual void SlotA0();
    virtual void SlotA4();
    virtual void OpenWindow(DWORD ParentWindow, UBOOL Temporary, INT NewX, INT NewY, INT OpenX, INT OpenY); // 0xa8

    BYTE Pad28[0x0c];
    UInteraction *Field34;                   // 0x34
    BYTE Pad38[0x2c];
    UConsole *Console;                       // 0x64
    DWORD Field68;                           // 0x68
    UInput *Input;                           // 0x6c
    URenderDevice *RenDev;                   // 0x70
};

class UClient : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Init(UEngine *InEngine);    // 0x58
    virtual void Slot5C();
    virtual void Slot60();
    virtual void Slot64();
    virtual void Slot68();
    virtual void Slot6C();
    virtual void Slot70();
    virtual void Slot74();
    virtual UViewport *NewViewport(FName Name); // 0x78

    BYTE Pad28[0x7c];
    UInteractionMaster *InteractionMaster;   // 0xa4
};

class UAudioSubsystem : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual UBOOL Init();                    // 0x5c
    virtual void SetViewport(UViewport *Viewport); // 0x60
    virtual void Slot64();
    virtual void Slot68();
    virtual void Slot6C();
    virtual void Slot70();
    virtual void Slot74();
    virtual void Slot78();
    virtual void Virtual7C(DWORD Param, INT Zero); // 0x7c
    virtual void Slot80();
    virtual void Slot84();
    virtual void Slot88();
    virtual void Slot8C();
    virtual void Slot90();
    virtual void Slot94();
    virtual void Slot98();
    virtual void Slot9C();
    virtual void SlotA0();
    virtual void SlotA4();
    virtual void SlotA8();
    virtual void SlotAC();
    virtual void SlotB0();
    virtual void SlotB4();
    virtual void SlotB8();
    virtual void SlotBC();
    virtual void SlotC0();
    virtual void SlotC4();
    virtual void SlotC8();
    virtual void SlotCC();
    virtual void SlotD0();
    virtual void SlotD4();
    virtual void SlotD8();
    virtual void SlotDC();
    virtual void SlotE0();
    virtual void SlotE4();
    virtual void SlotE8();
    virtual void SlotEC();
    virtual void SlotF0();
    virtual void SlotF4();
    virtual void SlotF8();
    virtual void SlotFC();
    virtual void Virtual100(FString Name);   // 0x100
};

class UObject3C : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual void Init(UEngine *InEngine);    // 0x5c
};

class UObject40 : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual void Slot5C();
    virtual void Slot60();
    virtual void Slot64();
    virtual void Slot68();
    virtual void Init(UEngine *InEngine);    // 0x6c
};

class UObject44 : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual void LoadMenu(const FString &Filename); // 0x5c
};

class ALevelInfo : public UObject
{
public:
    BYTE Pad28[0x410];
    BYTE DetailMode;                         // 0x438
    BYTE Pad439[0x3f];
    DWORD Field478;                          // 0x478
    BYTE Pad47C[0x60];
    UObject *Field4DC;                       // 0x4dc
};

class AActor : public UObject
{
public:
    BYTE Pad28[0x2b7];
    BYTE Field2DF;                           // 0x2df
};

class ULevel : public UObject
{
public:
    DWORD Pad28;
    AActor **ActorsData;                     // 0x2c
    INT ActorsNum;                           // 0x30

    ALevelInfo *GetLevelInfo() { return (ALevelInfo *)ActorsData[0]; }
    AActor *SpawnPlayActor(UViewport *Player, ENetRole RemoteRole, const FURL &URL, FString &Error);
    void SetDetailMode(BYTE Mode);
};

extern "C" __declspec(dllimport) TCHAR *__cdecl wcscat(TCHAR *Dest, const TCHAR *Src);

// Stand-in for FString::operator=(const TCHAR*) (RVA 0x4750: this in ESI, Other in EDI).
#pragma auto_inline(off)
__declspec(noinline) FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data)
    {
        if (*Other == 0)
        {
            if (Data)
            {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
        }
        else
        {
            if (Data == 0)
            {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), Text_FStringEq);
            }
            else
            {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), Text_FArray);
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}
#pragma auto_inline(on)

// Stand-in for ULevel::SpawnPlayActor (RVA 0x11ac30: URL in ECX, rest on stack, ret 0x10).
extern AActor *SpawnPlayActorHelper(TCHAR *Options, ULevel *Level, UViewport *Player, ENetRole Role, FString &Error, FString &Temp);
extern void SpawnPlayActorPost(AActor *Actor, ULevel *Level, UViewport *Player, ENetRole Role, FString &Error);
#pragma auto_inline(off)
__declspec(noinline) AActor *ULevel::SpawnPlayActor(UViewport *Player, ENetRole RemoteRole, const FURL &URL, FString &Error)
{
    Error = L"";
    FString Temp;
    TCHAR Options[1024] = { 0 };
    for (INT i = 0; i < URL.Op.ArrayNum; i++)
    {
        wcscat(Options, L"?");
        wcscat(Options, *((FString *)URL.Op.Data)[i]);
    }
    AActor *Result = SpawnPlayActorHelper(Options, this, Player, RemoteRole, Error, Temp);
    for (INT j = 0; j < ActorsNum; j++)
    {
        if (ActorsData[j])
            SpawnPlayActorPost(ActorsData[j], this, Player, RemoteRole, Error);
    }
    return Result;
}

// Stand-in for ULevel::SetDetailMode (RVA 0xf5660: this in ESI, Mode on stack, ret 4).
extern void FlushDetailHelper(void *Global);
extern void *GDetailGlobal;
void ULevel::SetDetailMode(BYTE Mode)
{
    FlushDetailHelper(GDetailGlobal);
    GetLevelInfo()->DetailMode = Mode;
    if (GetLevelInfo()->Field4DC)
        GetLevelInfo()->Field4DC->ProcessEvent(GetLevelInfo()->Field4DC->FindFunction(NAME_Unknown_C84, 0), 0, 0);
    for (INT i = 0; i < ActorsNum; i++)
        if (ActorsData[i])
            ActorsData[i]->Field2DF = 0;
}
#pragma auto_inline(on)

struct FManager
{
    BYTE Pad00[0x34];
    UGameEngine *Engine;                     // 0x34
    UViewport *Viewport;                     // 0x38
};

extern FManager *GManager;                   // 0x10c75e94
extern UBOOL GIsClient;                      // 0x10c968f8
extern UObject *GTransientPackage;           // 0x10c925b4
extern FOutputDevice *GError;                // 0x10c71aa8
extern UGameEngine *GEngine;                 // 0x10c923c4
extern UInteraction *GGUIController;         // 0x10c923c8
extern UBOOL GIsRunning;                     // 0x10c925f8
extern UViewport *GViewport;                 // 0x10c92250
extern TCHAR GCmdLine[];                     // 0x10c92680

extern UClass UClass_PrivateStaticClass;
extern UClass UClient_PrivateStaticClass;    // 0x10cbec78
extern UClass URenderDevice_PrivateStaticClass; // 0x10cc4e48
extern UClass UObject40_PrivateStaticClass;  // 0x10cbca88
extern UClass UObject44_PrivateStaticClass;  // 0x10cbcba0
extern UClass UObject3C_PrivateStaticClass;  // 0x10cbe5e8
extern UClass UInteractionMaster_PrivateStaticClass; // 0x10cbc298
extern UClass UAudioSubsystem_PrivateStaticClass;

extern const TCHAR Text_Entry[];             // 0x10c495d0 L"Entry"
extern const TCHAR Text_SERVER[];            // 0x10c495dc L"SERVER"
extern const TCHAR Text_PLATFORM1[];         // 0x10c495ec L"PLATFORM="
extern const TCHAR Text_PLATFORM2[];         // 0x10c49600 L"PLATFORM="
extern const TCHAR Text_EmptyInit[];         // 0x10c9248c L""
extern const TCHAR Text_EmptyCmp[];          // 0x10c92490 L""
extern const TCHAR Text_nosound[];
extern const ANSICHAR Text_OptionsMgm[];     // 0x10c49614 "Options.mgm"
extern const ANSICHAR Text_HudMgm[];         // 0x10c49620 "hud.mgm"

extern void InitGlobal1();                   // 0x1090e080
extern FManager *CreateManager();            // 0x10a4a800
extern "C" void __cdecl SetManager(FManager *M); // 0x10b9ef60
extern void InitInteractionPre();            // 0x109fcbd0
extern const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

// Retail 0x1afe0.
UObject *StaticLoadObject(UClass *ObjectClass, UObject *InOuter, FName Name1, FName Name2,
                          FName Name3, void *Extra1, DWORD LoadFlags, void *Extra2);

// Stand-in for StaticLoadClass (RVA 0x1b390: Extra1 in EDX, Extra2 in ECX).
#pragma auto_inline(off)
UClass *StaticLoadClass(UClass *BaseClass, UObject *InOuter, FName Name1, FName Name2,
                        FName Name3, DWORD LoadFlags, void *Extra1, void *Extra2)
{
    try
    {
        return (UClass *)StaticLoadObject(&UClass_PrivateStaticClass, InOuter, Name1, Name2, Name3, Extra1, LoadFlags | 8, Extra2);
    }
    catch (...)
    {
        return 0;
    }
}

// Stand-in for ParseParam (RVA 0x121c0).
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

// Stand-in for ParseToken (RVA 0x126c0: Str in EAX, Result in EBX, MaxLen & UseEscape on stack).
UBOOL ParseToken(const TCHAR *&Str, TCHAR *Result, INT MaxLen, UBOOL UseEscape)
{
    INT Len = 0;
    while (*Str == ' ' || *Str == '\t')
        Str++;
    if (*Str == '\"')
    {
        Str++;
        while (*Str && *Str != '\"' && Len + 1 < MaxLen)
        {
            TCHAR c = *Str++;
            if (c == '\\' && UseEscape)
            {
                c = *Str++;
                if (!c) break;
            }
            Result[Len++] = c;
        }
        if (*Str == '\"')
            Str++;
    }
    else
    {
        while (*Str && *Str != ' ' && *Str != '\t' && Len + 1 < MaxLen)
            Result[Len++] = *Str++;
    }
    Result[Len] = 0;
    return Len != 0;
}

// Stand-in for SetGViewport (RVA 0x1708c0: Viewport in EAX).
void SetGViewport(UViewport *V)
{
    GViewport = V;
}
#pragma auto_inline(on)

// Retail 0x1d380.
UObject *StaticConstructObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                               UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot,
                               UObject *InstanceGraph);

template<class T> inline T *ConstructObject(UClass *Class, UObject *Outer, FName Name = NAME_None, DWORD SetFlags = 0)
{
    T *Result = (T *)StaticConstructObject(Class, Outer, Name, SetFlags, 0, GError, 0, 0);
    if (Result)
        Class->ClassConstructor(Result);
    return Result;
}

inline const TCHAR *appCmdLine() { return GCmdLine; }

class UEngine : public UObject
{
public:
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1C();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2C();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3C();
    virtual void Slot40();
    virtual void Slot44();
    virtual void Slot48();
    virtual void Slot4C();
    virtual void Slot50();
    virtual void Slot54();
    virtual void Slot58();
    virtual void Init();                     // 0x5c (slot 23)
    virtual void Slot60();
    virtual void Slot64();
    virtual void Slot68();
    virtual void Slot6C();
    virtual void Slot70();
    virtual void Slot74();
    virtual void Slot78();
    virtual void Slot7C();
    virtual void Slot80();
    virtual void Slot84();
    virtual void Slot88();
    virtual void Slot8C();
    virtual void Slot90();
    virtual void Slot94();
    virtual void Slot98();
    virtual void Slot9C();
    virtual void SlotA0();
    virtual void SlotA4();
    virtual void SlotA8();
    virtual void SlotAC();
    virtual void SlotB0();
    virtual void SlotB4();
    virtual void SlotB8();
    virtual void SlotBC();
    virtual UBOOL Browse(FURL URL, void *Extra, FString &Error); // 0xc0
    virtual ULevel *LoadMap(const FURL &URL, void *Pending, void *TravelInfo, FString &Error, INT InFlag); // 0xc4

    BYTE Pad28[0x08];
    UClient *Client;                         // 0x30
    UAudioSubsystem *Audio;                  // 0x34
    URenderDevice *GRenDev;                  // 0x38
    UObject3C *Field3C;                      // 0x3c
    UObject40 *Field40;                      // 0x40
    UObject44 *Field44;                      // 0x44
    BYTE Pad48[0x5c];
    DWORD UseSound : 1;                      // 0xa4

    void InitAudio();
};

// Stand-in for UEngine::InitAudio (RVA 0x96830: this in EBX).
#pragma auto_inline(off)
void UEngine::InitAudio()
{
    if (UseSound && GIsClient && !ParseParam(appCmdLine(), Text_nosound))
    {
        UClass *AudioClass = StaticLoadClass(&UAudioSubsystem_PrivateStaticClass, 0, NAME_Unknown_C0, NAME_None, NAME_Unknown_CF, 1, 0, 0);
        Audio = ConstructObject<UAudioSubsystem>(AudioClass, GTransientPackage);
        if (!Audio->Init())
        {
            delete Audio;
            Audio = 0;
        }
    }
}
#pragma auto_inline(on)

class UGameEngine : public UEngine
{
public:
    BYTE PadA8[0x88];
    ULevel *GLevel;                          // 0x130
    ULevel *GEntry;                          // 0x134
    BYTE Pad138[0x20];
    FString Field158;                        // 0x158

    virtual void Init();
};

// Retail RVA 0xe7b00: UGameEngine::Init()
void UGameEngine::Init()
{
    UEngine::Init();

    GLevel = 0;
    InitGlobal1();
    SetManager(CreateManager());
    GManager->Engine = this;

    if (GIsClient)
    {
        UClass *ClientClass = StaticLoadClass(&UClient_PrivateStaticClass, 0, NAME_Unknown_C1, NAME_None, NAME_Unknown_C6, 1, 0, 0);
        Client = ConstructObject<UClient>(ClientClass, GTransientPackage);
        Client->Init(this);

        UClass *RenDevClass = StaticLoadClass(&URenderDevice_PrivateStaticClass, 0, NAME_Unknown_BF, NAME_None, NAME_Unknown_C8, 1, 0, 0);
        GRenDev = ConstructObject<URenderDevice>(RenDevClass, GTransientPackage);
        GRenDev->Init();
    }

    UClass *Class40 = StaticLoadClass(&UObject40_PrivateStaticClass, 0, NAME_Unknown_B8, NAME_None, NAME_Unknown_B9, 1, 0, 0);
    Field40 = ConstructObject<UObject40>(Class40, GTransientPackage);
    Field40->Init(this);

    UClass *Class44 = StaticLoadClass(&UObject44_PrivateStaticClass, 0, NAME_Unknown_7D2, NAME_None, NAME_Unknown_7ED, 0x40, 0, 0);
    Field44 = ConstructObject<UObject44>(Class44, GTransientPackage);

    GEngine = this;

    UClass *Class3C = StaticLoadClass(&UObject3C_PrivateStaticClass, 0, NAME_Unknown_C1, NAME_None, NAME_Unknown_CA, 0, 0, 0);
    if (Class3C)
    {
        Field3C = ConstructObject<UObject3C>(Class3C, GTransientPackage);
        Field3C->Init(this);
    }
    else
    {
        Field3C = 0;
    }

    FString Error;
    if (Client)
    {
        LoadMap(FURL(Text_Entry), 0, 0, Error, 0);
        Exchange(GLevel, GEntry);
    }

    FURL DefaultURL;
    TCHAR Temp[4096] = { Text_EmptyInit[0] };
    const TCHAR *Stream = appCmdLine();
    if (!ParseToken(Stream, Temp, 4096, 0)
        || (appStricmp(Temp, Text_SERVER) == 0 && !ParseToken(Stream, Temp, 4096, 0))
        || (appStrncmp(Temp, Text_PLATFORM1, appStrlen(Text_PLATFORM2)) == 0 && !ParseToken(Stream, Temp, 4096, 0))
        || Temp[0] == '-')
    {
        appStrcpy(Temp, *FURL::DefaultLocalMap);
    }

    FURL URL(&DefaultURL, Temp, TRAVEL_Partial);
    if (!Browse(URL, 0, Error) && appStricmp(*Error, Text_EmptyCmp) == 0 && appStricmp(Temp, *FURL::DefaultLocalMap) != 0)
    {
        Browse(FURL(&DefaultURL, *FURL::DefaultLocalMap, TRAVEL_Partial), 0, Error);
    }

    if (Client)
    {
        InitInteractionPre();

        UClass *IMClass = StaticLoadClass(&UInteractionMaster_PrivateStaticClass, 0, NAME_Engine, NAME_None, NAME_Unknown_469, 1, 0, 0);
        Client->InteractionMaster = ConstructObject<UInteractionMaster>(IMClass, GTransientPackage);
        Client->InteractionMaster->Client = Client;

        UViewport *Viewport = Client->NewViewport(NAME_None);
        SetGViewport(Viewport);
        GManager->Viewport = Viewport;

        GGUIController = Client->InteractionMaster->eventAddInteraction(NAME_Engine, NAME_Unknown_CC052, 0);
        if (GGUIController)
        {
            { FString MenuName(Text_OptionsMgm); Field44->LoadMenu(MenuName); }
            { FString MenuName(Text_HudMgm); Field44->LoadMenu(MenuName); }
            GGUIController->bNativeEvents = 1;
            GGUIController->bRequiresTick = 1;
            GGUIController->bVisible = 1;
            GGUIController->bActive = 1;
            GGUIController->Bit34_0 = 0;
            GGUIController->Bit34_1 = 0;
        }

        UInteraction *Console = Client->InteractionMaster->eventAddInteraction(NAME_Console, NAME_Unknown_E7, 0);
        if (Console && Console->IsA(UConsole::StaticClass()))
        {
            Cast<UConsole>(Console)->eventInitialized();
            Viewport->Console = Cast<UConsole>(Console);
        }

        UInteraction *BaseConsole = Client->InteractionMaster->eventAddInteraction(NAME_Engine, NAME_Unknown_252, 0);
        if (BaseConsole)
        {
            Client->InteractionMaster->BaseConsole = BaseConsole;
            BaseConsole->ViewportOwner = Viewport;
        }
        Console->ViewportOwner = Viewport;
        Viewport->Field34 = Client->InteractionMaster->GlobalInteractionsData[1];

        FString SpawnError;
        GLevel->SpawnPlayActor(Viewport, ROLE_SimulatedProxy, URL, SpawnError);
        Viewport->Input->Init(Viewport);
        Viewport->OpenWindow(0, 0, INDEX_NONE, INDEX_NONE, 0, 0);

        InitAudio();
        if (Audio)
        {
            Audio->SetViewport(Viewport);
            Audio->Virtual100(*Field158);
            Audio->Virtual7C(GLevel->GetLevelInfo()->Field478, 0);
        }

        GLevel->SetDetailMode(Viewport->RenDev->SuperHighDetailActors ? DM_SuperHigh : Viewport->RenDev->HighDetailActors ? DM_High : DM_Low);
    }

    GIsRunning = 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Consume(void *, void *, void *, void *);
void Driver_e7b00(void *Buf, ULevel *L, UViewport **V, INT Count, const FURL *U, FString *Err)
{
    Escape(&GMalloc);
    Escape(&GManager);
    Escape(&GIsClient);
    Escape(&GTransientPackage);
    Escape(&GError);
    Escape(&GEngine);
    Escape(&GGUIController);
    Escape(&GIsRunning);
    Escape(&GViewport);
    Escape(&FURL::DefaultLocalMap);
    Escape(&FURL::DefaultProtocol);
    Escape(&FURL::DefaultHost);
    Escape(&FURL::DefaultMap);
    Escape(&FURL::DefaultPortal);
    Escape(&FURL::DefaultPort);
    Escape(GCmdLine);
    // Additional retail-like call sites for /GL callees so LTCG picks
    // their retail register conventions (URL in ECX for SpawnPlayActor,
    // Other in EBX for FURL copy ctor).
    for (INT i = 0; i < Count; i++)
    {
        AActor *A = L->SpawnPlayActor(V[i], ROLE_SimulatedProxy, *U, *Err);
        FURL Copy(*U);
        Consume(A, V[i], &Copy, L);
    }
    UGameEngine *E = new (Buf) UGameEngine;
    Escape(E);
}
