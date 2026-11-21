// Work item 0162: Versus RVA 0xc9e30-0xca368 (Engine UInteraction natives).
//   0xc9e30 UInteraction::execConsoleCommand (matches:
//     try_ltcg.py --root "?Driver_c9e30@@YAXXZ" --flags "/O2 /Ob1 /Gy /GX")
//   0xc9f80 UInteraction::execWorldToScreen and 0xca160 (an LTCG constructor)
//     are not attempted here; their callees use unrecovered register conventions.
// Engine was built with /GL and linked with /LTCG. The natives keep the
// ordinary thiscall convention (reached through GNatives), but callees use
// link-time register conventions:
//   FOutputDevice::Logf (0x118d0): this in EBX.
// Callees defined below the unit exist only so the link gives them their
// retail conventions; they are not part of this unit.
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef char *va_list;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern "C" __declspec(dllimport) INT __cdecl _vsnwprintf(TCHAR *, unsigned int, const TCHAR *, va_list);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsstr(const TCHAR *, const TCHAR *);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

extern const TCHAR FString_Empty[];      // 0x10c10928: L""

class FString : public FArray
{
public:
    FString() {}
    ~FString();                          // 0x48b0
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : FString_Empty; }
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);
};
extern FOutputDevice *GLog;              // 0x10c71aa4
extern FOutputDevice *GLog_10c946bc;      // 0x10c946bc: unidentified log device used for warnings

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class UObject
{
public:
    virtual ~UObject();
    INT ObjectPad[9];
};

class UPlayer : public UObject, public FOutputDevice, public FExec
{
};

class UViewport : public UPlayer
{
};

class UClient : public UObject
{
public:
    INT ClientPad;
    TArray<UViewport *> Viewports;      // 0x2c
};

class UInteractionMaster : public UObject
{
public:
    UClient *Client;                     // 0x28
    UBOOL ExecViewport(const TCHAR *Cmd, FOutputDevice &Ar)
    {
        if (Client && Client->Viewports.Num())
            return Client->Viewports(0)->Exec(Cmd, Ar);
        return 0;
    }
};

struct FFrame;
class UInteraction : public UObject
{
public:
    DWORD Flags;                         // 0x28: bActive, bVisible, bRequiresTick
    UPlayer *ViewportOwner;              // 0x2c
    UInteractionMaster *Master;          // 0x30
    void execConsoleCommand(FFrame &Stack, void *const Result);
};
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];                // 0x10c819d8

struct FFrame : public FOutputDevice
{
    void *Node;
    UObject *Object;
    BYTE *Code;
    void *Locals;
    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

extern const TCHAR execConsoleCommand_NoMaster[];  // 0x10c4d8d0: L"Attempt to execute a console command through an Interaction that is without a master"
extern const TCHAR execConsoleCommand_InLog[];     // 0x10c4d97c: L"in_log"

// RVA 0xc9e30
void UInteraction::execConsoleCommand(FFrame &Stack, void *const Result)
{
    P_GET_STR(S);
    P_FINISH;
    if (!Master) {
        GLog_10c946bc->Logf(execConsoleCommand_NoMaster);
        return;
    }
    if (wcsstr(*S, execConsoleCommand_InLog))
        *(UBOOL *)Result = Master->ExecViewport(*S, *GLog);
    else if (ViewportOwner)
        *(UBOOL *)Result = Master->ExecViewport(*S, *ViewportOwner);
    else
        *(UBOOL *)Result = Master->ExecViewport(*S, *Master->Client->Viewports(0));
}

// ---- Callees defined only for their link-time conventions (not part of the unit).
extern TCHAR GCmdLine[];
extern const TCHAR Logf_LogFlushParam[];
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param);
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, L"Logf");
    va_list ArgPtr = (va_list)&Fmt + sizeof(Fmt);
    _vsnwprintf(Buffer, 0x8000, Fmt, ArgPtr);
    Serialize(Buffer, 0x24c);
    GMalloc->Free(Buffer);
    if (!ParseParam(GCmdLine, Logf_LogFlushParam))
        Flush();
}

const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);
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

// ---- Scaffolding for the link, not part of the unit.
void Escape(void *);
extern Native Driver_Table[];
void Driver_c9e30()
{
    Escape(&GLog);
    Escape(&GLog_10c946bc);
    Escape(&GMalloc);
    Driver_Table[0] = (Native)&UInteraction::execConsoleCommand;
}
