// Work item 0398: Versus RVA 0x122620-0x122aa6, ALevelInfo script natives and helpers.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

#define NULL 0
#define RESULT_DECL void *const Result
#define TEXT(s) L##s

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);

inline INT appStricmp(const TCHAR *A, const TCHAR *B)
{
    return _wcsicmp(A, B);
}

INT __cdecl appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

template<class T> class TArray : public FArray
{
public:
    ~TArray();
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);

    const TCHAR *operator*() const
    {
        return ArrayNum ? (const TCHAR *)Data : TEXT("");
    }

    bool operator==(const TCHAR *Other) const
    {
        return appStricmp(**this, Other) == 0;
    }

    FString Right(INT Count) const;
    static FString __cdecl Printf(const TCHAR *Fmt, ...);
};

class UClass;
class UField;
class UPackageMap;
struct FFrame;

enum ELoadFlags
{
    LOAD_NoWarn = 0x0002,
    LOAD_Quiet  = 0x2000,
};

class UObject
{
public:
    virtual ~UObject();

    BYTE unk_04[0x24 - 0x04];
    UClass *Class;

    inline UBOOL IsA(UClass *SomeBase) const;

    static UObject *__cdecl StaticLoadObject(
        UClass *ObjectClass,
        UObject *InOuter,
        const TCHAR *InName,
        const TCHAR *Filename,
        DWORD LoadFlags,
        UPackageMap *Sandbox);
};

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
};

class UStruct : public UField {};
class UState : public UStruct {};
class UClass : public UState {};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

template<class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : NULL;
}

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame
{
    void *VTable;
    void *Node;
    UObject *Object;
    BYTE *Code;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UTexture : public UObject
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UEngine : public UObject
{
};

class ULevel;

class UGameEngine : public UEngine
{
public:
    BYTE unk_28[0x130 - 0x28];
    ULevel *GLevel;
    ULevel *GEntry;

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

struct FURL
{
    FString Protocol;
    FString Host;
    INT Port;
};

class ULevel : public UObject
{
public:
    BYTE unk_28[0xf0 - 0x28];
    UEngine *Engine;
    FURL URL;
};

class AActor : public UObject
{
public:
    BYTE unk_28[0x1a4 - 0x28];
    ULevel *XLevel;
};

class ALevelInfo : public AActor
{
public:
    void execGetAddressURL(FFrame &Stack, RESULT_DECL);
    void execIsEntry(FFrame &Stack, RESULT_DECL);
    void execGetLevelBrief(FFrame &Stack, RESULT_DECL);
    UTexture *GetLevelBrief(FString MapName);
    UTexture *GetLevelPicture(FString MapName);
    void execGetLevelPicture(FFrame &Stack, RESULT_DECL);
};

// RVA 0x122620
void ALevelInfo::execGetAddressURL(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FString *)Result = FString::Printf(TEXT("%s:%i"), *XLevel->URL.Host, XLevel->URL.Port);
}

// RVA 0x1226b0
void ALevelInfo::execIsEntry(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    *(UBOOL *)Result = 0;
    if (XLevel)
    {
        UGameEngine *GameEngine = Cast<UGameEngine>(XLevel->Engine);
        if (GameEngine)
        {
            if (GameEngine->GEntry == NULL || GameEngine->GLevel == GameEngine->GEntry)
                *(UBOOL *)Result = 1;
        }
    }
}

// RVA 0x122710
void ALevelInfo::execGetLevelBrief(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(MapName);
    P_FINISH;
    *(UTexture **)Result = GetLevelBrief(MapName);
}

// RVA 0x1227b0
UTexture *ALevelInfo::GetLevelBrief(FString MapName)
{
    if (MapName.Right(4) == TEXT("_ERR"))
        return NULL;
    if (XLevel)
    {
        TCHAR Buffer[256];
        appSprintf(Buffer, TEXT("%s.i_Briefing"), *MapName);
        return (UTexture *)UObject::StaticLoadObject(
            UTexture::StaticClass(), NULL, Buffer, NULL, LOAD_NoWarn | LOAD_Quiet, NULL);
    }
    return NULL;
}

// RVA 0x1228e0
UTexture *ALevelInfo::GetLevelPicture(FString MapName)
{
    if (MapName.Right(4) == TEXT("_ERR"))
        return NULL;
    if (XLevel)
    {
        TCHAR Buffer[256];
        appSprintf(Buffer, TEXT("%s.i_Menu"), *MapName);
        return (UTexture *)UObject::StaticLoadObject(
            UTexture::StaticClass(), NULL, Buffer, NULL, LOAD_NoWarn | LOAD_Quiet, NULL);
    }
    return NULL;
}

// RVA 0x122a10
void ALevelInfo::execGetLevelPicture(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(MapName);
    P_FINISH;
    *(UTexture **)Result = GetLevelPicture(MapName);
}

// Scaffolding for LTCG links, not part of the unit.
typedef void (ALevelInfo::*LevelNative)(FFrame &, RESULT_DECL);
void Escape(void *);

void Driver_122710(ALevelInfo *Self, FFrame &Stack, void *Result, FString S)
{
    LevelNative Fn = &ALevelInfo::execGetLevelBrief;
    Escape(&Fn);
    (Self->*Fn)(Stack, Result);
    Escape(Self->GetLevelBrief(S));
}

void Driver_122a10(ALevelInfo *Self, FFrame &Stack, void *Result, FString S)
{
    LevelNative Fn = &ALevelInfo::execGetLevelPicture;
    Escape(&Fn);
    (Self->*Fn)(Stack, Result);
    Escape(Self->GetLevelPicture(S));
}
