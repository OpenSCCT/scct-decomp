// w4_item_0039.cpp -- Versus RVA 0x12a6a0-0x12aa2c (6 functions)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef float FLOAT;
typedef double DOUBLE;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef char ANSICHAR;
typedef unsigned short TCHAR;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

struct FVector {
    FLOAT X, Y, Z;
};

enum EName {
    NAME_None      = 0,
    NAME_PROBEMIN  = 300,
    NAME_Event_15e = 0x15e,
    NAME_PROBEMAX  = 364,
    NAME_Event_f25 = 0xf25
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

class FString {
public:
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
    FString operator+(const TCHAR *Str) const;

    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
    const TCHAR *operator*() const { return ArrayNum ? Data : L""; }

protected:
    TCHAR *Data;
    INT    ArrayNum;
    INT    ArrayMax;
};

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

struct FGuid;
class UFunction;
struct FFrame;

#pragma pack(push, 4)
struct FStateFrame {
    BYTE  unk_0[0x1c];
    QWORD ProbeMask;
    INT   LatentAction;
};
#pragma pack(pop)

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
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

    INT          Index;
    BYTE         unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0x18];

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);

    UBOOL IsProbing(FName ProbeName)
    {
        return (ProbeName.GetIndex() < NAME_PROBEMIN ||
                ProbeName.GetIndex() >= NAME_PROBEMAX ||
                !StateFrame ||
                (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN))));
    }
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    class UStruct *Node;
    UObject       *Object;
    BYTE          *Code;
    BYTE          *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_BYTE(Var)  BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_STR(Var)   FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH         Stack.Code++

class AActor : public UObject {
public:
    virtual ~AActor();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void setPhysics(BYTE NewPhysics, AActor *NewFloor, INT UnknownArg);
    virtual void performPhysics(FLOAT DeltaSeconds);

    BYTE    unk_28[0x70];
    FVector Velocity;       // 0x98
    BYTE    unk_a4[0x234];
    BYTE    Physics;        // 0x2d8
    BYTE    unk_2d9[0x1f];

    void eventUnnamed_12a810(INT A, INT B, INT C, FVector V1, FVector V2, INT D, INT E);
    void eventUnnamed_12a890(INT A, INT B, INT C, FVector V1, FVector V2, INT D);

    DECLARE_NATIVE(execSetPhysics)
    DECLARE_NATIVE(execAutonomousPhysics)
};

class ASLogManager : public AActor {
public:
    virtual ~ASLogManager();

    FString   unk_2f8;
    FString   unk_304;
    FArchive *LogAr;        // 0x310
    BITFIELD  bEnabled : 1; // 0x314

    DECLARE_NATIVE(execLogEvent)
    DECLARE_NATIVE(execGetAverageFPS)
};

extern const TCHAR GLineTerminator[]; // retail L"\r\n" in writable .data
extern FLOAT       GAverageFrameTime; // retail global at 0x10cbf650
extern INT         GSetPhysicsArg;    // retail global at 0x10ccacbc

// RVA 0x12a6a0: ASLogManager::execLogEvent
void ASLogManager::execLogEvent(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Event);
    P_FINISH;

    if (bEnabled && LogAr) {
        FString Line = Event + GLineTerminator;
        ANSICHAR Temp[1024];
        INT i;
        for (i = 0; i < Line.Len(); i++) {
            TCHAR Ch = (*Line)[i];
            Temp[i] = (ANSICHAR)(Ch < 0x100 ? Ch : 0x7f);
        }
        Temp[i] = 0;
        LogAr->Serialize(Temp, i);
    }
}

// RVA 0x12a7c0: ASLogManager::execGetAverageFPS
void ASLogManager::execGetAverageFPS(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    *(FLOAT *)Result = (GAverageFrameTime != 0.0f) ? (1.0f / GAverageFrameTime) : 0.0f;
}

// RVA 0x12a810: Unnamed event wrapper (FName 0xf25; owning AActor subclass not recovered)
struct Event_f25_Parms {
    INT     A;
    INT     B;
    INT     C;
    FVector V1;
    FVector V2;
    INT     D;
    INT     E;
};

void AActor::eventUnnamed_12a810(INT A, INT B, INT C, FVector V1, FVector V2, INT D, INT E)
{
    Event_f25_Parms Parms;
    Parms.A = A;
    Parms.B = B;
    Parms.C = C;
    Parms.V1 = V1;
    Parms.V2 = V2;
    Parms.D = D;
    Parms.E = E;
    ProcessEvent(FindFunctionChecked(NAME_Event_f25), &Parms);
}

// RVA 0x12a890: Unnamed event wrapper (probe FName 0x15e; owning AActor subclass not recovered)
struct Event_15e_Parms {
    INT     A;
    INT     B;
    INT     C;
    FVector V1;
    FVector V2;
    INT     D;
};

void AActor::eventUnnamed_12a890(INT A, INT B, INT C, FVector V1, FVector V2, INT D)
{
    Event_15e_Parms Parms;
    if (IsProbing(NAME_Event_15e)) {
        Parms.A = A;
        Parms.B = B;
        Parms.C = C;
        Parms.V1 = V1;
        Parms.V2 = V2;
        Parms.D = D;
        ProcessEvent(FindFunctionChecked(NAME_Event_15e), &Parms);
    }
}

// RVA 0x12a920: AActor::execSetPhysics
void AActor::execSetPhysics(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(NewPhysics);
    P_FINISH;

    setPhysics(NewPhysics, 0, GSetPhysicsArg);
}

// RVA 0x12a970: AActor::execAutonomousPhysics
void AActor::execAutonomousPhysics(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(DeltaSeconds);
    P_FINISH;

    Velocity.X = (INT)(Velocity.X * 10.0f) * 0.1f;
    Velocity.Y = (INT)(Velocity.Y * 10.0f) * 0.1f;
    Velocity.Z = (INT)(Velocity.Z * 10.0f) * 0.1f;
    if (Physics != 0)
        performPhysics(DeltaSeconds);
}

// Scaffolding for LTCG links, not part of the unit.
#pragma inline_depth(0)
void Driver_12a810(AActor *Self, INT A, INT B, INT C, FVector V1, FVector V2, INT D, INT E)
{
    Self->eventUnnamed_12a810(A, B, C, V1, V2, D, E);
    Self->eventUnnamed_12a810(B, C, A, V2, V1, E, D);
}

void Driver_12a890(AActor *Self, INT A, INT B, INT C, FVector V1, FVector V2, INT D)
{
    Self->eventUnnamed_12a890(A, B, C, V1, V2, D);
    Self->eventUnnamed_12a890(B, C, A, V2, V1, A);
}
#pragma inline_depth()
