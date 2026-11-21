// Work item 0330: Versus RVA 0x10cd80 and 0x10d010.
// Class names are neutral: the evidence (field offsets, vtable slots) does not
// identify the Unreal classes. UnnamedOwner_10cd80 is the object at this+0x68,
// which keeps a player list at +0x2c and eight back-pointers at +0x4fc.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned short TCHAR;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Remove(INT Index, INT Count, INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
};

class UnnamedObject_10cd80
{
public:
    virtual void VFunc00();
    virtual void VFunc04();
    virtual void VFunc08();
    virtual void Destroy(INT Flags); // slot 0x0c
};

class UnnamedPlayer_10cd80;

class UnnamedOwner_10cd80
{
public:
    char Pad00[0x2c];
    TArray<UnnamedPlayer_10cd80 *> Players; // 0x2c
    INT bLocked;                            // 0x38
    char Pad3c[0x100 - 0x3c];
    INT Count100;                           // 0x100
    char Pad104[0x4fc - 0x104];
    void *Refs[8];                          // 0x4fc
};

class UnnamedTarget_10cd80
{
public:
    char Pad00[0x1a4];
    void *Owner1a4;                         // 0x1a4
    char Pad1a8[0x4a4 - 0x1a8];
    INT Field4a4;                           // 0x4a4
};

class UnnamedSub_10cd80
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void Shutdown(); // slot 0x60
};

class UnnamedBase_10cd80
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6c();
    virtual void Cleanup(); // slot 0x70
    void Destroy(); // 0x10915ce0
};

class UnnamedPlayer_10cd80 : public UnnamedBase_10cd80
{
public:
    char Pad04[0x30 - 0x04];
    UnnamedTarget_10cd80 *Target;           // 0x30
    char Pad34[0x68 - 0x34];
    UnnamedOwner_10cd80 *Owner;             // 0x68
    INT bDeleted;                           // 0x6c
    char Pad70[0xb4 - 0x70];
    UnnamedObject_10cd80 *Objb4;            // 0xb4
    char Padb8[0xee8 - 0xb8];
    INT Fieldee8;                           // 0xee8
    INT Fieldeec;                           // 0xeec
    UnnamedSub_10cd80 *Subef0;              // 0xef0
    char Padef4[0x26fc - 0xef4];
    TArray<UnnamedObject_10cd80 *> Objects; // 0x26fc
    char Pad2708[0x47b0 - 0x2708];
    INT Field47b0;                          // 0x47b0
    char Pad47b4[0x49c0 - 0x47b4];
    void *Refs[8];                          // 0x49c0

    void Destroy();
};

extern INT GDAT_10c8bbf4;
extern INT GDAT_10c9690c;
void __stdcall FUN_10a1a790(void *Owner, UnnamedTarget_10cd80 *Target, INT Flag);

void UnnamedPlayer_10cd80::Destroy()
{
    if (Owner->Refs[0] == Target) Owner->Refs[0] = 0;
    if (Owner->Refs[1] == Target) Owner->Refs[1] = 0;
    if (Owner->Refs[2] == Target) Owner->Refs[2] = 0;
    if (Owner->Refs[3] == Target) Owner->Refs[3] = 0;
    if (Owner->Refs[4] == Target) Owner->Refs[4] = 0;
    if (Owner->Refs[5] == Target) Owner->Refs[5] = 0;
    if (Owner->Refs[6] == Target) Owner->Refs[6] = 0;
    if (Owner->Refs[7] == Target) Owner->Refs[7] = 0;

    for (INT i = 0; i < Owner->Players.Num(); i++)
    {
        if (Owner->Players(i)->Refs[0] == Target) Owner->Players(i)->Refs[0] = 0;
        if (Owner->Players(i)->Refs[1] == Target) Owner->Players(i)->Refs[1] = 0;
        if (Owner->Players(i)->Refs[2] == Target) Owner->Players(i)->Refs[2] = 0;
        if (Owner->Players(i)->Refs[3] == Target) Owner->Players(i)->Refs[3] = 0;
        if (Owner->Players(i)->Refs[4] == Target) Owner->Players(i)->Refs[4] = 0;
        if (Owner->Players(i)->Refs[5] == Target) Owner->Players(i)->Refs[5] = 0;
        if (Owner->Players(i)->Refs[6] == Target) Owner->Players(i)->Refs[6] = 0;
        if (Owner->Players(i)->Refs[7] == Target) Owner->Players(i)->Refs[7] = 0;
    }

    if (Subef0)
        Subef0->Shutdown();
    Cleanup();

    if ((Field47b0 || Fieldee8) && !Owner->bLocked && Fieldeec)
        Owner->Count100--;

    if (Owner->bLocked)
    {
        if (!GDAT_10c8bbf4)
            Owner->bLocked = 0;
    }
    else
    {
        TArray<UnnamedPlayer_10cd80 *> &List = Owner->Players;
        for (INT i = 0; i < List.Num(); i++)
        {
            if (List(i) == this)
                List.Remove(i--);
        }
    }

    bDeleted = 1;
    for (INT i = Objects.Num() - 1; i >= 0; i--)
    {
        if (Objects(i))
            Objects(i)->Destroy(1);
    }
    if (Objb4)
        Objb4->Destroy(1);

    if (GDAT_10c9690c && Target)
    {
        void *TargetOwner = Target->Owner1a4;
        Target->Field4a4 = 0;
        FUN_10a1a790(TargetOwner, Target, 1);
        Target = 0;
    }
    UnnamedBase_10cd80::Destroy();
}

// ---------------------------------------------------------------------------
// RVA 0x10d010: an Exec handler of a neutral-named class (UnnamedExec_10d010).
// Two console commands print a rounded field; anything else goes to the base
// class Exec at 0x10a06320. The object was built with /GL; ParseCommand
// (ESI = stream, EBX = match) and FOutputDevice::Logf (EBX = this) use LTCG
// register conventions. Retail keeps the strings in writable .data.

typedef unsigned int size_t;
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR *A, const TCHAR *B, size_t Count);
extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *S);
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count) { return _wcsnicmp(A, B, Count); }
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline UBOOL appIsAlnum(TCHAR c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

enum EName { NAME_None = 0 };

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);              // RVA 0x118d0 (this in EBX)
};

extern const TCHAR TEXT_GETPING[];                 // 0x10c47b78 "GETPING"
extern const TCHAR TEXT_Fmt_47b88[];               // 0x10c47b88 " %i"
extern const TCHAR TEXT_GETLOSS[];                 // 0x10c47b90 "GETLOSS"
extern const TCHAR TEXT_Fmt_47ba0[];               // 0x10c47ba0 " %i"


class UnnamedExecBase_10d010
{
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar); // RVA 0x10a06320
};

class UnnamedExec_10d010 : public UnnamedExecBase_10d010
{
public:
    char Pad04[0x18c - 0x04];
    FLOAT Field18c;                                // 0x18c
    char Pad190[0x1a4 - 0x190];
    FLOAT Field1a4;                                // 0x1a4
    UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);
};

// ---- Stand-ins: callees from other /GL units, defined only for their
// ---- link-time calling conventions. Not part of the unit.
#pragma auto_inline(off)
UBOOL ParseCommand(const TCHAR **Stream, const TCHAR *Match)
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
extern UBOOL GLogFilterActive;
struct FLogFilter { INT Pad[1]; DWORD Flags; };
struct FLogOwner { char Pad[0x930]; FLogFilter *Filter; };
extern FLogOwner *GLogOwner;
extern TCHAR GCmdLine[];
extern const TCHAR Text_LogFlushParam[];
extern const TCHAR Text_Logf[];
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
typedef char *va_list;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Dest, size_t Count, const TCHAR *Fmt, va_list Args);
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
        while ((Start = appStrfind(Start + 1, Param)) != 0)
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
    return 0;
}
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!GLogFilterActive || !(GLogOwner->Filter->Flags & 0x1000))
    {
        TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, Text_Logf);
        _vsnwprintf(Buffer, 0x8000, Fmt, (va_list)&Fmt + sizeof(Fmt));
        Serialize(Buffer, NAME_None);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}
#pragma auto_inline(on)

// ---- The unit: RVA 0x10d010.
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
UBOOL UnnamedExec_10d010::Exec(const TCHAR *Cmd, FOutputDevice &Ar)
{
    if (ParseCommand(&Cmd, TEXT_GETPING))
    {
        Ar.Logf(TEXT_Fmt_47b88, Max(5, (INT)(Field1a4 * 1000.f)));
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_GETLOSS))
    {
        Ar.Logf(TEXT_Fmt_47ba0, (INT)Field18c);
        return 1;
    }
    else return UnnamedExecBase_10d010::Exec(Cmd, Ar) ? 1 : 0;
}

// Scaffolding for the link, not part of the unit. Constructing the object
// in place emits its vtable so Exec keeps retail's virtual thiscall form.
void Escape(void *);
inline void *operator new(size_t, void *Mem) { return Mem; }
UBOOL Driver_10d010(void *Mem, const TCHAR *Cmd, FOutputDevice &Ar)
{
    Escape(&GMalloc); Escape(&GLogFilterActive);
    UnnamedExecBase_10d010 *E = new (Mem) UnnamedExec_10d010;
    Escape(E);
    return E->Exec(Cmd, Ar);
}
