// w3_item_0384.cpp -- Versus RVA 0x11c880 (AActor vtable slot 46)
// Virtual method on AActor that dispatches the probe event for FName index 0x13b
// (probe bit 15) with one 4-byte actor/pointer parameter.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

struct FGuid;
class UObject;
class UStruct;
class UState;
class UFunction;

enum EName
{
    NAME_None     = 0,
    NAME_PROBEMIN = 300,
    NAME_Probe13b = 0x13b,
    NAME_PROBEMAX = 364
};

class FName
{
public:
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

#pragma pack(push, 4)
struct FFrame : public FOutputDevice
{
    UStruct *Node;          // +0x04
    UObject *Object;        // +0x08
    BYTE    *Code;          // +0x0c
    BYTE    *Locals;        // +0x10
};

struct FStateFrame : public FFrame
{
    BYTE     unk_14[0x4];
    UState  *StateNode;     // +0x18
    QWORD    ProbeMask;     // +0x1c
};
#pragma pack(pop)

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
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // slot 4 (+0x10)

    INT          Index;         // +0x04
    BYTE         unk_8[0x4];
    FStateFrame *StateFrame;    // +0x0c

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);

    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};

struct AActor_eventProbe13b_Parms
{
    class AActor *Other;
};

class AActor : public UObject
{
public:
    void eventProbe13b(AActor *Other)
    {
        if (IsProbing(NAME_Probe13b))
        {
            AActor_eventProbe13b_Parms Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(FName(NAME_Probe13b)), &Parms);
        }
    }

    // Virtual slot 46 on AActor (exact original method name not recovered).
    virtual void NotifyProbe13b(AActor *Other);
};

// AActor::NotifyProbe13b (RVA 0x11c880)
void AActor::NotifyProbe13b(AActor *Other)
{
    eventProbe13b(Other);
}
