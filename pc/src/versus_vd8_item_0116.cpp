// Work item 0116 (vwork4): Versus RVA 0x155480-0x155654, UGUIController profile & memory card natives.
//   0x155480 UGUIController::execIsSavingMediaAvailable
//   0x1554b0 UGUIController::execIsMemoryCardReady
//   0x1554e0 UGUIController::execSetMemoryCardActivation
//   0x155540 UGUIController::execHasMemoryCardBeenChanged
//   0x155570 UGUIController::execRequestGetProfileList
//   0x1555b0 UGUIController::execIsGetProfileListFinished

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

class UObject {
public:
    virtual void VFunc00(); virtual void VFunc04(); virtual void VFunc08(); virtual void VFunc0c();
    virtual void VFunc10(); virtual void VFunc14(); virtual void VFunc18(); virtual void VFunc1c();
    virtual void VFunc20(); virtual void VFunc24(); virtual void VFunc28(); virtual void VFunc2c();
    virtual void VFunc30(); virtual void VFunc34(); virtual void VFunc38(); virtual void VFunc3c();
    virtual void VFunc40(); virtual void VFunc44(); virtual void VFunc48(); virtual void VFunc4c();
    virtual void VFunc50();
    virtual void NetDirty(UProperty *Property); // +0x54
};

struct FFrame {
    void *VfTable;
    void *Node;         // +0x04
    UObject *Object;    // +0x08
    BYTE *Code;         // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }

    __forceinline void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var);
#define P_GET_INT_REF(Var) \
    INT Var##T = 0; Stack.StepRef(Stack.Object, &Var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    INT *Var = GPropAddr ? (INT *)GPropAddr : &Var##T;
#define P_FINISH Stack.Code++;

// Neutral name: subsystem at *(0x10c923c4) + 0x184 holding session/profile context.
struct FProfileContext {
    BYTE unk_0[0x7c];
    INT RequestParam;   // +0x7c
};

// Consumer-specific view of the object-pointer slot at VA 0x10c924e8; class identity is unknown.
class FObjectView_10c924e8_0116 {
public:
    virtual void VFunc00(); virtual void VFunc04(); virtual void VFunc08(); virtual void VFunc0c();
    virtual void VFunc10(); virtual void VFunc14(); virtual void VFunc18(); virtual void VFunc1c();
    virtual void VFunc20(); virtual void VFunc24(); virtual void VFunc28(); virtual void VFunc2c();
    virtual void VFunc30(); virtual void VFunc34(); virtual void VFunc38(); virtual void VFunc3c();
    virtual void VFunc40(); virtual void VFunc44(); virtual void VFunc48(); virtual void VFunc4c();
    virtual void VFunc50(); virtual void VFunc54(); virtual void VFunc58(); virtual void VFunc5c();
    virtual UBOOL IsSavingMediaAvailable();                 // +0x60
    virtual UBOOL IsMemoryCardReady();                      // +0x64
    virtual UBOOL HasMemoryCardBeenChanged();               // +0x68
    virtual UBOOL SetMemoryCardActivation(UBOOL bActive);   // +0x6c
    virtual void VirtualSlot28();                            // +0x70, identity unknown

    BYTE   unk_04[0x24];
    void  *vtable_28;
    INT RequestParam;       // +0x2c
    INT unk_30;             // +0x30
    INT Done[7];            // +0x34
    INT Current;            // +0x50
    BYTE unk_54[0x44];
    INT Status[7];          // +0x98
    INT ModeStack[16];      // +0xb4
    INT ModeValues[16];     // +0xf4
    INT Depth;              // +0x134

    __declspec(noinline) void Pop(INT Mode);
    UBOOL PushMode1();

    inline UBOOL IsGetProfileListFinished(INT &OutStatus)
    {
        if (Done[1]) {
            OutStatus = Status[1];
            Pop(1);
            return 1;
        }
        return 0;
    }
};

#define GObjectView_10c924e8_0116 (*((FObjectView_10c924e8_0116 **)&GObject_10c924e8))

class UGUIController : public UObject {
public:
    void execIsSavingMediaAvailable(FFrame &Stack, RESULT_DECL);
    void execIsMemoryCardReady(FFrame &Stack, RESULT_DECL);
    void execSetMemoryCardActivation(FFrame &Stack, RESULT_DECL);
    void execHasMemoryCardBeenChanged(FFrame &Stack, RESULT_DECL);
    void execRequestGetProfileList(FFrame &Stack, RESULT_DECL);
    void execIsGetProfileListFinished(FFrame &Stack, RESULT_DECL);
};

// UGUIController::execIsSavingMediaAvailable (RVA 0x155480)
void UGUIController::execIsSavingMediaAvailable(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (GObjectView_10c924e8_0116)
        *(UBOOL *)Result = GObjectView_10c924e8_0116->IsSavingMediaAvailable();
    else
        *(UBOOL *)Result = 0;
}

// UGUIController::execIsMemoryCardReady (RVA 0x1554b0)
void UGUIController::execIsMemoryCardReady(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (GObjectView_10c924e8_0116)
        *(UBOOL *)Result = GObjectView_10c924e8_0116->IsMemoryCardReady();
    else
        *(UBOOL *)Result = 0;
}

// UGUIController::execSetMemoryCardActivation (RVA 0x1554e0)
void UGUIController::execSetMemoryCardActivation(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(bActive);
    P_FINISH;
    if (GObjectView_10c924e8_0116)
        *(UBOOL *)Result = GObjectView_10c924e8_0116->SetMemoryCardActivation(bActive);
    else
        *(UBOOL *)Result = 0;
}

// UGUIController::execHasMemoryCardBeenChanged (RVA 0x155540)
void UGUIController::execHasMemoryCardBeenChanged(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (GObjectView_10c924e8_0116)
        *(UBOOL *)Result = GObjectView_10c924e8_0116->HasMemoryCardBeenChanged();
    else
        *(UBOOL *)Result = 0;
}

// UGUIController::execRequestGetProfileList (RVA 0x155570)
void UGUIController::execRequestGetProfileList(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    FObjectView_10c924e8_0116 *ProfileManager = GObjectView_10c924e8_0116;
    if (ProfileManager) {
        ProfileManager->RequestParam = ((FProfileContext *)GGlobalContext->unk_184)->RequestParam;
        *(UBOOL *)Result = ProfileManager->PushMode1();
    } else {
        *(UBOOL *)Result = 0;
    }
}

// UGUIController::execIsGetProfileListFinished (RVA 0x1555b0)
void UGUIController::execIsGetProfileListFinished(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_REF(ErrorCode);
    P_FINISH;
    FObjectView_10c924e8_0116 *ProfileManager = GObjectView_10c924e8_0116;
    if (ProfileManager)
        *(UBOOL *)Result = ProfileManager->IsGetProfileListFinished(*ErrorCode);
    else
        *(UBOOL *)Result = 1;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

void FObjectView_10c924e8_0116::Pop(INT Mode)
{
    if (Depth) {
        if (ModeStack[0] != Mode)
            return;
        Done[Mode] = 1;
        for (INT i = 1; i < Depth; i++) {
            ModeStack[i - 1] = ModeStack[i];
            ModeValues[i - 1] = ModeValues[i];
        }
        Depth--;
        if (Depth) {
            Status[ModeStack[0]] = 0;
            Current = ModeValues[0];
        }
    }
    VirtualSlot28();
}

void Driver_1555b0(Native *Out, FObjectView_10c924e8_0116 *M, INT Mode)
{
    Escape(&GPropAddr);
    Escape(&GPropObject);
    Escape(&GProperty);
    Escape(&GObjectView_10c924e8_0116);
    Escape(GNatives);
    M->Pop(Mode);
    *Out = (Native)&UGUIController::execIsGetProfileListFinished;
}
