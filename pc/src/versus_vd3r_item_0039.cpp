// Work item 0039 (LTCG retry): FArchiveFileWriter (UE2 FFileManagerWindows.h).
// Layout: vtable 0x00, FArchive state 0x04..0x3c, Handle 0x40, Error 0x44,
// Pos 0x48, BufferCount 0x4c, Buffer[4096] 0x50. Flush is vtable slot 0x4c.
// FArchive fields 0x34..0x3c are SCCT additions (names unknown).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef void* HANDLE;
typedef long LONG;
#define TEXT(s) L##s
#define FILE_BEGIN 0
#define INVALID_SET_FILE_POINTER ((DWORD)-1)

extern "C" __declspec(dllimport) DWORD __stdcall SetFilePointer(HANDLE, LONG, LONG*, DWORD);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(HANDLE);

inline void* operator new(unsigned int, void* Mem) { return Mem; }

typedef char* va_list;
#define va_start(ap, v) (ap = (va_list)&v + sizeof(v))
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR*, unsigned int, const TCHAR*, va_list);
enum EName { NAME_Error = 0x24c };

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;

// Retail keeps these literals in writable data.
extern const TCHAR ErrorSeekingFile[];   // L"Error seeking file"
extern const TCHAR ErrorWritingToFile[]; // L"Error writing to file"

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR* V, EName Event);
    virtual void Flush();
    void Logf(const TCHAR* Fmt, ...);
};

class FArchive
{
public:
    FArchive()
    :   ArVer(175), ArNetVer(2000), ArLicenseeVer(0), ArIsLoading(0), ArIsSaving(0),
        ArIsTrans(0), ArIsPersistent(0), ArForEdit(1), ArForClient(1), ArForServer(1),
        ArIsError(0), ArIsCriticalError(0), Ar34(3), Ar38(0), Ar3C(-1)
    {}
    virtual ~FArchive() {}
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(void* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(class FName& N);
    virtual FArchive& operator<<(class UObject*& Res);
    virtual INT MapName(class FName* Name);
    virtual INT MapObject(class UObject* Object);
    virtual INT Tell();
    virtual INT TotalSize();
    virtual UBOOL AtEnd();
    virtual void Seek(INT InPos);
    virtual void AttachLazyLoader(class FLazyLoader* LazyLoader);
    virtual void DetachLazyLoader(class FLazyLoader* LazyLoader);
    virtual void Precache(INT HintCount);
    virtual void Unused1();
    virtual UBOOL Close();
    virtual void Flush();

    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
    UBOOL ArForEdit, ArForClient, ArForServer;
    UBOOL ArIsError, ArIsCriticalError;
    INT Ar34, Ar38, Ar3C;
};

class FArchiveFileWriter : public FArchive
{
public:
    FArchiveFileWriter(HANDLE InHandle, FOutputDevice* InError, INT InPos)
    :   Handle(InHandle), Error(InError), Pos(InPos), BufferCount(0)
    {
        ArIsSaving = ArIsPersistent = 1;
    }
    ~FArchiveFileWriter();
    void Seek(INT InPos);
    UBOOL Close();
    void Serialize(void* V, INT Length);
    void Flush();

    HANDLE         Handle;      // 0x40
    FOutputDevice* Error;       // 0x44
    INT            Pos;         // 0x48
    INT            BufferCount; // 0x4c
    BYTE           Buffer[4096];// 0x50
};

FArchiveFileWriter::~FArchiveFileWriter()
{
    if (Handle)
        Close();
    Handle = 0;
}

void FArchiveFileWriter::Seek(INT InPos)
{
    Flush();
    if (SetFilePointer(Handle, InPos, 0, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        ArIsError = 1;
        Error->Logf(ErrorSeekingFile);
    }
    Pos = InPos;
}

UBOOL FArchiveFileWriter::Close()
{
    Flush();
    if (Handle && !CloseHandle(Handle))
    {
        ArIsError = 1;
        Error->Logf(ErrorWritingToFile);
    }
    Handle = 0;
    return !ArIsError;
}

// Built with /O2 /Gy /GX /Ob1: with /Ob2 the link inlines Close into the
// destructor, which retail does not.
// Scaffolding for the link, not part of the unit: stand-ins for the real
// FOutputDevice::Logf (retail RVA 0x118d0) and ParseParam (0x121c0), which
// live in other objects. They are defined here only so the linker gives Logf
// retail's link-time convention (this in EBX); their shape follows retail.
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR*);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR*, const TCHAR*, unsigned int);
extern TCHAR GCmdLine[];
extern const TCHAR LogfParam[];
extern const TCHAR LogfTag[];
const TCHAR* appStrfind(const TCHAR* Str, const TCHAR* Find)
{
    UBOOL Alnum  = 0;
    TCHAR f      = (*Find < 'a' || *Find > 'z') ? (*Find) : (TCHAR)(*Find + 'A' - 'a');
    INT   Length = (INT)wcslen(Find++) - 1;
    TCHAR c      = *Str++;
    while (c)
    {
        if (c >= 'a' && c <= 'z') c += 'A' - 'a';
        if (!Alnum && c == f && !_wcsnicmp(Str, Find, Length))
            return Str - 1;
        Alnum = (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
        c = *Str++;
    }
    return 0;
}
UBOOL ParseParam(const TCHAR* Stream, const TCHAR* Param)
{
    const TCHAR* Start = Stream;
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
void FOutputDevice::Logf(const TCHAR* Fmt, ...)
{
    TCHAR* Buffer = (TCHAR*)GMalloc->Malloc(0x10000, LogfTag);
    va_list Args;
    va_start(Args, Fmt);
    _vsnwprintf(Buffer, 0x8000, Fmt, Args);
    Serialize(Buffer, NAME_Error);
    GMalloc->Free(Buffer);
    if (!ParseParam(GCmdLine, LogfParam))
        Flush();
}
extern "C" FArchive* Driver_9970(void* Mem, HANDLE H, FOutputDevice* E, INT P) { return new(Mem) FArchiveFileWriter(H, E, P); }
extern "C" void Driver_99e0(FArchiveFileWriter* A) { A->~FArchiveFileWriter(); }
extern "C" void Driver_9a40(FArchive* A, INT P) { A->Seek(P); }
extern "C" UBOOL Driver_9a90(FArchiveFileWriter* A) { return A->FArchiveFileWriter::Close(); }
