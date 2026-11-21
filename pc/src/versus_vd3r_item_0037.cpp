// Work item 0037 (LTCG retry): Versus RVA 0x9550-0x9775.
// FFileManagerWindows::IsDrive and the FArchiveFileReader buffered reader
// (UE2 FFileManagerWindows.h). These objects were built with /GL and linked
// with /LTCG, which gave them custom register conventions.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef void *HANDLE;
typedef unsigned int size_t;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcschr(const TCHAR *, TCHAR);
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect);
extern "C" __declspec(dllimport) int __stdcall VirtualFree(void *lpAddress, DWORD dwSize, DWORD dwFreeType);
extern "C" __declspec(dllimport) int __stdcall ReadFile(HANDLE hFile, void *lpBuffer, DWORD nNumberOfBytesToRead, DWORD *lpNumberOfBytesRead, void *lpOverlapped);

inline void *operator new(size_t, void *Mem) { return Mem; }

inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }
inline const TCHAR *appStrchr(const TCHAR *S, INT C) { return wcschr(S, (TCHAR)C); }
inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : c + 'A' - 'a'; }
inline TCHAR appToLower(TCHAR c) { return (c < 'A' || c > 'Z') ? c : c + 'a' - 'A'; }

extern const TCHAR Text_Empty[];     // L""
extern const TCHAR Text_Backslash[]; // L"\\"
extern const TCHAR Text_UNCRoot[];   // L"\\\\"
extern const TCHAR Text_ReadFileFailed[]; // L"ReadFile failed: Count=%i BufferCount=%i Error=%s"

typedef char *va_list;
extern "C" __declspec(dllimport) DWORD __stdcall GetLastError();
extern "C" __declspec(dllimport) DWORD __stdcall FormatMessageW(DWORD dwFlags, const void *lpSource, DWORD dwMessageId, DWORD dwLanguageId, TCHAR *lpBuffer, DWORD nSize, va_list *Arguments);
INT appGetVarArgs(TCHAR *Dest, INT Count, const TCHAR *&Fmt, va_list ArgPtr);

// Callees from other units, defined here (they were /GL objects too) so the
// link gives them the same register conventions as retail: the error number
// in EAX for appGetSystemErrorMessage and `this` in EBX for Logf.
extern TCHAR appGetSystemErrorMessage_Msg[1024]; // local static in appGetSystemErrorMessage

#pragma auto_inline(off)
const TCHAR *appGetSystemErrorMessage(INT Error = 0)
{
    *appGetSystemErrorMessage_Msg = 0;
    if (Error == 0)
        Error = GetLastError();
    FormatMessageW(0x1000 /*FORMAT_MESSAGE_FROM_SYSTEM*/, 0, Error, 0x400 /*LANG_NEUTRAL, SUBLANG_DEFAULT*/, appGetSystemErrorMessage_Msg, 1024, 0);
    if (appStrchr(appGetSystemErrorMessage_Msg, '\r'))
        *(TCHAR *)appStrchr(appGetSystemErrorMessage_Msg, '\r') = 0;
    if (appStrchr(appGetSystemErrorMessage_Msg, '\n'))
        *(TCHAR *)appStrchr(appGetSystemErrorMessage_Msg, '\n') = 0;
    return appGetSystemErrorMessage_Msg;
}

enum EName { NAME_Log = 0x24c };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Dest, size_t Count, const TCHAR *Fmt, va_list Args);
extern const TCHAR Text_Logf[]; // allocation tag

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);
};

// Neutral stand-ins for the SCCT log filter state Logf reads.
struct FLogFilter { INT Pad[1]; DWORD Flags; };
struct FLogOwner { unsigned char Pad[0x930]; FLogFilter *Filter; };
extern UBOOL GLogFilterActive;
extern FLogOwner *GLogOwner;
extern TCHAR GCmdLine[];               // the command line buffer
extern const TCHAR Text_LogFlushParam[]; // the switch Logf tests
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

// UE2 ParseParam (retail 0x121c0: Stream in EDI, Param in ESI).
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}

// Approximation of retail 0x118d0 (SCCT's Logf with a heap buffer); only its
// register use matters here.
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!GLogFilterActive || !(GLogOwner->Filter->Flags & 0x1000))
    {
        TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, Text_Logf);
        _vsnwprintf(Buffer, 0x8000, Fmt, (va_list)&Fmt + sizeof(Fmt));
        Serialize(Buffer, NAME_Log);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}
#pragma auto_inline(on)

class FFileManagerWindows
{
public:
    UBOOL IsDrive(const TCHAR *Path);
};

// 0x9550
UBOOL FFileManagerWindows::IsDrive(const TCHAR *Path)
{
    if (appStricmp(Path, Text_Empty) == 0)
        return 1;
    else if (appToUpper(Path[0]) != appToLower(Path[0]) && Path[1] == ':' && Path[2] == 0)
        return 1;
    else if (appStricmp(Path, Text_Backslash) == 0)
        return 1;
    else if (appStricmp(Path, Text_UNCRoot) == 0)
        return 1;
    else if (Path[0] == '\\' && Path[1] == '\\' && !appStrchr(Path + 2, '\\'))
        return 1;
    else if (Path[0] == '\\' && Path[1] == '\\' && appStrchr(Path + 2, '\\') && !appStrchr(appStrchr(Path + 2, '\\') + 1, '\\'))
        return 1;
    else
        return 0;
}

class FArchive
{
public:
    FArchive()
    : ArVer(175), ArNetVer(2000), ArLicenseeVer(0), ArIsLoading(0), ArIsSaving(0), ArIsTrans(0),
      ArIsPersistent(0), ArForEdit(1), ArForClient(1), ArForServer(1), ArIsError(0), ArIsCriticalError(0),
      ArUnknown34(3), ArUnknown38(0), ArUnknown3C(-1)
    {}
    virtual ~FArchive() {}
    virtual void Precache(INT HintCount);
    virtual void Close();

    INT ArVer;              // 0x04
    INT ArNetVer;           // 0x08
    INT ArLicenseeVer;      // 0x0c
    UBOOL ArIsLoading;      // 0x10
    UBOOL ArIsSaving;       // 0x14
    UBOOL ArIsTrans;        // 0x18
    UBOOL ArIsPersistent;   // 0x1c
    UBOOL ArForEdit;        // 0x20
    UBOOL ArForClient;      // 0x24
    UBOOL ArForServer;      // 0x28
    UBOOL ArIsError;        // 0x2c
    UBOOL ArIsCriticalError;// 0x30
    INT ArUnknown34;        // 0x34 (neutral name)
    INT ArUnknown38;        // 0x38 (neutral name)
    INT ArUnknown3C;        // 0x3c (neutral name)
};

class FArchiveFileReader : public FArchive
{
public:
    FArchiveFileReader(HANDLE InHandle, FOutputDevice *InError, INT InSize);
    ~FArchiveFileReader();
    virtual void Precache(INT HintCount);
    void Close();

    HANDLE Handle;          // 0x40
    FOutputDevice *Error;   // 0x44
    INT Size;               // 0x48
    INT Pos;                // 0x4c
    INT BufferBase;         // 0x50
    INT BufferCount;        // 0x54
    unsigned char *Buffer;  // 0x58
};

// 0x9640
FArchiveFileReader::FArchiveFileReader(HANDLE InHandle, FOutputDevice *InError, INT InSize)
: Handle(InHandle), Error(InError), Size(InSize), Pos(0), BufferBase(0), BufferCount(0)
{
    ArIsLoading = ArIsPersistent = 1;
    Buffer = Handle ? (unsigned char *)VirtualAlloc(0, Size, 0x1000 /*MEM_COMMIT*/, 4 /*PAGE_READWRITE*/) : 0;
}

// 0x96c0
#pragma auto_inline(off)
FArchiveFileReader::~FArchiveFileReader()
{
    if (Handle)
        Close();
    if (Buffer)
        VirtualFree(Buffer, 0, 0x8000 /*MEM_RELEASE*/);
}
#pragma auto_inline(on)

// 0x96f0
void FArchiveFileReader::Precache(INT HintCount)
{
    BufferBase = Pos;
    INT Avail = 0x1000 - (Pos & 0xfff);
    if (HintCount > Avail)
        HintCount = Avail;
    INT Left = Size - Pos;
    BufferCount = HintCount <= Left ? HintCount : Left;
    INT Count = 0;
    ReadFile(Handle, Buffer, BufferCount, (DWORD *)&Count, 0);
    if (Count != BufferCount)
    {
        ArIsError = 1;
        Error->Logf(Text_ReadFileFailed, Count, BufferCount, appGetSystemErrorMessage());
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
UBOOL Driver_9550(FFileManagerWindows *F, const TCHAR *P) { return F->IsDrive(P); }
void Driver_9640(void *Mem, HANDLE H, FOutputDevice *E, INT S) { new(Mem) FArchiveFileReader(H, E, S); }
void Driver_96c0(FArchiveFileReader *R, FArchiveFileReader *R2) { R->FArchiveFileReader::~FArchiveFileReader(); R2->FArchiveFileReader::~FArchiveFileReader(); }
void Driver_96f0(FArchiveFileReader *R, INT N) { R->FArchiveFileReader::Precache(N); }
