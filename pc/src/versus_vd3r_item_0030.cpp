// Work item 0030 (LTCG retry): Versus RVA 0x68b0, 0x6a80, 0x6b20.
//
// 0x6a80 / 0x6b20 are the destructor and constructor of the setup-wizard dialog
// whose vtable is at 0x10c0ea18. It derives from the dialog of item 0029
// (UnnamedDialog_66b0, ctor 0x66b0 / dtor 0x65e0), whose declarations are copied
// here. The class name is not recovered: UnnamedDialog_6b20.
// 0x68b0 is Unreal's InitSplash. All three were checked with try_ltcg.py, /O2 /Gy /GX.
// The wrappers GetWindowsDirectoryX etc. must be extern "C": under /GX the compiler
// then treats InitLauncherPaths as non-throwing and drops the last EH state store
// in the constructor, as retail does.
typedef unsigned short TCHAR;
typedef int BOOL, INT, INT_PTR;
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

    __declspec(noinline) UnnamedDialog_66b0()
        : WDialog(FName(0x226), 0x68),
          Check3(this, 3, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck3)),
          Check1004(this, 1004, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck1004)),
          Check1005(this, 1005, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck1005)),
          Check2(this, 2, FDelegate(this, (TDelegate)&UnnamedDialog_66b0::OnCheck2)),
          Label(this, 1061),
          Unknown2f8(0)
    {}
    __declspec(noinline) ~UnnamedDialog_66b0()
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
__declspec(noinline) WLabel::~WLabel() { MaybeDestroy(); }


typedef void *HGDIOBJ;
typedef void *HBITMAP;
extern "C" __declspec(dllimport) int __stdcall DeleteObject(HGDIOBJ ho);

typedef void *HINSTANCE;
typedef INT_PTR (__stdcall *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
HBITMAP LoadFileToBitmap(const TCHAR *Filename, INT &SizeX, INT &SizeY);

// Unreal Window.h bitmap holder.
class FWindowsBitmap
{
public:
    INT SizeX, SizeY, Keep;
    HBITMAP hBitmap;
    FWindowsBitmap(UBOOL InKeep = 0) : SizeX(0), SizeY(0), Keep(InKeep), hBitmap(0) {}
    ~FWindowsBitmap()
    {
        if (hBitmap && !Keep)
            DeleteObject(hBitmap);
    }
    UBOOL LoadFile(const TCHAR *Filename)
    {
        if (hBitmap)
            DeleteObject(hBitmap);
        hBitmap = LoadFileToBitmap(Filename, SizeX, SizeY);
        return hBitmap != 0;
    }
    HBITMAP GetBitmapHandle() { return hBitmap; }
};

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();                                                  // RVA 0x48b0
};

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
inline INT appStrlen(const TCHAR *S) { return wcslen(S); }
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }
inline TCHAR *appStrcpy(TCHAR *Dest, const TCHAR *Src) { return wcscpy(Dest, Src); }

// Unicode/ANSI OS wrappers imported from the Window/Core layer (Unreal "...X" helpers).
extern "C" __declspec(dllimport) UINT __stdcall GetWindowsDirectoryX(TCHAR *Buffer, UINT Size);
extern "C" __declspec(dllimport) UINT __stdcall GetSystemDirectoryX(TCHAR *Buffer, UINT Size);
extern "C" __declspec(dllimport) DWORD __stdcall GetModuleFileNameX(void *Module, TCHAR *Buffer, DWORD Size);

extern TCHAR GWindowsDir[256];
extern TCHAR GSystemDir[256];
extern TCHAR GModuleFile[256];

// RVA 0x69e0: cache the OS directories and the executable path, mapping .ICD to .EXE.
void InitLauncherPaths()
{
    GetWindowsDirectoryX(GWindowsDir, 256);
    GetSystemDirectoryX(GSystemDir, 256);
    GetModuleFileNameX(0, GModuleFile, 256);
    if (appStricmp(GModuleFile + appStrlen(GModuleFile) - 4, L".ICD") == 0)
        appStrcpy(GModuleFile + appStrlen(GModuleFile) - 4, L".EXE");
}

#define IDC_Logo 1024

class UnnamedDialog_6b20 : public UnnamedDialog_66b0
{
public:
    WLabel LogoStatic;                                           // +0x2fc
    FWindowsBitmap LogoBitmap;                                   // +0x33c
    void *Unknown34c;                                            // +0x34c
    FString Title;                                               // +0x350

    // RVA 0x6b20
    UnnamedDialog_6b20()
        : LogoStatic(this, IDC_Logo), Unknown34c(0)
    {
        InitLauncherPaths();
    }
    // RVA 0x6a80. Byte-identical after binding, but try_ltcg.py flags the operand of the
    // inlined MaybeDestroy's `call [vtable+0x14]` as a constant that differs: it compares
    // the vtable contents (stub pointers) with retail, as for item 0029's 0x65e0.
    ~UnnamedDialog_6b20()
    {
        MaybeDestroy();
    }
};

extern "C" __declspec(dllimport) HWND __stdcall GetDlgItem(HWND hDlg, INT nIDDlgItem);
extern "C" __declspec(dllimport) INT __stdcall GetSystemMetrics(INT nIndex);
extern "C" __declspec(dllimport) BOOL __stdcall SetWindowPos(HWND hWnd, HWND hWndInsertAfter, INT X, INT Y, INT cx, INT cy, UINT uFlags);
extern "C" __declspec(dllimport) BOOL __stdcall UpdateWindow(HWND hWnd);
__declspec(dllimport) HWND __stdcall CreateDialogParamX(HINSTANCE hInstance, const TCHAR *Template, HWND hWndParent, DLGPROC DialogProc, LPARAM InitParam);
__declspec(dllimport) LONG __stdcall SendMessageX(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

#define SM_CXSCREEN      0
#define SM_CYSCREEN      1
#define HWND_TOPMOST     ((HWND)-1)
#define HWND_NOTOPMOST   ((HWND)-2)
#define SWP_NOSIZE       0x0001
#define SWP_NOMOVE       0x0002
#define SWP_SHOWWINDOW   0x0040
#define STM_SETIMAGE     0x0172
#define IMAGE_BITMAP     0
#define MAKEINTRESOURCEW(i) ((const TCHAR *)((DWORD)((unsigned short)(i))))
#define IDDIALOG_Splash  119

extern HINSTANCE hInstance;
extern HWND hWndSplash;
INT __stdcall SplashDialogProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

// RVA 0x68b0: Unreal's InitSplash (link-time generated, ordinary cdecl).
void InitSplash(const TCHAR *Filename)
{
    HBITMAP hBitmap = 0;
    INT SizeX = 0, SizeY = 0;
    FWindowsBitmap Bitmap(1);
    if (Filename)
    {
        Bitmap.LoadFile(Filename);
        SizeX = Bitmap.SizeX;
        SizeY = Bitmap.SizeY;
        hBitmap = Bitmap.GetBitmapHandle();
    }
    hWndSplash = CreateDialogParamX(hInstance, MAKEINTRESOURCEW(IDDIALOG_Splash), 0, SplashDialogProc, 0);
    if (hWndSplash)
    {
        HWND hWndLogo = GetDlgItem(hWndSplash, IDC_Logo);
        if (hWndLogo)
        {
            SetWindowPos(hWndSplash, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - SizeX) / 2, (GetSystemMetrics(SM_CYSCREEN) - SizeY) / 2, SizeX, SizeY, SWP_SHOWWINDOW);
            SetWindowPos(hWndSplash, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            SendMessageX(hWndLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
            UpdateWindow(hWndSplash);
        }
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_6b20(void *Mem) { new (Mem) UnnamedDialog_6b20; }
void Driver_6a80(UnnamedDialog_6b20 *D) { D->UnnamedDialog_6b20::~UnnamedDialog_6b20(); }
void Driver_68b0(const TCHAR *F) { InitSplash(F); }
