// Work item 0341: Versus RVA 0x96830, UEngine::InitAudio (UE2 UnEngine.cpp).
// LTCG object: `this` arrives in EBX. Loads the configured audio subsystem
// class unless sound is disabled, constructs it and drops it if Init fails.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

// EName values used here; 0xc0 and 0xcf are SCCT name-table entries whose
// text was not recovered (neutral names).
enum EName { NAME_None = 0, NAME_Unknown_C0 = 0xc0, NAME_Unknown_CF = 0xcf };

class FName
{
public:
    FName(EName N) : Index(N) {}
    INT Index;
};

class FOutputDevice;
class UClass;

class UObject
{
public:
    virtual void VirtualSlot00();
    virtual void VirtualSlot04();
    virtual void VirtualSlot08();
    virtual ~UObject(); // 0x0c, scalar deleting destructor slot
};

class UClass : public UObject
{
public:
    unsigned char Pad04[0x100];
    void (*ClassConstructor)(void *); // 0x104
};

class UAudioSubsystem : public UObject
{
public:
    virtual void VirtualSlot10();
    virtual void VirtualSlot14();
    virtual void VirtualSlot18();
    virtual void VirtualSlot1C();
    virtual void VirtualSlot20();
    virtual void VirtualSlot24();
    virtual void VirtualSlot28();
    virtual void VirtualSlot2C();
    virtual void VirtualSlot30();
    virtual void VirtualSlot34();
    virtual void VirtualSlot38();
    virtual void VirtualSlot3C();
    virtual void VirtualSlot40();
    virtual void VirtualSlot44();
    virtual void VirtualSlot48();
    virtual void VirtualSlot4C();
    virtual void VirtualSlot50();
    virtual void VirtualSlot54();
    virtual void VirtualSlot58();
    virtual UBOOL Init(); // 0x5c
};

extern UClass UAudioSubsystem_PrivateStaticClass; // UAudioSubsystem::StaticClass()
extern UBOOL GIsClient;
extern UObject *GTransientPackage;  // inlined UObject::GetTransientPackage()
extern FOutputDevice *GError;
extern TCHAR GCmdLine[];             // appCmdLine() buffer
extern const TCHAR Text_nosound[];   // L"nosound"

extern UClass UClass_PrivateStaticClass; // UClass::StaticClass()
// Retail 0x1afe0: SCCT's object loader (neutral parameter names).
UObject *StaticLoadObject(UClass *ObjectClass, UObject *InOuter, FName Name1, FName Name2,
                          FName Name3, void *Extra1, DWORD LoadFlags, void *Extra2);
// Retail 0x1b390: SCCT's class loader. A /GL unit; this stand-in only gives
// the link the same register convention (Extra1 in EDX, Extra2 in ECX).
#pragma auto_inline(off)
UClass *StaticLoadClass(UClass *BaseClass, UObject *InOuter, FName Name1, FName Name2,
                        FName Name3, DWORD LoadFlags, void *Extra1, void *Extra2)
{
    try
    {
        return (UClass *)StaticLoadObject(&UClass_PrivateStaticClass, InOuter, Name1, Name2, Name3, Extra1, LoadFlags | 8, Extra2);
    }
    catch (...)
    {
        return 0;
    }
}
#pragma auto_inline(on)
// Retail 0x1d380.
UObject *StaticConstructObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                               UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot,
                               UObject *InstanceGraph);

inline const TCHAR *appCmdLine() { return GCmdLine; }
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

// UE2 ParseParam (retail 0x121c0: Stream in EDI, Param in ESI). Defined here
// so the link gives it the retail register convention.
#pragma auto_inline(off)
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
#pragma auto_inline(on)

template <class T> inline T *ConstructObject(UClass *Class, UObject *Outer, FName Name = NAME_None, DWORD SetFlags = 0)
{
    T *Result = (T *)StaticConstructObject(Class, Outer, Name, SetFlags, 0, GError, 0, 0);
    if (Result)
        Class->ClassConstructor(Result);
    return Result;
}

class UEngine : public UObject
{
public:
    unsigned char Pad04[0x30];
    UAudioSubsystem *Audio;   // 0x34
    unsigned char Pad38[0x6c];
    DWORD UseSound : 1;       // 0xa4
    void InitAudio();
};

// 0x96830
void UEngine::InitAudio()
{
    if (UseSound && GIsClient && !ParseParam(appCmdLine(), Text_nosound))
    {
        UClass *AudioClass = StaticLoadClass(&UAudioSubsystem_PrivateStaticClass, 0, NAME_Unknown_C0, NAME_None, NAME_Unknown_CF, 1, 0, 0);
        Audio = ConstructObject<UAudioSubsystem>(AudioClass, GTransientPackage);
        if (!Audio->Init())
        {
            delete Audio;
            Audio = 0;
        }
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_96830(UEngine *E) { Escape(&GIsClient); Escape(&GTransientPackage); Escape(&GError); E->InitAudio(); }
