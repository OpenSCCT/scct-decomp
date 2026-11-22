// w4_item_0122.cpp -- Versus UGUIController::execGetStyle (RVA 0x1564a0)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);

inline INT appStricmp(const TCHAR *String1, const TCHAR *String2)
{
    return _wcsicmp(String1, String2);
}

struct FGuid;
struct FFrame;
struct FStateFrame;
class UObject;
class UClass;
class UStruct;

enum EName { NAME_None = 0 };

#define RESULT_DECL void *const Result

class FArray
{
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    ~FString();

    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : (const TCHAR *)L""; }
    UBOOL operator==(const FString &Other) const { return appStricmp(**this, *Other) == 0; }
};

class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();

    INT           Index;
    BYTE          unk_8[0x4];
    FStateFrame  *StateFrame;
    BYTE          unk_10[0xc];
    DWORD         ObjectFlags;
    BYTE          unk_20[0x4];
    UClass       *Class;
};

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UGUI : public UObject
{
public:
    BYTE unk_28[0x4];
};

class UGUIStyles : public UGUI
{
public:
    FString KeyName;
};

class UGUIController : public UObject
{
public:
    BYTE                 unk_28[0xc68];
    TArray<UGUIStyles *> StyleStack;

    void execGetStyle(FFrame &Stack, RESULT_DECL);
};

// UGUIController::execGetStyle (RVA 0x1564a0)
void UGUIController::execGetStyle(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(StyleName);
    P_FINISH;

    if (StyleStack.Num() == 0)
    {
        *(UGUIStyles **)Result = 0;
        return;
    }

    for (INT i = 0; i < StyleStack.Num(); i++)
    {
        if (StyleName == StyleStack(i)->KeyName)
        {
            *(UGUIStyles **)Result = StyleStack(i);
            return;
        }
    }

    *(UGUIStyles **)Result = 0;
}
