// Work item 0342: Versus RVA 0x96b30-0x96eb5, UGameEngine methods.
// UGameEngine is identified by the reflected vtable (slots 27 and 30) and by
// the "VER" / "FLUSH" console commands of UGameEngine::Exec. The global at
// retail 0x10ca77f0 is GCache (FMemCache): Flush() calls it with the
// FMemCache::Flush(Id=0, Mask=~0, IgnoreLocked=0) arguments and Exec() asks
// it to handle console commands. Members whose role is not evident are named
// after their offset.
//
// The object was compiled with link-time code generation, so callees in it
// take custom conventions. Functions marked "stand-in" below are only there so
// the linker picks the same conventions as retail; their addresses are bound
// to the retail functions and their bodies are not part of the unit.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;
extern "C" void* memset(void* Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)
extern "C" __declspec(dllimport) unsigned int wcslen(const TCHAR* S);
extern "C" __declspec(dllimport) int _wcsnicmp(const TCHAR* A, const TCHAR* B, unsigned int Count);
inline INT appStrlen(const TCHAR* S) { return (INT)wcslen(S); }
inline INT appStrnicmp(const TCHAR* A, const TCHAR* B, INT Count) { return _wcsnicmp(A, B, Count); }
inline UBOOL appIsAlnum(TCHAR c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

class UObject;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Pad04();
    virtual void Pad08();
    virtual void Pad0C();
    virtual void Pad10();
    virtual void Pad14();
    virtual FArchive& operator<<(UObject*& Res);   // 0x18
};
template<class T> inline FArchive& operator<<(FArchive& Ar, T*& Res)
{
    return Ar << *(UObject**)&Res;
}

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;                           // retail 0x10c73bf0
inline void appFree(void* Original) { GMalloc->Free(Original); }
inline void operator delete(void* Ptr) { appFree(Ptr); }

class FString
{
public:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FString();                                    // RVA 0x48b0
    const TCHAR* operator*() const;
    static FString Printf(const TCHAR* Fmt, ...);  // RVA 0x11b20
};
extern const TCHAR GNullString[];                  // L"" (stand-in use only)
inline const TCHAR* FString::operator*() const { return ArrayNum ? Data : GNullString; }

extern DWORD GLogGate;                             // stand-in use only
struct FUnnamedLogSettings { DWORD Field0; DWORD Flags; };
struct FUnnamedLogOwner { unsigned char Pad[0x930]; FUnnamedLogSettings* Settings; };
extern FUnnamedLogOwner* GLogOwner;                // stand-in use only
extern TCHAR GCmdLine[];                           // stand-in use only
extern const TCHAR GUnnamedLogParam[];             // stand-in use only
const TCHAR* appStrfind(const TCHAR* Str, const TCHAR* Find);
// RVA 0x121c0 (Stream in EDI, Param in ESI): stand-in body.
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
enum { NAME_Log = 0x24c };

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR* V, INT Event);
    virtual void Flush();
    // RVA 0x117a0 (this in EBX, text on the stack): stand-in body.
    __declspec(noinline) void Log(const TCHAR* S)
    {
        if (!GLogGate || !(GLogOwner->Settings->Flags & 0x1000))
            Serialize(S, NAME_Log);
        if (!ParseParam(GCmdLine, GUnnamedLogParam))
            Flush();
    }
    // RVA 0x117f0 (this in EBX, string in EAX): stand-in body.
    __declspec(noinline) void Log(const FString& S)
    {
        if (!GLogGate || !(GLogOwner->Settings->Flags & 0x1000))
            Serialize(*S, NAME_Log);
        if (!ParseParam(GCmdLine, GUnnamedLogParam))
            Flush();
    }
};

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar);
};

// RVA 0x125e0 (Stream in ESI, Match in EBX).
__declspec(noinline) UBOOL ParseCommand(const TCHAR** Stream, const TCHAR* Match)
{
    while ((**Stream == ' ') || (**Stream == 9))
        (*Stream)++;
    if (appStrnicmp(*Stream, Match, appStrlen(Match)) == 0)
    {
        *Stream += appStrlen(Match);
        if (!appIsAlnum(**Stream))
        {
            while ((**Stream == ' ') || (**Stream == 9))
                (*Stream)++;
            return 1;
        }
        else
        {
            *Stream -= appStrlen(Match);
            return 0;
        }
    }
    else return 0;
}

class UObject
{
public:
    virtual ~UObject();
    virtual void Pad04();
    virtual void Pad08();
    virtual void ConditionalRelease(INT Flag);     // 0x0c
    virtual void Destroy();                        // RVA 0x15ce0
    virtual void Pad14();
    virtual void Pad18();
    virtual void Pad1C();
    virtual void Pad20();
    virtual void Pad24();
    virtual void Pad28();
    virtual void Pad2C();
    virtual void Pad30();
    virtual void Pad34();
    virtual void Pad38();
    virtual void Pad3C();
    virtual void Pad40();
    virtual void Pad44();
    virtual void Pad48();
    virtual void Pad4C();
    virtual void Pad50();
    virtual void Pad54();
    virtual void Pad58();
    DWORD ObjectFields[9];                         // 0x04..0x28
    void Serialize(FArchive& Ar);                  // RVA 0x15f50
    static UBOOL StaticExec(const TCHAR* Cmd, FOutputDevice& Ar); // RVA 0x188e0
};

class USubsystem : public UObject, public FExec
{
public:
    virtual void Pad5C();
    virtual void Pad60();
    virtual void Pad64();
    virtual void Pad68();
};

class UViewport : public UObject, public FOutputDevice
{
public:
    DWORD Field2C;                                 // 0x2c
    UObject* Actor;                                // 0x30
};

// The client object at UGameEngine+0x30.
class UClient : public UObject
{
public:
    virtual void Flush(UBOOL AllowPrecache);       // 0x5c
    virtual void Pad60();
    virtual void Pad64();
    virtual void Pad68();
    virtual void Pad6C();
    virtual void Pad70();
    virtual UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar); // 0x74
    DWORD Field28;                                 // 0x28
    UViewport** Viewports;                         // 0x2c (TArray data)
    INT ViewportsNum;
    INT ViewportsMax;
    DWORD Fields38[27];                            // 0x38..0xa4
    class UInteractionMaster* InteractionMaster;   // 0xa4
};

// Client+0xa4. RVA 0x10fa00 (this in ESI, arguments on the stack).
UBOOL UnnamedKeyHandler(INT Key, INT Unicode);
void UnnamedKeyNotify(class UInteractionMaster* Master);
class UInteractionMaster
{
public:
    INT Field0;
    __declspec(noinline) UBOOL MasterProcessKeyType(INT Key, INT Unicode) // stand-in body
    {
        UnnamedKeyNotify(this);
        Field0 = UnnamedKeyHandler(Key, Unicode);
        UnnamedKeyNotify(this);
        return Field0;
    }
};

void FArray_Remove(void* Array, INT Index, INT Count, INT ElementSize);
extern const TCHAR GUnnamedCommand[];              // stand-in use only

struct FCacheItem
{
    const TCHAR* Name;
    DWORD Fields04[4];
    FCacheItem* Next;                              // 0x14
};

// GCache, retail 0x10ca77f0.
struct FMemCache
{
    DWORD Initialized;                             // 0x00
    DWORD Fields04[4];
    void* Buffer14;                                // 0x14
    struct FCacheItem* First;                      // 0x18
    struct FCacheItem* Last;                       // 0x1c
    unsigned char Data20[0x10004];
    void* Buffer10024;                             // 0x10024
    // RVA 0x21fec0 (this in EDX): stand-in body.
    __declspec(noinline) void Exit()
    {
        memset(Data20, 0, sizeof(Data20));
        Fields04[0] = 0;
    }
    // RVA 0x220440 (this in EDI, arguments on the stack): stand-in body.
    __declspec(noinline) UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar)
    {
        if (ParseCommand(&Cmd, GUnnamedCommand))
        {
            for (FCacheItem* Item = First; Item != Last; Item = Item->Next)
                Ar.Log(Item->Name);
            return 1;
        }
        return 0;
    }
};
extern FMemCache GCache;
// RVA 0x21ffd0, FMemCache::Flush(QWORD Id, DWORD Mask, UBOOL IgnoreLocked);
// link-time code generation passes `this` on the stack, written as __stdcall.
void __stdcall FMemCache_Flush(FMemCache* This, QWORD Id, DWORD Mask, UBOOL IgnoreLocked);

extern FExec* GExec;                               // retail 0x10c946c8
extern USubsystem* GUnnamedSubsystem_946cc;        // retail 0x10c946cc
extern INT GUnnamed_9690c;                         // retail 0x10c9690c

// TArray<UObject*> (RVA 0x10bd60: RemoveItem, this in EDI).
struct FObjectArray
{
    UObject** Data;
    INT ArrayNum;
    INT ArrayMax;
    __declspec(noinline) INT RemoveItem(UObject* const& Item)
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if (Data[Index] == Item)
                FArray_Remove(this, Index--, 1, sizeof(UObject*));
        return OriginalNum - ArrayNum;
    }
};
extern FObjectArray GUnnamedEngineList;            // retail 0x10cc9ea4

void UnnamedShutdown_33390();                      // RVA 0x133390

// Global at retail 0x10c8bbe0 (RVA 0x57780 cleans it up, this on the stack).
struct FUnnamedGlobal_c8bbe0
{
    DWORD Fields[6];
    __declspec(noinline) void Cleanup()            // stand-in body
    {
        UnnamedShutdown_33390();
        FArray_Remove(this, 0, 1, 4);
    }
};
extern FUnnamedGlobal_c8bbe0 GUnnamedGlobal_c8bbe0;

// Object at retail 0x10c8bbf8 (destructor RVA 0x1346b0 and Exec RVA
// 0x134dc0, both with this on the stack).
class UnnamedSingleton_c8bbf8
{
public:
    DWORD Field0;
    __declspec(noinline) ~UnnamedSingleton_c8bbf8() // stand-in body
    {
        UnnamedShutdown_33390();
        FArray_Remove(this, 0, 0, 4);
    }
    __declspec(noinline) UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar) // stand-in body
    {
        if (ParseCommand(&Cmd, GUnnamedCommand))
        {
            Ar.Log(GUnnamedCommand);
            return 1;
        }
        return 0;
    }
};
extern UnnamedSingleton_c8bbf8* GUnnamedSingleton_c8bbf8;

// Strings live in writable .data in retail.
extern const TCHAR TEXT_VER[];                     // L"VER"
extern const TCHAR TEXT_VerFormat[];               // L"Ver: %d"
extern const TCHAR TEXT_FLUSH[];                   // L"FLUSH"
extern const TCHAR TEXT_FlushedEngineCaches[];     // L"Flushed engine caches"

class UGameEngine : public USubsystem
{
public:
    UObject*    Cylinder;                          // 0x2c
    UClient*    Client;                            // 0x30
    USubsystem* Field34;                           // 0x34
    UObject*    Field38;                           // 0x38
    DWORD       Field3C;                           // 0x3c
    USubsystem* Field40;                           // 0x40
    UObject*    Field44;                           // 0x44

    virtual void Flush(UBOOL AllowPrecache);       // slot 27 (0x6c)
    virtual void Pad70();
    virtual void Pad74();
    virtual UBOOL Key(UViewport* Viewport, INT Key, INT Unicode); // slot 30
    void Destroy();
    UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar);
    void ReleaseField34();
    void Serialize(FArchive& Ar);
};

// RVA 0x96b30
void UGameEngine::ReleaseField34()
{
    if (Field34)
    {
        Field34->ConditionalRelease(1);
        Field34 = 0;
    }
}

// RVA 0x96b50
void UGameEngine::Destroy()
{
    GUnnamedEngineList.RemoveItem(this);
    Field34 = 0;
    Client = 0;
    UnnamedShutdown_33390();
    GUnnamedGlobal_c8bbe0.Cleanup();
    if (GCache.Initialized)
    {
        GCache.Exit();
        appFree(GCache.Buffer14);
        appFree(GCache.Buffer10024);
        GCache.Initialized = 0;
    }
    if (GUnnamedSingleton_c8bbf8)
    {
        delete GUnnamedSingleton_c8bbf8;
        GUnnamedSingleton_c8bbf8 = 0;
    }
    UObject::Destroy();
}

// RVA 0x96bf0
void UGameEngine::Flush(UBOOL AllowPrecache)
{
    FMemCache_Flush(&GCache, 0, ~0ul, 0);
    if (Client)
        Client->Flush(AllowPrecache);
}

// RVA 0x96c50
void UGameEngine::Serialize(FArchive& Ar)
{
    UObject::Serialize(Ar);
    Ar << Cylinder << Client << Field34 << Field38 << Field40 << Field44;
}

// RVA 0x96cb0 (near match: retail materialises Valid with a branch,
// "mov ecx,1 / jne / xor ecx,ecx", where this compiles to setne; every
// other instruction matches, shifted by those 4 bytes).
UBOOL UGameEngine::Exec(const TCHAR* Cmd, FOutputDevice& Ar)
{
    if (GUnnamedSubsystem_946cc && GUnnamedSubsystem_946cc->Exec(Cmd, Ar))
        return 1;
    if (UObject::StaticExec(Cmd, Ar))
        return 1;
    if (GCache.Exec(Cmd, Ar))
        return 1;
    if (GExec && GExec->Exec(Cmd, Ar))
        return 1;
    if (Client && Client->Exec(Cmd, Ar))
        return 1;
    if (Field34 && Field34->Exec(Cmd, Ar))
        return 1;
    if (Field40 && Field40->Exec(Cmd, Ar))
        return 1;
    if (GUnnamedSingleton_c8bbf8 && GUnnamedSingleton_c8bbf8->Exec(Cmd, Ar))
        return 1;
    if (ParseCommand(&Cmd, TEXT_VER))
    {
        if (Client)
        {
            UViewport* Viewport = Client->Viewports[0];
            UBOOL Valid = Viewport != 0;
            if (Viewport->Actor && Valid)
                Client->Viewports[0]->Log(FString::Printf(TEXT_VerFormat, 167));
        }
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_FLUSH))
    {
        Flush(1);
        Ar.Log(TEXT_FlushedEngineCaches);
        return 1;
    }
    return 0;
}

// RVA 0x96e80
UBOOL UGameEngine::Key(UViewport* Viewport, INT Key, INT Unicode)
{
    if (!GUnnamed_9690c)
        return 0;
    UInteractionMaster* Master = Client->InteractionMaster;
    if (Master)
        return Master->MasterProcessKeyType(Key, Unicode);
    return 0;
}

// Scaffolding for the link, not part of the unit: calls each function the
// way retail does and makes the retail globals address-taken.
void Escape(void*);
inline void* operator new(unsigned int, void* Where) { return Where; }
INT Driver_96cb0(UGameEngine* E, const TCHAR* Cmd, FOutputDevice* Ar, UViewport* V, INT K, INT U, void* Mem)
{
    Escape(new (Mem) UGameEngine);                 // emits the vtable
    Escape(&GMalloc);
    Escape(&GUnnamedEngineList);
    Escape(&GUnnamedGlobal_c8bbe0);
    Escape(&GCache);
    Escape(&GUnnamedSingleton_c8bbf8);
    Escape(&GUnnamed_9690c);
    Escape(&GExec);
    Escape(&GUnnamedSubsystem_946cc);
    E->Destroy();
    E->Flush(0);
    INT R = ((FExec*)E)->Exec(Cmd, *Ar);
    return R + E->Key(V, K, U);
}
