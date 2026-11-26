// Work item 0055 (LTCG retry): Core Windows platform helpers (UnVcWin32.cpp in UE2).
// appClipboardCopy (0xdc40), appClipboardPaste (0xdc90), appLaunchURL (0xdf20),
// appCreateProc (0xdf70). These objects were compiled /GL and linked /LTCG, so the
// linker gave them register calling conventions (Str in EDI; Parms in EAX, Error/URL in ECX).
// __declspec(noinline) stands in for retail call sites the LTCG inliner declined.

typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short WORD;
typedef void *HANDLE;
typedef struct HWND__ *HWND;
typedef void *HGLOBAL;
typedef void *HINSTANCE;

extern "C" __declspec(dllimport) HWND __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) int __stdcall OpenClipboard(HWND);
extern "C" __declspec(dllimport) int __stdcall EmptyClipboard();
extern "C" __declspec(dllimport) int __stdcall CloseClipboard();
extern "C" __declspec(dllimport) HANDLE __stdcall SetClipboardData(unsigned int, HANDLE);
extern "C" __declspec(dllimport) HANDLE __stdcall GetClipboardData(unsigned int);
extern "C" __declspec(dllimport) HGLOBAL __stdcall GlobalAlloc(unsigned int, DWORD);
extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline TCHAR *appStrcpy(TCHAR *D, const TCHAR *S) { return wcscpy(D, S); }
inline TCHAR FromAnsi(ANSICHAR In) { return (BYTE)In; }

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

// Literals retail keeps in writable .data.
extern const TCHAR FArray_ProtectedCstor[];   // "Farray::protectedcstor"
extern const TCHAR appClipboardPaste_Empty1[]; // TEXT("") (no clipboard data)
extern const TCHAR appClipboardPaste_Empty2[]; // TEXT("") (clipboard not opened)

template<class T> class TArray {
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    TArray(INT InNum) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (ArrayMax == 0)
            Data = 0;
        else
            Data = (T *)GMalloc->Malloc(ArrayMax * sizeof(T), FArray_ProtectedCstor);
    }
    ~TArray();
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const TCHAR *Other);
};

FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

#define GMEM_DDESHARE  0x2000
#define CF_TEXT        1
#define CF_UNICODETEXT 13

__declspec(noinline) void appClipboardCopy(const TCHAR *Str)
{
    if (OpenClipboard(GetActiveWindow())) {
        EmptyClipboard();
        HGLOBAL GlobalMem = GlobalAlloc(GMEM_DDESHARE, sizeof(TCHAR) * (appStrlen(Str) + 1));
        appStrcpy((TCHAR *)GlobalMem, Str);
        SetClipboardData(CF_UNICODETEXT, GlobalMem);
        CloseClipboard();
    }
}

__declspec(noinline) FString appClipboardPaste()
{
    FString Result;
    if (OpenClipboard(GetActiveWindow())) {
        HGLOBAL GlobalMem = GetClipboardData(CF_UNICODETEXT);
        if (GlobalMem) {
            Result = (TCHAR *)GlobalMem;
        } else {
            GlobalMem = GetClipboardData(CF_TEXT);
            if (GlobalMem) {
                ANSICHAR *ACh = (ANSICHAR *)GlobalMem;
                INT i;
                for (i = 0; ACh[i]; i++)
                    ;
                TArray<TCHAR> Ch(i + 1);
                for (i = 0; i < Ch.Num(); i++)
                    Ch(i) = FromAnsi(ACh[i]);
                Result = &Ch(0);
            } else {
                Result = appClipboardPaste_Empty1;
            }
        }
        CloseClipboard();
    } else {
        Result = appClipboardPaste_Empty2;
    }
    return Result;
}

// Versus is Unicode-only; the ANSI half of TCHAR_CALL_OS is dead code but its
// appAlloca still forces the frame-pointer epilogue (lea esp, [ebp-N]).
#define GUnicodeOS 1
extern "C" void *__cdecl _alloca(unsigned int);
INT winGetSizeANSI(const TCHAR *Str);
ANSICHAR *winToANSI(ANSICHAR *ACh, const TCHAR *InUCh, INT Count);
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR *)_alloca(winGetSizeANSI(str)), str, winGetSizeANSI(str))
#define TCHAR_CALL_OS(funcW, funcA) (GUnicodeOS ? (funcW) : (funcA))

// Dispatch slot for the wide entry point.
extern HINSTANCE (__stdcall *slot_ShellExecuteW)(HWND, const TCHAR *, const TCHAR *, const TCHAR *, const TCHAR *, INT);
extern "C" __declspec(dllimport) HINSTANCE __stdcall ShellExecuteA(HWND, const ANSICHAR *, const ANSICHAR *, const ANSICHAR *, const ANSICHAR *, INT);
extern const TCHAR appLaunchURL_Empty1[]; // TEXT("") for missing Parms
extern const TCHAR appLaunchURL_Empty2[]; // TEXT("") directory
extern const TCHAR appLaunchURL_Open[];   // TEXT("open")
extern const TCHAR appLaunchURL_Failed[]; // error message
extern const TCHAR appLaunchURL_Empty3[]; // TEXT("") success

__declspec(noinline) void appLaunchURL(const TCHAR *URL, const TCHAR *Parms, FString *Error)
{
    INT Code = (INT)TCHAR_CALL_OS(
        slot_ShellExecuteW(0, appLaunchURL_Open, URL, Parms ? Parms : appLaunchURL_Empty1, appLaunchURL_Empty2, 1),
        ShellExecuteA(0, "open", TCHAR_TO_ANSI(URL), Parms ? TCHAR_TO_ANSI(Parms) : "", "", 1));
    if (Error)
        *Error = Code <= 32 ? appLaunchURL_Failed : appLaunchURL_Empty3;
}

struct SECURITY_ATTRIBUTES {
    DWORD nLength;
    void *lpSecurityDescriptor;
    UBOOL bInheritHandle;
};
struct STARTUPINFO {
    DWORD cb;
    TCHAR *lpReserved;
    TCHAR *lpDesktop;
    TCHAR *lpTitle;
    DWORD dwX, dwY, dwXSize, dwYSize;
    DWORD dwXCountChars, dwYCountChars, dwFillAttribute, dwFlags;
    WORD wShowWindow, cbReserved2;
    BYTE *lpReserved2;
    HANDLE hStdInput, hStdOutput, hStdError;
};
struct PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
};
extern int (__stdcall *slot_CreateProcessW)(const TCHAR *, TCHAR *, SECURITY_ATTRIBUTES *, SECURITY_ATTRIBUTES *, UBOOL, DWORD,
                                       void *, const TCHAR *, STARTUPINFO *, PROCESS_INFORMATION *);
extern "C" __declspec(dllimport) int __stdcall CreateProcessA(const ANSICHAR *, ANSICHAR *, SECURITY_ATTRIBUTES *, SECURITY_ATTRIBUTES *, UBOOL, DWORD,
                                                          void *, const ANSICHAR *, void *, PROCESS_INFORMATION *);
INT appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
extern const TCHAR appCreateProc_Fmt[]; // TEXT("%s %s")

__declspec(noinline) void *appCreateProc(const TCHAR *URL, const TCHAR *Parms)
{
    TCHAR CommandLine[1024];
    appSprintf(CommandLine, appCreateProc_Fmt, URL, Parms);
    PROCESS_INFORMATION ProcInfo;
    SECURITY_ATTRIBUTES Attr;
    Attr.nLength = sizeof(SECURITY_ATTRIBUTES);
    Attr.lpSecurityDescriptor = 0;
    Attr.bInheritHandle = 1;
    STARTUPINFO StartupInfo = { sizeof(STARTUPINFO), 0, 0, 0,
        0x80000000, 0x80000000, 0x80000000, 0x80000000,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    if (!TCHAR_CALL_OS(
            slot_CreateProcessW(0, CommandLine, &Attr, &Attr, 1, 0x108, 0, 0, &StartupInfo, &ProcInfo),
            CreateProcessA(0, TCHAR_TO_ANSI(CommandLine), &Attr, &Attr, 1, 0x108, 0, 0, &StartupInfo, &ProcInfo)))
        return 0;
    return ProcInfo.hProcess;
}

// Scaffolding for the link, not part of the unit (several call sites keep
// the functions out of line, as in retail).
void Escape(void *);
void Driver_dc40(const TCHAR *A, const TCHAR *B, const TCHAR *C) { appClipboardCopy(A); appClipboardCopy(B); appClipboardCopy(C); }
void Driver_dc90(FString *A, FString *B, FString *C)
{
    Escape(&GMalloc);
    { FString S = appClipboardPaste(); *A = S.Data; }
    { FString S = appClipboardPaste(); *B = S.Data; }
    { FString S = appClipboardPaste(); *C = S.Data; }
}
void Driver_df20(const TCHAR *U, const TCHAR *P, FString *E, FString *F)
{
    Escape(&GMalloc);
    appLaunchURL(U, P, E);
    appLaunchURL(P, U, F);
    appLaunchURL(U, 0, 0);
}
void *Driver_df70(const TCHAR *U, const TCHAR *P)
{
    void *a = appCreateProc(U, P);
    void *b = appCreateProc(P, U);
    void *c = appCreateProc(U, U);
    return (void *)((DWORD)a + (DWORD)b + (DWORD)c);
}
