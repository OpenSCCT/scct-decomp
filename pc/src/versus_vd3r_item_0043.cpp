#include "versus_unicows_thunks.h"

// Work item 0043 (LTCG retry): Versus RVA 0xa4f0-0xa725.
// FFileManagerWindows directory helpers (UE2 FFileManagerWindows.h):
//   0xa4f0 MakeDirectory, 0xa540 DeleteDirectory, 0xa5a0 FindFiles,
//   0xa6b0 SetDefaultDirectory, 0xa6d0 GetDefaultDirectory.
// Retail built this unit with /GL and linked with /LTCG. The Win32 calls go
// through TCHAR_CALL_OS; Versus is Unicode-only, so the ANSI half is dead code,
// but its appAlloca still forces the EBP frame every function here has.
// Identification: GetLastError checks against ERROR_ALREADY_EXISTS (0xb7) and
// ERROR_FILE_NOT_FOUND (2), "." / ".." skip and FILE_ATTRIBUTE_DIRECTORY.

typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef DWORD UBOOL;

#define NULL 0
#define INVALID_HANDLE_VALUE ((HANDLE)-1)
#define ERROR_FILE_NOT_FOUND 2
#define ERROR_ALREADY_EXISTS 183
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))

struct WIN32_FIND_DATAA
{
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    ANSICHAR cFileName[260];
    ANSICHAR cAlternateFileName[14];
};

extern "C" {
__declspec(dllimport) DWORD __stdcall GetLastError();
__declspec(dllimport) BOOL __stdcall FindClose(HANDLE hFindFile);
__declspec(dllimport) BOOL __stdcall CreateDirectoryA(const ANSICHAR *, void *);
__declspec(dllimport) BOOL __stdcall RemoveDirectoryA(const ANSICHAR *);
__declspec(dllimport) HANDLE __stdcall FindFirstFileA(const ANSICHAR *, WIN32_FIND_DATAA *);
__declspec(dllimport) BOOL __stdcall FindNextFileA(HANDLE, WIN32_FIND_DATAA *);
__declspec(dllimport) BOOL __stdcall SetCurrentDirectoryA(const ANSICHAR *);
__declspec(dllimport) DWORD __stdcall GetCurrentDirectoryA(DWORD, ANSICHAR *);
__declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
__declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
void *__cdecl _alloca(unsigned int);
}
#define appStricmp _wcsicmp

// Wide Win32 entry points held in writable data (0x10c74b60...).

#define GUnicodeOS 1
INT winGetSizeANSI(const TCHAR *Str);
ANSICHAR *winToANSI(ANSICHAR *ACh, const TCHAR *InUCh, INT Count);
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR *)_alloca(winGetSizeANSI(str)), str, winGetSizeANSI(str))
#define TCHAR_CALL_OS(funcW, funcA) (GUnicodeOS ? (funcW) : (funcA))

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern const TCHAR FArray_ProtectedCstorTag[]; // 0x10c10944
extern const TCHAR FString_AssignTag[];        // L"FString::=" 0x10c1092c
extern const TCHAR FArray_ReallocTag[];        // L"FArray"
void *appMemcpy(void *Dest, const void *Src, INT Count);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
    }
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);                // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);             // RVA 0x4550
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        ArrayNum = 0;
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(((T *)Other.Data)[i]);
    }
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1);
    void Empty(INT Slack = 0);
    TArray &operator=(const TArray &Other)
    {
        if (this != &Other)
        {
            Empty(Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new (*this) T(Other(i));
        }
        return *this;
    }
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template <class T> void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}

// No matching placement delete: retail sets no EH state around new(Result).
template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString &Other); // RVA 0x4640
    FString(const TCHAR *In);      // RVA 0x46c0
    ~FString();                    // RVA 0x48b0
    FString &operator=(const TCHAR *Other); // RVA 0x4750
};

// RVA 0x4750, defined so the link gives it its register convention (matched
// separately; see the brief's worked example).
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (TCHAR *)Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), FString_AssignTag);
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), FArray_ReallocTag);
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

FString appFromAnsi(const ANSICHAR *In);

class FFileManager
{
public:
    virtual UBOOL MakeDirectory(const TCHAR *Path, UBOOL Tree = 0);
    virtual UBOOL DeleteDirectory(const TCHAR *Path, UBOOL RequireExists = 0, UBOOL Tree = 0);
    virtual TArray<FString> FindFiles(const TCHAR *Filename, UBOOL Files, UBOOL Directories);
    virtual UBOOL SetDefaultDirectory(const TCHAR *Filename);
    virtual FString &GetDefaultDirectory(FString &Result);
};

class FFileManagerGeneric : public FFileManager
{
public:
    UBOOL MakeDirectory(const TCHAR *Path, UBOOL Tree = 0);                           // RVA 0x9160
    UBOOL DeleteDirectory(const TCHAR *Path, UBOOL RequireExists = 0, UBOOL Tree = 0); // RVA 0x9210
};

class FFileManagerWindows : public FFileManagerGeneric
{
public:
    FFileManagerWindows() {}
    UBOOL MakeDirectory(const TCHAR *Path, UBOOL Tree = 0);
    UBOOL DeleteDirectory(const TCHAR *Path, UBOOL RequireExists = 0, UBOOL Tree = 0);
    TArray<FString> FindFiles(const TCHAR *Filename, UBOOL Files, UBOOL Directories);
    UBOOL SetDefaultDirectory(const TCHAR *Filename);
    FString &GetDefaultDirectory(FString &Result);
};

extern const TCHAR Text_Dot[];    // L"."  at 0x10c0ffe8
extern const TCHAR Text_DotDot[]; // L".." at 0x10c0ffe0

// RVA 0xa4f0
UBOOL FFileManagerWindows::MakeDirectory(const TCHAR *Path, UBOOL Tree)
{
    if (Tree)
        return FFileManagerGeneric::MakeDirectory(Path, Tree);
    return TCHAR_CALL_OS(slot_CreateDirectoryW(Path, NULL), CreateDirectoryA(TCHAR_TO_ANSI(Path), NULL)) != 0
        || GetLastError() == ERROR_ALREADY_EXISTS;
}

// RVA 0xa540
UBOOL FFileManagerWindows::DeleteDirectory(const TCHAR *Path, UBOOL RequireExists, UBOOL Tree)
{
    if (Tree)
        return FFileManagerGeneric::DeleteDirectory(Path, RequireExists, Tree);
    return TCHAR_CALL_OS(slot_RemoveDirectoryW(Path), RemoveDirectoryA(TCHAR_TO_ANSI(Path))) != 0
        || (!RequireExists && GetLastError() == ERROR_FILE_NOT_FOUND);
}

// RVA 0xa5a0
TArray<FString> FFileManagerWindows::FindFiles(const TCHAR *Filename, UBOOL Files, UBOOL Directories)
{
    TArray<FString> Result;
    HANDLE Handle = NULL;
    if (GUnicodeOS)
    {
        WIN32_FIND_DATAW Data;
        Handle = slot_FindFirstFileW(Filename, &Data);
        if (Handle != INVALID_HANDLE_VALUE)
            do
                if (appStricmp(Data.cFileName, Text_Dot)
                &&  appStricmp(Data.cFileName, Text_DotDot)
                &&  ((Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? Directories : Files))
                    new(Result) FString(Data.cFileName);
            while (slot_FindNextFileW(Handle, &Data));
    }
    else
    {
        WIN32_FIND_DATAA Data;
        Handle = FindFirstFileA(TCHAR_TO_ANSI(Filename), &Data);
        if (Handle != INVALID_HANDLE_VALUE)
            do
                if ((Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? Directories : Files)
                    new(Result) FString(appFromAnsi(Data.cFileName));
            while (FindNextFileA(Handle, &Data));
    }
    if (Handle)
        FindClose(Handle);
    return Result;
}

// RVA 0xa6b0
UBOOL FFileManagerWindows::SetDefaultDirectory(const TCHAR *Filename)
{
    return TCHAR_CALL_OS(slot_SetCurrentDirectoryW(Filename), SetCurrentDirectoryA(TCHAR_TO_ANSI(Filename))) != 0;
}

// RVA 0xa6d0. UE2 returns FString by value; Versus assigns the buffer into the
// caller's string with FString::operator= (0x4750) and returns it, with no
// construction of the result, so it is written here as an out parameter.
FString &FFileManagerWindows::GetDefaultDirectory(FString &Result)
{
    TCHAR Buffer[1024] = { 0 };
    TCHAR_CALL_OS(slot_GetCurrentDirectoryW(ARRAY_COUNT(Buffer), Buffer),
                  GetCurrentDirectoryA(ARRAY_COUNT(Buffer), TCHAR_TO_ANSI(Buffer)));
    Result = Buffer;
    return Result;
}

// Scaffolding for the link, not part of the unit. Driver_a4f0 is the only
// root. The TArray<FString> uses reproduce the retail callers that fix the
// conventions of the array helpers FindFiles calls: the copy constructor
// (0xc550, this on the stack, Other in EDI) and the destructor (0xc5f0, a
// plain thiscall, kept so by the vector destructor iterator taking its address).
inline void *operator new(unsigned int, void *Mem) { return Mem; }
inline void operator delete(void *, void *) {}
void Escape(void *);
void MayThrow(void *);
TArray<FString> MakeList();
inline TArray<FString> CopyList(TArray<FString> &Local) { return Local; }
FFileManager *Driver_a4f0(void *Mem, TArray<FString> &Dest)
{
    Escape(&GMalloc);
    FFileManager *M = new(Mem) FFileManagerWindows;
    Escape(M);
    Dest = MakeList();
    TArray<FString> Copy = CopyList(Dest);
    MayThrow(&Copy);
    TArray<TCHAR> A;
    MayThrow(&A);
    TArray<FString> Lists[2];
    MayThrow(Lists);
    return M;
}
