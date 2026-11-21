// Work item 0198: Versus RVA 0x4eca0-0x4efbc, PlayStation 2 network stub
// natives on UObject (UnScript.cpp, Core). They do nothing on PC beyond
// reading their parameters and returning 0. The unit is link-time optimised
// (VC7.0 /GL, /LTCG): the struct destructors take `this` on the stack.
//   0x4eca0 UObject::execPSX2DNASProgress
//   0x4ed20 UObject::execPSX2NetCnfGetCombinationList
//   0x4eda0 UObject::execPSX2NetCnfGetCombination
//   0x4ee70 FPSX2NetCnfCombination::~FPSX2NetCnfCombination (compiler generated)
//   0x4eed0 UObject::execPSX2NetCtlGetStatus
//   0x4ef70 FPSX2NetCtlStatus::~FPSX2NetCtlStatus (compiler generated)
// The two struct names are guesses from the native names; their layout comes
// from the stack frames (two leading INTs, FStrings at +8, +0x14, +0x20).
// Matched with try_ltcg.py /O2 /Gy /GX /Ob1: with full inlining the link
// folds the struct destructors into the natives, which retail does not.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
#define RESULT_DECL void *const Result

class UObject;
class UProperty;
struct FFrame;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
};

class UObject {
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property);                                 // +0x54

    void execPSX2DNASProgress(FFrame &Stack, RESULT_DECL);
    void execPSX2NetCnfGetCombinationList(FFrame &Stack, RESULT_DECL);
    void execPSX2NetCnfGetCombination(FFrame &Stack, RESULT_DECL);
    void execPSX2NetCtlGetStatus(FFrame &Stack, RESULT_DECL);
};

struct FFrame {
    void *VfTable;
    void *Node;                 // +0x04
    UObject *Object;            // +0x08
    BYTE *Code;                 // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    // Steps an out parameter: GPropAddr is cleared once the opcode is fetched.
    __forceinline void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct FPSX2NetCnfCombination {
    INT Number;
    INT Status;
    FString Name1;              // +0x08
    FString Name2;              // +0x14
    FString Name3;              // +0x20
    ~FPSX2NetCnfCombination();
};
FPSX2NetCnfCombination::~FPSX2NetCnfCombination() {}

struct FPSX2NetCtlStatus {
    INT Status;
    INT Error;
    FString Name1;              // +0x08
    FString Name2;              // +0x14
    INT Extra[4];               // +0x20
    ~FPSX2NetCtlStatus();
};
FPSX2NetCtlStatus::~FPSX2NetCtlStatus() {}

#define P_GET_INT(var) INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_GET_REF(typ, var) typ var##T; Stack.StepRef(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    typ &var = GPropAddr ? *(typ *)GPropAddr : var##T;
#define P_FINISH Stack.Code++;

void UObject::execPSX2DNASProgress(FFrame &Stack, RESULT_DECL)
{
    INT ProgressT = 0;
    Stack.StepRef(Stack.Object, &ProgressT);
    if (GPropObject) GPropObject->NetDirty(GProperty);
    P_FINISH;
    *(UBOOL *)Result = 0;
}

void UObject::execPSX2NetCnfGetCombinationList(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(List);
    P_FINISH;
    *(UBOOL *)Result = 0;
}

void UObject::execPSX2NetCnfGetCombination(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_GET_REF(FPSX2NetCnfCombination, Combination);
    P_FINISH;
    *(UBOOL *)Result = 0;
}

void UObject::execPSX2NetCtlGetStatus(FFrame &Stack, RESULT_DECL)
{
    P_GET_REF(FPSX2NetCtlStatus, Status);
    P_FINISH;
    *(UBOOL *)Result = 0;
}

// Scaffolding for the link, not part of the unit.
// The natives are reached through GNatives, so their addresses escape; the
// globals they touch have their addresses taken elsewhere in the program.
void Escape(void *);
void Driver_4eca0(Native *Out) { *Out = &UObject::execPSX2DNASProgress; Escape(&GPropAddr); Escape(&GPropObject); Escape(&GProperty); Escape(GNatives); }
void Driver_4ed20(Native *Out) { *Out = &UObject::execPSX2NetCnfGetCombinationList; Escape(GNatives); }
void Driver_4eda0(Native *Out) { *Out = &UObject::execPSX2NetCnfGetCombination; Escape(&GPropAddr); Escape(&GPropObject); Escape(&GProperty); Escape(GNatives); }
void Driver_4eed0(Native *Out) { *Out = &UObject::execPSX2NetCtlGetStatus; Escape(&GPropAddr); Escape(&GPropObject); Escape(&GProperty); Escape(GNatives); }
