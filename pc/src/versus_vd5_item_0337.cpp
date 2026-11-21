// Work item 0337 (wave 3): Versus RVA 0x10ed60. LTCG script event thunk
// (this in ESI, the single parameter in EAX). It runs ProcessEvent on the
// function named by FName index 0x83f93; the event and class names are not
// recovered, so the class is UObject and the event is eventUnnamed_10ed60.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

enum EName { NAME_None = 0 };
class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

class UFunction;

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);

    __declspec(noinline) void eventUnnamed_10ed60(INT A);
};

// RVA 0x10ed60: event for FName index 0x83f93 (name not recovered).
void UObject::eventUnnamed_10ed60(INT A)
{
    struct { INT A; } Parms;
    Parms.A = A;
    ProcessEvent(FindFunctionChecked(FName((EName)0x83f93)), &Parms);
}

// Scaffolding for the LTCG link, not part of the unit.
void Driver_10ed60(UObject *O, INT X) { O->eventUnnamed_10ed60(X); }
