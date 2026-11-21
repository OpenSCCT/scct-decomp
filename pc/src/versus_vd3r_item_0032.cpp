// Work item 0032 (LTCG retry): Versus RVA 0x7130 (destructor), 0x71d0
// (constructor) and 0x7300 (button handler) of an unidentified dialog class
// with vtable 0x10c0ec08. Its third button opens the UE2 versions page
// (0x7370, written in item_0032). Names are neutral. Base and member classes
// follow work items 0017 (button class, vtable 0x10c0e828) and 0028 (dialog
// base, ctor 0x6530 / dtor 0x64d0). All three units were link-time optimised.
// Status: 0x71d0 and 0x7300 MATCH with try_ltcg.py (/O2 /Gy /GX). 0x7130 links
// to bytes identical with retail, but the tool flags the devirtualised
// `call [vtable+0x14]` (ConditionalDestroy) because it compares the contents
// of our vtable slot with retail's, so it never prints MATCH.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short WORD;

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
    FArray Children;
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
    UnnamedBase_4e70(UnnamedObject *InOwner, INT InIndex, UnnamedDelegate InDelegate, DWORD InName = 0);
    ~UnnamedBase_4e70();
};

UnnamedBase_4e70::UnnamedBase_4e70(UnnamedObject *InOwner, INT InIndex, UnnamedDelegate InDelegate, DWORD InName)
    : UnnamedBase_15970(InOwner, InIndex, InName ? InName : GName_c91644), Delegate40(InDelegate), Field8C(0)
{
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

// Retail keeps this constructor out of line (it is shared by many dialogs
// that are not in this file); noinline stands in for those other callers.
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

// Check box control: the 0x4ed0 base plus one field (size 0x94).
class UnnamedCheckBox : public UnnamedBase_4e70
{
public:
    DWORD Field90;
    UnnamedCheckBox(UnnamedObject *InOwner, INT InIndex)
        : UnnamedBase_4e70(InOwner, InIndex, UnnamedDelegate()), Field90(0) {}
    ~UnnamedCheckBox() { ConditionalDestroy(); }
};

// Dialog with vtable 0x10c0e400 (item_0031: constructor 0x6d90, destructor
// 0x6ce0, size 0x328). Only its interface matters here.
class UnnamedDialog_6d90 : public UnnamedDialogBase_64d0
{
public:
    UnnamedObject *OwnerWindow;
    UnnamedCheckBox Check44;
    UnnamedCheckBox CheckD8;
    UnnamedCheckBox Check16C;
    UnnamedCheckBox Check200;
    UnnamedCheckBox Check294;
    UnnamedDialog_6d90(UnnamedObject *InOwner);
    ~UnnamedDialog_6d90();
};

UnnamedDialog_6d90::UnnamedDialog_6d90(UnnamedObject *InOwner)
    : UnnamedDialogBase_64d0(DialogName_6d90, InOwner, 0x7e5), OwnerWindow(InOwner),
      Check44(this, 0x454), CheckD8(this, 0x457), Check16C(this, 0x458),
      Check200(this, 0x459), Check294(this, 0x45a)
{
}

UnnamedDialog_6d90::~UnnamedDialog_6d90()
{
    ConditionalDestroy();
}

extern const TCHAR DialogName_71d0[];   // retail 0x10c10544
extern const TCHAR NewTag_7300[];       // retail 0x10c109d8

// Dialog with vtable 0x10c0ec08.
class UnnamedDialog_71d0 : public UnnamedDialogBase_64d0
{
public:
    UnnamedOwnerWindow *OwnerWindow;    // +0x40
    UnnamedButton_4f90 Button44;
    UnnamedButton_4f90 ButtonE0;
    UnnamedButton_4f90 Button17C;
    UnnamedDialog_71d0(UnnamedOwnerWindow *InOwner);
    ~UnnamedDialog_71d0();
    void OnButton44();      // RVA 0x72f0
    void OnButtonE0();      // RVA 0x7300
    void OnButton17C();     // RVA 0x7370
};

// RVA 0x71d0
UnnamedDialog_71d0::UnnamedDialog_71d0(UnnamedOwnerWindow *InOwner)
    : UnnamedDialogBase_64d0(DialogName_71d0, InOwner, 0x7e4),
      OwnerWindow(InOwner),
      Button44(this, 0x454, UnnamedDelegate(this, (void (UnnamedObject::*)())&UnnamedDialog_71d0::OnButton44)),
      ButtonE0(this, 0x455, UnnamedDelegate(this, (void (UnnamedObject::*)())&UnnamedDialog_71d0::OnButtonE0)),
      Button17C(this, 0x422, UnnamedDelegate(this, (void (UnnamedObject::*)())&UnnamedDialog_71d0::OnButton17C))
{
}

// RVA 0x7130
UnnamedDialog_71d0::~UnnamedDialog_71d0()
{
    ConditionalDestroy();
}

// RVA 0x7300
void UnnamedDialog_71d0::OnButtonE0()
{
    OwnerWindow->SetDialog(new(NewTag_7300) UnnamedDialog_6d90(OwnerWindow));
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Memory) { return Memory; }
void Driver_7130(UnnamedDialog_71d0 *Object)
{
    Object->UnnamedDialog_71d0::~UnnamedDialog_71d0();
}
UnnamedDialog_71d0 *Driver_71d0(void *Memory, UnnamedOwnerWindow *Owner)
{
    Escape(&GName_c91644);
    Escape(&GMalloc);
    return new (Memory) UnnamedDialog_71d0(Owner);
}
void Driver_7300(UnnamedDialog_71d0 *Object)
{
    Escape(&GMalloc);
    Object->OnButtonE0();
}
