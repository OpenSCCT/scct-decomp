// Work item 0193 (RVA 0x49cf0-0x49f3a): UObject script natives from UnScript.cpp:
// execSaveConfig, execStaticSaveConfig, execGetEnum, execDynamicLoadObject_Fname
// and execIsInState.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UObject;
class UClass;
class UField;
class UState;
class UPackageMap;
struct FFrame;

enum EName { NAME_None = 0 };

class FName {
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
};

template <class T> struct TArray {
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

enum { CPF_Config = 0x4000 };
enum { LOAD_NoWarn = 0x2, LOAD_Quiet = 0x2000 };

struct FStateFrame;

class UObject {
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    BYTE Pad10[0x20 - 0x10];
    FName Name;
    UClass *Class;

    UClass *GetClass() const { return Class; }
    FName GetFName() const { return Name; }
    inline UBOOL IsA(UClass *SomeBase) const;

    // Config writer at 0x17010 (stdcall: object, flags, filename, flag).
    static void __stdcall SaveConfigObject(UObject *Obj, DWORD Flags, const TCHAR *Filename, UBOOL bFlush);
    // Loader at 0x1afe0 (cdecl, Versus FName variant of StaticLoadObject).
    static UObject *__cdecl StaticLoadObjectByName(UClass *ObjectClass, UObject *InOuter, FName ObjectName,
                                                   FName PackageName, FName GroupName, const TCHAR *Filename,
                                                   DWORD LoadFlags, UPackageMap *Sandbox);

    void execSaveConfig(FFrame &Stack, void *const Result);
    void execStaticSaveConfig(FFrame &Stack, void *const Result);
    void execGetEnum(FFrame &Stack, void *const Result);
    void execDynamicLoadObject_Fname(FFrame &Stack, void *const Result);
    void execIsInState(FFrame &Stack, void *const Result);
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

class UField : public UObject {
public:
    UField *SuperField;   // +0x28
    UField *Next;         // +0x2c
};

class UEnum : public UField {
public:
    TArray<FName> Names; // +0x30
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UStruct : public UField {
};

class UState : public UStruct {
};

class UClass : public UState {
public:
    BYTE Pad30[0xac - 0x30];
    TArray<BYTE> Defaults;
    UObject *GetDefaultObject() { return (UObject *)Defaults.Data; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

struct FFrame {
    void *VTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct FStateFrame {
    BYTE Pad00[0x18];
    UState *StateNode;
};

#define RESULT_DECL void *const Result
#define P_GET_NAME(var) FName var = NAME_None; Stack.Step(Stack.Object, &var);
#define P_GET_INT(var) INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL(var) DWORD var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var) cls *var = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

void UObject::execSaveConfig(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    SaveConfigObject(this, CPF_Config, 0, 1);
}

void UObject::execStaticSaveConfig(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    SaveConfigObject(GetClass()->GetDefaultObject(), CPF_Config, 0, 1);
}

void UObject::execGetEnum(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, E);
    P_GET_INT(i);
    P_FINISH;

    *(FName *)Result = NAME_None;
    if (E && E->IsA(UEnum::StaticClass()) && i >= 0 && i < ((UEnum *)E)->Names.Num())
        *(FName *)Result = ((UEnum *)E)->Names(i);
}

void UObject::execDynamicLoadObject_Fname(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(ObjectName);
    P_GET_NAME(PackageName);
    P_GET_NAME(GroupName);
    P_GET_OBJECT(UClass, ObjectClass);
    P_GET_UBOOL(bMayFail);
    P_FINISH;

    *(UObject **)Result = StaticLoadObjectByName(ObjectClass, 0, ObjectName, PackageName, GroupName, 0,
                                                 LOAD_NoWarn | (bMayFail ? LOAD_Quiet : 0), 0);
}

void UObject::execIsInState(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(StateName);
    P_FINISH;

    if (StateFrame)
        for (UState *Test = StateFrame->StateNode; Test; Test = (UState *)Test->SuperField)
            if (Test->GetFName() == StateName) {
                *(DWORD *)Result = 1;
                return;
            }
    *(DWORD *)Result = 0;
}
