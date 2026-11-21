// Work item w3 0238: UnrealScript natives (Engine, UnActor.cpp / UnController.cpp).
// RVA 0xf0f80 AActor::execSuggestFallVelocity, 0xf1050 AController::execLineOfSightTo.
// Both objects were built with /GL: the natives keep thiscall (their addresses go
// into GNatives), but their callees use LTCG register conventions:
// SuggestFallVelocity takes the result in ECX, Dest in EDX, Start in EAX;
// LineOfSightTo takes this in EDI. The callee bodies at the end of the file are
// approximate stand-ins (not matched) that give the linker those conventions.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef unsigned short TCHAR;

class __single_inheritance UObject;
class UStruct;
struct FFrame;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
};

FLOAT appSqrt(FLOAT F);

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    UStruct *Node;
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
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UObject
{
public:
    virtual void Virtual00();
    INT Index;
};
#define SLOT(n) virtual void Slot##n();

class AActor : public UObject
{
public:
    BYTE Pad[0x80 - 8];
    FVector Location;
    BYTE Pad2[0x1a0 - 0x8c];
    struct ALevelInfo *Level;
    struct ULevel *XLevel;
    BYTE Pad3[0x268 - 0x1a8];
    FLOAT CollisionRadius;
    FLOAT CollisionHeight;
    UBOOL IsA(class UClass *SomeBase) const;

    // Virtual slots 1-78 are not used here; GetViewTarget is vtable +0x13c.
    SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78)
    virtual AActor *GetViewTarget();

    FVector SuggestFallVelocity(const FVector &Dest, const FVector &Start, FLOAT XYSpeed,
                                FLOAT BaseZ, FLOAT JumpZ, FLOAT MaxXYSpeed);
    void execSuggestFallVelocity(FFrame &Stack, RESULT_DECL);
};

struct ULevel;
struct ALevelInfo;
class APawn : public AActor
{
public:
    BYTE PPad[0x3f4 - 0x270];
    FLOAT EyeHeight;
};
class AController : public AActor
{
public:
    BYTE CPad[0x2fc - 0x270];
    APawn *Pawn;
    BYTE CPad3[0x310 - 0x300];
    DWORD Flags;
    BYTE CPad4[0x350 - 0x314];
    APawn *Enemy;
    BYTE CPad5[0x358 - 0x354];
    FVector LastSeenPos;
    FVector LastSeeingPos;
    FLOAT LastSeenTime;

    UBOOL LineOfSightTo(AActor *Other, INT bUseLOSFlag);
    void execLineOfSightTo(FFrame &Stack, RESULT_DECL);
};

void AActor::execSuggestFallVelocity(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Destination);
    P_GET_VECTOR(Start);
    P_GET_FLOAT(MaxZ);
    P_GET_FLOAT(MaxXYSpeed);
    P_FINISH;
    *(FVector *)Result = SuggestFallVelocity(Destination, Start, MaxXYSpeed, 0.f, MaxZ, MaxXYSpeed);
}

void AController::execLineOfSightTo(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, Other);
    P_FINISH;
    *(DWORD *)Result = LineOfSightTo(Other, 0);
}

// Scaffolding for the LTCG link, not part of the unit. Stand-ins for the callees
// (retail 0xb01e0 AActor::SuggestFallVelocity, 0xf14a0 AController::LineOfSightTo),
// compiled with /GL so the call sites get retail's conventions.
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

FVector AActor::SuggestFallVelocity(const FVector &Dest, const FVector &Start, FLOAT XYSpeed,
                                    FLOAT BaseZ, FLOAT JumpZ, FLOAT MaxXYSpeed)
{
    FLOAT DX = Dest.X - Start.X;
    FLOAT DY = Dest.Y - Start.Y;
    FLOAT DistZ = Dest.Z - Start.Z;
    FLOAT XYDist = (FLOAT)sqrt(DX * DX + DY * DY);
    if (XYDist == 0.f || XYSpeed == 0.f)
        return FVector(0.f, 0.f, BaseZ < JumpZ ? JumpZ : BaseZ);
    FLOAT Scale = XYSpeed / XYDist;
    if (DistZ > MaxXYSpeed)
        Scale = MaxXYSpeed / XYDist;
    else if (DistZ < 0.f)
        DistZ = (FLOAT)sqrt(-DistZ) * JumpZ;
    return FVector(DX * Scale, DY * Scale, DistZ + BaseZ);
}

struct FCheckResult
{
    FCheckResult *Next;
    AActor *Actor;
    BYTE Pad[0x40];
    FCheckResult(FLOAT InTime, FCheckResult *InNext);
};
struct ULevel
{
    void SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                         const FVector &Start, DWORD TraceFlags, DWORD Extra);
};
struct ALevelInfo
{
    BYTE Pad[0x3b0];
    FLOAT TimeSeconds;
};
extern DWORD GTraceExtra;
extern class UClass *PlayerClass;

UBOOL AController::LineOfSightTo(AActor *Other, INT bUseLOSFlag)
{
    if (!Other)
        return 0;
    AActor *ViewTarg = GetViewTarget();
    FVector ViewPoint = ViewTarg->Location;
    if (ViewTarg == Pawn)
        ViewPoint.Z += Pawn->EyeHeight;
    FCheckResult Hit(1.f, 0);
    FLOAT DistSq;
    const FVector &OtherLoc = Other->Location;
    if (Other == Enemy)
    {
        XLevel->SingleLineCheck(Hit, this, OtherLoc, ViewPoint, 0x286, GTraceExtra);
        if (Hit.Actor && Hit.Actor != Other)
        {
            FVector Head(Enemy->Location.X, Enemy->Location.Y, Enemy->Location.Z + Enemy->EyeHeight);
            XLevel->SingleLineCheck(Hit, this, Head, ViewPoint, 0x286, GTraceExtra);
        }
        if (!Hit.Actor || Hit.Actor == Other)
        {
            LastSeenTime = Level->TimeSeconds;
            LastSeeingPos = GetViewTarget()->Location;
            LastSeenPos = Enemy->Location;
            Flags |= 0x100;
            return 1;
        }
        FVector D = OtherLoc - ViewTarg->Location;
        DistSq = D.SizeSquared();
        if (Other->CollisionRadius * Other->CollisionRadius / DistSq < 0.0001f)
            return 0;
    }
    else
    {
        XLevel->SingleLineCheck(Hit, this, OtherLoc, ViewPoint, 0x286, GTraceExtra);
        if (!Hit.Actor || Hit.Actor == Other)
            return 1;
        FVector D = OtherLoc - ViewTarg->Location;
        DistSq = D.SizeSquared();
        if (DistSq > 64000000.f)
            return 0;
        if ((!(Flags & 1) || !Other->IsA(PlayerClass)) && DistSq > 4000000.f)
            return 0;
        if (!bUseLOSFlag || !(Flags & 4))
        {
            FVector Head(OtherLoc.X, OtherLoc.Y, OtherLoc.Z + Other->CollisionHeight * 0.8f);
            XLevel->SingleLineCheck(Hit, this, Head, ViewPoint, 0x286, GTraceExtra);
            if (!Hit.Actor || Hit.Actor == Other)
                return 1;
        }
        if (bUseLOSFlag && !(Flags & 4))
            return 0;
        if (Other->CollisionRadius * Other->CollisionRadius / DistSq < 0.00015f)
            return 0;
    }
    FVector Points[4];
    FLOAT R = Other->CollisionRadius;
    Points[0] = FVector(OtherLoc.X + R, OtherLoc.Y + R, OtherLoc.Z);
    Points[1] = FVector(OtherLoc.X - R, OtherLoc.Y - R, OtherLoc.Z);
    Points[2] = FVector(OtherLoc.X - R, OtherLoc.Y + R, OtherLoc.Z);
    Points[3] = FVector(OtherLoc.X + R, OtherLoc.Y - R, OtherLoc.Z);
    INT IMin = 0, IMax = 0;
    FLOAT CurrentMin = (Points[0] - ViewPoint).SizeSquared();
    FLOAT CurrentMax = CurrentMin;
    for (INT i = 1; i < 4; i++)
    {
        FLOAT NextSize = (Points[i] - ViewPoint).SizeSquared();
        if (NextSize > CurrentMax)
        {
            CurrentMax = NextSize;
            IMax = i;
        }
        else if (NextSize < CurrentMin)
        {
            CurrentMin = NextSize;
            IMin = i;
        }
    }
    for (INT i = 0; i < 3; i++)
    {
        if (i != IMin && i != IMax)
        {
            XLevel->SingleLineCheck(Hit, this, Points[i], ViewPoint, 0x286, GTraceExtra);
            if (!Hit.Actor || Hit.Actor == Other)
                return 1;
        }
    }
    return 0;
}

typedef void (AActor::*ActorNative)(FFrame &, void *const);
extern ActorNative KeepSuggestFallVelocity;
extern ActorNative KeepLineOfSightTo;
void Driver_f0f80() { KeepSuggestFallVelocity = &AActor::execSuggestFallVelocity; }
void Driver_f1050() { KeepLineOfSightTo = (ActorNative)&AController::execLineOfSightTo; }
