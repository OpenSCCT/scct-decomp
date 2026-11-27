#include "versus_unicows_thunks.h"

// Work item 0120 (vwork4): Versus RVA 0x155e30-0x155f17, 1 function, 231 bytes.
//   0x155e30 UGUIController::execLaunchURL
//
// Retail built this unit with VC7.0 /GL and linked with /LTCG, so the call to
// appCreateProc (0xdf70, published in pc/src/versus_vd3r_item_0055.cpp) uses its
// link-time register convention (URL in ECX, Parms in EAX). appCreateProc is
// defined below with its published shape so the link assigns the same convention.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef DWORD UBOOL;

#define NULL 0
#define GENERIC_READ          0x80000000
#define FILE_SHARE_READ       1
#define CREATE_NEW            1
#define FILE_ATTRIBUTE_NORMAL 0x80
#define RESULT_DECL           void *const Result

extern "C" {
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE hObject);
void *__cdecl _alloca(unsigned int);
}

// Dispatch slots for wide Win32 entry points (unicows.lib).

// Literals retail keeps in writable .data (one per call site, unpooled).
extern const TCHAR Text_MyFileHtml1[];   // L"MYFILE.html" (0x10c461ac)
extern const TCHAR Text_MyFileHtml2[];   // L"MYFILE.html" (0x10c461c4)
extern const TCHAR Text_MyFileHtml3[];   // L"MYFILE.html" (0x10c461dc)

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

inline void *operator new[](unsigned int Size)
{
    return GMalloc->Malloc(Size, L"new");
}

inline void operator delete[](void *Ptr)
{
    GMalloc->Free(Ptr);
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString()
    {
        Data = 0;
        ArrayNum = 0;
        ArrayMax = 0;
    }
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

struct FFrame;

class UObject
{
public:
    virtual ~UObject();
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    void *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH       Stack.Code++

// Published appCreateProc (0xdf70, pc/src/versus_vd3r_item_0055.cpp) so LTCG
// assigns its (ECX=URL, EAX=Parms) calling convention.
#define GUnicodeOS 1
INT winGetSizeANSI(const TCHAR *Str);
ANSICHAR *winToANSI(ANSICHAR *ACh, const TCHAR *InUCh, INT Count);
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR *)_alloca(winGetSizeANSI(str)), str, winGetSizeANSI(str))
#define TCHAR_CALL_OS(funcW, funcA) (GUnicodeOS ? (funcW) : (funcA))

extern "C" __declspec(dllimport) int __stdcall CreateProcessA(const ANSICHAR *, ANSICHAR *, SECURITY_ATTRIBUTES *, SECURITY_ATTRIBUTES *, UBOOL, DWORD,
                                                              void *, const ANSICHAR *, void *, PROCESS_INFORMATION *);
INT appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
extern const TCHAR appCreateProc_Fmt[];

__declspec(noinline) void *appCreateProc(const TCHAR *URL, const TCHAR *Parms)
{
    TCHAR CommandLine[1024];
    appSprintf(CommandLine, appCreateProc_Fmt, URL, Parms);
    PROCESS_INFORMATION ProcInfo;
    SECURITY_ATTRIBUTES Attr;
    Attr.nLength = sizeof(SECURITY_ATTRIBUTES);
    Attr.lpSecurityDescriptor = 0;
    Attr.bInheritHandle = 1;
    STARTUPINFOW StartupInfo = { sizeof(STARTUPINFOW), 0, 0, 0,
        0x80000000, 0x80000000, 0x80000000, 0x80000000,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    if (!TCHAR_CALL_OS(
            slot_CreateProcessW(0, CommandLine, &Attr, &Attr, 1, 0x108, 0, 0, &StartupInfo, &ProcInfo),
            CreateProcessA(0, TCHAR_TO_ANSI(CommandLine), &Attr, &Attr, 1, 0x108, 0, 0, &StartupInfo, &ProcInfo)))
        return 0;
    return ProcInfo.hProcess;
}

class UGUIController : public UObject
{
public:
    void execLaunchURL(FFrame &Stack, RESULT_DECL);
};

// UGUIController::execLaunchURL (RVA 0x155e30)
void UGUIController::execLaunchURL(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(URL);
    P_FINISH;

    TCHAR *ResultExe = new TCHAR[255];
    HANDLE hFile = slot_CreateFileW(Text_MyFileHtml1, GENERIC_READ, FILE_SHARE_READ,
                                    NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    slot_FindExecutableW(Text_MyFileHtml2, NULL, ResultExe);
    appCreateProc(ResultExe, *URL);
    CloseHandle(hFile);
    slot_DeleteFileW(Text_MyFileHtml3);
    delete[] ResultExe;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
typedef void (UGUIController::*GUINative)(FFrame &, RESULT_DECL);
void Driver_155e30(const TCHAR *U, const TCHAR *P)
{
    Escape(&GMalloc);
    GUINative Fn = &UGUIController::execLaunchURL;
    Escape(&Fn);
    appCreateProc(U, P);
    appCreateProc(P, U);
    appCreateProc(U, U);
}
