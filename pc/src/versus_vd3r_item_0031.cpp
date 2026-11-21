// Work item 0031 (LTCG retry): Versus RVA 0x6ce0 (destructor), 0x6d90
// (constructor) and 0x6f50 (OK handler) of the launcher options dialog
// (vtable 0x10c0e400) that toggles " -nosound", " -defaultres", the .ini
// reset, " -nommx -nokni -nok6" and " -nojoy", then ShellExecutes the game.
// Class names are neutral. Base and member classes follow work items 0017,
// 0028 and 0032 (dialog base: ctor 0x6530 / dtor 0x64d0; check box base:
// ctor 0x4ed0 / dtor 0x4e70). All three units were link-time optimised.
// Status (try_ltcg.py, /O2 /Gy /GX, roots Driver_6ce0 Driver_6d90
// Driver_6f50 Driver_6530 Driver_64d0): 0x6d90 and 0x6f50 MATCH. 0x6ce0
// links byte-identical to retail, but the tool flags the devirtualised
// `call [vtable+0x14]` (ConditionalDestroy) because it compares our vtable
// slot contents with retail's, so it never prints MATCH.
// 0x6f50 keeps an EBP frame and ends with `lea esp,[ebp-0x3c]` because the
// ShellExecute call is UE2's TCHAR_CALL_OS with a TCHAR_TO_ANSI (alloca)
// branch that folds away in this Unicode-only build.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef DWORD UBOOL;
typedef void *HWND;
typedef long LRESULT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef void *HINSTANCE;
#define BM_GETCHECK 0x00F0
#define BM_SETCHECK 0x00F1
#define BST_CHECKED 1
#define SW_SHOWNORMAL 1
// UE2 Window.h reaches these through pointers chosen at startup (retail
// 0x10c74c4c and 0x10c74bd8); declared here as imports, which compile to
// the same indirect calls.
extern "C" __declspec(dllimport) LRESULT __stdcall SendMessageX(HWND, unsigned int, WPARAM, LPARAM);
extern "C" __declspec(dllimport) HINSTANCE __stdcall ShellExecuteX(HWND, const TCHAR *, const TCHAR *, const TCHAR *, const TCHAR *, INT);
extern "C" __declspec(dllimport) int __stdcall EndDialog(HWND, INT);


enum EFindName { FNAME_Find, FNAME_Add };

class FName
{
public:
    INT Index;
    FName(const TCHAR *Name, EFindName FindType);   // RVA 0x1ff70
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);
};

class UnnamedObject;
// TArray<UnnamedObject*>::RemoveItem (RVA 0x10bd60).
class UnnamedObjectArray : public FArray
{
public:
    INT RemoveItem(UnnamedObject *const &Item);
};

// Root object type with vtable 0x10c0f458; destructor 0x10b146b0.
class UnnamedObject
{
public:
    virtual void Slot0();
    virtual ~UnnamedObject();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Destroy();

    DWORD Field4;
    DWORD Field8;
    WORD Index;
    WORD NextIndex;
    DWORD Flags;
    UnnamedObject *Owner;
    DWORD Field18;
    DWORD Field1C;
    UnnamedObjectArray Children;
    DWORD Field2C[3];
    DWORD Field38;

    UnnamedObject() {}
    UnnamedObject(UnnamedObject *InOwner, DWORD InField8, WORD InIndex)
        : Field4(0), Field8(InField8), Index(InIndex), NextIndex(0x2000), Flags(Flags & ~3), Owner(InOwner),
          Field18(0), Field1C(0), Field38(0)
    {
    }
    void ConditionalDestroy()
    {
        if (!(Flags & 1))
        {
            Flags |= 1;
            Destroy();
        }
    }
};

// Callback object with vtable 0x10c0f060 (Execute at 0x4c70).
class UnnamedDelegate
{
public:
    UnnamedObject *Object;
    void (UnnamedObject::*Function)();
    UnnamedDelegate() : Object(0), Function(0) {}
    UnnamedDelegate(UnnamedObject *InObject, void (UnnamedObject::*InFunction)())
        : Object(InObject), Function(InFunction) {}
    virtual void Execute()
    {
        if (Object)
            (Object->*Function)();
    }
};

// vtable 0x10c0f280: constructor 0x4cd0, destructor 0x10b15970.
class UnnamedBase_15970 : public UnnamedObject
{
public:
    DWORD Name;
    UnnamedBase_15970(UnnamedObject *InOwner, INT InIndex, DWORD InName);
    ~UnnamedBase_15970();
};

UnnamedBase_15970::UnnamedBase_15970(UnnamedObject *InOwner, INT InIndex, DWORD InName)
    : UnnamedObject(InOwner, 0, 0), Name(InName)
{
    Index = (WORD)(InIndex ? InIndex : InOwner->NextIndex++);
    FArray &Array = Owner->Children;
    ((UnnamedObject **)Array.Data)[Array.Add(1, 4)] = this;
}

extern DWORD GName_c91644;  // default name for 0x4ed0

// vtable 0x10c0f368: constructor 0x4ed0, destructor 0x4e70.
class UnnamedBase_4e70 : public UnnamedBase_15970
{
public:
    UnnamedDelegate Delegate40;
    UnnamedDelegate Delegate4C;
    UnnamedDelegate Delegate58;
    UnnamedDelegate Delegate64;
    UnnamedDelegate Delegate70;
    UnnamedDelegate Delegate7C;
    DWORD Field88;
    DWORD Field8C;
    DWORD Field90;
    UnnamedBase_4e70(UnnamedObject *InOwner, INT InIndex, UnnamedDelegate InDelegate, DWORD InName = 0);
    ~UnnamedBase_4e70();
    HWND GetHwnd() { return (HWND)Field4; }
    UBOOL IsChecked() { return SendMessageX(GetHwnd(), BM_GETCHECK, 0, 0) == BST_CHECKED; }
};

UnnamedBase_4e70::UnnamedBase_4e70(UnnamedObject *InOwner, INT InIndex, UnnamedDelegate InDelegate, DWORD InName)
    : UnnamedBase_15970(InOwner, InIndex, InName ? InName : GName_c91644), Delegate40(InDelegate), Field8C(0)
{
}

// RVA 0x215970
UnnamedBase_15970::~UnnamedBase_15970()
{
    if (Owner)
        Owner->Children.RemoveItem(this);
}

// RVA 0x4e70
UnnamedBase_4e70::~UnnamedBase_4e70()
{
    ConditionalDestroy();
}

// vtable 0x10c0e828, destructor 0x4f90 (size 0x9c).
class UnnamedButton_4f90 : public UnnamedBase_4e70
{
public:
    DWORD Field90;
    DWORD Field94;
    DWORD Field98;
    UnnamedButton_4f90(UnnamedObject *InOwner, INT InIndex, UnnamedDelegate InDelegate)
        : UnnamedBase_4e70(InOwner, InIndex, InDelegate), Field94(0), Field98(5) {}
    ~UnnamedButton_4f90();
};

UnnamedButton_4f90::~UnnamedButton_4f90()
{
    ConditionalDestroy();
}

// Dialog base: vtable 0x10c0f068, constructor 0x6530, destructor 0x64d0.
class UnnamedDialogBase_64d0 : public UnnamedObject
{
public:
    UnnamedObject *OwnerWindow3C;
    UnnamedDialogBase_64d0(const TCHAR *InName, UnnamedObject *InOwner, WORD InIndex);
    ~UnnamedDialogBase_64d0();
};

__declspec(noinline) UnnamedDialogBase_64d0::UnnamedDialogBase_64d0(const TCHAR *InName, UnnamedObject *InOwner, WORD InIndex)
    : UnnamedObject(InOwner, FName(InName, FNAME_Add).Index, InIndex), OwnerWindow3C(InOwner)
{
}

UnnamedDialogBase_64d0::~UnnamedDialogBase_64d0()
{
    ConditionalDestroy();
}

#define SLOTS10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
    virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); \
    virtual void p##8(); virtual void p##9();

// The window that owns the dialog; slot 60 (vtable +0xf0) takes the next dialog.
class UnnamedOwnerWindow : public UnnamedObject
{
public:
    SLOTS10(SlotA) SLOTS10(SlotB) SLOTS10(SlotC) SLOTS10(SlotD) SLOTS10(SlotE)
    virtual void SlotF0(); virtual void SlotF1(); virtual void SlotF2(); virtual void SlotF3();
    virtual void SetDialog(UnnamedObject *Dialog);   // slot 60
};

extern const TCHAR DialogName_6d90[];   // retail 0x10c10618

class FString : public FArray
{
public:
    FString() {}
    FString(const TCHAR *In);                       // RVA 0x46c0
    ~FString();                                     // RVA 0x48b0
    FString &operator+=(const TCHAR *Str);          // RVA 0x4930
    FString operator+(const TCHAR *Str) const;      // RVA 0x4990
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

class FConfigCache
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Flush(const TCHAR *Filename, INT A, INT B);   // slot 5
};
extern FConfigCache *GConfig;       // retail 0x10c71ab4

const TCHAR *appPackage();          // RVA 0xe6d0
extern void *hInstance;                                     // retail 0x10c78b50
extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameX(void *, TCHAR *, unsigned long);  // 0x10c74b98
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern const TCHAR *const PATH_SEPARATOR;                   // retail 0x10c71704
extern TCHAR appBaseDir_Result[256];                        // local static, retail 0x10ccb238

// RVA 0xe5e0: UE2 appBaseDir.
__declspec(noinline) const TCHAR *appBaseDir()
{
    if (!appBaseDir_Result[0])
    {
        GetModuleFileNameX(hInstance, appBaseDir_Result, 256);
        INT i;
        for (i = (INT)wcslen(appBaseDir_Result) - 1; i > 0; i--)
            if (appBaseDir_Result[i - 1] == PATH_SEPARATOR[0] || appBaseDir_Result[i - 1] == '/')
                break;
        appBaseDir_Result[i] = 0;
    }
    return appBaseDir_Result;
}
extern const TCHAR LauncherGameExe[];   // retail 0x10c97558
extern const TCHAR Str_NoSound[];       // L" -nosound", 0x10c105f8
extern const TCHAR Str_DefaultRes[];    // L" -defaultres", 0x10c105dc
extern const TCHAR Str_Ini[];           // L".ini", 0x10c108f4
extern const TCHAR Str_NoMMX[];         // L" -nommx -nokni -nok6", 0x10c105b0
extern const TCHAR Str_NoJoy[];         // L" -nojoy", 0x10c105a0
extern const TCHAR Str_Open[];          // L"open", 0x10c10594

// Check box control: the 0x4ed0/0x4e70 class used directly (size 0x94).
typedef UnnamedBase_4e70 UnnamedCheckBox;

// Dialog with vtable 0x10c0e400, size 0x328.
class UnnamedDialog_6d90 : public UnnamedDialogBase_64d0
{
public:
    UnnamedObject *OwnerWindow;     // +0x40
    UnnamedCheckBox NoSoundCheck;   // +0x44
    UnnamedCheckBox DefaultResCheck;// +0xd8
    UnnamedCheckBox IniCheck;       // +0x16c
    UnnamedCheckBox NoMMXCheck;     // +0x200
    UnnamedCheckBox NoJoyCheck;     // +0x294
    UnnamedDialog_6d90(UnnamedObject *InOwner);
    ~UnnamedDialog_6d90();
    // Virtual slots 6..61 (vtable 0x10c0e400); only OnInitDialog (slot 37,
    // RVA 0x6ed0) and OnOk (slot 61, RVA 0x6f50) are identified.
    SLOTS10(SlotA) SLOTS10(SlotB) SLOTS10(SlotC) virtual void SlotD0();   // slots 6..36
    virtual void OnInitDialog();                                        // slot 37
    SLOTS10(SlotE) SLOTS10(SlotF) virtual void SlotG0(); virtual void SlotG1();
    virtual void SlotG2();                                              // slots 38..60
    virtual INT OnOk();
};

// RVA 0x6d90
UnnamedDialog_6d90::UnnamedDialog_6d90(UnnamedObject *InOwner)
    : UnnamedDialogBase_64d0(DialogName_6d90, InOwner, 0x7e5), OwnerWindow(InOwner),
      NoSoundCheck(this, 0x454, UnnamedDelegate()), DefaultResCheck(this, 0x457, UnnamedDelegate()),
      IniCheck(this, 0x459, UnnamedDelegate()), NoMMXCheck(this, 0x45a, UnnamedDelegate()),
      NoJoyCheck(this, 0x45b, UnnamedDelegate())
{
}

// RVA 0x6ce0
UnnamedDialog_6d90::~UnnamedDialog_6d90()
{
    ConditionalDestroy();
}

extern "C" void *__cdecl _alloca(unsigned int);
#pragma intrinsic(_alloca)
typedef char ANSICHAR;
const INT GUnicodeOS = 1;   // Unicode-only build: the ANSI branches fold away
INT winGetSizeANSI(const TCHAR *Str);
ANSICHAR *winToANSI(ANSICHAR *ACh, const TCHAR *InUCh, INT Count);
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR *)_alloca(winGetSizeANSI(str)), str, winGetSizeANSI(str))
#define TCHAR_CALL_OS(funcW, funcA) (GUnicodeOS ? (funcW) : (funcA))
extern "C" __declspec(dllimport) HINSTANCE __stdcall ShellExecuteA(HWND, const ANSICHAR *, const ANSICHAR *, const ANSICHAR *, const ANSICHAR *, INT);
// RVA 0x6f50
INT UnnamedDialog_6d90::OnOk()
{
    FString Params;
    if (NoSoundCheck.IsChecked())
        Params += Str_NoSound;
    if (DefaultResCheck.IsChecked())
        Params += Str_DefaultRes;
    if (IniCheck.IsChecked())
        GConfig->Flush(*(FString(appPackage()) + Str_Ini), 0, 0);
    if (NoMMXCheck.IsChecked())
        Params += Str_NoMMX;
    if (NoJoyCheck.IsChecked())
        Params += Str_NoJoy;
    TCHAR_CALL_OS(ShellExecuteX(0, Str_Open, LauncherGameExe, *Params, appBaseDir(), SW_SHOWNORMAL),
                  ShellExecuteA(0, "open", TCHAR_TO_ANSI(LauncherGameExe), TCHAR_TO_ANSI(*Params), TCHAR_TO_ANSI(appBaseDir()), SW_SHOWNORMAL));
    UnnamedObject *Owner = OwnerWindow;
    EndDialog((HWND)Owner->Field4, 0);
    return 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Memory) { return Memory; }
void Driver_6ce0(UnnamedDialog_6d90 *Object)
{
    Object->UnnamedDialog_6d90::~UnnamedDialog_6d90();
}
UnnamedDialog_6d90 *Driver_6d90(void *Memory, UnnamedObject *Owner)
{
    Escape(&GName_c91644);
    Escape(&GMalloc);
    return new (Memory) UnnamedDialog_6d90(Owner);
}
INT Driver_6f50(UnnamedDialog_6d90 *Object)
{
    Escape(&GConfig);
    return Object->OnOk();
}
// Stand-ins for the many retail dialogs built on the 0x6530 base.
void Driver_6530(void **Memory, const TCHAR *Name, UnnamedObject *Owner)
{
    new (Memory[0]) UnnamedDialogBase_64d0(Name, Owner, 1);
    new (Memory[1]) UnnamedDialogBase_64d0(Name, Owner, 2);
    new (Memory[2]) UnnamedDialogBase_64d0(Name, Owner, 3);
    new (Memory[3]) UnnamedDialogBase_64d0(Name, Owner, 4);
    new (Memory[4]) UnnamedDialogBase_64d0(Name, Owner, 5);
    new (Memory[5]) UnnamedDialogBase_64d0(Name, Owner, 6);
}
// Stand-ins for the other retail dialogs destroyed through the 0x64d0 base.
class Driver_DialogA : public UnnamedDialogBase_64d0
{
public:
    Driver_DialogA(UnnamedObject *InOwner) : UnnamedDialogBase_64d0(DialogName_6d90, InOwner, 0x7e4) {}
    ~Driver_DialogA() { ConditionalDestroy(); }
};
class Driver_DialogB : public UnnamedDialogBase_64d0
{
public:
    Driver_DialogB(UnnamedObject *InOwner) : UnnamedDialogBase_64d0(DialogName_6d90, InOwner, 0x7e3) {}
    ~Driver_DialogB() { ConditionalDestroy(); }
};
void Driver_64d0(void **Memory, UnnamedObject *Owner)
{
    new (Memory[0]) Driver_DialogA(Owner);
    new (Memory[1]) Driver_DialogB(Owner);
    ((Driver_DialogA *)Memory[2])->Driver_DialogA::~Driver_DialogA();
    ((Driver_DialogB *)Memory[3])->Driver_DialogB::~Driver_DialogB();
}
