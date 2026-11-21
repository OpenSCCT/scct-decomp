// Work item 0217 (wave 3): Versus RVA 0xec850-0xecbf4.
// Three functions from the UGameEngine object (UnGame.cpp), which retail built
// with /GL and linked with /LTCG: Logf takes the device in EBX, ParseParam
// takes Stream in EDI and Param in ESI, FString::operator= takes `this` in ESI
// and the text in EDI, and TFieldIterator::IterateToNext takes `this` in ESI.
// Those callees are defined below (approximate bodies) so the link gives them
// the same register conventions as retail.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned int size_t;
typedef char *va_list;
#define va_start(ap, v) (ap = (va_list)&v + sizeof(v))

enum EName { NAME_Log = 0x24c };
enum { RF_Suppress = 0x1000 };

extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Dest, size_t Count, const TCHAR *Fmt, va_list Args);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR *, const TCHAR *, size_t);

// Retail appStrfind, defined so ParseParam's link sees the same callee.
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find)
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

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern TCHAR GCmdLine[];                  // the command line buffer
extern const TCHAR Text_LogFlushParam[];  // the switch Log tests before flushing
extern const TCHAR Text_Logf[];           // Logf allocation tag

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};

class FName
{
public:
    INT Index;
    const TCHAR *operator*() const { return Names[Index]->Name; }
    static UBOOL SafeSuppressed(EName N) { return Initialized && (Names[N]->Flags & RF_Suppress) != 0; }
    static FNameEntry **Names;  // FName::Names.Data
    static UBOOL Initialized;
};

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString &operator=(const TCHAR *Other);
};

// UE2 ParseParam (retail 0x121c0: Stream in EDI, Param in ESI).
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

// Retail 0x4750.
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}
#pragma auto_inline(on)

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush();
    void Log(const TCHAR *S)
    {
        if (!FName::SafeSuppressed(NAME_Log))
            Serialize(S, NAME_Log);
        if (!ParseParam(GCmdLine, Text_LogFlushParam))
            Flush();
    }
    void Logf(const TCHAR *Fmt, ...);
};

// Stand-in for retail 0x118d0 (SCCT's Logf with a heap buffer), shaped like
// retail so the link gives it the same convention (`this` in EBX).
#pragma auto_inline(off)
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, Text_Logf);
    va_list Args;
    va_start(Args, Fmt);
    _vsnwprintf(Buffer, 0x8000, Fmt, Args);
    Serialize(Buffer, NAME_Log);
    GMalloc->Free(Buffer);
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}
#pragma auto_inline(on)

class UClass;
class UStruct;

class UObject
{
public:
    virtual void UObjectVirtual00(); // UObject's own virtuals are not needed here
    BYTE Pad04[0x1c];
    FName Name;        // 0x20
    UClass *Class;     // 0x24
    UClass *GetClass() const { return Class; }
    const TCHAR *GetName() const { return *Name; }
    const TCHAR *GetPathName(UObject *StopOuter = 0, TCHAR *Str = 0) const; // retail 0x15d90
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject
{
public:
    UField *SuperField; // 0x28
    UField *Next;       // 0x2c
};

class UStruct : public UField
{
public:
    UField *Children;   // 0x30
    UStruct *GetSuperStruct() const { return (UStruct *)SuperField; }
    virtual UStruct *GetInheritanceSuper();
    UBOOL IsChildOf(const UStruct *SomeBase) const
    {
        for (const UStruct *Struct = this; Struct; Struct = Struct->GetSuperStruct())
            if (Struct == SomeBase)
                return 1;
        return 0;
    }
};

class UClass : public UStruct
{
public:
    BYTE Pad34[0x88 - 0x34];
    DWORD ClassFlags;   // 0x88
    BYTE Pad8C[0xac - 0x8c];
    BYTE *Defaults;     // 0xac, Defaults.Data
    BYTE *GetDefaults() { return Defaults; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

enum { CPF_ExportObject = 0x10000 }; // the flag the dump tests; name is a guess

class UProperty : public UField
{
public:
    SWORD ArrayDim;      // 0x30
    SWORD ElementSize;   // 0x32
    DWORD PropertyFlags; // 0x34
    BYTE Pad38[4];
    INT Offset;          // 0x3c
    // Slots 1-33 stand in for the UObject/UField/UProperty virtuals before ExportText.
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void V25(); virtual void V26(); virtual void V27(); virtual void V28();
    virtual void V29(); virtual void V30(); virtual void V31(); virtual void V32();
    virtual void V33();
    virtual UBOOL ExportText(INT ArrayElement, TCHAR *ValueStr, BYTE *Data, BYTE *Delta, INT PortFlags) const; // slot 34
};

class UObjectProperty : public UProperty
{
public:
    BYTE Pad40[0x58 - 0x40];
    UClass *PropertyClass; // 0x58
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class AActor : public UObject
{
public:
    BYTE Pad28[0x2f0 - 0x28];
    DWORD ActorFlags2F0;   // bit 4 enables the dump (neutral name)
    BYTE Pad2F4[0x434 - 0x2f4];
    DWORD ActorFlags434;   // LevelInfo flags; bit 0x40 is tested by GetMaxTickRate (neutral name)
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template<class T> class TFieldIterator
{
public:
    TFieldIterator(UStruct *InStruct) : Struct(InStruct), Field(InStruct ? InStruct->Children : 0) { IterateToNext(); }
    operator UBOOL() { return Field != 0; }
    void operator++() { Field = Field->Next; IterateToNext(); }
    T *operator*() { return (T *)Field; }
    T *operator->() { return (T *)Field; }
    void IterateToNext();
protected:
    UStruct *Struct;
    UField *Field;
};

enum { CLASS_IsAUProperty = 0x8000 };

// Retail 0x1f850 (out of line, `this` in ESI).
template<class T> __declspec(noinline) void TFieldIterator<T>::IterateToNext()
{
    while (Struct)
    {
        while (Field)
        {
            if (Field->GetClass()->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

extern const TCHAR Text_ClassName[];   // 0x10c49b80, "Class %s Name %s..."
extern const TCHAR Text_IndexFmt[];    // 0x10c49bac, "[%i]"
extern const TCHAR Text_Equals[];      // 0x10c49bb8
extern const TCHAR Text_None[];        // 0x10c49bbc, "None"
extern const TCHAR Text_ObjectFmt[];   // 0x10c49bc8
extern const TCHAR Text_ValueFmt[];    // 0x10c49bd4, "%s..."
extern const TCHAR Text_DumpEnd[];     // 0x10c49be0

// The unit's own functions are virtuals or called from elsewhere; keep the
// link from inlining them into the drivers.
#pragma auto_inline(off)

// 0xec850. Dumps an actor's exportable properties to Ar (neutral name: the
// original's name is not known). Near match: 9 bytes differ, retail reloads
// Actor (EDI) before i (EBX) after the last Logf; this source reloads them in
// the other order.
void DumpActorProperties(FOutputDevice &Ar, AActor *Actor)
{
    if (!(Actor->ActorFlags2F0 & 4))
        return;
    TCHAR Value[1024];
    Ar.Logf(Text_ClassName, Actor->GetClass()->GetPathName(), Actor->GetName());
    for (TFieldIterator<UProperty> It(Actor->GetClass()); It; ++It)
    {
        for (INT i = 0; i < It->ArrayDim; i++)
        {
            if ((It->PropertyFlags & CPF_ExportObject)
             && It->ExportText(i, Value, (BYTE *)Actor, &Actor->GetClass()->Defaults[0], 0))
            {
                Ar.Log(It->GetName());
                if (It->ArrayDim != 1)
                    Ar.Logf(Text_IndexFmt, i);
                Ar.Log(Text_Equals);
                if (It->IsA(UObjectProperty::StaticClass())
                 && ((UObjectProperty *)*It)->PropertyClass->IsChildOf(AActor::StaticClass()))
                {
                    UObject *Obj = *(UObject **)((BYTE *)Actor + It->Offset + i * It->ElementSize);
                    Ar.Logf(Text_ObjectFmt, Obj ? Obj->GetName() : Text_None);
                }
                Ar.Logf(Text_ValueFmt, Value);
            }
        }
    }
    Ar.Logf(Text_DumpEnd);
}

class UNetConnection
{
public:
    BYTE Pad00[0x44];
    INT CurrentNetSpeed;     // 0x44
};

class UNetDriver
{
public:
    BYTE Pad00[0x38];
    UNetConnection *ServerConnection; // 0x38
    BYTE Pad3C[0x68 - 0x3c];
    INT NetServerMaxTickRate; // 0x68
    INT LanServerMaxTickRate; // 0x6c
};

class ULevel
{
public:
    BYTE Pad00[0x2c];
    AActor **Actors;         // 0x2c, Actors.Data
    BYTE Pad30[0xec - 0x30];
    UNetDriver *NetDriver;   // 0xec
};

class UPlayer
{
public:
    BYTE Pad00[0x11c];
    INT TravelType;          // 0x11c
    FString TravelURL;       // 0x120
    UBOOL bTravelItems;      // 0x12c
};

extern UBOOL GIsClient;
extern UBOOL GTravelPending;  // 0x10c924a8, set when a client travel is queued (neutral name)
extern const TCHAR Text_LanPlay[]; // L"lanplay"
extern FLOAT GetMaxTickRate_NetSpeedScale; // 0x10c10cc4
extern FLOAT GetMaxTickRate_ClientMax;     // 0x10c10d30

template<class T> inline T Clamp(T X, T Min, T Max) { return X < Min ? Min : X < Max ? X : Max; }
template<class T> inline T Min(T A, T B) { return A <= B ? A : B; }

class UGameEngine
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37();
    virtual void SetClientTravel(UPlayer *Viewport, const TCHAR *NextURL, UBOOL bItems, INT TravelType); // slot 38
    virtual void V39();
    virtual FLOAT GetMaxTickRate(); // slot 40
    virtual void V41(); virtual void V42(); virtual void V43(); virtual void V44();
    virtual void V45(); virtual void V46(); virtual void V47(); virtual void V48();
    virtual void V49(); virtual void V50();
    virtual void CancelPending(); // slot 51

    BYTE Pad04[0x130 - 4];
    ULevel *GLevel;          // 0x130
    BYTE Pad134[4];
    void *GPendingLevel;     // 0x138
};

// 0xecac0, UGameEngine vtable slot 38.
void UGameEngine::SetClientTravel(UPlayer *Viewport, const TCHAR *NextURL, UBOOL bItems, INT TravelType)
{
    if (GPendingLevel)
        CancelPending();
    Viewport->TravelURL = NextURL;
    Viewport->TravelType = TravelType;
    Viewport->bTravelItems = bItems;
    GTravelPending = 1;
}

extern DWORD GetMaxTickRate_Guard;   // guard bits of the local static below
extern UBOOL GetMaxTickRate_LanPlay; // local static: ParseParam(appCmdLine(), "lanplay")

// 0xecb10, UGameEngine vtable slot 40.
FLOAT UGameEngine::GetMaxTickRate()
{
    if (!(GetMaxTickRate_Guard & 1))
    {
        GetMaxTickRate_Guard |= 1;
        GetMaxTickRate_LanPlay = ParseParam(GCmdLine, Text_LanPlay);
    }
    if (GLevel && GLevel->NetDriver && !GIsClient)
        return (FLOAT)Clamp(GetMaxTickRate_LanPlay ? GLevel->NetDriver->LanServerMaxTickRate : GLevel->NetDriver->NetServerMaxTickRate, 10, 120);
    else if (GLevel && GLevel->NetDriver && GLevel->NetDriver->ServerConnection && (GLevel->Actors[0]->ActorFlags434 & 0x40))
        return Min(GetMaxTickRate_ClientMax, GLevel->NetDriver->ServerConnection->CurrentNetSpeed * GetMaxTickRate_NetSpeedScale);
    else
        return 0.f;
}

#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_ec850(FOutputDevice *Ar, AActor *A) { Escape(&FName::Names); Escape(&FName::Initialized); DumpActorProperties(*Ar, A); }
void Driver_ecac0(UGameEngine *E, UPlayer *P, const TCHAR *U, UBOOL B, INT T) { E->UGameEngine::SetClientTravel(P, U, B, T); }
FLOAT Driver_ecb10(UGameEngine *E) { Escape(&GetMaxTickRate_Guard); return E->UGameEngine::GetMaxTickRate(); }
