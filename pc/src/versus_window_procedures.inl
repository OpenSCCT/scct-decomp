// Class registration uses initialized WNDCLASSEX structures in the Unicode and ANSI builds.
// Initialize all WNDCLASSEX members before GetClassInfoEx or a fresh registration.
inline void InitWindowClass(WNDCLASSEXW &Cls)
{
    Cls.cbSize = sizeof(Cls);
    Cls.style = 0;
    Cls.lpfnWndProc = 0;
    Cls.cbClsExtra = 0;
    Cls.cbWndExtra = 0;
    Cls.hInstance = 0;
    Cls.hIcon = 0;
    Cls.hCursor = 0;
    Cls.hbrBackground = 0;
    Cls.lpszMenuName = 0;
    Cls.lpszClassName = 0;
    Cls.hIconSm = 0;
}

// The ANSI registration must point to a converted class name for the duration of the call.
inline void RegisterWindowClassEx(WNDCLASSEXW &Cls)
{
    if (GUnicodeOS) {
        RegisterClassExW(&Cls);
    } else {
        tagWNDCLASSEXA AnsiClass;
        memcpy(&AnsiClass, &Cls, sizeof(AnsiClass));
        AnsiClass.lpszClassName = TCHAR_TO_ANSI(Cls.lpszClassName);
        RegisterClassExA(&AnsiClass);
    }
}

WNDPROC WWindow::RegisterWindowClass(const TCHAR *Name, UINT Style)
{
    WNDCLASSEXW Cls;
    InitWindowClass(Cls);
    Cls.style = Style;
    Cls.lpfnWndProc = WWindow::StaticProc;
    Cls.hInstance = hInstanceWindow;
    Cls.hIcon = LoadIconW(hInstanceWindow, (const TCHAR *)128);
    Cls.lpszClassName = Name;
    Cls.hIconSm = LoadIconW(hInstanceWindow, (const TCHAR *)128);
    RegisterWindowClassEx(Cls);
    return 0;
}

WNDPROC WControl::RegisterWindowClass(const TCHAR *Name, const TCHAR *BaseClass)
{
    WNDCLASSEXW Cls;
    InitWindowClass(Cls);
    if (GUnicodeOS)
        GetClassInfoExW(0, BaseClass, &Cls);
    else {
        tagWNDCLASSEXA AnsiClass;
        AnsiClass.cbSize = sizeof(AnsiClass);
        GetClassInfoExA(0, TCHAR_TO_ANSI(BaseClass), &AnsiClass);
        memcpy(&Cls, &AnsiClass, sizeof(Cls));
    }
    WNDPROC SuperProc = Cls.lpfnWndProc;
    Cls.lpfnWndProc = WWindow::StaticProc;
    Cls.lpszClassName = Name;
    Cls.hInstance = hInstanceWindow;
    RegisterWindowClassEx(Cls);
    return SuperProc;
}
