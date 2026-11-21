// w4_item_0135.cpp -- UGUIComponent mouse hit/hover and timer methods (Versus 0x159800-0x1599dd)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define RESULT_DECL void *const Result

struct FGuid;
struct FFrame;
struct FStateFrame;
class UClass;
class UProperty;
class UStruct;
class UObject;
class UGUIController;
class UGUIComponent;

enum EName {
    NAME_None     = 0,
    NAME_GUI_Timer = 0xce84
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
};

struct FScriptDelegate {
    UObject *Object;
    FName    FunctionName;
};

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
    INT AddItem(const T &Item)
    {
        INT Index = Add();
        (*this)(Index) = Item;
        return Index;
    }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
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
    virtual void VirtualSlot4();
    virtual void ProcessDelegate(FName DelegateName, FScriptDelegate *Delegate, void *Parms, void *Result = 0);
    virtual void VirtualSlot6();
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
    BYTE         unk_08[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0xc];
    DWORD        ObjectFlags;
    BYTE         unk_20[0x4];
    UClass      *Class;
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_UBOOL_OPTX(Var, Def) DWORD Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

enum eMenuState {
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4
};

class UGUIController : public UObject {
public:
    BYTE           unk_28[0xc58];
    UGUIComponent *FocusedControl;
    BYTE           unk_c84[0x48];
    INT            MouseX;
    INT            MouseY;
    BYTE           unk_cd4[0x48];
    UGUIComponent *HoverControl;
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    UGUIController *Controller;
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual UBOOL PerformHitTest(INT MouseX, INT MouseY);
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual UGUIComponent *UnderCursor(FLOAT MouseX, FLOAT MouseY);
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual UBOOL MouseHover();
    virtual void Timer();
    virtual void VirtualSlot43();

    void execSetTimer(FFrame &Stack, RESULT_DECL);

    UGUIComponent  *MenuOwner;          // 0x2c
    BYTE            MenuState;          // 0x30
    BYTE            unk_31[0x3];
    FString         unk_34;             // 0x34
    FString         unk_40;             // 0x40
    BYTE            unk_4c[0x10];
    DWORD           bFlag0 : 1;         // 0x5c
    DWORD           bFlag1 : 1;
    DWORD           bFlag2 : 1;
    DWORD           bVisible : 1;
    BYTE            unk_60[0x4];
    FString         unk_64;             // 0x64
    FLOAT           WinTop;             // 0x70
    FLOAT           WinLeft;            // 0x74
    FLOAT           WinWidth;           // 0x78
    FLOAT           WinHeight;          // 0x7c
    BYTE            unk_80[0x20];
    FLOAT           Bounds[4];          // 0xa0
    FLOAT           ClientBounds[4];    // 0xb0
    BYTE            unk_c0[0x4];
    INT             TimerIndex;         // 0xc4
    DWORD           bTimerRepeat : 1;   // 0xc8
    FLOAT           TimerCountdown;     // 0xcc
    FLOAT           TimerInterval;      // 0xd0
    BYTE            unk_d4[0x54];
    FScriptDelegate __OnTimer__Delegate; // 0x128
    BYTE            unk_130[0x60];
};

class UGUIMultiComponent : public UGUIComponent {
public:
    virtual ~UGUIMultiComponent();

    TArray<UGUIComponent *> Controls;
    BYTE                    unk_19c[0x4];
};

class UGUIPage : public UGUIMultiComponent {
public:
    virtual ~UGUIPage();

    BYTE                    unk_1a0[0x5c];
    TArray<UGUIComponent *> Timers;     // 0x1fc
};

// UGUIComponent::MouseHover (RVA 0x159800, vtable slot 41; exact method name open)
UBOOL UGUIComponent::MouseHover()
{
    if (bVisible && Controller && this != Controller->FocusedControl) {
        FLOAT X = (FLOAT)Controller->MouseX;
        if (X >= Bounds[0] && X <= Bounds[2]) {
            FLOAT Y = (FLOAT)Controller->MouseY;
            if (Y >= Bounds[1] && Y <= Bounds[3]) {
                if (Controller->HoverControl == this) {
                    Controller->HoverControl = 0;
                    return 0;
                }
                if (Controller->HoverControl == 0) {
                    Controller->HoverControl = this;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// UGUIComponent::UnderCursor (RVA 0x159890, vtable slot 32)
UGUIComponent *UGUIComponent::UnderCursor(FLOAT MouseX, FLOAT MouseY)
{
    if (bVisible && MenuState != MSAT_Disabled) {
        if (PerformHitTest((INT)MouseX, (INT)MouseY)) {
            return this;
        }
    }
    return 0;
}

// UGUIComponent::Timer (RVA 0x1598d0, vtable slot 42)
void UGUIComponent::Timer()
{
    ProcessDelegate(NAME_GUI_Timer, &__OnTimer__Delegate, 0);
}

// UGUIComponent::execSetTimer (RVA 0x1598f0)
void UGUIComponent::execSetTimer(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Interval);
    P_GET_UBOOL_OPTX(bRepeat, 0);
    P_FINISH;

    UGUIComponent *Owner = this;
    while (Owner->MenuOwner) {
        Owner = Owner->MenuOwner;
    }

    if (TimerIndex < 0 && Interval > 0.0f) {
        TimerIndex = ((UGUIPage *)Owner)->Timers.AddItem(this);
    }

    TimerInterval = Interval;
    TimerCountdown = Interval;
    bTimerRepeat = 0;
    if (Interval > 0.0f) {
        bTimerRepeat = bRepeat;
    }
}
