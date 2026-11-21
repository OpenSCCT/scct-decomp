// Work item 0220 (w3): Versus RVA 0xedec0-0xee1b4.
// 0xedec0 (operator new) is in w3_item_0220_opnew.cpp: it needs FName with
//          a trivial copy, while these event thunks need the copy
//          constructor, so the two came from different units.
// 0xedef0/0xedf80/0xee010/0xee0a0: UnrealScript eventXxx thunks, /GL
//          (this in ESI). Event names not recovered; EName indices kept.
// 0xee0c0: FString::FString(const ANSICHAR*), with ANSI_TO_TCHAR expanded.
typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

enum EName {
    NAME_Unnamed_B19 = 0xb19,
    NAME_Unnamed_C90 = 0xc90,
    NAME_Unnamed_D3D = 0xd3d,
    NAME_Unnamed_F86 = 0xf86,
};

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
};
extern FMalloc *GMalloc;

void *appMemcpy(void *Dest, const void *Src, INT Count);

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int CodePage, DWORD dwFlags, const ANSICHAR *lpMultiByteStr,
    int cbMultiByte, TCHAR *lpWideCharStr, int cchWideChar);
extern "C" void *_alloca(unsigned int);
#pragma intrinsic(_alloca)
extern "C" unsigned int strlen(const char *);
#pragma intrinsic(strlen)

inline INT winGetSizeUNICODE(const ANSICHAR *InA)
{
    return MultiByteToWideChar(0, 0, InA, -1, 0, 0);
}
inline TCHAR *winToUNICODE(TCHAR *Dest, const ANSICHAR *Src, INT Len)
{
    MultiByteToWideChar(0, 0, Src, -1, Dest, Len);
    return Dest;
}
#define appAlloca(size) ((size) == 0 ? 0 : _alloca(((size) + 7) & ~7))
#define ANSI_TO_TCHAR(str) winToUNICODE((TCHAR *)appAlloca(winGetSizeUNICODE(str) * sizeof(TCHAR)), str, winGetSizeUNICODE(str))

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (ArrayNum == 0)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayNum * ElementSize, L"Farray::protectedcstor");
    }
    ~FArray();
};

template<class T> class TArray : public FArray {
public:
    TArray() {}
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const ANSICHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
};

// RVA 0xee0c0.
FString::FString(const ANSICHAR *In)
    : TArray<TCHAR>(*In ? (INT)strlen(In) + 1 : 0)
{
    if (ArrayNum)
        appMemcpy(&(*this)(0), ANSI_TO_TCHAR(In), ArrayNum * sizeof(TCHAR));
}

class UClass;
class UFunction;

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
};

// Owning class not recovered.
class UnnamedClass_edef0 : public UObject {
public:
    __declspec(noinline) void eventUnnamed_edef0(INT A, const FString &S, INT B);
    __declspec(noinline) void eventUnnamed_edf80(const FString &S, INT B);
    __declspec(noinline) void eventUnnamed_ee010(INT A, const FString &S, INT B);
    __declspec(noinline) void eventUnnamed_ee0a0();
};

void UnnamedClass_edef0::eventUnnamed_edef0(INT A, const FString &S, INT B)
{
    struct UnnamedClass_edef0_eventUnnamed_edef0_Parms {
        INT A;
        FString S;
        INT B;
    } Parms;
    Parms.A = A;
    Parms.S = S;
    Parms.B = B;
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_D3D)), &Parms);
}

void UnnamedClass_edef0::eventUnnamed_edf80(const FString &S, INT B)
{
    struct UnnamedClass_edef0_eventUnnamed_edf80_Parms {
        FString S;
        INT B;
    } Parms;
    Parms.S = S;
    Parms.B = B;
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_C90)), &Parms);
}

void UnnamedClass_edef0::eventUnnamed_ee010(INT A, const FString &S, INT B)
{
    struct UnnamedClass_edef0_eventUnnamed_ee010_Parms {
        INT A;
        FString S;
        INT B;
    } Parms;
    Parms.A = A;
    Parms.S = S;
    Parms.B = B;
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_F86)), &Parms);
}

void UnnamedClass_edef0::eventUnnamed_ee0a0()
{
    ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_B19)), 0);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_edef0(UnnamedClass_edef0 *X, INT A, const FString &S, INT B) { X->eventUnnamed_edef0(A, S, B); }
void Driver_edf80(UnnamedClass_edef0 *X, const FString &S, INT B) { X->eventUnnamed_edf80(S, B); }
void Driver_ee010(UnnamedClass_edef0 *X, INT A, const FString &S, INT B) { X->eventUnnamed_ee010(A, S, B); }
void Driver_ee0a0(UnnamedClass_edef0 *X) { X->eventUnnamed_ee0a0(); }
