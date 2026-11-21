// Work item 0191: Versus RVA 0x49250-0x4944a (Core UnScript.cpp natives).
//   0x49250 UObject::execWarn
//   0x492f0 UObject::execLocalize
// Built with try_ltcg.py --root "?Driver_49250@@YAXXZ" --flags "/O2 /Ob1 /Gy /GX"; both match.
// execLocalize takes an optional section prefix: "Prefix.Section" when both names are set.
// Core was built with /GL and linked with /LTCG. The natives themselves keep
// the ordinary thiscall convention (they are reached through GNatives), but
// their callees use link-time register conventions:
//   FOutputDevice::Logf (0x118d0): this in EBX.
//   Localize (0x128b0): LangExt in EAX, Package in EBX, Key in EDI.
//   FString::operator=(const TCHAR*) (0x4750): this in ESI, Other in EDI.
// Those callees are defined here only so the link gives them their retail
// conventions; their bodies are simplified and are not part of this unit.
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef char *va_list;

enum EName { NAME_None = 0 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) INT __cdecl _vsnwprintf(TCHAR *, unsigned int, const TCHAR *, va_list);
void appMemcpy(void *Dest, const void *Src, INT Count);

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

extern FArray FName_Names;               // 0x10cc9e5c: FName::Names (TArray<FNameEntry*>)

class FName
{
public:
    INT Index;
    const TCHAR *operator*() const { return ((FNameEntry **)FName_Names.Data)[Index]->Name; }
    UBOOL operator==(EName N) const { return Index == N; }
};

extern const TCHAR FString_Empty[];      // 0x10c10928: L""

class FString : public FArray
{
public:
    FString() {}
    ~FString();                          // 0x48b0
    FString &operator=(const TCHAR *Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : FString_Empty; }
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);
};

struct FFrame;
class UObject
{
public:
    void execWarn(FFrame &Stack, void *const Result);
    void execLocalize(FFrame &Stack, void *const Result);
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
#define P_GET_NAME(Var) FName Var; Var.Index = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

INT appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);   // 0xf4f0
const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package, const TCHAR *LangExt = 0, UBOOL Optional = 0);

extern const TCHAR execWarn_Format[];      // 0x10c525a8: L"%s"
extern const TCHAR execLocalize_Format[];  // 0x10c525b0: L"%s.%s"

// RVA 0x49250
void UObject::execWarn(FFrame &Stack, void *const Result)
{
    P_GET_STR(S);
    P_FINISH;
    Stack.Logf(execWarn_Format, *S);
}

// RVA 0x492f0
void UObject::execLocalize(FFrame &Stack, void *const Result)
{
    P_GET_NAME(SectionPrefix);
    P_GET_NAME(SectionName);
    P_GET_NAME(KeyName);
    P_GET_NAME(PackageName);
    P_FINISH;
    if (SectionPrefix == NAME_None) {
        *(FString *)Result = Localize(*SectionName, *KeyName, *PackageName);
    } else if (SectionName == NAME_None) {
        *(FString *)Result = Localize(*SectionPrefix, *KeyName, *PackageName);
    } else {
        TCHAR Section[128];
        appSprintf(Section, execLocalize_Format, *SectionPrefix, *SectionName);
        *(FString *)Result = Localize(Section, *KeyName, *PackageName);
    }
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

class FConfigCache
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual const TCHAR *GetStr(const TCHAR *Section, INT Unknown, const TCHAR *Key, const TCHAR *Filename);
};
extern UBOOL GIsStarted;
extern FConfigCache *GConfig;
extern TCHAR GLanguage[];
extern TCHAR GEmptyLocalized[];
extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package, const TCHAR *LangExt, UBOOL Optional)
{
    if (!GIsStarted || !GConfig)
        return Key;
    if (!LangExt)
        LangExt = GLanguage;
    TCHAR Filename[256];
    for (;;) {
        appSprintf(Filename, L"%s.%s", Package, LangExt);
        if (const TCHAR *Result = GConfig->GetStr(Section, 0, Key, Filename))
            return Result;
        if (_wcsicmp(LangExt, L"int") == 0)
            break;
        LangExt = L"int";
    }
    return Optional ? GEmptyLocalized : Key;
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

FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data) {
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

// ---- Scaffolding for the link, not part of the unit.
void Escape(void *);
extern Native Driver_Table[];
void Driver_49250()
{
    Escape(&FName_Names);
    Escape(&GIsStarted);
    Escape(&GConfig);
    Escape(&GMalloc);
    Driver_Table[0] = &UObject::execWarn;
    Driver_Table[1] = &UObject::execLocalize;
}
