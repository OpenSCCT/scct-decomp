// Work item 0029 (LTCG retry): Versus RVA 0x65e0 / 0x66b0, launcher dialog code.
//
// The class is a WDialog (UE2 Window.h) holding four check boxes (ids 3,
// 1004, 1005, 2), a control at +0x2ac (id 1061) and a TArray at +0x2ec. It is
// itself the base of the dialog at 0x6a80/0x6b20. Its name is not recovered,
// so it is UnnamedDialog_66b0. Both functions are link-time generated: the
// object was compiled /GL and its callers pass `this` on the stack.
//
// try_ltcg.py, /O2 /Gy /GX: the constructor (0x66b0) MATCHes. The destructor
// (0x65e0) is byte-identical after binding, but the tool flags the operand of
// `call [vtable+0x14]` (inlined MaybeDestroy -> DoDestroy) as a constant that
// differs, because it compares the vtable's contents (stub pointers) with retail.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef struct HWND__ *HWND;
typedef unsigned int UINT, WPARAM;
typedef long LONG, LPARAM, LRESULT;
typedef LRESULT (__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Add(INT Count, INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    __declspec(noinline) ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
};

struct FName
{
    INT Index;
    FName(INT N) : Index(N) {}
};

class FCommandTarget
{
public:
    virtual void Unused();
};
typedef void (FCommandTarget::*TDelegate)();

class FDelegate
{
public:
    FCommandTarget *TargetObject;
    TDelegate TargetInvoke;
    FDelegate() : TargetObject(0), TargetInvoke(0) {}
    FDelegate(FCommandTarget *InTargetObject, TDelegate InTargetInvoke)
        : TargetObject(InTargetObject), TargetInvoke(InTargetInvoke) {}
    virtual void operator()() { if (TargetObject) (TargetObject->*TargetInvoke)(); }
};

class WControl;
class WWindow : public FCommandTarget
{
public:
    HWND hWnd;
    FName PersistentName;
    WORD ControlId, TopControlId;
    BITFIELD Destroyed : 1;
    BITFIELD MdiChild : 1;
    WWindow *OwnerWindow;
    void *NotifyHook;
    void *Snoop;
    TArray<WControl *> Controls;
    INT Unknown2c[3];
    INT Unknown38;

    WWindow(FName InPersistentName = FName(0), WWindow *InOwnerWindow = 0)
        : hWnd(0), PersistentName(InPersistentName), ControlId(0), TopControlId(0x2000),
          Destroyed(0), MdiChild(0), OwnerWindow(InOwnerWindow), NotifyHook(0), Snoop(0),
          Unknown38(0)
    {}
    virtual ~WWindow();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void DoDestroy();
    void MaybeDestroy()
    {
        if (!Destroyed) {
            Destroyed = 1;
            DoDestroy();
        }
    }
};

class WDialog : public WWindow
{
public:
    WDialog(FName InPersistentName, INT InDialogId, WWindow *InOwnerWindow = 0)
        : WWindow(InPersistentName, InOwnerWindow)
    {
        ControlId = InDialogId;
    }
};

class WControl : public WWindow
{
public:
    WNDPROC WindowDefWndProc;
    WControl(WWindow *InOwnerWindow, INT InId, WNDPROC InSuperProc);
};

class WButton : public WControl
{
public:
    FDelegate ClickDelegate;
    FDelegate DoubleClickDelegate;
    FDelegate PushDelegate;
    FDelegate UnPushDelegate;
    FDelegate SetFocusDelegate;
    FDelegate KillFocusDelegate;
    void *Unknown88;
    INT Unknown8c;
    INT Unknown90;
    static WNDPROC SuperProc;
    WButton(WWindow *InOwner, INT InId = 0, FDelegate InClicked = FDelegate(), WNDPROC InSuperProc = 0);
    ~WButton();
};

class WCheckBox : public WButton
{
public:
    UBOOL bChecked;
    INT Style;
    WCheckBox(WWindow *InOwner, INT InId = 0, FDelegate InClicked = FDelegate())
        : WButton(InOwner, InId, InClicked), bChecked(0), Style(5) {}
    ~WCheckBox();
};

class WLabel : public WControl
{
public:
    static WNDPROC SuperProc;
    WLabel(WWindow *InOwner, INT InId = 0) : WControl(InOwner, InId, SuperProc) {}
    ~WLabel();
};

class UnnamedDialog_66b0 : public WDialog
{
public:
    WCheckBox Check3;
    WCheckBox Check1004;
    WCheckBox Check1005;
    WCheckBox Check2;
    WLabel Label;
    TArray<INT> Items;
    INT Unknown2f8;

    UnnamedDialog_66b0()
        : WDialog(FName(0x226), 0x68),
          Check3(this, 3, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck3)),
          Check1004(this, 1004, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck1004)),
          Check1005(this, 1005, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck1005)),
          Check2(this, 2, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck2)),
          Label(this, 1061),
          Unknown2f8(0)
    {}
    ~UnnamedDialog_66b0()
    {
        MaybeDestroy();
    }
    void OnCheck3();
    void OnCheck1004();
    void OnCheck1005();
    void OnCheck2();
};

// Out-of-line callees, defined here so the link gives them their LTCG conventions.
__declspec(noinline) WControl::WControl(WWindow *InOwnerWindow, INT InId, WNDPROC InSuperProc)
    : WWindow(FName(0), InOwnerWindow), WindowDefWndProc(InSuperProc)
{
    ControlId = InId ? InId : InOwnerWindow->TopControlId++;
    OwnerWindow->Controls.AddItem(this);
}

WButton::WButton(WWindow *InOwner, INT InId, FDelegate InClicked, WNDPROC InSuperProc)
    : WControl(InOwner, InId, InSuperProc ? InSuperProc : SuperProc), ClickDelegate(InClicked),
      Unknown8c(0)
{}

WCheckBox::~WCheckBox() { MaybeDestroy(); }
WLabel::~WLabel() { MaybeDestroy(); }

// Scaffolding for the link, not part of the unit.
void Driver_66b0(void *Mem) { new (Mem) UnnamedDialog_66b0; }
void Driver_65e0(UnnamedDialog_66b0 *D) { D->UnnamedDialog_66b0::~UnnamedDialog_66b0(); }
