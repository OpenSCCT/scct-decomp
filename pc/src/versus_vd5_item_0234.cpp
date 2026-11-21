// Work item w3 0234 (RVA 0xf0080-0xf0619): AController natives (UnController.cpp, Engine).
//   0xf0080 AController::execGetPing
//   0xf00e0 AController::execCanSee
//   0xf0130 AController::execPickTarget
// Engine was built with /GL and linked with /LTCG: AController::LineOfSightTo
// (0xf1170) takes `this` in EAX, Other in ESI and bUseLOSFlag in EBX.
// Field names follow UE2 (UT2003/2004) AController/APawn/ALevelInfo where the
// offsets agree with their use here; names marked "uncertain" are guesses.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
#define RESULT_DECL void *const Result

class UObject;
class UProperty;
class UClass;
class AActor;
class APawn;
class AController;
struct FFrame;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    // Member-wise copy: retail copies vectors one component at a time.
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    UBOOL Normalize();                          // RVA 0x4f7a0
};

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

class UObject {
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property);                                 // +0x54
    BYTE ObjectPad04[0x24 - 4];
    UClass *Class;                                                               // +0x24

    UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject {
public:
    UField *SuperField;                                                          // +0x28
};

class UClass : public UField {
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

class UPlayer : public UObject {
};

// UNetConnection; the float at +0x1d0 is the connection lag in seconds (name uncertain).
class UNetConnection : public UPlayer {
public:
    static UClass PrivateStaticClass;          // VA 0x10cbc5e8
    static UClass *StaticClass() { return &PrivateStaticClass; }
    BYTE Pad[0x1d0 - 0x28];
    FLOAT BestLag;                              // +0x1d0
};

struct FFrame {
    void *VfTable;
    void *Node;                 // +0x04
    UObject *Object;            // +0x08
    BYTE *Code;                 // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    __forceinline void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_FLOAT(var) FLOAT var = 0.f; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR(var) FVector var; Stack.Step(Stack.Object, &var);
#define P_GET_ACTOR(var) AActor *var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_FLOAT_REF(var) FLOAT var##T = 0.f; Stack.StepRef(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    FLOAT *var = GPropAddr ? (FLOAT *)GPropAddr : &var##T;
#define P_FINISH Stack.Code++;

#define TRACE_PickTarget 0x286

// SCCT's FCheckResult (0x38 bytes): only Actor is initialised by the constructor.
struct FCheckResult {
    FCheckResult *Next;         // +0x00
    AActor *Actor;              // +0x04
    BYTE Pad08[0x38 - 0x08];
    FCheckResult() : Actor(0) {}
};

// Last argument of SingleLineCheck: a dword global (VA 0x10ccacc0), meaning unknown.
extern DWORD GSingleLineCheckArg_10ccacc0;

class ULevel : public UObject {
public:
    BYTE Pad28[0x2c - 0x28];
    AActor **Actors;            // +0x2c (TArray<AActor*> data)
    UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                          const FVector &Start, DWORD TraceFlags, DWORD Extra); // RVA 0x11d200
};

class AActor : public UObject {
public:
    BYTE Pad28[0x80 - 0x28];
    FVector Location;           // +0x80
    BYTE Pad8c[0x1a0 - 0x8c];
    class ALevelInfo *Level;    // +0x1a0
    ULevel *XLevel;             // +0x1a4
};

class AGameInfo : public AActor {
public:
    BYTE Pad1a8[0x2f8 - 0x1a8];
    DWORD bTeamGameFlags_2f8;   // bit 4: bTeamGame
};

class ALevelInfo : public AActor {
public:
    BYTE Pad1a8[0x4dc - 0x1a8];
    AGameInfo *Game;            // +0x4dc
    BYTE Pad4e0[0x510 - 0x4e0];
    AController *ControllerList; // +0x510
};

class ATeamInfo;
class APlayerReplicationInfo : public AActor {
public:
    BYTE Pad1a8[0x3c8 - 0x1a8];
    ATeamInfo *Team;            // +0x3c8
};

class APawn : public AActor {
public:
    BYTE Pad1a8[0x2f0 - 0x1a8];
    DWORD PawnFlags_2f0;        // bit 17: bProjTarget
    BYTE Pad2f4[0x3f8 - 0x2f4];
    FLOAT EyeHeight;            // +0x3f8 (BaseEyeHeight, uncertain)
    BYTE Pad3fc[0x40c - 0x3fc];
    INT Health;                 // +0x40c
};

class AController : public AActor {
public:
    BYTE Pad1a8[0x2f4 - 0x1a8];
    BYTE Pad2f4[2];
    BYTE Flags_2f6;             // bit 0: lets an out-of-range target count (name uncertain)
    BYTE Pad2f7;
    BYTE Pad2f8[0x2fc - 0x2f8];
    APawn *Pawn;                // +0x2fc
    BYTE Pad300[0x308 - 0x300];
    FLOAT Value_308;            // compared with Value_510 (uncertain)
    BYTE Pad30c[0x324 - 0x30c];
    AController *nextController; // +0x324
    BYTE Pad328[0x388 - 0x328];
    APlayerReplicationInfo *PlayerReplicationInfo; // +0x388
    BYTE Pad38c[0x4a4 - 0x38c];
    UPlayer *Player;            // +0x4a4 (uncertain)
    BYTE Pad4a8[0x510 - 0x4a8];
    FLOAT Value_510;            // +0x510 (uncertain)

    DWORD LineOfSightTo(AActor *Other, INT bUseLOSFlag);   // RVA 0xf1170
    void execGetPing(FFrame &Stack, RESULT_DECL);
    void execCanSee(FFrame &Stack, RESULT_DECL);
    void execPickTarget(FFrame &Stack, RESULT_DECL);
};

void AController::execGetPing(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (Player && Player->IsA(UNetConnection::StaticClass())) {
        INT Ping = (INT)(((UNetConnection *)Player)->BestLag * 1000.f);
        *(INT *)Result = Ping > 5 ? Ping : 5;
    } else {
        *(INT *)Result = 0;
    }
}

void AController::execCanSee(FFrame &Stack, RESULT_DECL)
{
    P_GET_ACTOR(Other);
    P_FINISH;
    *(DWORD *)Result = LineOfSightTo(Other, 0);
}

void AController::execPickTarget(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT_REF(bestAim);
    P_GET_FLOAT_REF(bestDist);
    P_GET_VECTOR(FireDir);
    P_GET_VECTOR(projStart);
    P_GET_FLOAT(MaxRange);
    P_FINISH;

    APawn *pick = 0;
    FLOAT VerticalAim = *bestAim * 3.f - 2.f;
    FCheckResult Hit;
    MaxRange *= MaxRange;
    FVector ViewPoint = Pawn->Location;
    ViewPoint.Z += Pawn->EyeHeight;

    for (AController *next = ((ALevelInfo *)XLevel->Actors[0])->ControllerList; next; next = next->nextController) {
        if (next == this || !next->Pawn || next->Pawn->Health <= 0 || !(next->Pawn->PawnFlags_2f0 & 0x20000))
            continue;
        if (PlayerReplicationInfo && next->PlayerReplicationInfo && (Level->Game->bTeamGameFlags_2f8 & 0x10)
            && PlayerReplicationInfo->Team == next->PlayerReplicationInfo->Team)
            continue;
        const FVector &TargetLoc = next->Pawn->Location;
        FVector AimDir = TargetLoc - projStart;
        FLOAT aim = AimDir | FireDir;
        if (aim > 0.f) {
            FVector FireDir2D(FireDir.X, FireDir.Y, 0.f);
            FireDir2D.Normalize();
            FLOAT aim2D = FireDir2D | AimDir;
            FLOAT FireDist = AimDir.SizeSquared();
            if (FireDist < MaxRange || ((Flags_2f6 & 1) && Value_308 != Value_510)) {
                FireDist = appSqrt(FireDist);
                FLOAT Scale = 1.f / FireDist;
                aim *= Scale;
                if (aim > *bestAim) {
                    XLevel->SingleLineCheck(Hit, this, TargetLoc, ViewPoint, TRACE_PickTarget, GSingleLineCheckArg_10ccacc0);
                    if (Hit.Actor)
                        XLevel->SingleLineCheck(Hit, this, FVector(next->Pawn->Location.X, next->Pawn->Location.Y, next->Pawn->Location.Z + next->Pawn->EyeHeight), ViewPoint, TRACE_PickTarget, GSingleLineCheckArg_10ccacc0);
                    if (!Hit.Actor) {
                        pick = next->Pawn;
                        *bestAim = aim;
                        *bestDist = FireDist;
                    }
                } else if (!pick && aim2D * Scale > *bestAim && aim > VerticalAim) {
                    XLevel->SingleLineCheck(Hit, this, TargetLoc, ViewPoint, TRACE_PickTarget, GSingleLineCheckArg_10ccacc0);
                    if (Hit.Actor)
                        XLevel->SingleLineCheck(Hit, this, FVector(next->Pawn->Location.X, next->Pawn->Location.Y, next->Pawn->Location.Z + next->Pawn->EyeHeight), ViewPoint, TRACE_PickTarget, GSingleLineCheckArg_10ccacc0);
                    if (!Hit.Actor) {
                        pick = next->Pawn;
                        *bestDist = FireDist;
                    }
                }
            }
        }
    }
    *(APawn **)Result = pick;
}

// Scaffolding for the LTCG link, not part of the unit. LineOfSightTo is
// defined only so the linker gives it the register convention retail uses.
void LosHelper(AActor *A, INT B);
__declspec(noinline) DWORD AController::LineOfSightTo(AActor *Other, INT bUseLOSFlag)
{
    APawn *P = Pawn;
    if (!P || !Other)
        return 0;
    LosHelper(Other, 1);
    LosHelper(Other, 2);
    LosHelper(Other, 3);
    LosHelper(P, bUseLOSFlag);
    LosHelper(Other, 4);
    return bUseLOSFlag;
}
void Escape(void *);
typedef void (AController::*ExecFunc)(FFrame &, RESULT_DECL);
void Driver_f0080()
{
    ExecFunc F = &AController::execGetPing;
    Escape(&F);
    F = &AController::execCanSee;
    Escape(&F);
    F = &AController::execPickTarget;
    Escape(&F);
    Escape(&GPropAddr);
    Escape(&GPropObject);
    Escape(&GProperty);
    Escape(&GSingleLineCheckArg_10ccacc0);
}
