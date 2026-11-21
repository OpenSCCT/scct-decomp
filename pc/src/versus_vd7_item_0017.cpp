// Work item 0017: Versus RVA 0x1259b0-0x125d06, AActor audio script natives.
//   0x1259b0 AActor::execGetAllPlayingSounds
//   0x125b80 AActor::execSetAudioZoom
//   0x125c00 AActor::execSetWeirdEffect
//   0x125c60 AActor::execPlayMusic

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
#define RESULT_DECL void *const Result

class UObject;
class UProperty;
class USound;
struct FFrame;

extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

struct FVector
{
    FLOAT X, Y, Z;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray();
    void Empty(INT ElementSize, INT Slack = 0)
    {
        ArrayNum = 0;
        if (Slack)
        {
            if (ArrayMax != Slack)
            {
                ArrayMax = Slack;
                if (!Data)
                    Data = GMalloc->Malloc(ElementSize * Slack, L"FArray::Empty");
                else
                    Data = GMalloc->Realloc(Data, ElementSize * Slack, L"FArray");
            }
        }
        else if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

template<class T> class TArray : public FArray
{
public:
    TArray();
    ~TArray();
    void Empty(INT Slack = 0)
    {
        FArray::Empty(sizeof(T), Slack);
    }
};

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property); // +0x54
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame
{
    void *VfTable;
    void *Node;         // +0x04
    UObject *Object;    // +0x08
    BYTE *Code;         // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    __forceinline void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

class UAudioSubsystem
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30();
    virtual INT PlayMusic(USound *Song, FLOAT FadeInTime);                  // +0x7c (slot 31)
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38(); virtual void Slot39();
    virtual void Slot40(); virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual void Slot44(); virtual void Slot45(); virtual void Slot46(); virtual void Slot47();
    virtual void Slot48(); virtual void Slot49(); virtual void Slot50();
    // +0xcc (slot 51); guess on parameter types (12-byte POD array and 4-byte POD array).
    virtual void GetAllPlayingSounds(TArray<FVector> *Locations, TArray<INT> *Ids);
    virtual void Slot52(); virtual void Slot53(); virtual void Slot54(); virtual void Slot55();
    virtual void Slot56(); virtual void Slot57(); virtual void Slot58(); virtual void Slot59();
    virtual void Slot60();
    virtual void DisableAudioZoom(INT Unused);                              // +0xf4 (slot 61)
    virtual void SetAudioZoom(FLOAT Zoom);                                  // +0xf8 (slot 62)
    virtual void SetWeirdEffect(INT Effect);                                // +0xfc (slot 63)
};

class UEngine
{
public:
    BYTE unk_00[0x34];
    UAudioSubsystem *Audio; // +0x34
};

class ULevel
{
public:
    BYTE unk_00[0xf0];
    UEngine *Engine;        // +0xf0
};

class AActor : public UObject
{
public:
    BYTE unk_04[0x1a0];
    ULevel *XLevel;         // +0x1a4

    void execGetAllPlayingSounds(FFrame &Stack, RESULT_DECL);
    void execSetAudioZoom(FFrame &Stack, RESULT_DECL);
    void execSetWeirdEffect(FFrame &Stack, RESULT_DECL);
    void execPlayMusic(FFrame &Stack, RESULT_DECL);
};

// Command-line query helpers (Core UnMisc.cpp / appCmdLine).
extern TCHAR GCmdLine[];
inline const TCHAR *appCmdLine() { return GCmdLine; }
extern const TCHAR Text_NoMusic[]; // L"nomusic"

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *S);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(
    const TCHAR *A, const TCHAR *B, unsigned int Count);
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count)
{
    return _wcsnicmp(A, B, Count);
}

#pragma auto_inline(off)
// 0x11f90: UE2 appStrfind (Str in EAX).
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find)
{
    UBOOL Alnum = 0;
    TCHAR f = (*Find < 'a' || *Find > 'z') ? (*Find) : (*Find + 'A' - 'a');
    INT Length = appStrlen(Find++) - 1;
    TCHAR c = *Str++;
    while (c)
    {
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        if (!Alnum && c == f && !appStrnicmp(Str, Find, Length))
            return Str - 1;
        Alnum = (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
        c = *Str++;
    }
    return 0;
}

// 0x121c0: UE2 ParseParam (Stream in EDI, Param in ESI).
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

#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT_OPTX(Var, Def) FLOAT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_ARRAY_REF(Type, Var) \
    Type Var##T[256]; \
    Stack.StepRef(Stack.Object, Var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    Type *Var = GPropAddr ? (Type *)GPropAddr : Var##T
#define P_FINISH Stack.Code++

// RVA 0x1259b0: AActor::execGetAllPlayingSounds
void AActor::execGetAllPlayingSounds(FFrame &Stack, RESULT_DECL)
{
    P_GET_ARRAY_REF(TArray<FVector>, Locations);
    P_GET_ARRAY_REF(TArray<INT>, Ids);
    P_FINISH;

    ULevel *Level = XLevel;
    if (Level->Engine->Audio)
    {
        Level->Engine->Audio->GetAllPlayingSounds(Locations, Ids);
    }
    else
    {
        Locations->Empty();
        Ids->Empty();
    }
}

// RVA 0x125b80: AActor::execSetAudioZoom
void AActor::execSetAudioZoom(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT_OPTX(Zoom, -1.0f);
    P_FINISH;

    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
    {
        if (Zoom >= 0.0f)
            Audio->SetAudioZoom(Zoom);
        else
            Audio->DisableAudioZoom(0);
    }
}

// RVA 0x125c00: AActor::execSetWeirdEffect
void AActor::execSetWeirdEffect(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Effect);
    P_FINISH;

    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->SetWeirdEffect(Effect);
}

// RVA 0x125c60: AActor::execPlayMusic
void AActor::execPlayMusic(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Song);
    P_GET_FLOAT(FadeInTime);
    P_FINISH;

    if (ParseParam(appCmdLine(), Text_NoMusic))
    {
        *(INT *)Result = 0;
        return;
    }

    INT Ret = 0;
    if (XLevel->Engine->Audio)
        Ret = XLevel->Engine->Audio->PlayMusic(Song, FadeInTime);
    *(INT *)Result = Ret;
}

// Scaffolding for LTCG link of execPlayMusic, not part of the unit.
void Escape(void *);
void Escape(UBOOL);
typedef void (AActor::*ActorNative)(FFrame &Stack, RESULT_DECL);
void Driver_125c60(ActorNative *Out, const TCHAR *S, const TCHAR *P)
{
    *Out = &AActor::execPlayMusic;
    Escape(GNatives);
    Escape(GCmdLine);
    Escape(ParseParam(S, P));
}
