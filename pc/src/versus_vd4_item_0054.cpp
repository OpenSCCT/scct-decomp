#include "versus_unicows_thunks.h"

// RVA 0xd4d0: appGetSystemErrorMessage (Core, UnVcWin32.cpp), LTCG build:
// the error code arrives in EAX.
typedef unsigned short TCHAR;

extern "C" __declspec(dllimport) DWORD __stdcall GetLastError(void);
extern "C" __declspec(dllimport) TCHAR *wcschr(const TCHAR *, TCHAR);

// Unicode-layer slot for FormatMessageW (see versus_windows_dispatch.c).

// Was a function-local static: static TCHAR Msg[1024].
extern TCHAR appGetSystemErrorMessage_Msg[1024];

inline TCHAR *appStrchr(const TCHAR *S, INT C) { return wcschr(S, (TCHAR)C); }

const TCHAR *appGetSystemErrorMessage(INT Error)
{
    TCHAR *Msg = appGetSystemErrorMessage_Msg;
    *Msg = 0;
    if (Error == 0)
        Error = GetLastError();
    slot_FormatMessageW(0x1000 /*FORMAT_MESSAGE_FROM_SYSTEM*/, 0, Error, 0x400 /*MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT)*/, Msg, 1024, 0);
    if (appStrchr(Msg, '\r'))
        *appStrchr(Msg, '\r') = 0;
    if (appStrchr(Msg, '\n'))
        *appStrchr(Msg, '\n') = 0;
    return Msg;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
const TCHAR *Driver_d4d0(INT Error)
{
    Escape(&appGetSystemErrorMessage_Msg);
    Escape(&slot_FormatMessageW);
    return appGetSystemErrorMessage(Error);
}
