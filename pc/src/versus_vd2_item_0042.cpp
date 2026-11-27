#include "versus_unicows_thunks.h"

// Work item 0042: FFileManagerWindows (UnFile / FFileManagerWindows.h), RVA 0xa170-0xa4a9.
// Bodies follow the Unreal Engine 2 FFileManagerWindows; the Win32 wide calls go through
// the unicows-style dispatch slots (see versus_windows_dispatch.c).

typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef DWORD UBOOL;

#define NULL 0
#define GENERIC_READ 0x80000000
#define GENERIC_WRITE 0x40000000
#define FILE_SHARE_READ 1
#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_NORMAL 0x80
#define INVALID_HANDLE_VALUE ((HANDLE)-1)
#define ERROR_FILE_NOT_FOUND 2

extern "C" {
__declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE hFile, DWORD *lpFileSizeHigh);
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE hObject);
__declspec(dllimport) DWORD __stdcall GetLastError(void);
__declspec(dllimport) HANDLE __stdcall CreateFileA(const ANSICHAR *, DWORD, DWORD, void *, DWORD, DWORD, HANDLE);
__declspec(dllimport) BOOL __stdcall SetFileAttributesA(const ANSICHAR *, DWORD);
__declspec(dllimport) BOOL __stdcall DeleteFileA(const ANSICHAR *);
__declspec(dllimport) BOOL __stdcall MoveFileA(const ANSICHAR *, const ANSICHAR *);
__declspec(dllimport) BOOL __stdcall CopyFileA(const ANSICHAR *, const ANSICHAR *, BOOL);
void *__cdecl _alloca(unsigned int);
}

// Dispatch slots for the wide Win32 entry points.

// The Versus build is Unicode-only, so the ANSI half of TCHAR_CALL_OS is dead code,
// but its appAlloca still forces the frame-pointer epilogue.
#define GUnicodeOS 1
INT winGetSizeANSI(const TCHAR *Str);
ANSICHAR *winToANSI(ANSICHAR *ACh, const TCHAR *InUCh, INT Count);
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR *)_alloca(winGetSizeANSI(str)), str, winGetSizeANSI(str))
#define TCHAR_CALL_OS(funcW, funcA) (GUnicodeOS ? (funcW) : (funcA))

class FOutputDevice;
class FCopyProgress;

class FFileManagerGeneric
{
public:
    virtual void *CreateFileReader(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Buffered);
    virtual void *CreateFileWriter(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Buffered);
    virtual INT FileSize(const TCHAR *Filename);
    virtual DWORD Copy(const TCHAR *Dest, const TCHAR *Src, UBOOL Replace, UBOOL EvenIfReadOnly, UBOOL Attributes, UBOOL Unknown, FCopyProgress *Progress);
    virtual UBOOL Unknown10(const TCHAR *Filename);
    virtual UBOOL Delete(const TCHAR *Filename, UBOOL RequireExists, UBOOL EvenReadOnly);
};

class FFileManagerWindows : public FFileManagerGeneric
{
public:
    INT FileSize(const TCHAR *Filename);
    DWORD Copy(const TCHAR *Dest, const TCHAR *Src, UBOOL Replace, UBOOL EvenIfReadOnly, UBOOL Attributes, UBOOL Unknown, FCopyProgress *Progress);
    UBOOL Delete(const TCHAR *Filename, UBOOL RequireExists, UBOOL EvenReadOnly);
    UBOOL Move(const TCHAR *Dest, const TCHAR *Src, UBOOL Replace, UBOOL EvenReadOnly, UBOOL Attributes);
};

// RVA 0xa320
INT FFileManagerWindows::FileSize(const TCHAR *Filename)
{
    HANDLE Handle = TCHAR_CALL_OS(
        slot_CreateFileW(Filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL),
        CreateFileA(TCHAR_TO_ANSI(Filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL));
    if (Handle == INVALID_HANDLE_VALUE)
        return -1;
    DWORD Result = GetFileSize(Handle, NULL);
    CloseHandle(Handle);
    return Result;
}

// RVA 0xa370
DWORD FFileManagerWindows::Copy(const TCHAR *Dest, const TCHAR *Src, UBOOL Replace, UBOOL EvenIfReadOnly, UBOOL Attributes, UBOOL Unknown, FCopyProgress *Progress)
{
    if (EvenIfReadOnly)
        TCHAR_CALL_OS(slot_SetFileAttributesW(Dest, 0), SetFileAttributesA(TCHAR_TO_ANSI(Dest), 0));
    DWORD Result;
    if (Progress || Unknown)
        Result = FFileManagerGeneric::Copy(Dest, Src, Replace, EvenIfReadOnly, Attributes, Unknown, Progress);
    else
    {
        if (TCHAR_CALL_OS(slot_CopyFileW(Src, Dest, !Replace), CopyFileA(TCHAR_TO_ANSI(Src), TCHAR_TO_ANSI(Dest), !Replace)) != 0)
            Result = 0;
        else
            Result = 1;
    }
    if (Result == 0 && !Attributes)
        TCHAR_CALL_OS(slot_SetFileAttributesW(Dest, 0), SetFileAttributesA(TCHAR_TO_ANSI(Dest), 0));
    return Result;
}

// RVA 0xa400
UBOOL FFileManagerWindows::Delete(const TCHAR *Filename, UBOOL RequireExists, UBOOL EvenReadOnly)
{
    if (EvenReadOnly)
        TCHAR_CALL_OS(slot_SetFileAttributesW(Filename, FILE_ATTRIBUTE_NORMAL), SetFileAttributesA(TCHAR_TO_ANSI(Filename), FILE_ATTRIBUTE_NORMAL));
    INT Result = TCHAR_CALL_OS(slot_DeleteFileW(Filename), DeleteFileA(TCHAR_TO_ANSI(Filename))) != 0
              || (!RequireExists && GetLastError() == ERROR_FILE_NOT_FOUND);
    if (!Result)
    {
        DWORD Error = GetLastError();
    }
    return Result != 0;
}

// RVA 0xa470
UBOOL FFileManagerWindows::Move(const TCHAR *Dest, const TCHAR *Src, UBOOL Replace, UBOOL EvenReadOnly, UBOOL Attributes)
{
    Delete(Dest, 0, EvenReadOnly);
    INT Result = TCHAR_CALL_OS(slot_MoveFileW(Src, Dest), MoveFileA(TCHAR_TO_ANSI(Src), TCHAR_TO_ANSI(Dest)));
    if (!Result)
    {
        DWORD Error = GetLastError();
    }
    return Result != 0;
}

// RVA 0xa170 FFileManagerWindows::CreateFileReader and RVA 0xa230 CreateFileWriter are not
// written yet: they call the FArchiveFileReader/Writer and buffered-archive constructors
// (0x9640, 0x9be0, 0x9970, 0x9ee0) with link-time custom register conventions (this in eax
// or esi, arguments in ebx/edx/edi), which a standalone compile cannot reproduce.
