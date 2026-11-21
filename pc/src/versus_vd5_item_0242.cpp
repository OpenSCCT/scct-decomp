// Work item 0242 (wave 3): Versus RVA 0xf1f20-0xf21c8.
// AController::execGotoState and five script event thunks (LTCG, this in ESI).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

class UObject;
class UState;
class UClass;
class UFunction;

enum EName { NAME_None = 0, NAME_Begin = 100, NAME_PROBEMIN = 300, NAME_Auto = 690 };
enum EGotoState { GOTO_Abort = 0, GOTO_Success = 1 };

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[64];
};

class FName
{
public:
    INT Index;
    static FNameEntry **Names;   // FName::Names.Data, 0x10cc9e5c
    FName() {}
    FName(EName N) : Index(N) {}
    FName(const FName &O) : Index(O.Index) {}
    INT GetIndex() const { return Index; }
    const TCHAR *operator*() const { return Names[Index]->Name; }
    UBOOL operator==(const FName &O) const { return Index == O.Index; }
    UBOOL operator!=(const FName &O) const { return Index != O.Index; }
};

struct FFrame
{
    void *VfTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    inline void Step(UObject *Context, void *Result);
};

#pragma pack(push, 4)
struct FStateFrame
{
    BYTE Pad[0x18];
    UState *StateNode;
    QWORD ProbeMask;
};
#pragma pack(pop)

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);   // 0x10
    virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2C();
    virtual EGotoState GotoState(FName State);   // 0x30
    virtual INT GotoLabel(FName Label);          // 0x34

    INT Index;
    void *HashNext;
    FStateFrame *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    FName GetFName() const { return Name; }
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);   // 0x16830
};

class UState : public UObject {};
class UClass : public UState {};

typedef void (UObject::*Native)(FFrame &Stack, void *Result);
extern Native GNatives[];   // 0x10c819d8

inline void FFrame::Step(UObject *Context, void *Result)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

void debugf(const TCHAR *Fmt, ...);   // 0x118d0

#define P_GET_NAME_OPTX(v, def) FName v = def; Stack.Step(Stack.Object, &v);
#define P_GET_UBOOL_OPTX(v, def) UBOOL v = def; Stack.Step(Stack.Object, &v);
#define P_FINISH Stack.Code++;

// Event names: probe names 340..344 and name 0xf29; the real names are not
// recovered, so they are named by index.
#define PROBE_BIT(N) ((QWORD)1 << ((N) - NAME_PROBEMIN))

class AController : public UObject
{
public:
    BYTE Pad[0x2f8 - 0x28];
    FName PreviousStateName;   // 0x2f8 (name not recovered; holds the state left behind)

    void execGotoState(FFrame &Stack, void *Result);
    UBOOL IsProbing(INT N) { return !StateFrame || (StateFrame->ProbeMask & PROBE_BIT(N)); }
    void eventProbe344(INT A);
    void eventProbe340(INT A);
    void eventProbe341();
    void eventProbe342(INT A, INT B);
    void eventEvent_f29(INT A);
};

// RVA 0xf1f20
void AController::execGotoState(FFrame &Stack, void *Result)
{
    FName CurrentStateName = (StateFrame && (UClass *)StateFrame->StateNode != Class) ? StateFrame->StateNode->GetFName() : FName(NAME_None);
    P_GET_NAME_OPTX(S, CurrentStateName);
    P_GET_NAME_OPTX(L, NAME_None);
    P_GET_UBOOL_OPTX(bKeepPrevious, 0);
    P_FINISH;

    EGotoState Result2 = GOTO_Success;
    if (S != CurrentStateName)
        Result2 = GotoState(S);

    if (Result2 == GOTO_Success) {
        if (!bKeepPrevious)
            PreviousStateName = CurrentStateName;
        if (!GotoLabel(L == NAME_None ? FName(NAME_Begin) : L) && L != NAME_None)
            debugf(L"GotoState (%s %s): Label not found", *S, *L);
    } else if (Result2 == GOTO_Abort) {
        if (S != NAME_None && S != NAME_Auto)
            debugf(L"GotoState (%s %s): State not found", *S, *L);
    }
}

#pragma auto_inline(off)
// RVA 0xf2070 (LTCG: this in ESI)
void AController::eventProbe344(INT A)
{
    if (IsProbing(344)) {
        struct { INT A; } Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)344)), &Parms);
    }
}

// RVA 0xf20c0 (LTCG: this in ESI)
void AController::eventProbe340(INT A)
{
    if (IsProbing(340)) {
        struct { INT A; } Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)340)), &Parms);
    }
}

// RVA 0xf2110 (LTCG: this in ESI)
void AController::eventProbe341()
{
    if (IsProbing(341))
        ProcessEvent(FindFunctionChecked(FName((EName)341)), 0);
}

// RVA 0xf2150 (LTCG: this in ESI)
void AController::eventProbe342(INT A, INT B)
{
    if (IsProbing(342)) {
        struct { INT A; INT B; } Parms;
        Parms.A = A;
        Parms.B = B;
        ProcessEvent(FindFunctionChecked(FName((EName)342)), &Parms);
    }
}

// RVA 0xf21a0 (LTCG: this in ESI, A in EAX)
void AController::eventEvent_f29(INT A)
{
    struct { INT A; } Parms;
    Parms.A = A;
    ProcessEvent(FindFunctionChecked(FName((EName)0xf29)), &Parms);
}

#pragma auto_inline(on)

// ---- Scaffolding for the LTCG link, not part of the unit ----
void Driver_f2070(AController *C, INT A) { C->eventProbe344(A); }
void Driver_f20c0(AController *C, INT A) { C->eventProbe340(A); }
void Driver_f2110(AController *C) { C->eventProbe341(); }
void Driver_f2150(AController *C, INT A, INT B) { C->eventProbe342(A, B); }
void Driver_f21a0(AController *C, INT A) { C->eventEvent_f29(A); }
void Escape(void *);
void Driver_f1f20() { Escape(&FName::Names); GNatives[0] = (Native)&AController::execGotoState; }
