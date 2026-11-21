// Work item 0188 (RVA 0x483d0-0x48975): UObject string operator natives
// execConcat_StrStr, execAt_StrStr, execLess/Greater/LessEqual/GreaterEqual_StrStr.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

extern "C" __declspec(dllimport) int __cdecl wcscmp(const TCHAR *, const TCHAR *);

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
    TArray() {}
    INT Num() const { return ArrayNum; }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    ~FString();                                     // 0x48b0
    FString &operator=(const FString &Other);       // 0x4800
    FString operator+(const TCHAR *Str) const;      // 0x4990
    FString operator+(const FString &Str) const;    // 0xca00
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

class UObject;
struct FFrame;
typedef void (UObject::*Native)(FFrame &TheStack, void *Result);
extern Native GNatives[];                           // 0x10c819d8

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

struct FFrame : public FOutputDevice
{
    void *Node;
    UObject *Object;
    BYTE *Code;
    inline void Step(UObject *Context, void *const Result);
};

class UObject
{
public:
    virtual ~UObject();
    void execConcat_StrStr(FFrame &Stack, void *const Result);
    void execAt_StrStr(FFrame &Stack, void *const Result);
    void execLess_StrStr(FFrame &Stack, void *const Result);
    void execGreater_StrStr(FFrame &Stack, void *const Result);
    void execLessEqual_StrStr(FFrame &Stack, void *const Result);
    void execGreaterEqual_StrStr(FFrame &Stack, void *const Result);
};

inline void FFrame::Step(UObject *Context, void *const Result)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

void UObject::execConcat_StrStr(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(FString *)Result = (A + B);
}

void UObject::execAt_StrStr(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(FString *)Result = (A + L" " + B);
}

void UObject::execLess_StrStr(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = wcscmp(*A, *B) < 0;
}

void UObject::execGreater_StrStr(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = wcscmp(*A, *B) > 0;
}

void UObject::execLessEqual_StrStr(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = wcscmp(*A, *B) <= 0;
}

void UObject::execGreaterEqual_StrStr(FFrame &Stack, void *const Result)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = wcscmp(*A, *B) >= 0;
}
