// Work item 0134: Versus RVA 0x159320-0x159794 (UGUIComponent input methods).

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;
typedef double DOUBLE;

enum EMenuState
{
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4,
};

enum EInputKey
{
    IK_Tab = 9,
};

enum EInputAction
{
    IST_Press  = 1,
    IST_Repeat = 2,
};

// Versus registers these GUI script names before it loads packages.
enum {
    GUI_OnKeyEvent = 0xce95,
    GUI_NextControl = 0xceae,
    GUI_PrevControl = 0xceaf,
    GUI_NextPage = 0xceb0,
    GUI_PrevPage = 0xceb1,
};

class FName
{
public:
    INT Index;
    FName() {}
    FName(INT InIndex) : Index(InIndex) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString()
    {
        Data = 0;
        ArrayNum = 0;
        ArrayMax = 0;
    }
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    static FString __cdecl Printf(const TCHAR *Fmt, ...);
};

class UObject;
class UClass;
class UFunction;
class USound;
class UGUIController;
class UGUIComponent;
class UGUIMultiComponent;
class UGUIPage;

struct FScriptDelegate
{
    UObject *Object;
    FName FunctionName;
};

class UClass
{
public:
    BYTE unk_00[0x28];
    UClass *SuperField;
};

class UObject
{
public:
    virtual void VSlot00();
    virtual void VSlot01();
    virtual void VSlot02();
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void ProcessDelegate(FName DelegateName, FScriptDelegate *Delegate, void *Parms, void *Result = 0);
    virtual void VSlot06();
    virtual void VSlot07();
    virtual void VSlot08();
    virtual void VSlot09();
    virtual void VSlot10();
    virtual UBOOL IsPendingKill();

    BYTE unk_04[0x20];
    UClass *Class; // +0x24

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
    UBOOL IsA(UClass *SomeBase) const;
};

extern DOUBLE __cdecl appSeconds();
extern DOUBLE MouseReleased_LastClickTime; // static DOUBLE inside MouseReleased (0x10c91238)
extern const TCHAR GFormatChar[]; // L"%c"
extern INT GSoundParam_ccacc0;

class UAudioSubsystem
{
public:
    virtual void VSlot00();
    virtual void VSlot01();
    virtual void VSlot02();
    virtual void VSlot03();
    virtual void VSlot04();
    virtual void VSlot05();
    virtual void VSlot06();
    virtual void VSlot07();
    virtual void VSlot08();
    virtual void VSlot09();
    virtual void VSlot10();
    virtual void VSlot11();
    virtual void VSlot12();
    virtual void VSlot13();
    virtual void VSlot14();
    virtual void VSlot15();
    virtual void VSlot16();
    virtual void VSlot17();
    virtual void VSlot18();
    virtual void VSlot19();
    virtual void VSlot20();
    virtual void VSlot21();
    virtual void VSlot22();
    virtual void VSlot23();
    virtual void VSlot24();
    virtual void VSlot25();
    virtual void VSlot26();
    virtual void VSlot27();
    virtual void PlaySound(void *Actor, INT Id, USound *Sound, INT Location, FLOAT Volume, FLOAT Radius, FLOAT Pitch, INT Flags, FLOAT FadeDuration, FLOAT Priority, INT Channel); // +0x70
};

class UEngine
{
public:
    BYTE unk_00[0x34];
    UAudioSubsystem *Audio; // +0x34
};

class ULevel
{
public:
    BYTE unk_00[0xf0];
    UEngine *Engine; // +0xf0
};

class APlayerController
{
public:
    BYTE unk_00[0x1a4];
    ULevel *XLevel; // +0x1a4
};

class UViewport
{
public:
    BYTE unk_00[0x30];
    APlayerController *Actor; // +0x30
};

class UGUIController : public UObject
{
public:
    virtual void VSlot12();
    virtual void VSlot13();
    virtual void VSlot14();
    virtual void VSlot15();
    virtual void VSlot16();
    virtual void VSlot17();
    virtual void VSlot18();
    virtual void VSlot19();
    virtual void VSlot20();
    virtual void VSlot21();
    virtual void VSlot22();
    virtual void VSlot23();
    virtual void VSlot24();
    virtual void VSlot25();
    virtual void VSlot26();
    virtual void VSlot27();
    virtual void SetMoveTarget(UGUIComponent *Target, UBOOL bFlag); // +0x70 (slot 28)

    BYTE unk_28[0x04];
    UViewport *ViewportOwner; // +0x2c
    BYTE unk_30[0xc9c];
    INT MouseX; // +0xccc
    INT MouseY; // +0xcd0
    BYTE unk_cd4[0x08];
    BITFIELD ShiftPressed : 1; // +0xcdc bit 0
    BITFIELD AltPressed : 1;   // +0xcdc bit 1
    BITFIELD CtrlPressed : 1;  // +0xcdc bit 2
    FLOAT DblClickWindow;      // +0xce0
    BYTE unk_ce4[0x04];
    INT LastClickX;            // +0xce8
    INT LastClickY;            // +0xcec
    BYTE unk_cf0[0x4c];
    USound *ClickSound;        // +0xd3c
    USound *EditSound;         // +0xd40
    USound *UpSound;           // +0xd44
    USound *DownSound;         // +0xd48

    void PlaySound(USound *Sound);
    __declspec(noinline) void PlayInterfaceSound(BYTE SoundNum);
};

void UGUIController::PlaySound(USound *Sound)
{
    if (ViewportOwner->Actor &&
        ViewportOwner->Actor->XLevel &&
        ViewportOwner->Actor->XLevel->Engine &&
        ViewportOwner->Actor->XLevel->Engine->Audio)
    {
        ViewportOwner->Actor->XLevel->Engine->Audio->PlaySound(
            0, 0, Sound, GSoundParam_ccacc0, 1.0f, 4096.0f, 1.0f, 0x10, 0.0f, 0.0f, -1);
    }
}

__declspec(noinline) void UGUIController::PlayInterfaceSound(BYTE SoundNum)
{
    USound *Sound;
    switch (SoundNum)
    {
    case 1: Sound = ClickSound; break;
    case 2: Sound = EditSound; break;
    case 3: Sound = UpSound; break;
    case 4: Sound = DownSound; break;
    default: return;
    }
    if (Sound)
        PlaySound(Sound);
}

struct UGUIComponent_eventSetFocus_Parms
{
    UGUIComponent *Who;
};

struct UGUIComponent_eventMenuStateChange_Parms
{
    BYTE NewState;
};

struct UGUIComponent_eventOnMousePressed_Parms
{
    UGUIComponent *Sender;
    BITFIELD bRepeat;
};

struct UGUIComponent_eventOnMouseRelease_Parms
{
    UGUIComponent *Sender;
};

struct UGUIComponent_eventOnClick_Parms
{
    UGUIComponent *Sender;
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventOnDblClick_Parms
{
    UGUIComponent *Sender;
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventOnCapturedMouseMove_Parms
{
    FLOAT deltaX;
    FLOAT deltaY;
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventOnKeyEvent_Parms
{
    BYTE Key;
    BYTE State;
    FLOAT delta;
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventOnKeyType_Parms
{
    BYTE Key;
    FString Unicode;
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventNextPage_Parms
{
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventPrevPage_Parms
{
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventNextControl_Parms
{
    UGUIComponent *Sender;
    BITFIELD ReturnValue;
};

struct UGUIComponent_eventPrevControl_Parms
{
    UGUIComponent *Sender;
    BITFIELD ReturnValue;
};

class UGUIComponent : public UObject
{
public:
    virtual void VSlot12();
    virtual void VSlot13();
    virtual void VSlot14();
    virtual void VSlot15();
    virtual void VSlot16();
    virtual void VSlot17();
    virtual void VSlot18();
    virtual void VSlot19();
    virtual void VSlot20();
    virtual void VSlot21();
    virtual void VSlot22();
    virtual void VSlot23();
    virtual UBOOL PerformHitTest(INT MouseX, INT MouseY); // +0x60 (slot 24)
    virtual void VSlot25();
    virtual FLOAT ActualWidth();  // +0x68 (slot 26)
    virtual FLOAT ActualHeight(); // +0x6c (slot 27)
    virtual FLOAT ActualLeft();   // +0x70 (slot 28)
    virtual FLOAT ActualTop();    // +0x74 (slot 29)
    virtual void VSlot30();
    virtual void VSlot31();
    virtual void VSlot32();
    virtual UBOOL MouseMove(INT Xdelta, INT Ydelta);                       // +0x84 (slot 33)
    virtual UBOOL MousePressed(UBOOL IsRepeat);                            // +0x88 (slot 34)
    virtual UBOOL MouseReleased();                                         // +0x8c (slot 35)
    virtual void VSlot36();
    virtual UBOOL NativeKeyType(BYTE &iKey, TCHAR Unicode);                // +0x94 (slot 37)
    virtual UBOOL NativeKeyEvent(BYTE &iKey, BYTE &State, FLOAT Delta);    // +0x98 (slot 38)

    UGUIController *Controller; // +0x28
    UGUIComponent *MenuOwner;   // +0x2c
    BYTE MenuState;             // +0x30
    BYTE unk_31[0x1b];
    FLOAT WinTop;               // +0x4c
    FLOAT WinLeft;              // +0x50
    FLOAT WinWidth;             // +0x54
    FLOAT WinHeight;            // +0x58
    BITFIELD bFlag0 : 1;        // +0x5c bit 0
    BITFIELD bFlag1 : 1;        // +0x5c bit 1
    BITFIELD bFlag2 : 1;        // +0x5c bit 2
    BITFIELD bFlag3 : 1;        // +0x5c bit 3
    BITFIELD bFlag4 : 1;        // +0x5c bit 4
    BITFIELD bCaptureTabs : 1;         // +0x5c bit 5 (0x20)
    BITFIELD bCaptureMouse : 1;        // +0x5c bit 6 (0x40)
    BITFIELD bNeverFocus : 1;          // +0x5c bit 7 (0x80)
    BITFIELD bRepeatClick : 1;         // +0x5c bit 8 (0x100)
    BITFIELD bRequireReleaseClick : 1; // +0x5c bit 9 (0x200)
    BYTE unk_60[0x38];
    BYTE OnClickSound;          // +0x98
    BYTE unk_99[0x97];
    FScriptDelegate __OnClick__Delegate;              // +0x130
    FScriptDelegate __OnDblClick__Delegate;           // +0x138
    BYTE unk_140[0x08];
    FScriptDelegate __OnMousePressed__Delegate;       // +0x148
    FScriptDelegate __OnMouseRelease__Delegate;       // +0x150
    BYTE unk_158[0x08];
    FScriptDelegate __OnKeyType__Delegate;            // +0x160
    FScriptDelegate __OnKeyEvent__Delegate;           // +0x168
    FScriptDelegate __OnCapturedMouseMove__Delegate;  // +0x170

    void eventSetFocus(UGUIComponent *Who)
    {
        UGUIComponent_eventSetFocus_Parms Parms;
        Parms.Who = Who;
        ProcessEvent(FindFunctionChecked(FName(0xabaa), 0), &Parms, 0);
    }

    void eventMenuStateChange(BYTE NewState)
    {
        UGUIComponent_eventMenuStateChange_Parms Parms;
        Parms.NewState = NewState;
        ProcessEvent(FindFunctionChecked(FName(0xcea4), 0), &Parms, 0);
    }

    void delegateOnMousePressed(UGUIComponent *Sender, BITFIELD bRepeat)
    {
        UGUIComponent_eventOnMousePressed_Parms Parms;
        Parms.Sender = Sender;
        Parms.bRepeat = bRepeat;
        ProcessDelegate(FName(0xce8c), &__OnMousePressed__Delegate, &Parms, 0);
    }

    void delegateOnMouseRelease(UGUIComponent *Sender)
    {
        UGUIComponent_eventOnMouseRelease_Parms Parms;
        Parms.Sender = Sender;
        ProcessDelegate(FName(0xce8f), &__OnMouseRelease__Delegate, &Parms, 0);
    }

    BITFIELD delegateOnClick(UGUIComponent *Sender)
    {
        UGUIComponent_eventOnClick_Parms Parms;
        Parms.ReturnValue = 0;
        Parms.Sender = Sender;
        ProcessDelegate(FName(0xce86), &__OnClick__Delegate, &Parms, 0);
        return Parms.ReturnValue;
    }

    BITFIELD delegateOnDblClick(UGUIComponent *Sender)
    {
        UGUIComponent_eventOnDblClick_Parms Parms;
        Parms.Sender = Sender;
        Parms.ReturnValue = 0;
        ProcessDelegate(FName(0xce88), &__OnDblClick__Delegate, &Parms, 0);
        return Parms.ReturnValue;
    }

    BITFIELD delegateOnCapturedMouseMove(FLOAT deltaX, FLOAT deltaY);

    __declspec(noinline) BITFIELD delegateOnKeyEvent(BYTE &Key, BYTE &State, FLOAT delta)
    {
        UGUIComponent_eventOnKeyEvent_Parms Parms;
        Parms.Key = Key;
        Parms.State = State;
        Parms.delta = delta;
        Parms.ReturnValue = 0;
        ProcessDelegate(FName(GUI_OnKeyEvent), &__OnKeyEvent__Delegate, &Parms, 0);
        Key = Parms.Key;
        State = Parms.State;
        return Parms.ReturnValue;
    }

    BITFIELD delegateOnKeyType(BYTE &Key, const FString &Unicode)
    {
        UGUIComponent_eventOnKeyType_Parms Parms;
        Parms.Key = Key;
        Parms.Unicode = Unicode;
        Parms.ReturnValue = 0;
        ProcessDelegate(FName(0xce93), &__OnKeyType__Delegate, &Parms, 0);
        Key = Parms.Key;
        return Parms.ReturnValue;
    }

    BITFIELD eventNextPage()
    {
        UGUIComponent_eventNextPage_Parms Parms;
        Parms.ReturnValue = 0;
        ProcessEvent(FindFunctionChecked(FName(GUI_NextPage), 0), &Parms, 0);
        return Parms.ReturnValue;
    }

    BITFIELD eventPrevPage()
    {
        UGUIComponent_eventPrevPage_Parms Parms;
        Parms.ReturnValue = 0;
        ProcessEvent(FindFunctionChecked(FName(GUI_PrevPage), 0), &Parms, 0);
        return Parms.ReturnValue;
    }

    BITFIELD eventNextControl(UGUIComponent *Sender)
    {
        UGUIComponent_eventNextControl_Parms Parms;
        Parms.Sender = Sender;
        Parms.ReturnValue = 0;
        ProcessEvent(FindFunctionChecked(FName(GUI_NextControl), 0), &Parms, 0);
        return Parms.ReturnValue;
    }

    BITFIELD eventPrevControl(UGUIComponent *Sender)
    {
        UGUIComponent_eventPrevControl_Parms Parms;
        Parms.Sender = Sender;
        Parms.ReturnValue = 0;
        ProcessEvent(FindFunctionChecked(FName(GUI_PrevControl), 0), &Parms, 0);
        return Parms.ReturnValue;
    }
};

class UGUIMultiComponent : public UGUIComponent
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UGUIPage : public UGUIMultiComponent
{
public:
    BYTE unk_178[0x24];
    UGUIComponent *FocusedControl; // +0x19c

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T>
T *Cast(UObject *Src)
{
    if (Src)
    {
        for (UClass *TempClass = Src->Class; TempClass; TempClass = TempClass->SuperField)
        {
            if (TempClass == T::StaticClass())
                return (T *)Src;
        }
    }
    return 0;
}

// RVA 0x159320: UGUIComponent::MousePressed
UBOOL UGUIComponent::MousePressed(UBOOL IsRepeat)
{
    eventSetFocus(0);
    eventMenuStateChange(MSAT_Pressed);
    delegateOnMousePressed(this, IsRepeat);
    if (bRepeatClick)
    {
        Controller->PlayInterfaceSound(OnClickSound);
        delegateOnClick(this);
    }
    return 1;
}

// RVA 0x1593f0: UGUIComponent::MouseReleased
UBOOL UGUIComponent::MouseReleased()
{
    if (MenuState == MSAT_Disabled)
        return 1;

    if (!bRequireReleaseClick && !PerformHitTest(Controller->MouseX, Controller->MouseY))
    {
        if (MenuOwner && Cast<UGUIPage>(MenuOwner) && Cast<UGUIPage>(MenuOwner)->FocusedControl == this)
            eventMenuStateChange(MSAT_Focused);
        else
            eventMenuStateChange(MSAT_Blurry);
    }
    else
    {
        if (bNeverFocus)
            eventMenuStateChange(MSAT_Watched);
        else
            eventSetFocus(0);

        if (!bRepeatClick)
        {
            Controller->PlayInterfaceSound(OnClickSound);

            if (__OnDblClick__Delegate.Object && !__OnDblClick__Delegate.Object->IsPendingKill() &&
                appSeconds() < Controller->DblClickWindow + MouseReleased_LastClickTime &&
                Controller->LastClickX == Controller->MouseX &&
                Controller->LastClickY == Controller->MouseY)
            {
                delegateOnDblClick(this);
                Controller->LastClickX = -1;
                Controller->LastClickY = -1;
                MouseReleased_LastClickTime = 0.0;
            }
            else
            {
                delegateOnClick(this);
                Controller->LastClickX = Controller->MouseX;
                Controller->LastClickY = Controller->MouseY;
                MouseReleased_LastClickTime = appSeconds();
            }
        }
    }

    delegateOnMouseRelease(this);
    Controller->SetMoveTarget(0, 0);
    return 1;
}

// RVA 0x1595b0: UGUIComponent::MouseMove
UBOOL UGUIComponent::MouseMove(INT Xdelta, INT Ydelta)
{
    if (MenuState == MSAT_Pressed && bCaptureMouse)
        return delegateOnCapturedMouseMove((FLOAT)Xdelta, (FLOAT)Ydelta);
    return 0;
}

// RVA 0x1595e0: UGUIComponent::NativeKeyEvent
UBOOL UGUIComponent::NativeKeyEvent(BYTE &iKey, BYTE &State, FLOAT Delta)
{
    if (WinTop == 0.f)
        WinTop = ActualTop();
    if (WinHeight == 0.f)
        WinHeight = ActualHeight();
    if (WinWidth == 0.f)
        WinWidth = ActualWidth();
    if (WinLeft == 0.f)
        WinLeft = ActualLeft();

    if (iKey == IK_Tab && Controller->CtrlPressed && (State == IST_Press || State == IST_Repeat))
    {
        if (Controller->ShiftPressed)
        {
            if (eventPrevPage())
                return 1;
        }
        else
        {
            if (eventNextPage())
                return 1;
        }
    }

    return delegateOnKeyEvent(iKey, State, Delta);
}

// RVA 0x1596c0: UGUIComponent::NativeKeyType
UBOOL UGUIComponent::NativeKeyType(BYTE &iKey, TCHAR Unicode)
{
    if (iKey == IK_Tab && !bCaptureTabs)
    {
        if (Controller->ShiftPressed)
        {
            eventPrevControl(0);
            return 1;
        }
        else
        {
            if (!IsA(UGUIMultiComponent::StaticClass()))
                eventNextControl(0);
            return 1;
        }
    }

    return delegateOnKeyType(iKey, FString::Printf(GFormatChar, Unicode));
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

void Driver_0134(UGUIComponent *C, UBOOL IsRepeat, INT X, INT Y, BYTE &Key, BYTE &State, FLOAT Delta, TCHAR Unicode)
{
    Escape(&MouseReleased_LastClickTime);
    Escape(&UGUIMultiComponent::PrivateStaticClass);
    Escape(&UGUIPage::PrivateStaticClass);
    Escape((void *)GFormatChar);
    C->UGUIComponent::MousePressed(IsRepeat);
    C->UGUIComponent::MouseReleased();
    C->UGUIComponent::MouseMove(X, Y);
    C->UGUIComponent::NativeKeyEvent(Key, State, Delta);
    C->UGUIComponent::NativeKeyType(Key, Unicode);
}
