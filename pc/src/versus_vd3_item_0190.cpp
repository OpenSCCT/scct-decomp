// Work item 0190: Versus RVA 0x48eb0-0x49245, UObject string script natives
// (UE2 Core UnScript.cpp): execLeft, execRight, execCaps, execChr, execAsc,
// execLog. The object was built with /GL and linked with /LTCG, so callees in
// it (FString::Left, FString::Caps, FString::operator=(const TCHAR*)) have
// register conventions; they are defined here only so the link gives them
// retail's conventions.

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned int size_t;

extern "C" __declspec(dllimport) size_t __cdecl wcslen(const TCHAR *);
extern const TCHAR EmptyString[];   // L"" shared in retail (0x10c10928)

template <class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : c + 'A' - 'a'; }
void appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern const TCHAR Text_FStringAssign[]; // L"FString::="
extern const TCHAR Text_FArray[];        // L"FArray"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Num() const { return ArrayNum; }
};

class FString : public FArray
{
public:
    FString() {}
    FString(INT InCount, const TCHAR *InSrc);
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const TCHAR *Other);
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
    TCHAR &operator[](INT i) { return ((TCHAR *)Data)[i]; }
    INT Len() const { return Num() ? Num() - 1 : 0; }
    FString Left(INT Count) const;
    FString Right(INT Count) const;
    FString Caps() const;
};

#pragma auto_inline(off)
// 0x4750 (another work item)
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), Text_FStringAssign);
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), Text_FArray);
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

// 0x4af0 (another work item): this in ESI, InCount in EAX.
TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT Max);
void FArray_Realloc(FArray *A, INT ElementSize);
FString::FString(INT InCount, const TCHAR *InSrc)
{
    ArrayNum = ArrayMax = InCount ? InCount + 1 : 0;
    Data = 0;
    FArray_Realloc(this, sizeof(TCHAR));
    if (ArrayNum)
        appStrncpy((TCHAR *)Data, InSrc, InCount + 1);
}

// 0xf7d0 (another work item): this in ECX, result in EAX, Count in EDX.
FString FString::Left(INT Count) const
{
    return FString(Clamp(Count, 0, Len()), **this);
}

// 0x40370 (another work item)
FString FString::Caps() const
{
    FString New(**this);
    for (INT i = 0; i < ArrayNum; i++)
        New[i] = appToUpper(New[i]);
    return New;
}
#pragma auto_inline(on)

enum EName { NAME_ScriptLog = 0x23a };
struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
};

class __single_inheritance UObject;
struct FFrame;
typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame
{
    void *Vtbl;
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, void *Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

class UObject
{
public:
    virtual void Dummy00();
    void execLeft(FFrame &Stack, void *const Result);
    void execRight(FFrame &Stack, void *const Result);
    void execCaps(FFrame &Stack, void *const Result);
    void execChr(FFrame &Stack, void *const Result);
    void execAsc(FFrame &Stack, void *const Result);
    void execLog(FFrame &Stack, void *const Result);
};

#define P_GET_STR(V) FString V; Stack.Step(Stack.Object, &V);
#define P_GET_INT(V) INT V = 0; Stack.Step(Stack.Object, &V);
#define P_GET_NAME_OPTX(V, Def) FName V = Def; Stack.Step(Stack.Object, &V);
#define P_FINISH Stack.Code++;

// 0x48eb0
void UObject::execLeft(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_INT(N);
    P_FINISH;
    *(FString *)Result = A.Left(N);
}

// 0x48f70
void UObject::execRight(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_INT(N);
    P_FINISH;
    *(FString *)Result = A.Right(N);
}

// 0x49030
void UObject::execCaps(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_FINISH;
    *(FString *)Result = A.Caps();
}

// 0x490d0
void UObject::execChr(FFrame &Stack, void *const Result)
{
    P_GET_INT(i);
    P_FINISH;
    TCHAR Temp[2];
    Temp[0] = i;
    Temp[1] = 0;
    *(FString *)Result = Temp;
}

// 0x49120
void UObject::execAsc(FFrame &Stack, void *const Result)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT *)Result = **S;
}

// 0x491b0: the release build compiles out the log output.
void UObject::execLog(FFrame &Stack, void *const Result)
{
    P_GET_STR(S);
    P_GET_NAME_OPTX(N, NAME_ScriptLog);
    P_FINISH;
}

// Scaffolding for the link, not part of the unit. The natives are reached
// through GNatives, so the driver takes their addresses.
void Escape(void *);
void Driver_48eb0(Native *Out)
{
    Escape(&GNatives);
    Out[0] = &UObject::execLeft;
    Out[1] = &UObject::execRight;
    Out[2] = &UObject::execCaps;
    Out[3] = &UObject::execChr;
    Out[4] = &UObject::execAsc;
    Out[5] = &UObject::execLog;
}
