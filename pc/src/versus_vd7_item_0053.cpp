// Work item 0053: Versus RVA 0x131260-0x1313a6 (Engine: script event thunks
// and AActor::execGetURLMap).
//   0x131260 UObject::eventUnnamed_134  LTCG: this in ESI
//   0x1312a0 UObject::eventUnnamed_151  LTCG: this in ESI, arg on stack (ret 4)
//   0x1312e0 UObject::eventUnnamed_e79  LTCG: this in ESI
//   0x131300 UObject::eventUnnamed_157  LTCG: this in ESI, arg on stack (ret 4)
//   0x131350 UObject::eventUnnamed_11f5 LTCG: this in ESI, arg in EAX
//   0x131380 AActor::execGetURLMap      plain thiscall (vc70 /O2 /Gy)
// The five event names (FName indices 0x134, 0x151, 0xe79, 0x157, 0x11f5)
// are not yet recovered from evidence and use neutral names.

#include "versus_build.h"
#include "unreal_containers.h"
#pragma pack(push, 4)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#define RESULT_DECL void *const Result
#define P_FINISH Stack.Code++

enum EName {
    NAME_None = 0,
    NAME_PROBEMIN = 300,
    NAME_PROBEMAX = 364
};

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

struct FGuid;
class UObject;
class UStruct;
class UFunction;

struct FFrame : public FOutputDevice {
    UStruct *Node;           // +0x04
    UObject *Object;         // +0x08
    BYTE *Code;              // +0x0c
    BYTE *Locals;            // +0x10
};

struct FStateFrame : public FFrame {
    BYTE unk_14[0x08];       // +0x14
    QWORD ProbeMask;         // +0x1c
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // +0x10

    INT Index;               // +0x04
    UObject *HashNext;       // +0x08
    FStateFrame *StateFrame; // +0x0c

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);

    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }

    __declspec(noinline) void eventUnnamed_134();
    __declspec(noinline) void eventUnnamed_151(FLOAT Arg);
    __declspec(noinline) void eventUnnamed_e79();
    __declspec(noinline) void eventUnnamed_157(FLOAT Arg);
    __declspec(noinline) void eventUnnamed_11f5(DWORD Arg);
};

struct FURL {
    FString Protocol;        // +0x00
    FString Host;            // +0x0c
    INT Port;                // +0x18
    FString Map;             // +0x1c
};

class UEngine {
public:
    BYTE unk_00[0x13c];
};

class UGameEngine : public UEngine {
public:
    FURL LastURL;            // +0x13c (Map at +0x158)
};

class ULevel {
public:
    BYTE unk_00[0xf0];
    UEngine *Engine;         // +0xf0
};

class AActor : public UObject {
public:
    BYTE unk_10[0x1a4 - 0x10];
    ULevel *XLevel;          // +0x1a4

    void execGetURLMap(FFrame &Stack, RESULT_DECL);
};

// UObject::eventUnnamed_134 (RVA 0x131260; probe event 0x134)
void UObject::eventUnnamed_134()
{
    if (IsProbing(FName((EName)0x134)))
        ProcessEvent(FindFunctionChecked(FName((EName)0x134)), 0);
}

// UObject::eventUnnamed_151 (RVA 0x1312a0; probe event 0x151)
void UObject::eventUnnamed_151(FLOAT Arg)
{
    if (IsProbing(FName((EName)0x151))) {
        struct { FLOAT Arg; } Parms;
        Parms.Arg = Arg;
        ProcessEvent(FindFunctionChecked(FName((EName)0x151)), &Parms);
    }
}

// UObject::eventUnnamed_e79 (RVA 0x1312e0; event 0xe79)
void UObject::eventUnnamed_e79()
{
    ProcessEvent(FindFunctionChecked(FName((EName)0xe79)), 0);
}

// UObject::eventUnnamed_157 (RVA 0x131300; probe event 0x157)
void UObject::eventUnnamed_157(FLOAT Arg)
{
    if (IsProbing(FName((EName)0x157))) {
        struct { FLOAT Arg; } Parms;
        Parms.Arg = Arg;
        ProcessEvent(FindFunctionChecked(FName((EName)0x157)), &Parms);
    }
}

// UObject::eventUnnamed_11f5 (RVA 0x131350; event 0x11f5)
void UObject::eventUnnamed_11f5(DWORD Arg)
{
    struct { DWORD Arg; } Parms;
    Parms.Arg = Arg;
    ProcessEvent(FindFunctionChecked(FName((EName)0x11f5)), &Parms);
}

// AActor::execGetURLMap (RVA 0x131380)
void AActor::execGetURLMap(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = ((UGameEngine *)XLevel->Engine)->LastURL.Map;
}

#pragma pack(pop)

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Driver_131260(UObject *O) { O->eventUnnamed_134(); }
void Driver_1312a0(UObject *O, FLOAT X) { O->eventUnnamed_151(X); }
void Driver_1312e0(UObject *O) { O->eventUnnamed_e79(); }
void Driver_131300(UObject *O, FLOAT X) { O->eventUnnamed_157(X); }
void Driver_131350(UObject *O, DWORD X) { O->eventUnnamed_11f5(X); }
