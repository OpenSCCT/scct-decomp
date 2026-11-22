// Work item 0104 (wave 3): Versus RVA 0xafe30-0xb012e.
// APawn-family ShouldTrace override, a probe-event forwarder, and
// AActor::execPlayerCanSeeMe with its TestCanSeeMe helper (LTCG).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

enum EName { NAME_None = 0 };

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

// UE2 FStateFrame: probe mask lives at +0x1c.
#pragma pack(push, 4)
struct FStateFrame
{
    BYTE Pad[0x1c];
    QWORD ProbeMask;
};
#pragma pack(pop)

struct FFrame
{
    void *VTable;
    void *Node;
    void *Object;
    BYTE *Code;
};

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
};

inline FLOAT Square(FLOAT A) { return A * A; }

class FRotator
{
public:
    INT Pitch, Yaw, Roll;
    FVector Vector();               // RVA 0x41330
};

class UFunction;
class UClass;

class UField
{
public:
    BYTE Pad[0x28];
    UField *SuperField;
};

#define VSLOT(n) virtual void VSlot##n();

class AActor;

class UObject
{
public:
    VSLOT(00) VSLOT(01) VSLOT(02) VSLOT(03)
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);    // +0x10
    VSLOT(05) VSLOT(06) VSLOT(07) VSLOT(08) VSLOT(09) VSLOT(10) VSLOT(11)
    VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
    VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25)
    virtual UBOOL VSlot26_Test(AActor *Other);                                     // +0x68
    VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34)
    VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40) VSLOT(41) VSLOT(42)
    VSLOT(43) VSLOT(44) VSLOT(45) VSLOT(46) VSLOT(47) VSLOT(48) VSLOT(49) VSLOT(50)
    VSLOT(51) VSLOT(52) VSLOT(53) VSLOT(54) VSLOT(55) VSLOT(56) VSLOT(57) VSLOT(58)
    VSLOT(59) VSLOT(60) VSLOT(61) VSLOT(62) VSLOT(63) VSLOT(64) VSLOT(65) VSLOT(66)
    VSLOT(67) VSLOT(68) VSLOT(69) VSLOT(70) VSLOT(71) VSLOT(72) VSLOT(73) VSLOT(74)
    VSLOT(75) VSLOT(76) VSLOT(77) VSLOT(78)
    virtual AActor *GetViewTarget();                                               // +0x13c

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    BYTE Pad10[0x24 - 0x10];
    UField *Class;

    UBOOL IsA(UClass *SomeBase) const
    {
        for (UField *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
            if (TempClass == (UField *)SomeBase)
                return 1;
        return SomeBase == 0;
    }
    UBOOL IsA_92b40(UClass *SomeBase);                  // RVA 0x92b40 (out-of-line copy)
    UBOOL IsProbing(FName ProbeName);                   // RVA 0x40450
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);   // RVA 0x16830
};

class ULevel
{
public:
    BYTE Pad[0x190];
    DOUBLE TimeSeconds;
};

class ALevelInfo;
class AController;

class AActor : public UObject
{
public:
    BYTE Pad28[0x80 - 0x28];
    FVector Location;
    BYTE Pad8c[0x100 - 0x8c];
    void *Ptr100;                   // unnamed
    BYTE Pad104[0x1a0 - 0x104];
    ALevelInfo *Level;
    ULevel *XLevel;
    BYTE Pad1a8[0x1c0 - 0x1a8];
    FLOAT LastRenderTime;
    BYTE Pad1c4[0x268 - 0x1c4];
    FLOAT CollisionRadius;
    BYTE Pad26c[0x2d9 - 0x26c];
    BYTE Physics;
    BYTE Pad2da[0x2e8 - 0x2da];
    DWORD Bits2e8_Pad0 : 25;
    DWORD bFlag2e8_25 : 1;          // unnamed actor bool
    DWORD Bits2e8_Pad26 : 1;
    DWORD bFlag2e8_27 : 1;          // unnamed actor bool
    DWORD Bits2e8_Pad28 : 4;

    void execPlayerCanSeeMe(FFrame &Stack, void *Result);
    void eventProbe144(INT A);
};

class AController : public AActor
{
public:
    BYTE Pad2ec[0x2f4 - 0x2ec];
    DWORD Bits2f4_Pad0 : 16;
    DWORD bIsPlayer : 1;
    DWORD Bits2f4_Pad17 : 15;
    BYTE Pad2f8[0x324 - 0x2f8];
    AController *NextController;
    BYTE Pad328[0x504 - 0x328];
    AActor *ViewTarget;
    BYTE Pad508[0x5f0 - 0x508];
    DWORD bBehindView : 1;

    UBOOL LineOfSightTo(AActor *Other, INT bUseLOSFlag = 0);    // RVA 0xf14a0
};

// The rotation used by TestCanSeeMe lives at +0xe0 of the controller; it sits
// inside AActor's padding above, so it is reached through this accessor.
inline FRotator &ControllerRotation(AController *C) { return *(FRotator *)((BYTE *)C + 0xe0); }

UBOOL TestCanSeeMe(AController *Player, AActor *Actor);

class APlayerController : public AController
{
public:
    static UClass PrivateStaticClass;   // 0x10cc6ce8
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class ALevelInfo : public AActor
{
public:
    BYTE Pad2ec[0x4a8 - 0x2ec];
    BYTE NetMode;
    BYTE Pad4a9[0x510 - 0x4a9];
    AController *ControllerList;
};

enum ENetMode { NM_Standalone = 0, NM_DedicatedServer = 1, NM_ListenServer = 2, NM_Client = 3 };

class APawn : public AActor
{
public:
    BYTE Pad2ec[0x38c - 0x2ec];
    AController *Controller;

    UBOOL ShouldTrace(AActor *SourceActor, DWORD TraceFlags);
    void ForwardProbe144(INT A);
};

// Class pushed to the IsA test in ShouldTrace (0x10cc1568); unnamed.
extern UClass Unnamed_10cc1568;

// RVA 0xafe30. Reflected vtable slot 43 of ASPawnAttaque (AActor::ShouldTrace
// in UE2); the override lives in the pawn hierarchy.
UBOOL APawn::ShouldTrace(AActor *SourceActor, DWORD TraceFlags)
{
    if (TraceFlags & 0x100)
        return 0;
    if (bFlag2e8_27 && SourceActor && !SourceActor->IsA_92b40(&Unnamed_10cc1568))
        return 0;
    if ((TraceFlags & 0x40) && SourceActor && !SourceActor->VSlot26_Test(this))
        return 0;
    if (TraceFlags & 0x8000)
        return bFlag2e8_25;
    if ((TraceFlags & 0x2000) && Ptr100 && Physics == 8)
        return 1;
    return TraceFlags & 1;
}

struct Probe144_Parms
{
    INT A;
};

// RVA 0x92e70 (LTCG: this in ESI), published in versus_vd3_item_0339.cpp.
__declspec(noinline) void AActor::eventProbe144(INT A)
{
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 24)))
    {
        Probe144_Parms Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)0x144)), &Parms);
    }
}

// RVA 0xafed0. Hands probe event 0x144 to the controller when it is probing
// for it, otherwise raises it on the pawn itself. Unnamed in the evidence.
void APawn::ForwardProbe144(INT A)
{
    if (Controller && Controller->IsProbing(FName((EName)0x144)))
    {
        Controller->eventProbe144(A);
        return;
    }
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 24)))
    {
        Probe144_Parms Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)0x144)), &Parms);
    }
}

// RVA 0xb0010 (LTCG: Player in EAX, Actor in ESI). UE2 TestCanSeeMe helper of
// execPlayerCanSeeMe. Near: 10 bytes differ, Player kept in EBX instead of EDI
// because the LineOfSightTo stand-in takes this in EBX where retail uses EDI.
__declspec(noinline) UBOOL TestCanSeeMe(AController *Player, AActor *Actor)
{
    if (!Player)
        return 0;
    if (Player->GetViewTarget() == Actor)
        return 1;
    FLOAT DistSq = (Actor->Location - Player->ViewTarget->Location).SizeSquared();
    return (DistSq < 100000.0 * (Actor->CollisionRadius + 3.6))
        && (Player->bBehindView
            || Square(ControllerRotation(Player).Vector() | (Actor->Location - Player->ViewTarget->Location)) >= 0.25f * DistSq)
        && Player->LineOfSightTo(Actor);
}

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

// RVA 0xaff50. AActor::execPlayerCanSeeMe.
void AActor::execPlayerCanSeeMe(FFrame &Stack, void *Result)
{
    Stack.Code++;   // P_FINISH
    INT Seen = 0;
    if (Level->NetMode == NM_Standalone || Level->NetMode == NM_Client)
    {
        // Just check local player visibility.
        Seen = (XLevel->TimeSeconds - LastRenderTime < 0.1);
    }
    else
    {
        for (AController *Next = Level->ControllerList; Next; Next = Next->NextController)
        {
            if (Next->bIsPlayer && TestCanSeeMe(Cast<APlayerController>(Next), this))
            {
                Seen = 1;
                break;
            }
        }
    }
    *(DWORD *)Result = Seen;
}

// Scaffolding for the LTCG link, not part of the unit. Natives and virtuals
// are reached through their addresses in retail.
typedef void (AActor::*ActorNative)(FFrame &, void *);
typedef void (APawn::*PawnIntFunc)(INT);
ActorNative Driver_aff50() { return &AActor::execPlayerCanSeeMe; }
PawnIntFunc Driver_afed0() { return &APawn::ForwardProbe144; }
// Stand-in for AController::LineOfSightTo (RVA 0xf14a0), which retail links
// into the same LTCG image with a custom convention (this in EDI, arguments
// on the stack). Only its convention matters to the callers above; the body
// is filler that gives the optimiser a frame of similar shape.
UBOOL LOSCheck_Scaffold(AController *C, AActor *Other, AActor *View, FVector *Point, INT i);
__declspec(noinline) UBOOL AController::LineOfSightTo(AActor *Other, INT bUseLOSFlag)
{
    if (!Other)
        return 0;
    BYTE Scratch[0xa0];
    AActor *View = GetViewTarget();
    FVector ViewPoint = View->Location;
    AActor *Extra = *(AActor **)((BYTE *)this + 0x2fc);
    if (View == Extra)
        ViewPoint.Z += 1.0f;
    for (INT i = 0; i < bUseLOSFlag; i++)
    {
        if (LOSCheck_Scaffold(this, Other, View, &ViewPoint, i))
            return 1;
        if (LOSCheck_Scaffold(this, View, Other, (FVector *)Scratch, i + bUseLOSFlag))
            return 1;
    }
    return LOSCheck_Scaffold(this, Other, View, (FVector *)(Scratch + 4), bUseLOSFlag);
}

// UObject::IsProbing (RVA 0x40450, published in versus_vd1_item_0150.cpp),
// linked into the same image so the optimiser can see it does not write memory.
__declspec(noinline) UBOOL UObject::IsProbing(FName ProbeName)
{
    return ProbeName.Index < 0x12c
        || ProbeName.Index >= 0x16c
        || !StateFrame
        || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.Index - 0x12c)));
}
