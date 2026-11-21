// Work item 0065 (LTCG retry): Versus RVA 0x10c60.
// A Dump(FOutputDevice&) member that logs "Files map" and dumps the TMap at
// offset 4 (UE2 TMapBase::Dump). The object was built with /GL and linked with
// /LTCG: the callees take their FOutputDevice in EBX (FOutputDevice::Log,
// retail 0x117a0) and the map in EDI with the device in EAX (TMapBase::Dump,
// retail 0x14780). The owning class is not identified: neutral name.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef char *va_list;

enum EName { NAME_Log = 0x24c };

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush();
    void Log(const TCHAR *S);
    void Logf(const TCHAR *Fmt, ...);
};

// Neutral stand-ins for the SCCT log filter state Log reads.
struct FLogFilter { INT Pad[1]; DWORD Flags; };
struct FLogOwner { unsigned char Pad[0x930]; FLogFilter *Filter; };
extern UBOOL GLogFilterActive;
extern FLogOwner *GLogOwner;
extern TCHAR GCmdLine[];
extern const TCHAR Text_LogFlushParam[];
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);
typedef unsigned int size_t;

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

extern const TCHAR Text_FilesMap[];      // L"Files map..." at 0x10c749f4
extern const TCHAR Text_TMapDump[];      // TMapBase::Dump header format
extern const TCHAR Text_TMapHashSlot[];  // TMapBase::Dump per-slot format

// Callees from other units, defined here (they were /GL objects too) so the
// link gives them the retail register conventions. Approximations: only
// their calling conventions matter for this unit.
#pragma auto_inline(off)
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

// Retail 0x118d0 (SCCT's Logf with a heap buffer; `this` in EBX).
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

void FOutputDevice::Log(const TCHAR *S)
{
    if (!GLogFilterActive || !(GLogOwner->Filter->Flags & 0x1000))
        Serialize(S, NAME_Log);
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}

struct FPairBase { INT HashNext; INT Pad[11]; };

class TMapBase
{
public:
    FPairBase *Pairs;
    INT PairsNum;
    INT PairsMax;
    INT *Hash;
    INT HashCount;
    void Dump(FOutputDevice &Ar);
};

void TMapBase::Dump(FOutputDevice &Ar)
{
    Ar.Logf(Text_TMapDump, PairsNum, HashCount);
    for (INT i = 0; i < HashCount; i++)
    {
        INT c = 0;
        for (INT j = Hash[i]; j != -1; j = Pairs[j].HashNext)
            c++;
        Ar.Logf(Text_TMapHashSlot, i, c);
    }
}

class UnnamedClass_10c60
{
public:
    TMapBase FileMap;               // offset 4, after the vtable
    virtual void Dump(FOutputDevice &Ar);
};

// 0x10c60
void UnnamedClass_10c60::Dump(FOutputDevice &Ar)
{
    Ar.Log(Text_FilesMap);
    FileMap.Dump(Ar);
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_10c60(UnnamedClass_10c60 *C, FOutputDevice *Ar, TMapBase *M, FOutputDevice *Ar2)
{
    UnnamedClass_10c60 Local;   // references the vtable so the virtual is kept
    Escape(&Local);
    C->Dump(*Ar);
    M->Dump(*Ar2);
    Ar2->Log(Text_FilesMap);
}
