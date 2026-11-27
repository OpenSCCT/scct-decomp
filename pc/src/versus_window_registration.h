#ifndef VERSUS_WINDOW_REGISTRATION_H
#define VERSUS_WINDOW_REGISTRATION_H
#include "versus_build.h"
#include "versus_native_subsystem.h"
#include "windows_dispatch_types.h"

struct HBRUSH__;
typedef HBRUSH__ *HBRUSH;
typedef HANDLE HGDIOBJ;
typedef HANDLE HFONT;
typedef DWORD COLORREF;
struct tagWNDCLASSEXW {
    UINT cbSize, style;
    WNDPROC lpfnWndProc;
    INT cbClsExtra, cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCWSTR lpszMenuName, lpszClassName;
    HICON hIconSm;
};

extern HINSTANCE hInstanceWindow;
extern "C" {
__declspec(dllimport) void __stdcall InitCommonControls();
__declspec(dllimport) HBRUSH __stdcall CreateSolidBrush(COLORREF Color);
__declspec(dllimport) DWORD __stdcall GetSysColor(INT Index);
__declspec(dllimport) HDC __stdcall GetDC(HWND Window);
__declspec(dllimport) INT __stdcall ReleaseDC(HWND Window, HDC DC);
__declspec(dllimport) HGDIOBJ __stdcall GetStockObject(INT Object);
__declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR);
__declspec(dllimport) HMODULE __stdcall LoadLibraryW(LPCWSTR);
__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
__declspec(dllimport) UINT __stdcall RegisterWindowMessageW(LPCWSTR);
__declspec(dllimport) HICON __stdcall LoadIconW(HINSTANCE, LPCWSTR);
__declspec(dllimport) BOOL __stdcall GetClassInfoExW(HINSTANCE, LPCWSTR, LPWNDCLASSEXW);
__declspec(dllimport) ATOM __stdcall RegisterClassExW(const WNDCLASSEXW *);
}
struct tagWNDCLASSEXA {
    UINT cbSize, style;
    WNDPROC lpfnWndProc;
    INT cbClsExtra, cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName, lpszClassName;
    HICON hIconSm;
};
extern "C" {
__declspec(dllimport) UINT __stdcall RegisterWindowMessageA(LPCSTR);
__declspec(dllimport) BOOL __stdcall GetClassInfoExA(HINSTANCE, LPCSTR, tagWNDCLASSEXA *);
__declspec(dllimport) ATOM __stdcall RegisterClassExA(const tagWNDCLASSEXA *);
void *__cdecl _alloca(unsigned int Size);
void *__cdecl memcpy(void *Dest, const void *Source, unsigned int Count);
}
#define GUnicodeOS 1
INT winGetSizeANSI(const TCHAR *Source);
ANSICHAR *winToANSI(ANSICHAR *Dest, const TCHAR *Source, INT Count);
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR *)_alloca(winGetSizeANSI(str)), str, winGetSizeANSI(str))
#define TCHAR_CALL_OS(funcW, funcA) (GUnicodeOS ? (funcW) : (funcA))

// Only the static registration interface is needed for these control classes.
class FCommandTarget {
public:
    virtual void VirtualSlot0();
};
class WWindow : public FCommandTarget {
public:
    static LRESULT __stdcall StaticProc(HWND Window, UINT Msg, WPARAM WParam, LPARAM LParam);
    static WNDPROC RegisterWindowClass(const TCHAR *Name, UINT Style);
};
class WControl : public WWindow {
public:
    static WNDPROC RegisterWindowClass(const TCHAR *Name, const TCHAR *BaseClass);
};
extern UObject *GTransientPackage;
class UWindowManager : public USubsystem {
public:
    UWindowManager();
    void *operator new(unsigned int, UObject *Outer = GTransientPackage,
                       FName Name = NAME_None, DWORD Flags = 0)
    {
        return StaticAllocateObject(&PrivateStaticClass, Outer, Name, Flags);
    }
    virtual ~UWindowManager();
    virtual void Destroy();
    virtual void Serialize(FArchive &Ar);
    virtual void Tick(FLOAT DeltaTime);
    static UClass PrivateStaticClass;
    static void InternalConstructor(void *Storage);
};
extern const TCHAR WindowClassFormat[];
extern UWindowManager *GWindowManager;
extern TArray<UObject *> GObjRoot;
const TCHAR *appPackage();
INT appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
struct NOTIFYICONDATAW;
typedef BOOL (__stdcall *ShellNotifyIconProc)(DWORD Message, NOTIFYICONDATAW *Data);
typedef BOOL (__stdcall *SpecialFolderPathProc)(HWND Owner, LPWSTR Path, INT Folder, BOOL Create);
extern ShellNotifyIconProc ShellNotifyIconW;
extern SpecialFolderPathProc ShellGetSpecialFolderPathW;
extern UINT WindowMessageUnrealOpen, WindowMessageMouseWheel;
extern HFONT WindowDefaultFont, WindowTextFont, WindowSmallFont;
extern HBRUSH BrushBlack;
extern HBRUSH BrushWhite;
extern HBRUSH BrushGrayE0;
extern HBRUSH BrushGrayC8;
extern HBRUSH BrushGrayA0;
extern HBRUSH BrushGray40;
extern HBRUSH BrushGray80;
extern HBRUSH BrushButtonFace;
extern HBRUSH BrushGrayA0Alternate;
extern HBRUSH BrushGrayB4;
extern HBRUSH BrushGrayC5;
extern HBRUSH BrushCyanC8;
extern HBRUSH BrushCyan8C;
class WListBox : public WControl { public: static WNDPROC SuperProc; };
class WItemBox : public WListBox {};
class WCheckListBox : public WControl { public: static WNDPROC SuperProc; };
class WBitmapButton : public WControl { public: static WNDPROC SuperProc; };
class WColorButton : public WControl { public: static WNDPROC SuperProc; };
class WTabControl : public WControl { public: static WNDPROC SuperProc; };
class WLabel : public WControl { public: static WNDPROC SuperProc; };
class WGroupBox : public WControl { public: static WNDPROC SuperProc; };
class WCustomLabel : public WControl { public: static WNDPROC SuperProc; };
class WListView : public WControl { public: static WNDPROC SuperProc; };
class WEdit : public WControl { public: static WNDPROC SuperProc; };
class WRichEdit : public WControl { public: static WNDPROC SuperProc; };
class WComboBox : public WControl { public: static WNDPROC SuperProc; };
class WEditTerminal : public WEdit {};
class WButton : public WControl { public: static WNDPROC SuperProc; };
class WPropertySheet : public WControl { public: static WNDPROC SuperProc; };
class WToolTip : public WControl { public: static WNDPROC SuperProc; };
class WCoolButton : public WControl { public: static WNDPROC SuperProc; };
class WUrlButton : public WControl { public: static WNDPROC SuperProc; };
class WCheckBox : public WButton { public: static WNDPROC SuperProc; };
class WScrollBar : public WControl { public: static WNDPROC SuperProc; };
class WTreeView : public WControl { public: static WNDPROC SuperProc; };
class WTrackBar : public WControl { public: static WNDPROC SuperProc; };
class WProgressBar : public WControl { public: static WNDPROC SuperProc; };
#endif
