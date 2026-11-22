// Work item w3_0232: Versus RVA 0xefd20-0xefff3, APlayerController natives
// (UnPlayerController / UnScript natives in Engine): execSetViewTarget,
// SetViewTarget, execNativeGlobalPlayerCalcView, execConsoleCommand.
// Retail compiled this object with VC7.0 /GL and linked it with /LTCG:
// SetViewTarget takes this in ESI and the target in ECX, and
// FString::operator= (0x4750) takes this in ESI and the string in EDI.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

// Empty TEXT("") literals; retail keeps these in writable data, so they are
// declared rather than written as literals.
extern const TCHAR FString_Empty[];               // 0x10c10928, FString::operator*
extern const TCHAR FStringOutputDevice_Empty[];   // 0x10c92468, constructor default
extern const TCHAR ConsoleCommand_Empty[];        // 0x10c92464, execConsoleCommand

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const TCHAR *Other);
    const TCHAR *operator*() const { return ArrayNum ? Data : FString_Empty; }
};

// RVA 0x4750 (published separately); defined here so the LTCG link gives
// it retail's ESI/EDI convention.
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
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

class FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

class FStringOutputDevice : public FString, public FOutputDevice {
public:
    FStringOutputDevice(const TCHAR *InStr = FStringOutputDevice_Empty) : FString(InStr) {}
    void Serialize(const TCHAR *V, INT Event);
};

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class UClass;
class UProperty;
struct FFrame;

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();

class UObject {
public:
    // 0x00 vtable
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class; // 0x24

    V4(VA) V4(VB) V4(VC) V4(VD) V4(VE) // slots 0..19
    virtual void V50();                // 0x50
    virtual void NetDirty(UProperty *Property); // 0x54
};

class UField : public UObject {
public:
    UField *SuperField; // 0x28
    UField *Next;
};

class UClass : public UField {
};

typedef void (UObject::*Native)(FFrame &Stack, void *Result);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

struct FFrame : public FOutputDevice {
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, void *Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    void StepRef(UObject *Context, void *Result)
    {
        GPropAddr = 0;
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct FVector { FLOAT X, Y, Z; };
struct FRotator { INT Pitch, Yaw, Roll; };

class UPlayer : public UObject, public FOutputDevice, public FExec {
};

class UEngine : public UObject, public FExec {
};

class ULevel : public UObject {
public:
    BYTE Pad28[0xf0 - 0x28];
    UEngine *Engine; // 0xf0
};

class AActor : public UObject {
public:
    BYTE Pad28[0x1a4 - 0x28];
    ULevel *XLevel; // 0x1a4
    ULevel *GetLevel() const { return XLevel; }
    UBOOL IsA(UClass *SomeBase) const
    {
        for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
            if (TempClass == SomeBase)
                return 1;
        return 0;
    }
};

class AController : public AActor {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T> T *Cast(UObject *Src)
{
    return Src && ((AActor *)Src)->IsA(T::StaticClass()) ? (T *)Src : 0;
}

class APlayerController : public AController {
public:
    BYTE Pad1a8[0x4a4 - 0x1a8];
    UPlayer *Player;            // 0x4a4
    BYTE Pad4a8[0x504 - 0x4a8];
    AActor *ViewTarget;         // 0x504
    AController *RealViewTarget; // 0x508

    V4(P1) V4(P2) V4(P3) V4(P4) V4(P5) V4(P6) V4(P7) V4(P8) V4(P9) V4(PA)
    V4(PB) V4(PC) V4(PD) V4(PE)    // slots 22..77
    virtual void Slot78();
    virtual void UnnamedVirtual_13c(); // 0x13c, called after the view target changes
    virtual void Slot80(); virtual void Slot81(); virtual void Slot82();
    virtual void GlobalPlayerCalcView(AActor *&ViewActor, FVector &CameraLocation,
                                      FRotator &CameraRotation, UBOOL bFlag); // 0x14c

    void SetViewTarget(AActor *NewViewTarget);
    void execSetViewTarget(FFrame &Stack, void *Result);
    void execNativeGlobalPlayerCalcView(FFrame &Stack, void *Result);
    void execConsoleCommand(FFrame &Stack, void *Result);
};

#define P_GET_ACTOR(V) AActor *V = 0; Stack.Step(Stack.Object, &V);
#define P_GET_STR(V) FString V; Stack.Step(Stack.Object, &V);
#define P_GET_REF_TAIL(Type, V) Stack.StepRef(Stack.Object, &V##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    Type *V = GPropAddr ? (Type *)GPropAddr : &V##T;
#define P_GET_ACTOR_REF(V) AActor *V##T = 0; P_GET_REF_TAIL(AActor *, V)
#define P_GET_VECTOR_REF(V) FVector V##T; P_GET_REF_TAIL(FVector, V)
#define P_GET_ROTATOR_REF(V) FRotator V##T; P_GET_REF_TAIL(FRotator, V)
#define P_FINISH Stack.Code++;

// RVA 0xefd20
void APlayerController::execSetViewTarget(FFrame &Stack, void *Result)
{
    P_GET_ACTOR(NewTarget);
    P_FINISH;
    SetViewTarget(NewTarget);
}

// RVA 0xefd70
void APlayerController::SetViewTarget(AActor *NewViewTarget)
{
    ViewTarget = NewViewTarget;
    if (ViewTarget == this)
        RealViewTarget = 0;
    else
        RealViewTarget = Cast<AController>(ViewTarget);
    UnnamedVirtual_13c();
    if (ViewTarget == this)
        RealViewTarget = 0;
}

// RVA 0xefdd0
void APlayerController::execNativeGlobalPlayerCalcView(FFrame &Stack, void *Result)
{
    P_GET_ACTOR_REF(ViewActor);
    P_GET_VECTOR_REF(CameraLocation);
    P_GET_ROTATOR_REF(CameraRotation);
    P_FINISH;
    GlobalPlayerCalcView(*ViewActor, *CameraLocation, *CameraRotation, 1);
}

// RVA 0xefee0
void APlayerController::execConsoleCommand(FFrame &Stack, void *Result)
{
    P_GET_STR(Command);
    P_FINISH;
    *(FString *)Result = ConsoleCommand_Empty;
    FStringOutputDevice StrOut;
    if (Player)
        Player->Exec(*Command, StrOut);
    else
        GetLevel()->Engine->Exec(*Command, StrOut);
    *(FString *)Result = *StrOut;
}

// Scaffolding for the link, not part of the unit: the natives are reached
// through the GNatives table, so their addresses are taken. GPropAddr,
// GPropObject and GProperty are deliberately not escaped: retail's
// scheduling of the by-reference fetches only matches without it.
void Escape(void *);
typedef void (APlayerController::*PCNative)(FFrame &Stack, void *Result);
void Driver_efd20()
{
    Escape(&GNatives);
    Escape(&GMalloc);
    PCNative A = &APlayerController::execSetViewTarget;
    PCNative B = &APlayerController::execNativeGlobalPlayerCalcView;
    PCNative C = &APlayerController::execConsoleCommand;
    Escape(&A);
    Escape(&B);
    Escape(&C);
}
