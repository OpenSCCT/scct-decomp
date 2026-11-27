#include "versus_window_registration.h"
#include "versus_window_procedures.inl"

inline UINT RegisterWindowMessage(const TCHAR *Message)
{
    return TCHAR_CALL_OS(RegisterWindowMessageW(Message), RegisterWindowMessageA(TCHAR_TO_ANSI(Message)));
}

const TCHAR WindowClassFormat[] = L"%sUnreal%s";
inline void MakeWindowClassName(TCHAR *Dest, const TCHAR *ClassName)
{
    appSprintf(Dest, WindowClassFormat, appPackage(), ClassName);
}

#define WINDOW_WIDE_LITERAL_INNER(Text) L##Text
#define WINDOW_WIDE_LITERAL(Text) WINDOW_WIDE_LITERAL_INNER(Text)

// Several distinct superclass-name objects have identical contents in the shipped Windows package.
#define WINDOW_CONTROL(Control, BaseName) TCHAR Control##BaseNameText[] = BaseName;
#include "versus_window_controls.inl"
#undef WINDOW_CONTROL

#define REGISTER_CONTROL(NameBuffer, Control) \
    { \
        MakeWindowClassName(NameBuffer, WINDOW_WIDE_LITERAL(#Control)); \
        Control::SuperProc = WControl::RegisterWindowClass(NameBuffer, Control##BaseNameText); \
    }

#define REGISTER_WINDOW(NameBuffer, Window, Style) \
    MakeWindowClassName(NameBuffer, WINDOW_WIDE_LITERAL(#Window)); \
    WWindow::RegisterWindowClass(NameBuffer, Style)

// Each control keeps the original Windows window procedure for default handling.
UWindowManager::UWindowManager()
{
    TCHAR Name[256];
    const UINT CS_DBLCLKS = 0x0008;
    InitCommonControls();
    HMODULE Shell = GetModuleHandleW(L"SHELL32.DLL");
    ShellNotifyIconW = (ShellNotifyIconProc)GetProcAddress(Shell, "Shell_NotifyIconW");
    ShellGetSpecialFolderPathW = (SpecialFolderPathProc)GetProcAddress(Shell, "SHGetSpecialFolderPathW");
    LoadLibraryW(L"RICHED32.DLL");

#define WINDOW_CONTROL(Control, BaseName) REGISTER_CONTROL(Name, Control);
#include "versus_window_controls.inl"
#undef WINDOW_CONTROL
    REGISTER_WINDOW(Name, WTerminal, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WLog, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WCrashBoxDialog, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WProperties, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WObjectProperties, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WConfigProperties, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WClassProperties, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WWizardDialog, 0);
    REGISTER_WINDOW(Name, WWizardPage, 0);
    REGISTER_WINDOW(Name, WDragInterceptor, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WPictureButton, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WUDNWindow, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WThinScrollBar, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WTimeScrollBar, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WPropertyPage, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WSplitter, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WSplitterPane, CS_DBLCLKS);
    REGISTER_WINDOW(Name, WSplitterContainer, CS_DBLCLKS);

    BrushBlack = CreateSolidBrush(0x0);
    BrushWhite = CreateSolidBrush(0xffffff);
    BrushGrayE0 = CreateSolidBrush(0xe0e0e0);
    BrushGrayC8 = CreateSolidBrush(0xc8c8c8);
    BrushGrayA0 = CreateSolidBrush(0xa0a0a0);
    BrushGray40 = CreateSolidBrush(0x404040);
    BrushGray80 = CreateSolidBrush(0x808080);
    BrushButtonFace = CreateSolidBrush(GetSysColor(15));
    BrushGrayA0Alternate = CreateSolidBrush(0xa0a0a0);
    BrushGrayB4 = CreateSolidBrush(0xb4b4b4);
    BrushGrayC5 = CreateSolidBrush(0xc5c5c5);
    BrushCyanC8 = CreateSolidBrush(0xc8c800);
    BrushCyan8C = CreateSolidBrush(0x8c8c00);
    HDC DC = GetDC(0);
    WindowDefaultFont = (HFONT)GetStockObject(17);
    WindowTextFont = (HFONT)GetStockObject(17);
    WindowSmallFont = (HFONT)GetStockObject(17);
    ReleaseDC(0, DC);
    WindowMessageUnrealOpen = RegisterWindowMessage(L"UnrealOpen");
    WindowMessageMouseWheel = RegisterWindowMessage(L"MSWHEEL_ROLLMSG");
}

#undef REGISTER_WINDOW
#undef REGISTER_CONTROL
#undef WINDOW_WIDE_LITERAL
#undef WINDOW_WIDE_LITERAL_INNER

inline void *operator new(unsigned int, void *Storage) { return Storage; }
void UWindowManager::InternalConstructor(void *Storage)
{
    ::new(Storage) UWindowManager;
}

// Make the window manager part of the root set before its first tick.
void InitWindowing()
{
    GWindowManager = new UWindowManager;
    GObjRoot.AddItem(GWindowManager);
}
