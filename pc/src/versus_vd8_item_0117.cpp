// Work item 0117 (vwork4): Versus RVA 0x155660-0x155705.
// UGUIController::execIsProfileOnMC (RVA 0x155660).
// Calls the address-specific view's HasItem (RVA 0xe5e90, LTCG `this` in ESI).

#include "versus_globals.h"

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
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString &Other);
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

class UObject
{
public:
    virtual ~UObject();
};

struct FFrame;
typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    class UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define RESULT_DECL void *const Result
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class FObjectView_10c924e8_0117
{
public:
    virtual void VirtualSlot00();
    INT  unk_04[9];
    void *vtable_28;
    INT  unk_2c[2];
    INT Done[7];            // +0x34
    INT Current;            // +0x50
    INT unk_54[8];
    TArray<FString> Items;  // +0x74

    UBOOL HasItem(FString S);
};

// Consumer-specific view of the object-pointer slot at VA 0x10c924e8.
#define GObjectView_10c924e8_0117 (*((FObjectView_10c924e8_0117 **)&GObject_10c924e8))

class UGUIController : public UObject
{
public:
    void execIsProfileOnMC(FFrame &Stack, RESULT_DECL);
};

// RVA 0x155660: UGUIController::execIsProfileOnMC
void UGUIController::execIsProfileOnMC(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(ProfileName);
    P_FINISH;
    FObjectView_10c924e8_0117 *ProfileManager = GObjectView_10c924e8_0117;
    if (ProfileManager)
        *(UBOOL *)Result = ProfileManager->HasItem(ProfileName);
    else
        *(UBOOL *)Result = 1;
}

// Scaffolding for the link, not part of the unit.
// HasItem (published in versus_vd5_item_0203.cpp, RVA 0xe5e90) is included here
// so LTCG assigns its retail calling convention (`this` in ESI).
UBOOL FObjectView_10c924e8_0117::HasItem(FString S)
{
    for (INT i = 0; i < Items.Num(); i++)
        if (wcscmp(*Items(i), *S) == 0)
            return 1;
    return 0;
}

void Escape(void *);
void Driver_155660(UGUIController *C, FFrame *Stack, void *Result,
                   FObjectView_10c924e8_0117 *M, FString *S)
{
    Escape(&GObjectView_10c924e8_0117);
    Escape(GNatives);
    void (UGUIController::*Exec)(FFrame &, void *const) = &UGUIController::execIsProfileOnMC;
    Escape(&Exec);
    (C->*Exec)(*Stack, Result);
    M->HasItem(*S);
}
