// Work item 0016 (LTCG retry): Versus RVA 0x5470 (destructor) and 0x54f0
// (constructor) of an unidentified UObject-style class. The class registers
// the "UnrealNidMessage" window message, so it is the tray-icon
// (Shell_NotifyIcon) helper. Names are neutral where no label identifies them.
// Hierarchy (from the destructor chain): UnnamedObject (dtor 0x10b146b0)
// <- UnnamedClass_5150 (dtor 0x5150) <- UnnamedBase_52b0 (dtor 0x52b0, ctor
// 0x5330, second vtable at +0x3c, member at +0x40 with dtor 0x5200)
// <- UnnamedNotifyIcon_5470. Each destructor runs the DECLARE_CLASS-style
// ConditionalDestroy check on the flags at +0x10 before unwinding.
// Vtable slot 1 holds each class's scalar deleting destructor (0x5570 here);
// it is declared as a plain virtual, as in the sibling units, because a C++
// virtual destructor stops the linker giving the destructor its stack-based
// convention. Retail calls Destroy (slot 5) through memory at the vtable slot
// (call [vftable+0x14]); as in the sibling units, Destroy is declared
// dllimport to reproduce that indirect call. (An ordinary virtual called from
// an inline ConditionalDestroy gives the same bytes, but the verifier cannot
// bind an address inside the vtable.)
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef int INT;

// Retail calls RegisterWindowMessage through a function pointer held in
// writable data (0x10c74c40), not through the import table.
extern UINT (__stdcall* RegisterWindowMessageX)(const TCHAR* lpString);

class FString
{
public:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const TCHAR* In);   // RVA 0x46c0
    ~FString();                 // RVA 0x48b0
};

class FName
{
public:
    INT Index;
};

class UnnamedObject
{
public:
    virtual void Slot0();
    virtual void* DeletingDestructor(unsigned int Flags);  // slot 1
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    __declspec(dllimport) virtual void Destroy();  // slot 5
    DWORD Field4;
    FName Name;                 // +0x08
    DWORD FieldC;
    DWORD Flags;                // +0x10
    UnnamedObject* Outer;       // +0x14
    BYTE Pad18[0x3c - 0x18];

    UnnamedObject(UnnamedObject* InOuter, FName InName)
        : Name(InName), Outer(InOuter)
    {
    }
    ~UnnamedObject();           // RVA 0x10b146b0
};

class UnnamedClass_5150 : public UnnamedObject
{
public:
    UnnamedClass_5150(UnnamedObject* InOuter, FName InName)
        : UnnamedObject(InOuter, InName)
    {
    }
    ~UnnamedClass_5150();  // RVA 0x5150
};

class UnnamedInterface_52b0
{
public:
    virtual void InterfaceSlot0();
};

class UnnamedMember_5200
{
public:
    virtual void Slot0();
    UnnamedMember_5200();
    ~UnnamedMember_5200();         // RVA 0x5200
    BYTE Pad4[0x5c - 4];
};

class UnnamedBase_52b0 : public UnnamedClass_5150, public UnnamedInterface_52b0
{
public:
    UnnamedMember_5200 Member;     // +0x40
    DWORD Field9c;                 // +0x9c
    DWORD FieldA0;                 // +0xa0
    DWORD FieldA4;                 // +0xa4
    TCHAR Text[256];               // +0xa8
    DWORD Field2a8;                // +0x2a8
    UnnamedBase_52b0(UnnamedObject* InOuter, FName InName);  // RVA 0x5330
    ~UnnamedBase_52b0();   // RVA 0x52b0
};

class UnnamedNotifyIcon_5470 : public UnnamedBase_52b0
{
public:
    UINT NidMessage;            // +0x2ac
    const TCHAR* Field2b0;      // +0x2b0
    FString Tip;                // +0x2b4

    UnnamedNotifyIcon_5470(UnnamedObject* InOuter, const TCHAR* InTip, const TCHAR* InField2b0, FName InName);
    ~UnnamedNotifyIcon_5470();
};

// RVA 0x54f0. Near miss: the body is instruction-for-instruction retail
// (including Outer passed through in ECX to the base constructor), but retail
// has an EBP frame with a `lea esp, [ebp-0x10]` epilogue that this source
// does not produce (/Oy- gives the frame but not the epilogue resync).
UnnamedNotifyIcon_5470::UnnamedNotifyIcon_5470(UnnamedObject* InOuter, const TCHAR* InTip, const TCHAR* InField2b0, FName InName)
    : UnnamedBase_52b0(InOuter, InName)
    , NidMessage(RegisterWindowMessageX(L"UnrealNidMessage"))
    , Field2b0(InField2b0)
    , Tip(InTip)
{
}

// RVA 0x5470
UnnamedNotifyIcon_5470::~UnnamedNotifyIcon_5470()
{
    if (!(Flags & 1))
    {
        Flags |= 1;
        Destroy();
    }
}

// Scaffolding for the link, not part of the unit: the base destructor and
// constructor are defined here only so the linker gives them the same
// stack-based convention retail uses.
UnnamedBase_52b0::~UnnamedBase_52b0()
{
    if (!(Flags & 1))
    {
        Flags |= 1;
        Destroy();
    }
}
// (approximation of the retail body, which is not part of this unit)
extern "C" __declspec(dllimport) TCHAR* __cdecl wcscpy(TCHAR* Dest, const TCHAR* Src);
extern const TCHAR UnnamedBase_52b0_DefaultText[];
UnnamedBase_52b0::UnnamedBase_52b0(UnnamedObject* InOuter, FName InName)
    : UnnamedClass_5150(InOuter, InName)
{
    Field4 = 0;
    FieldC = 0x20000000;
    Flags &= ~3;
    for (INT i = 0; i < 9; i++)
        ((DWORD*)Pad18)[i] = 0;
    Field9c = 0;
    FieldA0 = 0x100;
    FieldA4 = 0x40;
    Field2a8 = 0;
    wcscpy(Text, UnnamedBase_52b0_DefaultText);
}
inline void* operator new(unsigned int, void* Mem) { return Mem; }
void Driver_5470(UnnamedNotifyIcon_5470* Object)
{
    Object->UnnamedNotifyIcon_5470::~UnnamedNotifyIcon_5470();
}
UnnamedNotifyIcon_5470* Driver_54f0(void* Mem, const TCHAR* Tip, const TCHAR* F2b0, FName Name, UnnamedObject* Outer)
{
    return new(Mem) UnnamedNotifyIcon_5470(Outer, Tip, F2b0, Name);
}
