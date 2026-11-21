// Work item 0221: script event thunk at RVA 0xee1c0 (LTCG: this in ESI).
// The class and event are unnamed: the event name is FName index 0x13f4,
// two FLOAT parameters and a DWORD parameter and a DWORD return value.
typedef int INT;
typedef unsigned long DWORD;
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
};

// Unnamed class owning the event (neutral name).
class UnnamedClass_ee1c0 : public UObject
{
public:
    __declspec(noinline) DWORD eventUnnamed_13f4(FLOAT A, FLOAT B, DWORD C);
};

DWORD UnnamedClass_ee1c0::eventUnnamed_13f4(FLOAT A, FLOAT B, DWORD C)
{
    struct
    {
        FLOAT A;
        FLOAT B;
        DWORD C;
        DWORD ReturnValue;
    } Parms;
    Parms.A = A;
    Parms.B = B;
    Parms.ReturnValue = 0;
    Parms.C = C;
    ProcessEvent(FindFunctionChecked(FName((EName)0x13f4)), &Parms);
    return Parms.ReturnValue;
}

// Scaffolding for the link, not part of the unit.
DWORD Driver_ee1c0(UnnamedClass_ee1c0 *P, FLOAT A, FLOAT B, DWORD C) { return P->eventUnnamed_13f4(A, B, C); }
