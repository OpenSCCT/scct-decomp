#include "versus_unicows_thunks.h"

// Work item 0042 (LTCG retry): FFileManagerWindows::CreateFileReader (RVA 0xa170)
// and CreateFileWriter (RVA 0xa230), UE2 FFileManagerWindows.h with the SCCT
// Versus addition of a compressed wrapper archive (fourth argument).
// Retail built this unit with /GL and linked with /LTCG, so the archive
// constructors they call have link-time register conventions; those
// constructors are defined below (shapes from items 0037, 0039, 0040, 0041)
// so the link assigns them the same conventions.

typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef long LONG;

#define NULL 0
#define GENERIC_READ 0x80000000
#define GENERIC_WRITE 0x40000000
#define FILE_SHARE_READ 1
#define CREATE_NEW 1
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define FILE_END 2
#define FILE_ATTRIBUTE_NORMAL 0x80
#define INVALID_HANDLE_VALUE ((HANDLE)-1)

enum EFileWrite
{
    FILEWRITE_NoFail            = 0x01,
    FILEWRITE_NoReplaceExisting = 0x02,
    FILEWRITE_EvenIfReadOnly    = 0x04,
    FILEWRITE_Unbuffered        = 0x08,
    FILEWRITE_Append            = 0x10,
    FILEWRITE_AllowRead         = 0x20,
};

extern "C" {
__declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE hFile, DWORD *lpFileSizeHigh);
__declspec(dllimport) DWORD __stdcall SetFilePointer(HANDLE, LONG, LONG *, DWORD);
__declspec(dllimport) HANDLE __stdcall CreateFileA(const ANSICHAR *, DWORD, DWORD, void *, DWORD, DWORD, HANDLE);
__declspec(dllimport) BOOL __stdcall SetFileAttributesA(const ANSICHAR *, DWORD);
__declspec(dllimport) void *__stdcall VirtualAlloc(void *, DWORD, DWORD, DWORD);
void *__cdecl _alloca(unsigned int);
}

// Dispatch slots for the wide Win32 entry points.

// Versus is Unicode-only; the ANSI half of TCHAR_CALL_OS is dead code but its
// appAlloca still forces the frame-pointer epilogue.
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

inline void *operator new(unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void *Ptr, const TCHAR *Tag) { GMalloc->Free(Ptr); }

// Retail keeps these literals in writable data.
extern const TCHAR Text_WindowsFileReader[]; // L"WindowsFileReader"
extern const TCHAR Text_WindowsFileWriter[]; // L"WindowsFileWriter"
extern const TCHAR Text_CompressedArchive[]; // allocation tag of the compressed wrappers (0x10c109d8)

class FOutputDevice;

class FArchive
{
public:
    FArchive()
    :   ArVer(175), ArNetVer(2000), ArLicenseeVer(0), ArIsLoading(0), ArIsSaving(0),
        ArIsTrans(0), ArIsPersistent(0), ArForEdit(1), ArForClient(1), ArForServer(1),
        ArIsError(0), ArIsCriticalError(0), Ar34(3), Ar38(0), Ar3C(-1)
    {}
    virtual ~FArchive() {}
    virtual void Serialize(void *V, INT Length);

    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
    UBOOL ArForEdit, ArForClient, ArForServer;
    UBOOL ArIsError, ArIsCriticalError;
    INT Ar34, Ar38, Ar3C;   // SCCT additions, names unknown
};

#pragma auto_inline(off)

// RVA 0x9640
class FArchiveFileReader : public FArchive
{
public:
    FArchiveFileReader(HANDLE InHandle, FOutputDevice *InError, INT InSize);
    HANDLE Handle; FOutputDevice *Error; INT Size, Pos, BufferBase, BufferCount; BYTE *Buffer;
};
FArchiveFileReader::FArchiveFileReader(HANDLE InHandle, FOutputDevice *InError, INT InSize)
:   Handle(InHandle), Error(InError), Size(InSize), Pos(0), BufferBase(0), BufferCount(0)
{
    ArIsLoading = ArIsPersistent = 1;
    Buffer = Handle ? (BYTE *)VirtualAlloc(0, Size, 0x1000, 4) : 0;
}

// RVA 0x9970
class FArchiveFileWriter : public FArchive
{
public:
    FArchiveFileWriter(HANDLE InHandle, FOutputDevice *InError, INT InPos);
    HANDLE Handle; FOutputDevice *Error; INT Pos, BufferCount; BYTE Buffer[4096];
};
FArchiveFileWriter::FArchiveFileWriter(HANDLE InHandle, FOutputDevice *InError, INT InPos)
:   Handle(InHandle), Error(InError), Pos(InPos), BufferCount(0)
{
    ArIsSaving = ArIsPersistent = 1;
}

// RVA 0x9be0 (neutral name; see item 0040)
class FArchiveCompressedReader_9be0 : public FArchive
{
public:
    FArchiveCompressedReader_9be0(FArchive *InInner);
    FArchive *Inner; INT Pos, BufferBase, Size, Total; BYTE *Buffer, *CompressedBuffer;
};
FArchiveCompressedReader_9be0::FArchiveCompressedReader_9be0(FArchive *InInner)
:   Inner(InInner), Pos(0), BufferBase(0), Size(0)
{
    ArIsLoading = ArIsPersistent = 1;
    DWORD Sizes[2];
    Inner->Serialize(Sizes, sizeof(Sizes));
    Buffer = (BYTE *)GMalloc->Malloc(Sizes[0], Text_CompressedArchive);
    CompressedBuffer = (BYTE *)GMalloc->Malloc(Sizes[1], Text_CompressedArchive);
    Inner->Serialize(CompressedBuffer, Sizes[1]);
    Size = Total = Sizes[0];
    GMalloc->Free(CompressedBuffer);
}

// RVA 0x9ee0 (neutral name; see item 0041)
class FArchiveCompressedWriter_9ee0 : public FArchive
{
public:
    FArchiveCompressedWriter_9ee0(FArchive *InInner);
    FArchive *Inner; INT TotalWritten, Count, Extra;
    BYTE Buffer[0xf00000]; INT BlockHeader[2]; BYTE Compressed[0xf00ff8];
    INT TotalUncompressed, TotalCompressed;
};
FArchiveCompressedWriter_9ee0::FArchiveCompressedWriter_9ee0(FArchive *InInner)
:   Inner(InInner), TotalWritten(0), Count(0), Extra(0), TotalUncompressed(0), TotalCompressed(0)
{
    ArIsSaving = ArIsPersistent = 1;
}

#pragma auto_inline(on)

class FFileManager
{
public:
    virtual void Init(UBOOL Startup);
    virtual FArchive *CreateFileReader(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Compressed);
    virtual FArchive *CreateFileWriter(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Compressed);
    virtual void Unknown0C();
    virtual INT FileSize(const TCHAR *Filename);
};
extern FFileManager *GFileManager;

class FFileManagerWindows : public FFileManager
{
public:
    FFileManagerWindows() {}
    FArchive *CreateFileReader(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Compressed);
    FArchive *CreateFileWriter(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Compressed);
};

// RVA 0xa170
FArchive *FFileManagerWindows::CreateFileReader(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Compressed)
{
    HANDLE Handle = TCHAR_CALL_OS(
        slot_CreateFileW(Filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL),
        CreateFileA(TCHAR_TO_ANSI(Filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL));
    if (Handle == INVALID_HANDLE_VALUE)
        return NULL;
    FArchive *Reader = new(Text_WindowsFileReader) FArchiveFileReader(Handle, Error, GetFileSize(Handle, NULL));
    if (Compressed)
        return new(Text_CompressedArchive) FArchiveCompressedReader_9be0(Reader);
    return Reader;
}

// RVA 0xa230
FArchive *FFileManagerWindows::CreateFileWriter(const TCHAR *Filename, DWORD Flags, FOutputDevice *Error, UBOOL Compressed)
{
    if (GFileManager->FileSize(Filename) >= 0 && (Flags & FILEWRITE_EvenIfReadOnly))
        TCHAR_CALL_OS(slot_SetFileAttributesW(Filename, 0), SetFileAttributesA(TCHAR_TO_ANSI(Filename), 0));
    DWORD Access   = GENERIC_WRITE;
    DWORD WinFlags = (Flags & FILEWRITE_AllowRead) ? FILE_SHARE_READ : 0;
    DWORD Create   = (Flags & FILEWRITE_Append) ? OPEN_ALWAYS : (Flags & FILEWRITE_NoReplaceExisting) ? CREATE_NEW : CREATE_ALWAYS;
    HANDLE Handle = TCHAR_CALL_OS(
        slot_CreateFileW(Filename, Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL),
        CreateFileA(TCHAR_TO_ANSI(Filename), Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL));
    INT Pos = 0;
    if (Handle == INVALID_HANDLE_VALUE)
        return NULL;
    if (Flags & FILEWRITE_Append)
        Pos = SetFilePointer(Handle, 0, 0, FILE_END);
    FArchive *Writer = new(Text_WindowsFileWriter) FArchiveFileWriter(Handle, Error, Pos);
    if (Compressed)
        return new(Text_CompressedArchive) FArchiveCompressedWriter_9ee0(Writer);
    return Writer;
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
FFileManager *Driver_a170(void *Mem, const TCHAR *F, DWORD Flags, FOutputDevice *E, UBOOL C)
{
    Escape(&GMalloc);
    Escape(&GFileManager);
    FFileManager *M = new(Mem) FFileManagerWindows;
    Escape(M);
    M->CreateFileReader(F, Flags, E, C);
    M->CreateFileWriter(F, Flags, E, C);
    return M;
}
