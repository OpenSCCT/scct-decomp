// Work item 0399: Versus RVA 0x122ab0-0x122e59, 4 functions, 919 bytes.
// ALevelInfo::execGetLevelLoading (0x122ab0),
// ALevelInfo::GetLevelLoading (0x122b90),
// ALevelInfo::execGetLevelSettings (0x122ce0),
// ALevelInfo::execGetLocalPlayerController (0x122e20).

#pragma pack(push, 4)

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

#define NULL 0

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR*, const TCHAR*);
INT __cdecl appSprintf(TCHAR* Dest, const TCHAR* Fmt, ...);

inline INT appStricmp(const TCHAR* String1, const TCHAR* String2)
{
    return _wcsicmp(String1, String2);
}

extern TCHAR GEmptyTCHAR[]; // 0x10c10928, L""

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    INT Num() const { return ArrayNum; }
    T& operator()(INT i) { return ((T*)Data)[i]; }
    const T& operator()(INT i) const { return ((T*)Data)[i]; }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString& Other);          // 0x4640
    ~FString();                             // 0x48b0
    FString Right(INT Count) const;         // 0x40310
    const TCHAR* operator*() const { return Num() ? &(*this)(0) : GEmptyTCHAR; }
};

class UObject;
class UClass;
class ULevel;
class UPackageMap;
class APlayerController;
struct FFrame;

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR* V, INT Event);
};

struct FFrame : public FOutputDevice
{
    void* Node;
    UObject* Object;
    BYTE* Code;
    inline void Step(UObject* Context, void* const Result);
};

class UObject
{
public:
    virtual ~UObject();
    static UObject* __cdecl StaticLoadObject(
        UClass* Class, UObject* InOuter, const TCHAR* Name,
        const TCHAR* Filename, DWORD LoadFlags, UPackageMap* Sandbox); // 0x1adb0
};

typedef void (UObject::*Native)(FFrame& TheStack, void* Result);
extern Native GNatives[]; // 0x10c819d8

inline void FFrame::Step(UObject* Context, void* const Result)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

#define P_GET_STR(var)  FString var; Stack.Step(Stack.Object, &var);
#define P_GET_BYTE(var) BYTE var = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH        Stack.Code++;

extern UClass GLoadingTextureClass;       // 0x10cbd8c8
extern UClass GMapSettingsClass;          // 0x10cc9ed8

extern const TCHAR GStrErrSuffixLoading[];  // 0x10c47a2c, L"_ERR"
extern const TCHAR GStrLoadingTrue[];       // 0x10c47a38
extern const TCHAR GStrLoadingFalse[];      // 0x10c47a40
extern const TCHAR GStrLoadingFormat[];     // 0x10c47a48
extern const TCHAR GStrErrSuffixSettings[]; // 0x10c47a6c, L"_ERR"
extern const TCHAR GStrSettingsFormat[];    // 0x10c47a78

class AActor : public UObject
{
public:
    BYTE unk_4[0x1a4 - 4];
    ULevel* XLevel; // 0x1a4
};

class ALevelInfo : public AActor
{
public:
    BYTE unk_1a8[0x514 - 0x1a8];
    APlayerController* LocalPlayerController; // 0x514

    void FindLocalPlayerController(); // 0x122e60
    UObject* GetLevelLoading(FString MapName, BYTE bFlag, BYTE Index);
    void execGetLevelLoading(FFrame& Stack, void* const Result);
    void execGetLevelSettings(FFrame& Stack, void* const Result);
    void execGetLocalPlayerController(FFrame& Stack, void* const Result);
};

// ALevelInfo::execGetLevelLoading (RVA 0x122ab0)
void ALevelInfo::execGetLevelLoading(FFrame& Stack, void* const Result)
{
    P_GET_STR(MapName);
    P_GET_BYTE(bFlag);
    P_GET_BYTE(Index);
    P_FINISH;
    *(UObject**)Result = GetLevelLoading(MapName, bFlag, Index);
}

// ALevelInfo::GetLevelLoading (RVA 0x122b90)
UObject* ALevelInfo::GetLevelLoading(FString MapName, BYTE bFlag, BYTE Index)
{
    if (appStricmp(*MapName.Right(4), GStrErrSuffixLoading) == 0)
        return NULL;
    if (XLevel)
    {
        TCHAR Buf[256];
        appSprintf(Buf, GStrLoadingFormat, *MapName, bFlag ? GStrLoadingTrue : GStrLoadingFalse, Index);
        return UObject::StaticLoadObject(&GLoadingTextureClass, NULL, Buf, NULL, 0x2002, NULL);
    }
    return NULL;
}

// ALevelInfo::execGetLevelSettings (RVA 0x122ce0)
void ALevelInfo::execGetLevelSettings(FFrame& Stack, void* const Result)
{
    P_GET_STR(MapName);
    P_FINISH;
    if (appStricmp(*MapName.Right(4), GStrErrSuffixSettings) == 0)
    {
        *(UObject**)Result = NULL;
        return;
    }
    if (XLevel)
    {
        TCHAR Buf[256];
        appSprintf(Buf, GStrSettingsFormat, *MapName);
        *(UObject**)Result = UObject::StaticLoadObject(&GMapSettingsClass, NULL, Buf, NULL, 0x2002, NULL);
    }
    else
    {
        *(UObject**)Result = NULL;
    }
}

// ALevelInfo::execGetLocalPlayerController (RVA 0x122e20)
void ALevelInfo::execGetLocalPlayerController(FFrame& Stack, void* const Result)
{
    P_FINISH;
    if (LocalPlayerController == NULL)
        FindLocalPlayerController();
    *(APlayerController**)Result = LocalPlayerController;
}

#pragma pack(pop)

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void*);
void ExternalCall(void*);

void ALevelInfo::FindLocalPlayerController()
{
    APlayerController* P = LocalPlayerController;
    while (P)
    {
        ExternalCall(P);
        ExternalCall(P);
        ExternalCall(this);
        P = *(APlayerController**)P;
    }
    LocalPlayerController = P;
}

void Driver_0399()
{
    Escape(GNatives);
    Escape(GEmptyTCHAR);
    Native p1 = (Native)&ALevelInfo::execGetLevelLoading;
    Native p2 = (Native)&ALevelInfo::execGetLevelSettings;
    Native p3 = (Native)&ALevelInfo::execGetLocalPlayerController;
    Escape(&p1);
    Escape(&p2);
    Escape(&p3);
}
