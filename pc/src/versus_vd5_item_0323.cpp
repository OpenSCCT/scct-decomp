// Work item 0323: UViewport::ExecMacro (Versus RVA 0x10bb40), the "EXEC <file>"
// handler reached from UViewport::Exec (0x10b3b0). Built /GL: Filename arrives
// in ECX, Ar in EAX, this on the stack (ret 4).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

enum EName { NAME_ExecWarning = 0x238 };
class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR* V, EName Event) = 0;
    virtual void Flush() = 0;
    void Logf(EName Event, const TCHAR* Fmt, ...);     // RVA 0x11850 (this in EBX, Event in EAX)
};

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar) = 0;
};

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                 // RVA 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize);
};

class FString
{
public:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
    const TCHAR* operator*() const { return ArrayNum ? Data : L""; }
};

class UObject
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual ~UObject();
    BYTE Pad[0x28];
};

// UTextBuffer: UObject (0x2c) + FOutputDevice (0x2c) + Pos/Top + Text (0x34).
class UTextBuffer : public UObject
{
public:
    void* OutputVtbl;
    INT Pos;
    FString Text;
};

class UObjectArray : public FArray
{
public:
    UObject*& operator()(INT i) { return ((UObject**)Data)[i]; }
    INT AddItem(UObject* const& Item) { INT Index = Add(1, sizeof(UObject*)); (*this)(Index) = Item; return Index; }
    INT RemoveItem(UObject* const& Item);              // RVA 0x10bd60
};

class UClass;
class ULevel;
class FFeedbackContext;
class AActor { public: BYTE Pad[0x1a4]; ULevel* XLevel; };

extern UClass UTextBuffer_PrivateStaticClass;          // 0x10cc9ff0
class FName { public: INT Index; FName(INT N) : Index(N) {} };
enum { NAME_None = 0 };
extern UObject* GObjTransientPkg;                      // UObject::GObjTransientPkg, 0x10c925b4
extern FFeedbackContext* GWarn;                        // 0x10c946bc
extern UObjectArray GObjRoot;                          // UObject::GObjRoot, 0x10cc9ea4
extern const TCHAR Text_CantFindFile[];                // L"Can't find file '%s'", 0x10c47f2c

class UFactory;
class UPackage;
// UFactory::StaticImportObject (RVA 0x59c40, cdecl).
UObject* StaticImportObject(ULevel* InLevel, UClass* Class, UObject* InOuter, FName Name, DWORD Flags,
                            const TCHAR* Filename, UObject* Context, UFactory* Factory,
                            const TCHAR* Parms, FFeedbackContext* Warn);
inline UObject* GetTransientPackage() { return GObjTransientPkg; }
template<class T> inline T* ImportObject(ULevel* InLevel, UObject* Outer, FName Name, DWORD Flags,
                                         const TCHAR* Filename, UObject* Context = 0,
                                         FFeedbackContext* Warn = GWarn)
{
    return (T*)StaticImportObject(InLevel, &UTextBuffer_PrivateStaticClass, Outer, Name, Flags, Filename, Context, 0, 0, Warn);
}
UBOOL ParseLine(const TCHAR** Stream, TCHAR* Result, INT MaxLen, UBOOL Exact = 0);  // RVA 0x127b0

class UViewport : public UObject, public FExec
{
public:
    AActor* Actor;                                     // 0x30
    UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar);
    void ExecMacro(const TCHAR* Filename, FOutputDevice& Ar);
};

void UViewport::ExecMacro(const TCHAR* Filename, FOutputDevice& Ar)
{
    UTextBuffer* Text = ImportObject<UTextBuffer>(Actor->XLevel, GetTransientPackage(), NAME_None, 0, Filename);
    if (Text)
    {
        GObjRoot.AddItem(Text);
        TCHAR Temp[256];
        const TCHAR* Data = *Text->Text;
        while (ParseLine(&Data, Temp, 256))
            Exec(Temp, Ar);
        GObjRoot.RemoveItem(Text);
        delete Text;
    }
    else
        Ar.Logf(NAME_ExecWarning, Text_CantFindFile, Filename);
}

// ---- Stand-in bodies for LTCG callees (so the linker picks retail conventions) ----
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR*, unsigned int, const TCHAR*, char*);
class FMalloc { public: virtual void* Malloc(DWORD, const TCHAR*) = 0; virtual void* Realloc(void*, DWORD, const TCHAR*) = 0; virtual void Free(void*) = 0; };
extern FMalloc* GMalloc;
struct FNameEntry { INT Index; DWORD Flags; };
extern FNameEntry** FName_Names;
extern INT FName_Initialized;
extern TCHAR GCmdLine[];
const TCHAR* appStrfind(const TCHAR* Str, const TCHAR* Find);
extern const TCHAR Text_Logf[];
extern const TCHAR Text_NOFLUSH[];
// UE2 ParseParam (retail 0x121c0: Stream in EDI, Param in ESI).
__declspec(noinline) UBOOL ParseParam(const TCHAR* Stream, const TCHAR* Param)
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
__declspec(noinline) void FOutputDevice::Logf(EName Event, const TCHAR* Fmt, ...)
{
    if (!FName_Initialized || !(FName_Names[Event]->Flags & 0x1000))
    {
        TCHAR* Buffer = (TCHAR*)GMalloc->Malloc(0x10000, Text_Logf);
        _vsnwprintf(Buffer, 0x8000, Fmt, (char*)(&Fmt + 1));
        Serialize(Buffer, Event);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, Text_NOFLUSH))
        Flush();
}

__declspec(noinline) UBOOL ParseLine(const TCHAR** Stream, TCHAR* Result, INT MaxLen, UBOOL Exact)
{
    UBOOL GotStream = 0;
    UBOOL IsQuoted = 0;
    UBOOL Ignore = 0;
    *Result = 0;
    while (**Stream != 0 && **Stream != 10 && **Stream != 13 && --MaxLen > 0) {
        if (!IsQuoted && !Exact && (*Stream)[0] == '/' && (*Stream)[1] == '/')
            Ignore = 1;
        if (!IsQuoted && !Exact && **Stream == '|')
            break;
        IsQuoted = IsQuoted ^ (**Stream == 34);
        GotStream = 1;
        if (!Ignore)
            *(Result++) = *((*Stream)++);
        else
            (*Stream)++;
    }
    if (Exact) {
        if (**Stream == 13) (*Stream)++;
        if (**Stream == 10) (*Stream)++;
    } else {
        while (**Stream == 10 || **Stream == 13 || **Stream == '|')
            (*Stream)++;
    }
    *Result = 0;
    return **Stream != 0 || GotStream;
}

__declspec(noinline) INT UObjectArray::RemoveItem(UObject* const& Item)
{
    INT OriginalNum = ArrayNum;
    for (INT Index = 0; Index < ArrayNum; Index++)
        if ((*this)(Index) == Item)
            Remove(Index--, 1, sizeof(UObject*));
    return OriginalNum - ArrayNum;
}

// Scaffolding for the link, not part of the unit.
void Escape(void*);
// RVA 0x126c0 (Str in EAX, Result in EBX): stand-in body.
__declspec(noinline) UBOOL ParseToken(const TCHAR *&Str, TCHAR *Result, INT MaxLen, UBOOL UseEscape)
{
    INT Len = 0;
    while (*Str == ' ' || *Str == 9)
        Str++;
    if (*Str == '"') {
        Str++;
        while (*Str && *Str != '"' && (Len + 1) < MaxLen) {
            TCHAR c = *Str++;
            if (c == '\\' && UseEscape) {
                c = *Str++;
                if (!c)
                    break;
            }
            if ((Len + 1) < MaxLen)
                Result[Len++] = c;
        }
        if (*Str == '"')
            Str++;
    } else {
        for (; *Str && *Str != ' ' && *Str != 9; Str++)
            if ((Len + 1) < MaxLen)
                Result[Len++] = *Str;
    }
    Result[Len] = 0;
    return Len != 0;
}

// Scaffolding: the EXEC branch of UViewport::Exec (0x10b3b0), the retail caller.
UBOOL Driver_10bb40(UViewport* V, const TCHAR* Cmd, FOutputDevice* Ar)
{
    Escape(&GWarn); Escape(&GObjRoot); Escape(&GObjTransientPkg); Escape(&GMalloc); Escape(&FName_Names); Escape(&FName_Initialized);
    TCHAR Filename[1024];
    if (ParseToken(Cmd, Filename, 1024, 0))
        V->ExecMacro(Filename, *Ar);
    return 1;
}

// Scaffolding: another Logf caller (GLog->Logf) so the linker sees retail-like call sites.
extern FOutputDevice* GLogDevice;
void Driver_Logf(const TCHAR* S, INT N)
{
    Escape(&GLogDevice);
    GLogDevice->Logf(NAME_ExecWarning, S, N);
}
