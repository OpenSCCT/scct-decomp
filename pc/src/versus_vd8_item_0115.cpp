/* w4_item_0115.cpp -- UGUIController::NativeTick and UGUIController::NativePreRender */

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FGuid;

class FName {
public:
    INT Index;
    FName(INT InIndex) : Index(InIndex) {}
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T>
class TArray : public FArray {
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
};

class UCanvas;
class UClass;
class UFunction;

struct FStateFrame {
    BYTE unk_00[0x1c];
    QWORD ProbeMask;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

/* Core.Object: 0x28 bytes, 22 virtual functions in Versus. */
class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void VirtualSlot5();
    virtual void ProcessState(FLOAT DeltaSeconds);
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    INT          Index;
    BYTE         unk_08[0x04];
    FStateFrame *StateFrame;
    BYTE         unk_10[0x0c];
    DWORD        ObjectFlags;
    BYTE         unk_20[0x04];
    UClass      *Class;

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class ALevelInfo : public UObject {
public:
    BYTE unk_28[0x384];
    FLOAT TimeDilation;
};

class APlayerController : public UObject {
public:
    BYTE unk_28[0x178];
    ALevelInfo *Level;
};

class UViewport : public UObject {
public:
    BYTE unk_28[0x08];
    APlayerController *Actor;
    BYTE unk_34[0x04];
    UBOOL bWindowsMouseAvailable:1;
    UBOOL bShowWindowsMouse:1;
    FLOAT WindowsMouseX;
    FLOAT WindowsMouseY;
};

class UClient : public UObject {
public:
    BYTE unk_28[0x04];
    TArray<UViewport *> Viewports;
};

#include "versus_gui_controller_types.h"

class UInteractionMaster : public UInteractions {
public:
    virtual ~UInteractionMaster();

    UClient *Client;
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x04];
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual UBOOL Draw(UCanvas *Canvas);

    BYTE unk_2c[0x98];
    INT TimerIndex;
    UBOOL bTimerRepeat:1;
    FLOAT TimerCountdown;
    FLOAT TimerInterval;
    BYTE unk_d4[0xbc];

    void eventTimer()
    {
        if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 8)))
            ProcessEvent(FindFunctionChecked(FName(0x134)), 0);
    }
};

class UGUIMultiComponent : public UGUIComponent {
public:
    virtual ~UGUIMultiComponent();

    BYTE unk_190[0x10];
};

class UGUIPage : public UGUIMultiComponent {
public:
    virtual ~UGUIPage();

    BYTE unk_1a0[0x58];
    UGUIPage *ParentPage;
    TArray<UGUIComponent *> Timers;

    void UpdateTimers(FLOAT DeltaTime);
    void eventOnTick(FLOAT DeltaTime);
};

/* Originally a static local/file BYTE initialized to IST_Hold (2). */
extern BYTE GGUIRepeatAction;

/* UGUIController::NativeTick */
void UGUIController::NativeTick(FLOAT DeltaTime)
{
    if (!ViewportOwner || !ViewportOwner->Actor || !ViewportOwner->Actor->Level)
        return;

    DeltaTime /= ViewportOwner->Actor->Level->TimeDilation;

    if (RepeatKey) {
        RepeatTime -= DeltaTime;
        if (RepeatTime <= 0.0f) {
            NativeKeyEvent(RepeatKey, GGUIRepeatAction, RepeatDelta);
            RepeatTime = ButtonRepeatDelay;
        }
    }

    CursorFade += (CursorStep * DeltaTime) * 255.0f;
    if (CursorFade <= 0.0) {
        CursorFade = 0.0f;
        CursorStep = 1;
    } else if (CursorFade >= 255.0) {
        CursorFade = 255.0f;
        CursorStep = -1;
    }

    FastCursorFade += (FastCursorStep * DeltaTime) * 8192.0f;
    if (FastCursorFade <= 0.0) {
        FastCursorFade = 0.0f;
        FastCursorStep = 1;
    } else if (FastCursorFade >= 255.0) {
        FastCursorFade = 255.0f;
        FastCursorStep = -1;
    }

    if (ActivePage)
        ActivePage->UpdateTimers(DeltaTime);
    if (ActivePage)
        ActivePage->ProcessState(DeltaTime);
    if (ActivePage)
        ActivePage->eventOnTick(DeltaTime);
}

/* UGUIController::NativePreRender */
void UGUIController::NativePreRender(UCanvas *Canvas)
{
    if (!Canvas || !Master || !Master->Client || !Master->Client->Viewports.Num()
        || !Master->Client->Viewports(0))
        return;

    if (Master->Client->Viewports(0)->bWindowsMouseAvailable) {
        LastMouseX = MouseX;
        LastMouseY = MouseY;
        MouseX = (INT)Master->Client->Viewports(0)->WindowsMouseX;
        MouseY = (INT)Master->Client->Viewports(0)->WindowsMouseY;
        Master->Client->Viewports(0)->bShowWindowsMouse = 1;
    } else {
        Master->Client->Viewports(0)->bShowWindowsMouse = 0;
    }

    if (ActivePage) {
        if (ActivePage->ParentPage)
            ActivePage->ParentPage->Draw(Canvas);
        ActivePage->Draw(Canvas);
    }
}

/* Callees compiled in the same LTCG link so the linker assigns their retail
 * custom calling conventions (this in EAX for UpdateTimers, ESI for eventOnTick). */
void UGUIPage::UpdateTimers(FLOAT DeltaTime)
{
    INT Count = Timers.Num();
    for (INT i = 0; i < Count; i++) {
        UGUIComponent *Comp = Timers(i);
        Comp->TimerIndex = i;
        Comp->TimerCountdown -= DeltaTime;
        if (Comp->TimerCountdown <= 0.0 && Comp->TimerInterval > 0.0) {
            Comp->eventTimer();
            if (Comp->bTimerRepeat) {
                Comp->TimerCountdown += Comp->TimerInterval;
                if (Comp->TimerCountdown <= 0.0)
                    Comp->TimerCountdown = Comp->TimerInterval;
            } else {
                Comp->TimerCountdown = 0.0f;
                Comp->TimerInterval = 0.0f;
            }
        }
        if (Comp->TimerInterval <= 0.0) {
            Comp->TimerIndex = -1;
            Timers.Remove(i);
            i--;
            Count--;
        }
    }
}

void UGUIPage::eventOnTick(FLOAT DeltaTime)
{
    struct { FLOAT DeltaTime; } Parms;
    Parms.DeltaTime = DeltaTime;
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 36)))
        ProcessEvent(FindFunctionChecked(FName(0x150)), &Parms);
}
