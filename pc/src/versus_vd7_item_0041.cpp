// Work item 0041: Versus RVA 0x12b000-0x12b4ab.
// Actor/Mover physics: AMover::performPhysics, AActor::performPhysics,
// AActor::fixedTurn, AActor::FindSlopeRotation, ASPawnAttaque::FindSlopeRotation.

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;

#define NULL 0
#define PI 3.1415926535897932f
#define MAXWORD 0xffff

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl atan2(double, double);
#pragma intrinsic(sqrt, atan2)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT appAtan2(FLOAT Y, FLOAT X) { return (FLOAT)atan2(Y, X); }
inline INT appTrunc(FLOAT F) { return (INT)F; }

template<class T> inline T Abs(const T A)
{
    return (A >= (T)0) ? A : -A;
}

template<class T> inline T Min(const T A, const T B)
{
    return (A <= B) ? A : B;
}

template<class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

enum EPhysics
{
    PHYS_None        = 0,
    PHYS_Walking     = 1,
    PHYS_Falling     = 2,
    PHYS_Rotating    = 3,
    PHYS_Projectile  = 4,
    PHYS_Trailer     = 5,
    PHYS_MovingBrush = 15,
};

enum EName
{
    NAME_PROBEMIN  = 300,
    NAME_PostTouch = 0x14b,
};

class FName
{
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    UBOOL IsZero() const
    {
        return ((Pitch & 65535) == 0) && ((Yaw & 65535) == 0) && ((Roll & 65535) == 0);
    }
    struct FVector Vector();
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    UBOOL IsNearlyZero() const;
    FRotator Rotation();
};

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FCoords &Other)
        : Origin(Other.Origin), XAxis(Other.XAxis), YAxis(Other.YAxis), ZAxis(Other.ZAxis) {}
    FCoords &operator/=(const FRotator &Rot);
    FCoords operator/(const FRotator &Rot) const;
};

struct FGlobalMath
{
    FCoords UnitCoords;
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;

inline FVector FRotator::Vector()
{
    return (GMath.UnitCoords / *this).XAxis;
}

class UFunction;
class ALevelInfo;

#pragma pack(push, 4)
struct FStateFrame
{
    BYTE  unk_00[0x1c];
    QWORD ProbeMask; // +0x1c
};
#pragma pack(pop)

class UObject
{
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = NULL);

    INT          Index;        // +0x04
    UObject     *HashNext;     // +0x08
    FStateFrame *StateFrame;   // +0x0c
    void        *_Linker;      // +0x10
    INT          _LinkerIndex; // +0x14
    UObject     *Outer;        // +0x18
    DWORD        ObjectFlags;  // +0x1c
    FName        Name;         // +0x20
    void        *Class;        // +0x24

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class AActor : public UObject
{
public:
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void performPhysics(FLOAT DeltaSeconds);                                       // slot 64 (+0x100)
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void physFalling(FLOAT DeltaTime, INT Iterations);                             // slot 68 (+0x110)
    virtual FRotator FindSlopeRotation(const FVector &FloorNormal, FRotator &NewRotation); // slot 69 (+0x114)

    BYTE        unk_28[0x1a0 - 0x28];
    ALevelInfo *Level;                 // +0x1a0
    BYTE        unk_1a4[0x1c0 - 0x1a4];
    FLOAT       LastRenderTime;        // +0x1c0
    BYTE        unk_1c4[0x280 - 0x1c4];
    FRotator    RotationRate;          // +0x280
    BYTE        unk_28c[0x298 - 0x28c];
    AActor     *PendingTouch;          // +0x298
    BYTE        unk_29c[0x2d8 - 0x29c];
    BYTE        Physics;               // +0x2d8
    BYTE        unk_2d9[0x2ec - 0x2d9];
    BITFIELD    unk_2ec_0 : 2;         // +0x2ec
    BITFIELD    unk_2ec_2 : 1;         // +0x2ec bit 2 (0x4)
    BITFIELD    unk_2ec_3 : 6;
    BITFIELD    unk_2ec_9 : 1;         // +0x2ec bit 9 (0x200)
    BITFIELD    unk_2ec_10 : 22;
    BITFIELD    unk_2f0_0 : 27;        // +0x2f0
    BITFIELD    bFixedRotationDir : 1; // +0x2f0 bit 27 (0x08000000)
    BITFIELD    bRotateToDesired : 1;  // +0x2f0 bit 28 (0x10000000)
    BITFIELD    bInterpolating : 1;    // +0x2f0 bit 29 (0x20000000)
    BITFIELD    unk_2f0_30 : 2;
    BYTE        unk_2f4[0x4];

    void physProjectile(FLOAT DeltaTime, INT Iterations);
    void physTrailer(FLOAT DeltaTime);
    void physicsRotation(FLOAT DeltaTime);
    INT fixedTurn(INT current, INT desired, INT deltaRate);
    void eventPostTouch(AActor *Other);
};

class ALevelInfo : public AActor
{
public:
    BYTE  unk_2f8[0x3b0 - 0x2f8];
    FLOAT TimeSeconds; // +0x3b0
};

class AMover : public AActor
{
public:
    BYTE     unk_2f8[0x4e4 - 0x2f8];
    BITFIELD unk_4e4_0 : 15; // +0x4e4
    BITFIELD unk_4e4_15 : 1; // +0x4e4 bit 15 (0x8000)
    BITFIELD unk_4e4_16 : 16;

    virtual void performPhysics(FLOAT DeltaSeconds);
    void physMover(FLOAT DeltaTime);
};

class ASPawnAttaque : public AActor
{
public:
    virtual FRotator FindSlopeRotation(const FVector &FloorNormal, FRotator &NewRotation);
};

struct AActor_eventPostTouch_Parms
{
    AActor *Other;
};

// RVA 0x12f6a0: autogenerated event thunk; inlined in AMover::performPhysics
// and called out of line in AActor::performPhysics.
void AActor::eventPostTouch(AActor *Other)
{
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << (NAME_PostTouch - NAME_PROBEMIN))))
    {
        AActor_eventPostTouch_Parms Parms;
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(FName(NAME_PostTouch)), &Parms);
    }
}

// RVA 0x12b000: AMover::performPhysics (AMover vtable slot 64)
void AMover::performPhysics(FLOAT DeltaSeconds)
{
    switch (Physics)
    {
    case PHYS_Falling:
        physFalling(DeltaSeconds, 0);
        break;
    case PHYS_Projectile:
        physProjectile(DeltaSeconds, 0);
        break;
    case PHYS_MovingBrush:
        physMover(DeltaSeconds);
        break;
    }

    if (unk_2ec_9 && Physics != PHYS_Rotating && Physics != PHYS_MovingBrush && Physics != PHYS_None)
        unk_2ec_2 = 1;

    if (!RotationRate.IsZero() && !bInterpolating)
    {
        if (Physics != PHYS_Rotating || !unk_4e4_15 || Level->TimeSeconds - LastRenderTime < 2.f)
            physicsRotation(DeltaSeconds);
    }

    if (PendingTouch)
    {
        PendingTouch->eventPostTouch(this);
        AActor *OldTouch = PendingTouch;
        PendingTouch = PendingTouch->PendingTouch;
        OldTouch->PendingTouch = NULL;
    }
}

// RVA 0x12b130: AActor::performPhysics (AActor vtable slot 64)
void AActor::performPhysics(FLOAT DeltaSeconds)
{
    if (Physics == PHYS_Rotating && !bInterpolating && Level->TimeSeconds - LastRenderTime > 1.f)
        return;

    switch (Physics)
    {
    case PHYS_Falling:
        physFalling(DeltaSeconds, 0);
        break;
    case PHYS_Projectile:
        physProjectile(DeltaSeconds, 0);
        break;
    case PHYS_Trailer:
        physTrailer(DeltaSeconds);
        break;
    }

    if (!bInterpolating && !RotationRate.IsZero())
        physicsRotation(DeltaSeconds);

    if (PendingTouch)
    {
        PendingTouch->eventPostTouch(this);
        AActor *OldTouch = PendingTouch;
        PendingTouch = PendingTouch->PendingTouch;
        OldTouch->PendingTouch = NULL;
    }
}

// RVA 0x12b210: AActor::fixedTurn
INT AActor::fixedTurn(INT current, INT desired, INT deltaRate)
{
    INT result = current & 65535;
    if (deltaRate == 0)
        return result;
    current = result;
    desired = desired & 65535;

    if (bFixedRotationDir)
    {
        if (bRotateToDesired)
        {
            if (deltaRate > 0)
            {
                if (current > desired)
                    desired += 65536;
                result += Min(deltaRate, desired - current);
            }
            else
            {
                if (current < desired)
                    current += 65536;
                result += Max(deltaRate, desired - current);
            }
        }
        else
            result += deltaRate;
    }
    else if (bRotateToDesired)
    {
        if (current > desired)
        {
            if (current - desired < 32768)
                result -= Min(current - desired, Abs(deltaRate));
            else
                result += Min(desired + 65536 - current, Abs(deltaRate));
        }
        else
        {
            if (desired - current < 32768)
                result += Min(desired - current, Abs(deltaRate));
            else
                result -= Min(current + 65536 - desired, Abs(deltaRate));
        }
    }
    return (result & 65535);
}

// RVA 0x12b310: AActor::FindSlopeRotation (AActor vtable slot 69)
FRotator AActor::FindSlopeRotation(const FVector &FloorNormal, FRotator &NewRotation)
{
    if (FloorNormal.Z < 0.95 && !FloorNormal.IsNearlyZero())
    {
        FRotator SlopeRot = NewRotation;
        SlopeRot.Pitch = 0;
        FVector ActorDir = SlopeRot.Vector();
        FVector SlopeDir = ActorDir - FloorNormal * (ActorDir | FloorNormal);
        SlopeRot = SlopeDir.Rotation();
        NewRotation.Pitch = SlopeRot.Pitch;
        SlopeRot = (SlopeDir ^ FloorNormal).Rotation();
        NewRotation.Roll = SlopeRot.Pitch;
        return NewRotation;
    }
    return FRotator(0, NewRotation.Yaw, 0);
}

// RVA 0x12b490: ASPawnAttaque::FindSlopeRotation (ASPawnAttaque vtable slot 69)
FRotator ASPawnAttaque::FindSlopeRotation(const FVector &FloorNormal, FRotator &NewRotation)
{
    return AActor::FindSlopeRotation(FloorNormal, NewRotation);
}

// Scaffolding for the LTCG link, not part of the units.
void Escape(void *);
AActor *GetActor();
void ExternalPhysWork(AActor *A, FLOAT DeltaTime, INT Iterations);

#pragma auto_inline(off)
// Matched in item 0204 (RVA 0x500c0); kept out of line so LTCG assigns
// its retail register calling convention (this in ESI, return in EDI).
FRotator FVector::Rotation()
{
    FRotator R;
    R.Yaw = appTrunc(appAtan2(Y, X) * (FLOAT)MAXWORD / (2.f * PI));
    R.Pitch = appTrunc(appAtan2(Z, appSqrt(X * X + Y * Y)) * (FLOAT)MAXWORD / (2.f * PI));
    R.Roll = 0;
    return R;
}

// Matched in item 0156 (RVA 0x411a0); kept out of line so LTCG sees that
// Rot does not escape and reuses SlopeRot's stack slot in FindSlopeRotation.
FCoords &FCoords::operator/=(const FRotator &Rot)
{
    FLOAT S, C;
    GMath.SinCos(Rot.Roll, &S, &C);
    GMath.SinCos(Rot.Pitch, &S, &C);
    GMath.SinCos(Rot.Yaw, &S, &C);
    Origin.X += S + C;
    return *this;
}

FCoords FCoords::operator/(const FRotator &Rot) const
{
    return FCoords(*this) /= Rot;
}

// LTCG callee stubs so the linker assigns their retail register conventions
// (this in EAX for physProjectile/physTrailer/physicsRotation, ESI for physMover).
void AActor::physProjectile(FLOAT DeltaTime, INT Iterations)
{
    Escape(&Iterations);
    AActor *Cur = this;
    while (Cur)
    {
        ExternalPhysWork(Cur, DeltaTime, Iterations);
        Cur = Cur->PendingTouch;
    }
}

void AActor::physTrailer(FLOAT DeltaTime)
{
    AActor *Cur = this;
    while (Cur)
    {
        ExternalPhysWork(Cur, DeltaTime, 2);
        Cur = Cur->PendingTouch;
    }
}

void AActor::physicsRotation(FLOAT DeltaTime)
{
    AActor *Cur = this;
    while (Cur)
    {
        ExternalPhysWork(Cur, DeltaTime, 0);
        Cur = Cur->PendingTouch;
    }
}

void AMover::physMover(FLOAT DeltaTime)
{
    if (Physics)
        ExternalPhysWork(this, DeltaTime, 0);
    ExternalPhysWork(this, DeltaTime, 1);
}
#pragma auto_inline(on)

void Driver_12b000(AMover *M, FLOAT Dt)
{
    void (AMover::*pPerf)(FLOAT) = &AMover::performPhysics;
    Escape(&pPerf);
    M->AMover::performPhysics(Dt);
    GetActor()->physProjectile(Dt, 1);
    GetActor()->physicsRotation(Dt);
}

void Driver_12b130(AActor *A, FLOAT Dt)
{
    void (AActor::*pPerf)(FLOAT) = &AActor::performPhysics;
    Escape(&pPerf);
    A->AActor::performPhysics(Dt);
    GetActor()->physProjectile(Dt, 1);
    GetActor()->physTrailer(Dt);
    GetActor()->physicsRotation(Dt);
}

INT Driver_12b210(AActor *A, INT Cur, INT Des, INT Rate)
{
    return A->fixedTurn(Cur, Des, Rate) + A->fixedTurn(Cur + 1, Des + 2, Rate + 3);
}

void Driver_12b310(AActor *A, const FVector *N, FRotator *R, FRotator *Out)
{
    Escape(&GMath);
    FCoords (FCoords::*pDiv)(const FRotator &) const = &FCoords::operator/;
    Escape(&pDiv);
    FRotator (AActor::*pFSR)(const FVector &, FRotator &) = &AActor::FindSlopeRotation;
    Escape(&pFSR);
    *Out = A->AActor::FindSlopeRotation(*N, *R);
}
