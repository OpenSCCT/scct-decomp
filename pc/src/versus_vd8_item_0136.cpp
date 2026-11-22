// w4_item_0136.cpp -- UGUIMultiComponent input, hit-test, and invalidation methods (Versus)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned short TCHAR;

struct FGuid;
struct FStateFrame;
class UClass;
class UFunction;

enum EName {
    NAME_None = 0,
    NAME_GUI_Delegate_ce84 = 0xce84
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
};

class UObject;

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
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray {
public:
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
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
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void ProcessDelegate(FName DelegateName, FScriptDelegate *Delegate,
                                 void *Parms, void *Result = 0);
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
    BYTE         unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0xc];
    DWORD        ObjectFlags;
    BYTE         unk_20[0x4];
    UClass      *Class;
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

enum EMenuState {
    MSAT_Blurry   = 0,
    MSAT_Watched  = 1,
    MSAT_Focused  = 2,
    MSAT_Pressed  = 3,
    MSAT_Disabled = 4
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
    virtual UBOOL NativeKeyType(BYTE &iKey, TCHAR Unicode);
    virtual UBOOL NativeKeyEvent(BYTE &iKey, BYTE &State, FLOAT Delta);
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual UBOOL SpecialHit();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();

    BYTE            unk_2c[0x4];
    BYTE            MenuState;
    BYTE            unk_31[0x3];
    FString         unk_34;
    FString         unk_40;
    BYTE            unk_4c[0x10];
    BITFIELD        unk_5c_0 : 3;
    BITFIELD        bVisible : 1;
    BYTE            unk_60[0x4];
    FString         unk_64;
    BYTE            unk_70[0xb8];
    FScriptDelegate Delegate_128;
    BYTE            unk_130[0x60];

    void delegateSlot42()
    {
        ProcessDelegate(NAME_GUI_Delegate_ce84, &Delegate_128, 0, 0);
    }
};

class UGUIMultiComponent : public UGUIComponent {
public:
    virtual ~UGUIMultiComponent();
    virtual UGUIComponent *UnderCursor(FLOAT MouseX, FLOAT MouseY);
    virtual UBOOL NativeKeyType(BYTE &iKey, TCHAR Unicode);
    virtual UBOOL NativeKeyEvent(BYTE &iKey, BYTE &State, FLOAT Delta);
    virtual UBOOL SpecialHit();
    virtual void VirtualSlot42();

    TArray<UGUIComponent *> Controls;
    UGUIComponent          *FocusedControl;
};

// UGUIMultiComponent::NativeKeyEvent (RVA 0x159b70)
UBOOL UGUIMultiComponent::NativeKeyEvent(BYTE &iKey, BYTE &State, FLOAT Delta)
{
    if (FocusedControl && FocusedControl->NativeKeyEvent(iKey, State, Delta))
        return 1;

    if (MenuState != MSAT_Disabled)
        return UGUIComponent::NativeKeyEvent(iKey, State, Delta);

    return 0;
}

// UGUIMultiComponent::NativeKeyType (RVA 0x159bd0)
UBOOL UGUIMultiComponent::NativeKeyType(BYTE &iKey, TCHAR Unicode)
{
    if (FocusedControl && FocusedControl->NativeKeyType(iKey, Unicode))
        return 1;

    if (MenuState != MSAT_Focused)
        return UGUIComponent::NativeKeyType(iKey, Unicode);

    return 0;
}

// UGUIComponent::UnderCursor (inlined into UGUIMultiComponent::UnderCursor)
UGUIComponent *UGUIComponent::UnderCursor(FLOAT MouseX, FLOAT MouseY)
{
    if (bVisible && MenuState != MSAT_Disabled && PerformHitTest((INT)MouseX, (INT)MouseY))
        return this;

    return 0;
}

// UGUIMultiComponent::UnderCursor (RVA 0x159c20)
UGUIComponent *UGUIMultiComponent::UnderCursor(FLOAT MouseX, FLOAT MouseY)
{
    UGUIComponent *t;

    if (FocusedControl) {
        t = FocusedControl->UnderCursor(MouseX, MouseY);
        if (t)
            return t;
    }

    for (INT i = Controls.Num(); i > 0; i--) {
        if (Controls(i - 1)->bVisible && Controls(i - 1)->MenuState != MSAT_Disabled) {
            t = Controls(i - 1)->UnderCursor(MouseX, MouseY);
            if (t)
                return t;
        }
    }

    return UGUIComponent::UnderCursor(MouseX, MouseY);
}

// UGUIMultiComponent::VirtualSlot42 (RVA 0x159cc0)
void UGUIMultiComponent::VirtualSlot42()
{
    delegateSlot42();
    if (FocusedControl)
        FocusedControl->VirtualSlot42();
}

// UGUIMultiComponent::SpecialHit (RVA 0x159d00)
UBOOL UGUIMultiComponent::SpecialHit()
{
    if (UGUIComponent::SpecialHit())
        return 1;

    for (INT i = 0; i < Controls.Num(); i++) {
        if (Controls(i) && Controls(i)->SpecialHit())
            return 1;
    }

    return 0;
}
