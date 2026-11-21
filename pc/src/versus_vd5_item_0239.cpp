// Work item 0239: Versus RVA 0xf1110-0xf1491.
// Retail compiled this unit with VC7.0 /GL and linked it with /LTCG.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

template<class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }

struct FRotator { INT Pitch, Yaw, Roll; };
struct FName { INT Index; FName(INT I) : Index(I) {} };
struct FFrame;
class UFunction;

struct FStateFrame {
    BYTE Pad[0x24];
    INT LatentAction;               // 0x24
};

class UObject {
public:
    virtual void Virtual00();
    virtual void Virtual04();
    virtual void Virtual08();
    virtual void Virtual0C();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
};

// Placeholder virtual slots up to vtable offset 0x13c (names not recovered).
#define SLOT(n) virtual void Slot##n();
#define SLOT10(a) SLOT(a##0) SLOT(a##1) SLOT(a##2) SLOT(a##3) SLOT(a##4) SLOT(a##5) SLOT(a##6) SLOT(a##7) SLOT(a##8) SLOT(a##9)
class UObjectSlots : public UObject {
public:
    SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
    SLOT10(1) SLOT10(2) SLOT10(3) SLOT10(4) SLOT10(5) SLOT10(6) SLOT10(7)
    virtual UBOOL CheckVirtual140(); // vtable +0x140, name not recovered
};

class AActor : public UObjectSlots {
public:
    BYTE Pad0[0xc - 4];
    FStateFrame *StateFrame;        // 0x0c
    BYTE Pad1[0xe0 - 0x10];
    FRotator Rotation;              // 0xe0
    BYTE Pad2[0x28c - 0xec];
    FRotator DesiredRotation;       // 0x28c
    BYTE Pad2b[0x2e8 - 0x298];
    DWORD Flags2E8;                 // 0x2e8, bit 0x8000 tested (name not recovered)
    BYTE Pad3[4];
    DWORD Flags2F0;                 // 0x2f0, bit 0x40 tested (name not recovered)
    BYTE Pad4[0x2fc - 0x2f4];
};


class APawn : public AActor {
public:
    UBOOL ReachedDesiredRotation();
};

class AController : public AActor {
public:
    APawn *Pawn;                    // 0x2fc
    void execPollFinishRotation(FFrame &Stack, void *Result);
};

// Unnamed ASPlayerController members; ResolveTarget is slot 79 of its vtable.
class ASPlayerController : public AController {
public:
    BYTE Pad6[0x504 - 0x300];
    AActor *ResolvedTarget;         // 0x504
    AController *TargetController;  // 0x508
    void eventTargetChanged(AActor *NewTarget);
    AActor *ResolveTarget();
};

// Inlined into the poll below by the link-time optimiser.
UBOOL APawn::ReachedDesiredRotation()
{
    INT YawDiff = DesiredRotation.Yaw - (Rotation.Yaw & 65535);
    UBOOL bResult = Abs(YawDiff) < 2000;
    if (!bResult)
        bResult = Abs(YawDiff) > 63535;
    return bResult;
}

// RVA 0xf1110: latent poll for FinishRotation.
void AController::execPollFinishRotation(FFrame &Stack, void *Result)
{
    if (!Pawn || Pawn->ReachedDesiredRotation())
        StateFrame->LatentAction = 0;
}

// RVA 0xf13f0: ASPlayerController vtable slot 79.
AActor *ASPlayerController::ResolveTarget()
{
    if (TargetController) {
        AActor *OldTarget = ResolvedTarget;
        AActor *P = TargetController->Pawn;
        if (P) {
            if (!(P->Flags2E8 & 0x8000))
                ResolvedTarget = P;
            else
                ResolvedTarget = TargetController;
        } else if (!OldTarget) {
            ResolvedTarget = TargetController;
        }
        if (OldTarget != ResolvedTarget) {
            if (CheckVirtual140())
                return ResolvedTarget;
            eventTargetChanged(ResolvedTarget);
            return ResolvedTarget;
        }
    } else if (!ResolvedTarget) {
        if (Pawn && !(Pawn->Flags2E8 & 0x8000) && !(Pawn->Flags2F0 & 0x40)) {
            ResolvedTarget = Pawn;
            return Pawn;
        }
        ResolvedTarget = this;
    }
    return ResolvedTarget;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
struct TargetChanged_Parms { AActor *NewTarget; };
// Script event at RVA 0xf21a0 (work item 0242); kept out of line as in retail.
__declspec(noinline) void ASPlayerController::eventTargetChanged(AActor *NewTarget)
{
    TargetChanged_Parms Parms;
    Parms.NewTarget = NewTarget;
    ProcessEvent(FindFunctionChecked(FName(0xf29)), &Parms);
}
typedef void (AController::*ControllerNative)(FFrame &, void *);
void Driver_f1110() { ControllerNative N = &AController::execPollFinishRotation; Escape(&N); }
typedef AActor *(ASPlayerController::*ResolveFn)();
void Driver_f13f0() { ResolveFn F = &ASPlayerController::ResolveTarget; Escape(&F); }
