// Work item w3 0231 (RVA 0xefbb0-0xefceb): APlayerController::execUpdateURL.
// Engine was built with /GL and linked with /LTCG: FURL::AddOption (0x134440)
// takes `this` in EAX and the option string on the stack.
// Layout evidence: AActor::XLevel at +0x1a4, ULevelBase::Engine at +0xf0,
// UGameEngine::LastURL at +0x13c (UE2 execUpdateURL; the bSaveDefault branch
// is absent in this build).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

#pragma pack(push, 4)

class UObject
{
public:
    virtual ~UObject();
};

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();                                         // 0x48b0
    FString operator+(const TCHAR *Text) const;         // 0x4990
    FString operator+(const FString &Str) const;        // 0xca00
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

struct FFrame;
typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define RESULT_DECL void *const Result
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL(var) UBOOL var = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

struct FURL
{
    BYTE Pad[0x40];
    void AddOption(const TCHAR *Str);
};

class UGameEngine
{
public:
    BYTE Pad[0x13c];
    FURL LastURL;   // +0x13c
};

class ULevel
{
public:
    BYTE Pad[0xf0];
    UGameEngine *Engine;  // +0xf0 (ULevelBase::Engine)
};

class APlayerController : public UObject
{
public:
    BYTE Pad[0x1a4 - 4];
    ULevel *XLevel;      // +0x1a4 (AActor::XLevel)
    void execUpdateURL(FFrame &Stack, RESULT_DECL);
};

extern const TCHAR UpdateURL_Equals[];   // L"="

void APlayerController::execUpdateURL(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(NV);
    P_GET_STR(NewValue);
    P_GET_UBOOL(bSaveDefault);
    P_FINISH;

    ULevel *Level = XLevel;
    UGameEngine *GameEngine = Level->Engine;
    GameEngine->LastURL.AddOption(*(NV + UpdateURL_Equals + NewValue));
}

// FURL::AddOption stays out of line; its real body is large. A stand-in body
// keeps the linker from inlining it.
void Opaque(void *, const TCHAR *);
void FURL::AddOption(const TCHAR *Str)
{
    for (INT i = 0; i < 0x40; i++)
    {
        if (Pad[i] == Str[i])
            Opaque(this, Str + i);
        else
            Opaque(Pad + i, Str);
    }
    Opaque(this + 1, Str);
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_efbb0(APlayerController *P, FFrame *Stack, void *Result)
{
    Escape(GNatives);
    void (APlayerController::*Exec)(FFrame &, void *const) = &APlayerController::execUpdateURL;
    Escape(&Exec);
    (P->*Exec)(*Stack, Result);
    P->XLevel->Engine->LastURL.AddOption((const TCHAR *)Result);
}
