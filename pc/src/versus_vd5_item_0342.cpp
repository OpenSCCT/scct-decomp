// Work item 0342: Versus RVA 0x10f940-0x10fe4e, UInteractionMaster natives.
// UInteractionMaster (UE2 UnInteractionMaster.cpp): Client at 0x28,
// BaseMenu 0x2c, Console 0x30, GlobalInteractions 0x34. 0x10f940 is
// execTravel (annotated); the others are the C++ Master* dispatchers, which
// call the script events Process_* (by-value TArray copy) and the native
// handlers of interactions with bNativeEvents set.
//
// The object was compiled with link-time code generation: the Master*
// functions take `this` in ESI, the Process_* events take `this` on the
// stack, and the TArray copy constructor (RVA 0x10ff00) takes `this` on the
// stack and the source in EBX. Functions marked "stand-in" are only there so
// the linker picks the same conventions as retail; their addresses bind to
// the retail functions and their bodies are not part of the unit.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;                           // retail 0x10c73bf0
extern const TCHAR TEXT_ProtectedCstor[];          // L"Farray::protectedcstor"
inline void* operator new(unsigned int, void* Mem) { return Mem; }

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);           // RVA 0x44e0
    INT Num() const { return ArrayNum; }
    void Empty(INT ElementSize, INT Slack = 0);    // RVA 0x4550
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
    FArray() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
protected:
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = ArrayMax ? GMalloc->Malloc(ArrayMax * ElementSize, TEXT_ProtectedCstor) : 0;
    }
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    // RVA 0x10ff00 (this on the stack, Other in EBX): stand-in body.
    __declspec(noinline) TArray(const TArray& Other)
        : FArray(Other.ArrayNum, sizeof(T))
    {
        ArrayNum = 0;
        for (INT i = 0; i < Other.ArrayNum; i++)
            new(&((T*)Data)[Add(1, sizeof(T))]) T(((T*)Other.Data)[i]);
    }
    // RVA 0x17bf30 (this on the stack): stand-in body.
    __declspec(noinline) ~TArray()
    {
        Remove(0, ArrayNum, sizeof(T));
    }
    // RVA 0x1100b0 (this in ESI, Other in EDI): stand-in body.
    __declspec(noinline) TArray& operator=(const TArray& Other)
    {
        if (this != &Other)
        {
            Empty(sizeof(T), Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new(&((T*)Data)[Add(1, sizeof(T))]) T(((T*)Other.Data)[i]);
        }
        return *this;
    }
    T& operator()(INT i) { return ((T*)Data)[i]; }
};

class FString : public FArray
{
public:
    FString() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~FString();                                    // RVA 0x48b0
    FString& operator=(const FString& Other);      // RVA 0x4800
    static FString Printf(const TCHAR* Fmt, ...);  // RVA 0x11b20
};

struct FFrame;
class UFunction;

class FName
{
public:
    INT Index;
    FName(INT InIndex) : Index(InIndex) {}
};

class UObject
{
public:
    virtual ~UObject();
    virtual void Pad04();
    virtual void Pad08();
    virtual void Pad0C();
    virtual void ProcessEvent(UFunction* Function, void* Parms, void* Result = 0); // 0x10
    virtual void Pad14();
    virtual void Pad18();
    virtual void Pad1C();
    virtual void Pad20();
    virtual void Pad24();
    virtual void Pad28();
    virtual void Pad2C();
    virtual void Pad30();
    virtual void Pad34();
    virtual void Pad38();
    virtual void Pad3C();
    virtual void Pad40();
    virtual void Pad44();
    virtual void Pad48();
    virtual void Pad4C();
    virtual void Pad50();
    virtual void Pad54();
    virtual void Pad58();
    DWORD ObjectFields[9];                         // 0x04..0x28
    UFunction* FindFunctionChecked(FName InName, UBOOL Global = 0); // RVA 0x16830
};

typedef void (UObject::*Native)(FFrame& TheStack, void* const Result);
extern Native GNatives[];                          // retail 0x10c819d8

struct FFrame
{
    void* VfTable;
    class UStruct* Node;
    UObject* Object;
    BYTE* Code;
    BYTE* Locals;
    void Step(UObject* Context, void* const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};
#define RESULT_DECL void* const Result
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class UCanvas;

class UInteraction : public UObject
{
public:
    DWORD bActive:1;                               // 0x28
    DWORD bVisible:1;
    DWORD bRequiresTick:1;
    DWORD bNativeEvents:1;
    virtual UBOOL NativeKeyType(BYTE& iKey, TCHAR Unicode);              // 0x5c
    virtual UBOOL NativeKeyEvent(BYTE& iKey, BYTE& State, FLOAT Delta);  // 0x60
    virtual void NativeTick(FLOAT DeltaTime);                            // 0x64
    virtual void NativePreRender(UCanvas* Canvas);                       // 0x68
    virtual void NativePostRender(UCanvas* Canvas);                      // 0x6c
};

class UViewport : public UObject
{
public:
    BYTE Pad28[0x58 - 0x28];
    TArray<UInteraction*> LocalInteractions;       // 0x58
    BYTE Pad64[0x11c - 0x64];
    INT TravelType;                                // 0x11c
    FString TravelURL;                             // 0x120
    UBOOL bTravelItems;                            // 0x12c
};

class UClient : public UObject
{
public:
    DWORD Field28;
    TArray<UViewport*> Viewports;                  // 0x2c
};

enum {
#define REGISTER_NAME(symbol, index, flags, text) NAME_##symbol = index,
#include "versus_hardcoded_names.inl"
#undef REGISTER_NAME
};

// Strings live in writable .data in retail.
extern const TCHAR TEXT_KeyTypeFormat1[];          // L"%c" (retail 0x10c47b68)
extern const TCHAR TEXT_KeyTypeFormat2[];          // L"%c" (retail 0x10c47b70)
extern const FLOAT GAxisThreshold;                 // retail 0x10c109f8

enum EInputKey { IK_Left = 0x25, IK_Up = 0x26, IK_Right = 0x27, IK_Down = 0x28,
                 IK_AxisHorizontal = 0xf0, IK_AxisVertical = 0xf1 }; // 0xf0/0xf1: names assumed
enum EInputAction { IST_None = 0 };

class UInteractions : public UObject
{
};

class UInteractionMaster : public UInteractions
{
public:
    UClient* Client;                               // 0x28
    UInteraction* BaseMenu;                        // 0x2c
    UInteraction* Console;                         // 0x30
    TArray<UInteraction*> GlobalInteractions;      // 0x34

    void execTravel(FFrame& Stack, RESULT_DECL);
    UBOOL MasterProcessKeyType(EInputKey iKey, TCHAR Unicode);
    UBOOL MasterProcessKeyEvent(EInputKey iKey, EInputAction State, FLOAT Delta);
    void MasterProcessTick(FLOAT DeltaTime);
    void MasterProcessPreRender(UCanvas* Canvas);
    void MasterProcessPostRender(UCanvas* Canvas);

    // RVA 0x1103e0 (this on the stack): stand-in body.
    __declspec(noinline) UBOOL eventProcess_KeyType(TArray<UInteraction*> InteractionArray, BYTE& Key, const FString& Unicode)
    {
        struct { TArray<UInteraction*> InteractionArray; BYTE Key; FString Unicode; UBOOL ReturnValue; } Parms;
        Parms.ReturnValue = 0;
        Parms.InteractionArray = InteractionArray;
        Parms.Key = Key;
        Parms.Unicode = Unicode;
        ProcessEvent(FindFunctionChecked(FName(NAME_Process_KeyType)), &Parms);
        Key = Parms.Key;
        return Parms.ReturnValue;
    }
    // RVA 0x110310 (this on the stack): stand-in body.
    __declspec(noinline) UBOOL eventProcess_KeyEvent(TArray<UInteraction*> InteractionArray, BYTE& Key, BYTE& Action, FLOAT Delta)
    {
        struct { TArray<UInteraction*> InteractionArray; BYTE Key; BYTE Action; FLOAT Delta; UBOOL ReturnValue; } Parms;
        Parms.ReturnValue = 0;
        Parms.InteractionArray = InteractionArray;
        Parms.Key = Key;
        Parms.Action = Action;
        Parms.Delta = Delta;
        ProcessEvent(FindFunctionChecked(FName(NAME_Process_KeyEvent)), &Parms);
        Key = Parms.Key;
        Action = Parms.Action;
        return Parms.ReturnValue;
    }
    // RVA 0x110260 (this on the stack): stand-in body.
    __declspec(noinline) void eventProcess_Tick(TArray<UInteraction*> InteractionArray, FLOAT DeltaTime)
    {
        struct { TArray<UInteraction*> InteractionArray; FLOAT DeltaTime; } Parms;
        Parms.InteractionArray = InteractionArray;
        Parms.DeltaTime = DeltaTime;
        ProcessEvent(FindFunctionChecked(FName(NAME_Process_Tick)), &Parms);
    }
    // RVA 0x1101b0 (this on the stack): stand-in body.
    __declspec(noinline) void eventProcess_PreRender(TArray<UInteraction*> InteractionArray, UCanvas* Canvas)
    {
        struct { TArray<UInteraction*> InteractionArray; UCanvas* Canvas; } Parms;
        Parms.InteractionArray = InteractionArray;
        Parms.Canvas = Canvas;
        ProcessEvent(FindFunctionChecked(FName(NAME_Process_PreRender)), &Parms);
    }
    // RVA 0x110100 (this on the stack): stand-in body.
    __declspec(noinline) void eventProcess_PostRender(TArray<UInteraction*> InteractionArray, UCanvas* Canvas)
    {
        struct { TArray<UInteraction*> InteractionArray; UCanvas* Canvas; } Parms;
        Parms.InteractionArray = InteractionArray;
        Parms.Canvas = Canvas;
        ProcessEvent(FindFunctionChecked(FName(NAME_Process_PostRender)), &Parms);
    }
};

// RVA 0x10f940
void UInteractionMaster::execTravel(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(URL);
    P_FINISH;
    if (Client && Client->Viewports.Num())
    {
        FString& TravelURL = Client->Viewports(0)->TravelURL;
        TravelURL = URL;
        Client->Viewports(0)->TravelType = 0;      // TRAVEL_Absolute
        Client->Viewports(0)->bTravelItems = 0;
    }
}

// RVA 0x10fa00
UBOOL UInteractionMaster::MasterProcessKeyType(EInputKey iKey, TCHAR Unicode)
{
    BYTE Key = iKey;
    if (eventProcess_KeyType(GlobalInteractions, Key, FString::Printf(TEXT_KeyTypeFormat1, Unicode)))
        return 1;
    for (INT i = 0; i < GlobalInteractions.Num(); i++)
    {
        UInteraction* Interaction = GlobalInteractions(i);
        if (Interaction->bNativeEvents && Interaction->bActive && Interaction->NativeKeyType(Key, Unicode))
            return 1;
    }
    for (INT i = 0; i < Client->Viewports.Num(); i++)
    {
        if (eventProcess_KeyType(Client->Viewports(i)->LocalInteractions, Key, FString::Printf(TEXT_KeyTypeFormat2, Unicode)))
            return 1;
    }
    return 0;
}

// RVA 0x10fb70: the analog axis keys 0xf0/0xf1 become arrow keys by the
// sign of Delta.
UBOOL UInteractionMaster::MasterProcessKeyEvent(EInputKey iKey, EInputAction State, FLOAT Delta)
{
    BYTE Key = iKey;
    BYTE Action = State;
    if (Key == IK_AxisHorizontal)
        Key = (Delta < GAxisThreshold) ? IK_Left : IK_Right;
    else if (Key == IK_AxisVertical)
        Key = (Delta < GAxisThreshold) ? IK_Down : IK_Up;
    if (eventProcess_KeyEvent(GlobalInteractions, Key, Action, Delta))
        return 1;
    for (INT i = 0; i < GlobalInteractions.Num(); i++)
    {
        UInteraction* Interaction = GlobalInteractions(i);
        if (Interaction->bNativeEvents && Interaction->bActive && Interaction->NativeKeyEvent(Key, Action, Delta))
            return 1;
    }
    for (INT i = 0; i < Client->Viewports.Num(); i++)
    {
        if (eventProcess_KeyEvent(Client->Viewports(i)->LocalInteractions, Key, Action, Delta))
            return 1;
    }
    return 0;
}

// RVA 0x10fc90
void UInteractionMaster::MasterProcessTick(FLOAT DeltaTime)
{
    eventProcess_Tick(GlobalInteractions, DeltaTime);
    for (INT i = 0; i < GlobalInteractions.Num(); i++)
    {
        UInteraction* Interaction = GlobalInteractions(i);
        if (Interaction->bNativeEvents && Interaction->bRequiresTick)
            Interaction->NativeTick(DeltaTime);
    }
    for (INT i = 0; i < Client->Viewports.Num(); i++)
        eventProcess_Tick(Client->Viewports(i)->LocalInteractions, DeltaTime);
}

// RVA 0x10fd30
void UInteractionMaster::MasterProcessPreRender(UCanvas* Canvas)
{
    for (INT i = 0; i < Client->Viewports.Num(); i++)
        eventProcess_PreRender(Client->Viewports(i)->LocalInteractions, Canvas);
    for (INT i = 0; i < GlobalInteractions.Num(); i++)
    {
        UInteraction* Interaction = GlobalInteractions(i);
        if (Interaction->bNativeEvents && Interaction->bVisible)
            Interaction->NativePreRender(Canvas);
    }
    eventProcess_PreRender(GlobalInteractions, Canvas);
}

// RVA 0x10fdc0
void UInteractionMaster::MasterProcessPostRender(UCanvas* Canvas)
{
    for (INT i = 0; i < Client->Viewports.Num(); i++)
        eventProcess_PostRender(Client->Viewports(i)->LocalInteractions, Canvas);
    for (INT i = 0; i < GlobalInteractions.Num(); i++)
    {
        UInteraction* Interaction = GlobalInteractions(i);
        if (Interaction->bNativeEvents && Interaction->bVisible)
            Interaction->NativePostRender(Canvas);
    }
    eventProcess_PostRender(GlobalInteractions, Canvas);
}

// Scaffolding for the link, not part of the unit: calls each function the
// way retail does and makes the retail globals address-taken.
void Escape(void*);
INT Driver_10fa00(UInteractionMaster* M, EInputKey K, TCHAR U, EInputAction S, FLOAT D, UCanvas* C, FFrame* F, void* R)
{
    Escape(&GMalloc);
    Escape(GNatives);
    void (UInteractionMaster::*Exec)(FFrame&, void* const) = &UInteractionMaster::execTravel;
    Escape(&Exec);
    (M->*Exec)(*F, R);
    INT Result = M->MasterProcessKeyType(K, U);
    Result += M->MasterProcessKeyEvent(K, S, D);
    M->MasterProcessTick(D);
    M->MasterProcessPreRender(C);
    M->MasterProcessPostRender(C);
    return Result;
}
