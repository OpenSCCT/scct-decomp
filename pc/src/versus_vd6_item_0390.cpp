// Work item 0390: Versus RVA 0x11dd60 and 0x11de30.
// 0x11dd60 is a script event thunk (FName 0xd03) taking two const FString& inputs
// and one out FString&, returning a UBOOL.
// 0x11de30 is a probed script event thunk (FName 0x12d) taking no parameters.
// Built with try_ltcg.py: 0x11dd60 with /O2 /Ob1 /Gy /GX, 0x11de30 with /O2 /Ob1 /Gy
// (/Ob1 keeps out-of-line event/destructor functions from being folded into callers).
// Class and event names are neutral placeholders; real names are not yet recovered.

#pragma pack(push, 4)

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned __int64 QWORD;
typedef unsigned char BYTE;

struct FGuid;
class UFunction;

enum { NAME_PROBEMIN = 300, NAME_PROBEMAX = 364 };

// Event name indices; real EName identifiers are not yet recovered.
enum EName
{
    NAME_Event_12d = 0x12d,
    NAME_Event_d03 = 0xd03
};

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~FString();
    FString &operator=(const FString &Other);
};

struct FStateFrame
{
    BYTE unk_0[0x1c];
    QWORD ProbeMask;
};

class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);

    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};

struct UnnamedClass_11dd60_eventUnnamed_11dd60_Parms
{
    FString InA;
    FString InB;
    FString OutC;
    UBOOL ReturnValue;
    ~UnnamedClass_11dd60_eventUnnamed_11dd60_Parms();
};

// Defined out-of-line for its LTCG convention (this on the stack); in retail
// COMDAT-folded with FPreferencesInfo::~FPreferencesInfo at RVA 0x6200.
UnnamedClass_11dd60_eventUnnamed_11dd60_Parms::~UnnamedClass_11dd60_eventUnnamed_11dd60_Parms()
{
}

// Unnamed UObject-derived class owning the events at 0x11dd60 and 0x11de30.
class UnnamedClass_11dd60 : public UObject
{
public:
    UBOOL eventUnnamed_11dd60(const FString &InA, const FString &InB, FString &OutC);
    void eventUnnamed_11de30();
};

// RVA 0x11dd60: UnnamedClass_11dd60::eventUnnamed_11dd60
UBOOL UnnamedClass_11dd60::eventUnnamed_11dd60(const FString &InA, const FString &InB, FString &OutC)
{
    UnnamedClass_11dd60_eventUnnamed_11dd60_Parms Parms;
    Parms.ReturnValue = 0;
    Parms.InA = InA;
    Parms.InB = InB;
    Parms.OutC = OutC;
    ProcessEvent(FindFunctionChecked(FName(NAME_Event_d03)), &Parms);
    OutC = Parms.OutC;
    return Parms.ReturnValue;
}

// RVA 0x11de30: UnnamedClass_11dd60::eventUnnamed_11de30
void UnnamedClass_11dd60::eventUnnamed_11de30()
{
    if (IsProbing(NAME_Event_12d))
        ProcessEvent(FindFunctionChecked(FName(NAME_Event_12d)), 0);
}

#pragma pack(pop)

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

UBOOL Driver_11dd60(UnnamedClass_11dd60 *Obj, const FString &A, const FString &B, FString &C)
{
    Escape(Obj);
    Escape(&C);
    return Obj->eventUnnamed_11dd60(A, B, C);
}

void Driver_11de30(UnnamedClass_11dd60 *Obj)
{
    Escape(Obj);
    Obj->eventUnnamed_11de30();
}
