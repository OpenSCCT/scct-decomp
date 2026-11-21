// w4_item_0123.cpp -- UGUIController input, sound, and EAX status methods
// Versus RVA 0x156dc0-0x156f9f:
//   0x156dc0 UGUIController::MousePressed
//   0x156e00 UGUIController::MouseReleased
//   0x156e20 UGUIController::PlayInterfaceSound
//   0x156e70 UGUIController::PlaySound
//   0x156ed0 UGUIController::execGetEAXStatus
//   0x156f20 UGUIController::execSetEAXStatus

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

enum EName {
    NAME_None = 0
};

enum EClickSound {
    CS_None  = 0,
    CS_Click = 1,
    CS_Edit  = 2,
    CS_Up    = 3,
    CS_Down  = 4
};

struct FVector {
    FLOAT X, Y, Z;
};

struct FGuid;
struct FFrame;
class UClass;
class UStruct;
class USound;
class ULevel;
class UEngine;
class UViewport;
class UInteractionMaster;
class UAudioSubsystem;
class AActor;
class APlayerController;
class UGUIComponent;
class UGUIPage;

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
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
    virtual void VirtualSlot5();
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

    INT     Index;
    BYTE    unk_8[0x1c];
    UClass *Class;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];              // 0x10c819d8

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    inline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(Var) UBOOL Var = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH         Stack.Code++

class USubsystem : public UObject, public FExec {
public:
    virtual ~USubsystem();
    virtual void VirtualSlot22();
};

class UAudioSubsystem : public USubsystem {
public:
    virtual ~UAudioSubsystem();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual UBOOL PlaySound(AActor *Actor, INT Id, USound *Sound, const FVector &Location,
                            FLOAT Volume, FLOAT Radius, FLOAT Pitch, INT Flags,
                            FLOAT FadeDuration, FLOAT Priority, INT Unknown);
};

class UEngine : public USubsystem {
public:
    BYTE             unk_2c[0x8];
    UAudioSubsystem *Audio; // 0x34
};

class ULevel : public UObject {
public:
    BYTE     unk_28[0xc8];
    UEngine *Engine; // 0xf0
};

class AActor : public UObject {
public:
    BYTE    unk_28[0x17c];
    ULevel *XLevel; // 0x1a4
};

class APlayerController : public AActor {
public:
};

class UViewport : public UObject {
public:
    BYTE               unk_28[0x8];
    APlayerController *Actor; // 0x30
};

class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual UBOOL MousePressed(UBOOL IsRepeat); // slot 34 (+0x88)
    virtual UBOOL MouseReleased();              // slot 35 (+0x8c)
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();               // slot 42 (+0xa8)
    virtual void VirtualSlot43();
};

class UGUIPage : public UGUIComponent {
public:
    virtual ~UGUIPage();
};

class UInteractions : public UObject {
public:
    virtual ~UInteractions();
};

class UInteraction : public UInteractions {
public:
    virtual ~UInteraction();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();

    UInteractionMaster *Master;        // 0x28
    UViewport          *ViewportOwner; // 0x2c
    DWORD               unk_30;        // 0x30
};

class UGUIController : public UInteraction {
public:
    virtual ~UGUIController();
    virtual void ChangeFocus(UGUIComponent *Who); // slot 28 (+0x70)
    virtual UBOOL MousePressed(UBOOL IsRepeat);   // slot 29 (+0x74)
    virtual UBOOL MouseReleased();                // slot 30 (+0x78)

    BYTE           unk_34[0xc4c];
    UGUIPage      *ActivePage;            // 0xc80
    BYTE           unk_c84[0x90];
    UGUIComponent *FocusedControl;        // 0xd14
    BYTE           unk_d18[0x24];
    USound        *ClickSound;            // 0xd3c
    USound        *EditSound;             // 0xd40
    USound        *UpSound;               // 0xd44
    USound        *DownSound;             // 0xd48
    BYTE           unk_d4c[0x4];
    DWORD          unk_d50 : 1;           // 0xd50 bit 0
    DWORD          bIgnoreUntilPress : 1; // 0xd50 bit 1

    // Retail kept PlayInterfaceSound out of line across 5 callers.
    __declspec(noinline) void PlayInterfaceSound(BYTE SoundType);
    void PlaySound(USound *Sound);

    DECLARE_NATIVE(execGetEAXStatus)
    DECLARE_NATIVE(execSetEAXStatus)
};

extern FOutputDevice *GLog;          // 0x10c71aa4
extern const FVector &GMath_Zero;    // 0x10ccacc0

// Strings kept in writable .data in retail VC7.0 output.
extern const TCHAR StrGetEAXStatus[];      // 0x10c462ac L"GETEAXSTATUS"
extern const TCHAR StrSetEAXStatusTrue[];  // 0x10c462c8 L"SETEAXSTATUS TRUE"
extern const TCHAR StrSetEAXStatusFalse[]; // 0x10c462ec L"SETEAXSTATUS FALSE"

// UGUIController::MousePressed (RVA 0x156dc0)
UBOOL UGUIController::MousePressed(UBOOL IsRepeat)
{
    bIgnoreUntilPress = 0;

    if (FocusedControl && FocusedControl != ActivePage)
        return FocusedControl->MousePressed(IsRepeat);

    if (ActivePage)
        ActivePage->VirtualSlot42();

    return 0;
}

// UGUIController::MouseReleased (RVA 0x156e00)
UBOOL UGUIController::MouseReleased()
{
    if (!bIgnoreUntilPress && FocusedControl)
        return FocusedControl->MouseReleased();

    return 0;
}

// UGUIController::PlayInterfaceSound (RVA 0x156e20)
void UGUIController::PlayInterfaceSound(BYTE SoundType)
{
    USound *Sound = 0;
    switch (SoundType) {
    case CS_Click:
        Sound = ClickSound;
        break;
    case CS_Edit:
        Sound = EditSound;
        break;
    case CS_Up:
        Sound = UpSound;
        break;
    case CS_Down:
        Sound = DownSound;
        break;
    default:
        return;
    }

    if (Sound)
        PlaySound(Sound);
}

// UGUIController::PlaySound (RVA 0x156e70)
void UGUIController::PlaySound(USound *Sound)
{
    if (ViewportOwner->Actor && ViewportOwner->Actor->XLevel &&
        ViewportOwner->Actor->XLevel->Engine && ViewportOwner->Actor->XLevel->Engine->Audio) {
        ViewportOwner->Actor->XLevel->Engine->Audio->PlaySound(
            0, 0, Sound, GMath_Zero, 1.0f, 4096.0f, 1.0f, 0x10, 0.0f, 0.0f, -1);
    }
}

// UGUIController::execGetEAXStatus (RVA 0x156ed0)
void UGUIController::execGetEAXStatus(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    if (ViewportOwner->Actor && ViewportOwner->Actor->XLevel &&
        ViewportOwner->Actor->XLevel->Engine && ViewportOwner->Actor->XLevel->Engine->Audio) {
        *(UBOOL *)Result =
            ViewportOwner->Actor->XLevel->Engine->Audio->Exec(StrGetEAXStatus, *GLog);
    }
}

// UGUIController::execSetEAXStatus (RVA 0x156f20)
void UGUIController::execSetEAXStatus(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(bEnable);
    P_FINISH;

    if (ViewportOwner->Actor && ViewportOwner->Actor->XLevel &&
        ViewportOwner->Actor->XLevel->Engine && ViewportOwner->Actor->XLevel->Engine->Audio) {
        if (bEnable)
            ViewportOwner->Actor->XLevel->Engine->Audio->Exec(StrSetEAXStatusTrue, *GLog);
        else
            ViewportOwner->Actor->XLevel->Engine->Audio->Exec(StrSetEAXStatusFalse, *GLog);
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(const void *);
void Driver_156e20(UGUIController *C, BYTE SoundType, USound *Sound)
{
    Escape(&GMath_Zero);
    C->PlayInterfaceSound(SoundType);
    C->PlaySound(Sound);
}
