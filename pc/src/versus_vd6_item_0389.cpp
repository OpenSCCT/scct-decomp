// w3_item_0389.cpp -- Versus RVA 0x11db70-0x11dd5f (6 functions)

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef float FLOAT;
typedef double DOUBLE;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned short TCHAR;

#define KINDA_SMALL_NUMBER (1.e-4f)

template<class T> inline T Abs(const T A)
{
    return (A >= (T)0) ? A : -A;
}

struct FVector {
    FLOAT X, Y, Z;

    UBOOL IsNearlyZero() const;
};

struct FRotator {
    INT Pitch, Yaw, Roll;

    UBOOL operator==(const FRotator &R) const;
};

enum EName {
    NAME_None            = 0,
    NAME_PROBEMIN        = 300,
    NAME_EncroachingOn   = 0x147,
    NAME_NotifyBump      = 0x15c,
    NAME_PROBEMAX        = 364,
    ENGINE_BulletWentTru = 0x9e7
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

struct FGuid;
class UFunction;

#pragma pack(push, 4)
struct FStateFrame {
    BYTE  unk_0[0x1c];
    QWORD ProbeMask;
    INT   LatentAction;
};
#pragma pack(pop)

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT          Index;
    BYTE         unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0x18];

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);

    UBOOL IsProbing(FName ProbeName)
    {
        return (ProbeName.GetIndex() < NAME_PROBEMIN ||
                ProbeName.GetIndex() >= NAME_PROBEMAX ||
                !StateFrame ||
                (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN))));
    }
};

class AActor : public UObject {
public:
    BYTE    unk_28[0xe0];
    AActor *Owner;

    void eventBulletWentTru(AActor *Instigator, FVector HitLocation, FVector HitNormal,
                            FVector Momentum);
    BITFIELD eventEncroachingOn(AActor *Other);
    UBOOL IsOwnedBy(const AActor *TestOwner) const;
};

class AController : public AActor {
public:
    BITFIELD eventNotifyBump(AActor *Other);
};

// RVA 0x11db70: AActor::eventBulletWentTru
struct AActor_eventBulletWentTru_Parms {
    AActor *Instigator;
    FVector HitLocation;
    FVector HitNormal;
    FVector Momentum;
};

void AActor::eventBulletWentTru(AActor *Instigator, FVector HitLocation, FVector HitNormal,
                                FVector Momentum)
{
    AActor_eventBulletWentTru_Parms Parms;
    Parms.Instigator = Instigator;
    Parms.HitLocation = HitLocation;
    Parms.HitNormal = HitNormal;
    Parms.Momentum = Momentum;
    ProcessEvent(FindFunctionChecked(ENGINE_BulletWentTru), &Parms);
}

// RVA 0x11dbf0: AController::eventNotifyBump
struct AController_eventNotifyBump_Parms {
    AActor  *Other;
    BITFIELD ReturnValue;
};

BITFIELD AController::eventNotifyBump(AActor *Other)
{
    AController_eventNotifyBump_Parms Parms;
    Parms.ReturnValue = 0;
    if (IsProbing(NAME_NotifyBump)) {
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(NAME_NotifyBump), &Parms);
    }
    return Parms.ReturnValue;
}

// RVA 0x11dc50: AActor::eventEncroachingOn
struct AActor_eventEncroachingOn_Parms {
    AActor  *Other;
    BITFIELD ReturnValue;
};

BITFIELD AActor::eventEncroachingOn(AActor *Other)
{
    AActor_eventEncroachingOn_Parms Parms;
    Parms.ReturnValue = 0;
    if (IsProbing(NAME_EncroachingOn)) {
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(NAME_EncroachingOn), &Parms);
    }
    return Parms.ReturnValue;
}

// RVA 0x11dcb0: AActor::IsOwnedBy
UBOOL AActor::IsOwnedBy(const AActor *TestOwner) const
{
    for (const AActor *Arg = this; Arg; Arg = Arg->Owner) {
        if (Arg == TestOwner)
            return 1;
    }
    return 0;
}

// RVA 0x11dcd0: FVector::IsNearlyZero
UBOOL FVector::IsNearlyZero() const
{
    return Abs(X) < KINDA_SMALL_NUMBER &&
           Abs(Y) < KINDA_SMALL_NUMBER &&
           Abs(Z) < KINDA_SMALL_NUMBER;
}

// RVA 0x11dd40: FRotator::operator==
UBOOL FRotator::operator==(const FRotator &R) const
{
    return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
}

// Scaffolding for LTCG links, not part of the unit.
#pragma inline_depth(0)
void Sink(INT);

void Driver_11db70(AActor *A, AActor *Instigator, FVector HitLocation, FVector HitNormal,
                   FVector Momentum)
{
    A->eventBulletWentTru(Instigator, HitLocation, HitNormal, Momentum);
    A->eventBulletWentTru(A, Momentum, HitLocation, HitNormal);
}

void Driver_11dbf0(AController *C, AActor *Other)
{
    Sink((INT)C->eventNotifyBump(Other));
    Sink((INT)C->eventNotifyBump(C));
}

void Driver_11dc50(AActor *A, AActor *Other)
{
    Sink((INT)A->eventEncroachingOn(Other));
    Sink((INT)A->eventEncroachingOn(A));
}

void Driver_11dcb0(const AActor *A, const AActor *B)
{
    Sink(A->IsOwnedBy(B));
    Sink(B->IsOwnedBy(A));
}

void Driver_11dd40(const FRotator *A, const FRotator *B)
{
    Sink(*A == *B);
    Sink(*B == *A);
}
#pragma inline_depth()
