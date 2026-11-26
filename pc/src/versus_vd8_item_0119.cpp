// Work item 0119: Versus RVA 0x155b10-0x155e2d, UGUIController script natives.
//   0x155b10 UGUIController::execIsWriteProfileFinished
//   0x155bc0 UGUIController::execRequestGetAccountList
//   0x155bf0 UGUIController::execIsGetAccountListFinished
//   0x155ca0 UGUIController::execRequestWriteAccountList
//   0x155cd0 UGUIController::execIsWriteAccountListFinished
//   0x155d80 UGUIController::execLaunchNewImage
// The three execIs*Finished natives call this address-specific view's FinishOp (RVA 0xe5dc0),
// which takes `this` in ECX and the operation mode in EAX under VC7.0 /LTCG.
#include "versus_globals.h"

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
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50();
    virtual void NetDirty(UProperty *Property); // +0x54
    BYTE unk_04[0x28 - 4];
};

struct FFrame {
    void *VfTable;
    void *Node;      // +0x04
    UObject *Object; // +0x08
    BYTE *Code;      // +0x0c

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

#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_GET_INT_REF(Var) \
    INT Var##T = 0; Stack.StepRef(Stack.Object, &Var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    INT *Var = GPropAddr ? (INT *)GPropAddr : &Var##T
#define P_FINISH Stack.Code++

class FObjectView_10c924e8_0119 {
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64(); virtual void Vf68(); virtual void Vf6c();
    virtual void VirtualSlot28(); // +0x70, identity unknown

    INT  unk_04[9];      // +0x04
    void *vtable_28;     // +0x28
    INT  unk_2c[2];      // +0x2c
    INT OpDone[7];       // +0x34 (op 1=+0x38, op 2=+0x3c, op 3=+0x40, op 4=+0x44, op 5=+0x48, op 6=+0x4c)
    INT Progress;        // +0x50
    INT unk_54[17];      // +0x54
    INT Status[7];       // +0x98 (op 1=+0x9c, op 2=+0xa0, op 3=+0xa4, op 4=+0xa8, op 5=+0xac, op 6=+0xb0)
    INT OpType[16];      // +0xb4
    INT OpParam[16];     // +0xf4
    INT OpCount;         // +0x134

    void FinishOp(INT Mode); // RVA 0xe5dc0
    UBOOL QueueOp4();        // RVA 0xe6150
    UBOOL QueueOp5();        // RVA 0xe61a0

    UBOOL IsOpFinished(INT Mode, INT *ErrorCode)
    {
        if (OpDone[Mode]) {
            *ErrorCode = Status[Mode];
            FinishOp(Mode);
            return 1;
        }
        return 0;
    }
};

#define GObjectView_10c924e8_0119 (*((FObjectView_10c924e8_0119 **)&GObject_10c924e8))

class UGUIController : public UObject {
public:
    void execIsWriteProfileFinished(FFrame &Stack, RESULT_DECL);
    void execRequestGetAccountList(FFrame &Stack, RESULT_DECL);
    void execIsGetAccountListFinished(FFrame &Stack, RESULT_DECL);
    void execRequestWriteAccountList(FFrame &Stack, RESULT_DECL);
    void execIsWriteAccountListFinished(FFrame &Stack, RESULT_DECL);
    void execLaunchNewImage(FFrame &Stack, RESULT_DECL);
};

// RVA 0x155b10
void UGUIController::execIsWriteProfileFinished(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_REF(ErrorCode);
    P_FINISH;
    FObjectView_10c924e8_0119 *SaveDevice = GObjectView_10c924e8_0119;
    if (SaveDevice) {
        *(UBOOL *)Result = SaveDevice->IsOpFinished(2, ErrorCode);
    } else {
        *(UBOOL *)Result = 1;
    }
}

// RVA 0x155bc0
void UGUIController::execRequestGetAccountList(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (GObjectView_10c924e8_0119) {
        *(UBOOL *)Result = GObjectView_10c924e8_0119->QueueOp4();
    } else {
        *(UBOOL *)Result = 0;
    }
}

// RVA 0x155bf0
void UGUIController::execIsGetAccountListFinished(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_REF(ErrorCode);
    P_FINISH;
    FObjectView_10c924e8_0119 *SaveDevice = GObjectView_10c924e8_0119;
    if (SaveDevice) {
        *(UBOOL *)Result = SaveDevice->IsOpFinished(4, ErrorCode);
    } else {
        *(UBOOL *)Result = 1;
    }
}

// RVA 0x155ca0
void UGUIController::execRequestWriteAccountList(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (GObjectView_10c924e8_0119) {
        *(UBOOL *)Result = GObjectView_10c924e8_0119->QueueOp5();
    } else {
        *(UBOOL *)Result = 0;
    }
}

// RVA 0x155cd0
void UGUIController::execIsWriteAccountListFinished(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_REF(ErrorCode);
    P_FINISH;
    FObjectView_10c924e8_0119 *SaveDevice = GObjectView_10c924e8_0119;
    if (SaveDevice) {
        *(UBOOL *)Result = SaveDevice->IsOpFinished(5, ErrorCode);
    } else {
        *(UBOOL *)Result = 1;
    }
}

// RVA 0x155d80
void UGUIController::execLaunchNewImage(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(ImageName);
    P_GET_STR(Parameters);
    P_FINISH;
}

// Scaffolding for the LTCG link, not part of the unit.
// FinishOp (RVA 0xe5dc0) receives `this` in ECX and `Mode` in EAX under /LTCG.
void Escape(void *);
void ExternalFinish(FObjectView_10c924e8_0119 *, INT);

__declspec(noinline) void FObjectView_10c924e8_0119::FinishOp(INT Mode)
{
    ExternalFinish(this, Mode);
}

void Driver_155b10(Native *Out)
{
    *Out = (Native)&UGUIController::execIsWriteProfileFinished;
    Escape(&GPropAddr);
    Escape(&GPropObject);
    Escape(&GProperty);
    Escape(&GObjectView_10c924e8_0119);
    Escape(GNatives);
}

void Driver_155bf0(Native *Out)
{
    *Out = (Native)&UGUIController::execIsGetAccountListFinished;
    Escape(&GPropAddr);
    Escape(&GPropObject);
    Escape(&GProperty);
    Escape(&GObjectView_10c924e8_0119);
    Escape(GNatives);
}

void Driver_155cd0(Native *Out)
{
    *Out = (Native)&UGUIController::execIsWriteAccountListFinished;
    Escape(&GPropAddr);
    Escape(&GPropObject);
    Escape(&GProperty);
    Escape(&GObjectView_10c924e8_0119);
    Escape(GNatives);
}
