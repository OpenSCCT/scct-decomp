/* Work item 0212: UGameEngine virtuals (RVA 0xe8380-0xe86ca).
   Reflected vtable UGameEngine@3041e8 slots 25 (0xe8380), 9 (0xe83f0),
   41 (0xe8450), 26 (0xe8580). Field names follow UE2 UGameEngine where the
   offsets agree (GLevel 0x130, GPendingLevel 0x138, LastURL 0x13c); the
   subsystem pointers at 0x34-0x40 are named neutrally. */
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FUnknown
{
public:
    virtual DWORD QueryInterface(const void *RIID, void **Interface);
    virtual DWORD AddRef();
    virtual DWORD Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();
    virtual void ProcessEvent(class UFunction *Function, void *Parms, void *Result = 0);
    /* Slots 5-37 not recovered. */
    virtual void Virtual05();
    virtual void Virtual06();
    virtual void Virtual07();
    virtual void Virtual08();
    virtual void Destroy(); /* slot 9 */
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Exit(); /* slot 25 */
    virtual void UnnamedVirtual26(); /* slot 26, name not recovered */
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    char UObjectPad[0x28];
};

class UnnamedObject_ec;
/* Object at UGameEngine 0x130 (GLevel); its field 0xec is an owned object. */
class ULevel : public UObject
{
public:
    char LevelPad[0xec - 0x2c];
    UnnamedObject_ec *OwnedEC;
};

/* Unnamed global object freed in Destroy (0x10c8bbf0). Its destructor is
   FUN_10a84b30 (outside this item): it stores the vtable and destroys the
   member at 0xc; the LTCG build passes this in EAX. */
struct FUnnamedMember_a85390
{
    ~FUnnamedMember_a85390();
};
class FUnnamedGlobal_c8bbf0
{
public:
    virtual void Virtual00();
    __declspec(noinline) ~FUnnamedGlobal_c8bbf0();
    void operator delete(void *P) { GMalloc->Free(P); }
    INT Field04, Field08;
    FUnnamedMember_a85390 Member0C;
};
extern FUnnamedGlobal_c8bbf0 *GUnnamedGlobal_c8bbf0;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }

class FString
{
public:
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const TCHAR *In);
    FString &operator=(const FString &Other);
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
    UBOOL operator!=(const TCHAR *Other) const { return appStricmp(**this, Other) != 0; }
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
};

enum ETravelType { TRAVEL_Absolute, TRAVEL_Partial, TRAVEL_Relative };

/* 0x44 bytes; the constructor is FUN_10a33560 (outside this item). */
class FURL
{
public:
    FURL();
    FURL(const FURL &Other);
    __declspec(noinline) FURL(FURL *Base, const TCHAR *TextURL, ETravelType Type);
    ~FURL();
    FString Protocol;   /* 0x00 */
    FString Host;       /* 0x0c */
    INT Port;           /* 0x18 */
    FString Map;        /* 0x1c */
    FString Op;         /* 0x28, TArray<FString> in UE2 */
    FString Portal;     /* 0x34 */
    INT Valid;          /* 0x40 */
};

/* Objects reached through GLevel/GPendingLevel 0xec -> 0x38 -> 0xef0;
   neutral names. */
class UnnamedObject_ef0 : public UObject { };
class UnnamedObject_38 : public UObject
{
public:
    char Pad30[0xef0 - 0x2c];
    UnnamedObject_ef0 *ObjectEF0;
};
class UnnamedObject_ec : public UObject
{
public:
    char Pad30[0x38 - 0x2c];
    UnnamedObject_38 *Object38;
};

typedef unsigned char BYTE;
enum EName { NAME_UnnamedEvent_b19 = 0xb19, NAME_UnnamedEvent_f86 = 0xf86, NAME_UnnamedEvent_f87 = 0xf87 };
struct FName
{
    FName(EName N) : Index(N) {}
    INT Index;
};
struct FColor
{
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA) : B(InB), G(InG), R(InR), A(InA) {}
    BYTE B, G, R, A;
};
class UFunction;

/* Actor->0x52c (HUD in UE2 terms); event thunk at 0xee0a0. */
class UnnamedHUD : public UObject
{
public:
    UFunction *FindFunctionChecked(FName Name, INT Global = 0);
    __declspec(noinline) void eventUnnamed_b19()
    {
        ProcessEvent(FindFunctionChecked(NAME_UnnamedEvent_b19), 0);
    }
};

/* Viewport->Actor (player controller); event thunk at 0xee010. */
class UnnamedPlayerController : public UObject
{
public:
    UFunction *FindFunctionChecked(FName Name, INT Global = 0);
    __declspec(noinline) void eventUnnamed_f86(INT Index, const FString &Text, FColor Color)
    {
        struct { INT Index; FString Text; FColor Color; } Parms;
        Parms.Index = Index;
        Parms.Text = Text;
        Parms.Color = Color;
        ProcessEvent(FindFunctionChecked(NAME_UnnamedEvent_f86), &Parms);
    }
    void eventUnnamed_f87(FLOAT Duration)
    {
        struct { FLOAT Duration; } Parms;
        Parms.Duration = Duration;
        ProcessEvent(FindFunctionChecked(NAME_UnnamedEvent_f87), &Parms);
    }
    char Pad2C[0x52c - 0x2c];
    UnnamedHUD *HUD52C;
};

class UViewport : public UObject
{
public:
    INT Unknown2C;
    UnnamedPlayerController *Actor; /* 0x30 */
};
class UClient : public UObject
{
public:
    UViewport **ViewportsData; /* TArray<UViewport*> Viewports at 0x2c */
    INT ViewportsNum;
};
class UEngine : public UObject
{
public:
    virtual void SetClientTravel(UViewport *Viewport, const TCHAR *NextURL, UBOOL bItems, INT TravelType); /* slot 38 */
    /* Slots 39-47 not recovered. */
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void UnnamedVirtual41(const TCHAR *First, const TCHAR *Second, FLOAT Duration); /* slot 41, name not recovered */
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual UBOOL Browse(FURL URL, const void *TravelInfo, FString &Error); /* slot 48 */
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void CancelPending(); /* slot 51 */
    virtual void Destroy();
    INT UnknownEngine2C;    /* 0x2c */
};

class UGameEngine : public UEngine
{
public:
    virtual void Exit();
    virtual void Destroy();
    virtual void UnnamedVirtual26();
    virtual void UnnamedVirtual41(const TCHAR *First, const TCHAR *Second, FLOAT Duration);

    UClient *Client;        /* 0x30 */
    UObject *Subsystem34;   /* 0x34 */
    UObject *Subsystem38;   /* 0x38 */
    UObject *Subsystem3C;   /* 0x3c */
    UObject *Subsystem40;   /* 0x40 */
    char Pad44[0x130 - 0x44];
    ULevel *GLevel;         /* 0x130 */
    ULevel *GEntry;         /* 0x134 */
    ULevel *GPendingLevel;  /* 0x138 */
    FURL LastURL;           /* 0x13c */
};

/* 0xe8380, vtable slot 25. */
void UGameEngine::Exit()
{
    if (Subsystem34) { delete Subsystem34; Subsystem34 = 0; }
    if (GLevel->OwnedEC) { delete GLevel->OwnedEC; GLevel->OwnedEC = 0; }
    if (Subsystem38) { delete Subsystem38; Subsystem38 = 0; }
    if (Subsystem40) { delete Subsystem40; Subsystem40 = 0; }
    if (Subsystem3C) { delete Subsystem3C; Subsystem3C = 0; }
}

/* 0xe83f0, vtable slot 9. */
void UGameEngine::Destroy()
{
    if (GUnnamedGlobal_c8bbf0)
    {
        delete GUnnamedGlobal_c8bbf0;
        GUnnamedGlobal_c8bbf0 = 0;
    }
    if (GPendingLevel)
        CancelPending();
    GLevel = 0;
    UEngine::Destroy();
}

/* 0xe8450, vtable slot 41. */
void UGameEngine::UnnamedVirtual41(const TCHAR *First, const TCHAR *Second, FLOAT Duration)
{
    if (Client && Client->ViewportsNum)
    {
        UnnamedPlayerController *Actor = Client->ViewportsData[0]->Actor;
        if (Duration == -1.f && Actor->HUD52C)
            Actor->HUD52C->eventUnnamed_b19();
        {
            FString Text(First);
            Actor->eventUnnamed_f86(0, Text, FColor(255, 255, 255, 255));
        }
        {
            FString Text(Second);
            Actor->eventUnnamed_f86(1, Text, FColor(255, 255, 255, 255));
        }
        Actor->eventUnnamed_f87(Duration);
    }
}

/* Literals in writable .data (retail keeps a second copy of each). */
extern const TCHAR FailedURL_c49638[];   /* L"?failed" */
extern const TCHAR EmptyString_c92494[]; /* L"" */

/* 0xe8580, vtable slot 26. */
void UGameEngine::UnnamedVirtual26()
{
    FString Error;
    if (Client && Client->ViewportsNum)
    {
        if (GLevel && GLevel->OwnedEC && GLevel->OwnedEC->Object38 && GLevel->OwnedEC->Object38->ObjectEF0)
        {
            GLevel->OwnedEC->Object38->ObjectEF0->Virtual24();
            GLevel->OwnedEC->Object38->Virtual28();
        }
        if (GPendingLevel && GPendingLevel->OwnedEC && GPendingLevel->OwnedEC->Object38 && GPendingLevel->OwnedEC->Object38->ObjectEF0)
        {
            GPendingLevel->OwnedEC->Object38->ObjectEF0->Virtual24();
            GPendingLevel->OwnedEC->Object38->Virtual28();
        }
        SetClientTravel(Client->ViewportsData[0], L"?failed", 0, TRAVEL_Absolute);
    }
    else
    {
        if (!Browse(FURL(&LastURL, FailedURL_c49638, TRAVEL_Absolute), 0, Error) && Error != EmptyString_c92494)
        {
        }
    }
}

/* Constructor at 0xa33560, outside this item; defined so the LTCG link
   sees it. Stand-in body. */
extern const TCHAR *URLDefaultProtocol, *URLDefaultHost, *URLDefaultMap, *URLDefaultPortal;
extern INT URLDefaultPort;
void UnnamedParseURL_a33560(FURL *URL, FURL *Base, const TCHAR *TextURL, INT Type, TCHAR *Buffer);
FURL::FURL(FURL *Base, const TCHAR *TextURL, ETravelType Type)
:   Protocol(URLDefaultProtocol), Host(URLDefaultHost), Port(URLDefaultPort),
    Map(URLDefaultMap), Portal(URLDefaultPortal), Valid(1)
{
    TCHAR Buffer[1024];
    UnnamedParseURL_a33560(this, Base, TextURL, Type, Buffer);
}

/* Destructor at 0xa84b30, outside this item; defined so the LTCG link
   gives it retail's convention. */
FUnnamedGlobal_c8bbf0::~FUnnamedGlobal_c8bbf0()
{
}

/* Scaffolding for the link, not part of the unit: constructing an engine
   emits the vtable, which keeps the virtuals out of line. */
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_e83f0(void *Mem) { Escape(&GMalloc); Escape(&GUnnamedGlobal_c8bbf0); Escape(new (Mem) UGameEngine); }
