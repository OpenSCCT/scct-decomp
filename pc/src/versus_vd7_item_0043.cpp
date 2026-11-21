// Work item 0043: Versus RVA 0x12c9f0 (AActor::stepUp), 0x12cd80 (AActor::processHitWall),
// and 0x12cdd0 (APawn::CanCrouchWalk).

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned short TCHAR;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

inline FLOAT Abs(FLOAT A) { return (FLOAT)fabs(A); }

enum EPhysics
{
    PHYS_None    = 0,
    PHYS_Walking = 1,
    PHYS_Falling = 2,
};

enum ETraceFlags
{
    TRACE_Pawns          = 0x0001,
    TRACE_Movers         = 0x0002,
    TRACE_Level          = 0x0004,
    TRACE_Volumes        = 0x0008,
    TRACE_Others         = 0x0010,
    TRACE_OnlyProjActor  = 0x0020,
    TRACE_Blocking       = 0x0040,
    TRACE_LevelGeometry  = 0x0080,
    TRACE_ShadowCast     = 0x0100,
    TRACE_StopAtFirstHit = 0x0200,
    TRACE_World          = TRACE_Level | TRACE_Movers | TRACE_LevelGeometry,
};

enum EName
{
    NAME_HitWall   = 0x135,
    ENGINE_HitWall = 0x135,
};

struct FName
{
    INT Index;
    FName() {}
    FName(INT InIndex) : Index(InIndex) {}
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    FLOAT Size() const { return (FLOAT)sqrt(X * X + Y * Y + Z * Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector SafeNormal() const; // 0x50d30
};

inline FVector operator*(FLOAT Scale, const FVector &V)
{
    return V.operator*(Scale);
}

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

__declspec(dllimport) extern const FVector GZeroVector;

class AActor;
class UPrimitive;
class UMaterial;
class UFunction;
class UClass;

struct FCheckResult
{
    FCheckResult *Next;     // 0x00
    AActor *Actor;          // 0x04
    FVector Location;       // 0x08
    FVector Normal;         // 0x14
    UPrimitive *Primitive;  // 0x20
    FLOAT Time;             // 0x24
    INT Item;               // 0x28
    UMaterial *Material;    // 0x2c
    INT unk_30;             // 0x30
    INT unk_34;             // 0x34

    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0); // 0x927b0
};

struct FStateFrame
{
    BYTE unk_00[0x1c];
    QWORD ProbeMask;        // 0x1c
};

class UObject
{
public:
    virtual void Vf00();
    virtual void Vf04();
    virtual void Vf08();
    virtual void Vf0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // 0x10

    INT Index;               // 0x04
    UObject *HashNext;       // 0x08
    FStateFrame *StateFrame; // 0x0c
    void *Linker;            // 0x10
    INT LinkerIndex;         // 0x14
    UObject *Outer;          // 0x18
    DWORD ObjectFlags;       // 0x1c
    FName Name;              // 0x20
    UClass *Class;           // 0x24

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0); // 0x16830
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject
{
public:
    BYTE unk_28[0x10c - 0x28];
    DWORD ClassPrime;        // 0x10c
    DWORD ClassPrimeProduct; // 0x110
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    return (!SomeBase || Class == SomeBase) ? 1 : ((Class->ClassPrimeProduct % SomeBase->ClassPrime) == 0);
}

class ULevel
{
public:
    UBOOL MoveActor(AActor *Actor, const FVector &Delta, const FRotator &NewRotation,
                    FCheckResult &Hit, UBOOL Test = 0, UBOOL IgnorePawns = 0,
                    UBOOL bIgnoreBases = 0, UBOOL bNoFail = 0, UBOOL bUnused = 0); // 0x11b780
    UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                          const FVector &Start, DWORD TraceFlags,
                          const FVector &Extent = GZeroVector); // 0x11d200
};

struct AActor_eventHitWall_Parms
{
    FVector HitNormal;
    AActor *HitWall;
};

class AActor : public UObject
{
public:
    virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64(); virtual void Vf68(); virtual void Vf6c();
    virtual void Vf70(); virtual void Vf74(); virtual void Vf78(); virtual void Vf7c();
    virtual void Vf80(); virtual void Vf84(); virtual void Vf88(); virtual void Vf8c();
    virtual void Vf90(); virtual void Vf94(); virtual void Vf98(); virtual void Vf9c();
    virtual void Vfa0(); virtual void Vfa4(); virtual void Vfa8(); virtual void Vfac();
    virtual void Vfb0(); virtual void Vfb4(); virtual void Vfb8(); virtual void Vfbc();
    virtual void Vfc0(); virtual void Vfc4(); virtual void Vfc8(); virtual void Vfcc();
    virtual void Vfd0(); virtual void Vfd4(); virtual void Vfd8(); virtual void Vfdc();
    virtual void Vfe0(); virtual void Vfe4(); virtual void Vfe8(); virtual void Vfec();
    virtual void Vff0(); virtual void Vff4(); virtual void Vff8(); virtual void Vffc();
    virtual void Vf100(); virtual void Vf104();
    virtual void processHitWall(const FVector &HitNormal, AActor *HitActor); // 0x108 (slot 66)
    virtual void Vf10c();
    virtual void Vf110(); virtual void Vf114(); virtual void Vf118();
    virtual void stepUp(const FVector &GravDir, const FVector &DesiredDir,
                        FVector Delta, FCheckResult &Hit); // 0x11c (slot 71)

    BYTE unk_28[0x80 - 0x28];
    FVector Location;        // 0x80
    FVector Velocity;        // 0x8c
    BYTE unk_98[0xe0 - 0x98];
    FRotator Rotation;       // 0xe0
    BYTE unk_ec[0x1a4 - 0xec];
    ULevel *XLevel;          // 0x1a4
    BYTE unk_1a8[0x26c - 0x1a8];
    FLOAT CollisionHeight;   // 0x26c
    BYTE unk_270[0x2d8 - 0x270];
    BYTE Physics;            // 0x2d8
    BYTE unk_2d9[3];         // 0x2d9

    void TwoWallAdjust(const FVector &DesiredDir, FVector &Delta,
                       const FVector &HitNormal, const FVector &OldHitNormal,
                       FLOAT HitTime); // 0xb0630
    void eventHitWall(FVector HitNormal, AActor *HitWall); // 0x12f760
};

class APawn : public AActor
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    BYTE unk_2dc[0x3c4 - 0x2dc];
    FLOAT UncrouchTime;      // 0x3c4
    BYTE unk_3c8[0x400 - 0x3c8];
    FLOAT CrouchHeight;      // 0x400
    FLOAT CrouchRadius;      // 0x404
    BYTE unk_408[0x4a8 - 0x408];
    DWORD unk_4a8_0 : 4;
    DWORD bWantsToCrouch : 1; // 0x10
    DWORD unk_4a8_5 : 1;
    DWORD bTryToUncrouch : 1; // 0x40
    DWORD bCanCrouch : 1;     // 0x80

    UBOOL CanCrouchWalk(const FVector &StartLocation, const FVector &EndLocation); // 0x12cdd0
};

#define MAXSTEPHEIGHT 34.f
#define MAXSTEPSIDEZ  0.08f

// RVA 0x12c9f0
void AActor::stepUp(const FVector &GravDir, const FVector &DesiredDir,
                    FVector Delta, FCheckResult &Hit)
{
    FVector Down = GravDir * MAXSTEPHEIGHT;

    if (Abs(Hit.Normal.Z) < MAXSTEPSIDEZ)
    {
        // step up - treat as vertical wall
        XLevel->MoveActor(this, -1.f * Down, Rotation, Hit);
        XLevel->MoveActor(this, Delta, Rotation, Hit);
    }
    else
    {
        // step up - treat as ramp
        FVector Up = Delta;
        Up.Z += Delta.Size() * Hit.Normal.Z;
        XLevel->MoveActor(this, Up, Rotation, Hit);
    }

    if (Hit.Time < 1.f)
    {
        if (Abs(Hit.Normal.Z) < MAXSTEPSIDEZ && Hit.Time * Delta.SizeSquared() > 144.f)
        {
            XLevel->MoveActor(this, Down, Rotation, Hit);
            stepUp(GravDir, DesiredDir, Delta * (1.f - Hit.Time), Hit);
            return;
        }

        // adjust and try again
        processHitWall(Hit.Normal, Hit.Actor);
        if (Physics == PHYS_Falling)
            return;

        Hit.Normal.Z = 0.f;
        Hit.Normal = Hit.Normal.SafeNormal();
        FVector OldHitNormal = Hit.Normal;
        FVector OldDelta = Delta;
        Delta = (Delta - Hit.Normal * (Delta | Hit.Normal)) * (1.f - Hit.Time);
        if ((Delta | OldDelta) >= 0.f)
        {
            XLevel->MoveActor(this, Delta, Rotation, Hit);
            if (Hit.Time < 1.f)
            {
                processHitWall(Hit.Normal, Hit.Actor);
                if (Physics == PHYS_Falling)
                    return;
                TwoWallAdjust(DesiredDir, Delta, Hit.Normal, OldHitNormal, Hit.Time);
                XLevel->MoveActor(this, Delta, Rotation, Hit);
            }
        }
    }
    XLevel->MoveActor(this, Down, Rotation, Hit);
}

// RVA 0x12cd80
void AActor::processHitWall(const FVector &HitNormal, AActor *HitActor)
{
    if (!HitActor->IsA(APawn::StaticClass()))
        eventHitWall(HitNormal, HitActor);
}

// RVA 0x12cdd0
__declspec(noinline) UBOOL APawn::CanCrouchWalk(const FVector &StartLocation, const FVector &EndLocation)
{
    const FVector HeightOffset(0.f, 0.f, CrouchHeight - CollisionHeight);
    const FVector Start = StartLocation + HeightOffset;
    const FVector End = EndLocation + HeightOffset;
    if (!bCanCrouch)
        return 0;

    FCheckResult Hit(1.f);
    XLevel->SingleLineCheck(Hit, this, End, Start, TRACE_World | TRACE_StopAtFirstHit);
    if (Hit.Actor)
        return 0;

    XLevel->SingleLineCheck(Hit, this, End, Start, TRACE_World, FVector(CrouchRadius, CrouchRadius, CrouchHeight));
    if (Hit.Time == 1.f)
    {
        bWantsToCrouch = 1;
        bTryToUncrouch = 1;
        UncrouchTime = 0.5f;
        return 1;
    }
    return 0;
}

// Callees defined here so LTCG assigns their retail register conventions.

// RVA 0x50d30
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// RVA 0xb0630
__declspec(noinline) void AActor::TwoWallAdjust(const FVector &DesiredDir, FVector &Delta,
                                                const FVector &HitNormal, const FVector &OldHitNormal,
                                                FLOAT HitTime)
{
    if ((OldHitNormal | HitNormal) <= 0.f)
    {
        FVector Dir = HitNormal ^ OldHitNormal;
        Dir = Dir.SafeNormal();
        Delta = Dir * ((Dir | Delta) * (1.f - HitTime));
        if ((Delta | DesiredDir) < 0.f)
            Delta = Delta * -1.f;
    }
    else
    {
        Delta = (Delta - HitNormal * (HitNormal | Delta)) * (1.f - HitTime);
        if ((Delta | DesiredDir) <= 0.f)
            Delta = GZeroVector;
    }
}

// RVA 0x12f760
__declspec(noinline) void AActor::eventHitWall(FVector HitNormal, AActor *HitWall)
{
    AActor_eventHitWall_Parms Parms;
    Parms.HitNormal = HitNormal;
    Parms.HitWall = HitWall;
    if (!StateFrame || (StateFrame->ProbeMask & 0x200))
        ProcessEvent(FindFunctionChecked(ENGINE_HitWall), &Parms);
}

// Scaffolding for the link, not part of the unit.
void Escape(const void *);
UBOOL MoveActorImpl(ULevel *, AActor *, const FRotator *, FCheckResult *, FLOAT, UBOOL, UBOOL, UBOOL, UBOOL, UBOOL);

__declspec(noinline) UBOOL ULevel::MoveActor(AActor *Actor, const FVector &Delta, const FRotator &NewRotation,
                                             FCheckResult &Hit, UBOOL Test, UBOOL IgnorePawns,
                                             UBOOL bIgnoreBases, UBOOL bNoFail, UBOOL bUnused)
{
    return MoveActorImpl(this, Actor, &NewRotation, &Hit, Delta.X + Delta.Y + Delta.Z,
                         Test, IgnorePawns, bIgnoreBases, bNoFail, bUnused);
}

void Driver_12c9f0(AActor *A, const FVector *G, const FVector *D, FVector Delta, FCheckResult *H)
{
    Escape(&GZeroVector);
    A->AActor::stepUp(*G, *D, Delta, *H);
    A->TwoWallAdjust(*D, Delta, *G, *D, 0.5f);
    A->TwoWallAdjust(*D, Delta, *D, *G, 0.5f);
    FVector N = G->SafeNormal();
    Escape(&N);
}

UBOOL Driver_12cdd0(APawn *P, const FVector *S, const FVector *E)
{
    Escape(&GZeroVector);
    return P->CanCrouchWalk(*S, *E);
}
