// Work item 0219 (w3): Versus RVA 0xedce0-0xede92.
// Six script event thunks (UnrealScript-generated eventXxx wrappers) on
// UObject-derived classes, compiled with /GL (this in ESI or EDI). The event
// names and owning classes are not recovered; the EName indices are kept.
// 0xedd30/0xedd70/0xeddb0 are probe events guarded by an inline IsProbing
// test (StateFrame->ProbeMask is a QWORD; probe base index 0x14c).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

enum EName {
    NAME_Unnamed_163 = 0x163,  // probe event names; real names not recovered
    NAME_Unnamed_164 = 0x164,
    NAME_Unnamed_165 = 0x165,
    NAME_Unnamed_A3D = 0xa3d,
    NAME_Unnamed_CF4 = 0xcf4,
    NAME_Unnamed_1412 = 0x1412,
    NAME_PROBEMIN = 0x14c,
    NAME_PROBEMAX = 0x18c,
};

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};


class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
    FString &operator=(const FString &Other);
};

struct FStateFrame {
    BYTE Pad00[0x20];
    QWORD ProbeMask;
};

class UFunction;

class UObject {
public:
    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;

    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};

// Owning class not recovered.
class UnnamedClass_edce0 : public UObject {
public:
    __declspec(noinline) void eventUnnamed_edce0(BYTE Value);
    __declspec(noinline) void eventUnnamed_edd10();
    __declspec(noinline) void eventUnnamed_edd30();
    __declspec(noinline) void eventUnnamed_edd70();
    __declspec(noinline) void eventUnnamed_eddb0();
    __declspec(noinline) void eventUnnamed_eddf0(const FString &InValue, FString &OutValue);
};

void UnnamedClass_edce0::eventUnnamed_edce0(BYTE Value)
{
    struct UnnamedClass_edce0_eventUnnamed_edce0_Parms {
        BYTE Value;
    } Parms;
    Parms.Value = Value;
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_1412)), &Parms);
}

void UnnamedClass_edce0::eventUnnamed_edd10()
{
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_A3D)), 0);
}

void UnnamedClass_edce0::eventUnnamed_edd30()
{
    if (IsProbing(FName(NAME_Unnamed_165)))
        ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_165)), 0);
}

void UnnamedClass_edce0::eventUnnamed_edd70()
{
    if (IsProbing(FName(NAME_Unnamed_164)))
        ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_164)), 0);
}

void UnnamedClass_edce0::eventUnnamed_eddb0()
{
    if (IsProbing(FName(NAME_Unnamed_163)))
        ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_163)), 0);
}

struct UnnamedClass_edce0_eventUnnamed_eddf0_Parms {
    FString InValue;
    FString OutValue;
    __declspec(noinline) ~UnnamedClass_edce0_eventUnnamed_eddf0_Parms() {}
};

void UnnamedClass_edce0::eventUnnamed_eddf0(const FString &InValue, FString &OutValue)
{
    UnnamedClass_edce0_eventUnnamed_eddf0_Parms Parms;
    Parms.InValue = InValue;
    Parms.OutValue = OutValue;
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_CF4)), &Parms);
    OutValue = Parms.OutValue;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_edce0(UnnamedClass_edce0 *A, BYTE V) { A->eventUnnamed_edce0(V); }
void Driver_edd10(UnnamedClass_edce0 *A) { A->eventUnnamed_edd10(); }
void Driver_edd30(UnnamedClass_edce0 *A) { A->eventUnnamed_edd30(); }
void Driver_edd70(UnnamedClass_edce0 *A) { A->eventUnnamed_edd70(); }
void Driver_eddb0(UnnamedClass_edce0 *A) { A->eventUnnamed_eddb0(); }
void Driver_eddf0(UnnamedClass_edce0 *A, const FString &I, FString &O) { A->eventUnnamed_eddf0(I, O); }
