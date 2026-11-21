// Work item w4 0040: Versus RVA 0x12aa30-0x12affe
// AActor physics helpers (Engine, UnPhysic.cpp), compiled with VC7.0 /GL and linked with /LTCG:
//   0x12aa30  AActor::execMoveSmooth
//   0x12aa90  AActor::moveSmooth
//   0x12ad80  AActor::processHitWall
//   0x12adb0  ASPawnAttaque::processHitWall
//   0x12ae30  AActor::FindBase
//   0x12af10  AActor::setPhysics

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#define RESULT_DECL void *const Result

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)

inline FLOAT Abs(FLOAT A) { return (FLOAT)fabs(A); }

enum { INDEX_NONE = -1 };

enum EName
{
    NAME_None = 0,
    NAME_PROBEMIN = 0x12c,
    NAME_PROBEMAX = 0x16c,
    NAME_HitWall = 0x135,
    NAME_NotifyHitWall = 0x161,
};

enum EPhysics
{
    PHYS_None       = 0,
    PHYS_Walking    = 1,
    PHYS_Falling    = 2,
    PHYS_Rotating   = 3,
    PHYS_RootMotion = 5,
};

enum ETraceFlags
{
    TRACE_AllBlocking = 0xdf,
};

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
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
    FVector SafeNormal() const; // 0x10950d30
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

// Imported static vectors (read through pointer indirection in retail):
//   0x10ccacc0 = GZeroVector (0, 0, 0)
//   0x10ccabf4 = GDownVector (0, 0, -1)
//   0x10ccacbc = GUpVector   (0, 0, 1)
__declspec(dllimport) extern const FVector GZeroVector;
__declspec(dllimport) extern const FVector GDownVector;
__declspec(dllimport) extern const FVector GUpVector;

class __single_inheritance UObject;
class UClass;
class UFunction;
class UStruct;
class UPrimitive;
class UMaterial;
class UMesh;
class USkeletalMesh;
class UMeshInstance;
class USkeletalMeshInstance;
class ULevel;
class AActor;
class AController;
struct FFrame;

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct FStateFrame
{
    BYTE  unk_00[0x1c];
    QWORD ProbeMask; // +0x1c
};

#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH          Stack.Code++

struct FIteratorList
{
    FIteratorList *Next;
    FIteratorList() {}
    FIteratorList(FIteratorList *InNext) : Next(InNext) {}
};

struct FIteratorActorList : public FIteratorList
{
    AActor *Actor;
    FIteratorActorList() {}
    FIteratorActorList(FIteratorActorList *InNext, AActor *InActor)
        : FIteratorList(InNext), Actor(InActor) {}
};

struct FCheckResult : public FIteratorActorList
{
    FVector     Location;   // +0x08
    FVector     Normal;     // +0x14
    UPrimitive *Primitive;  // +0x20
    FLOAT       Time;       // +0x24
    INT         Item;       // +0x28
    UMaterial  *Material;   // +0x2c
    INT         unk_30;     // +0x30
    void       *unk_34;     // +0x34

    FCheckResult() {}
    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0)
        : FIteratorActorList(InNext, 0)
        , Location(GZeroVector)
        , Normal(GZeroVector)
        , Primitive(0)
        , Time(InTime)
        , Item(INDEX_NONE)
        , Material(0)
        , unk_34(0)
    {}
};

class UObject
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // +0x10
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21();

    INT          Index;         // +0x04
    UObject     *HashNext;      // +0x08
    FStateFrame *StateFrame;    // +0x0c
    void        *_Linker;       // +0x10
    INT          _LinkerIndex;  // +0x14
    UObject     *Outer;         // +0x18
    DWORD        ObjectFlags;   // +0x1c
    FName        Name;          // +0x20
    UClass      *Class;         // +0x24

    UBOOL IsA(UClass *SomeBase) const; // 0x10904bc0
    UFunction *FindFunctionChecked(FName InName, INT Global = 0); // 0x10916830

    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};

class UClass : public UObject {};

class USkeletalMeshInstance : public UObject
{
public:
    void __stdcall LockRootMotion(UBOOL bLock); // 0x109b82b0
};

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Actor); // 0x109df4e0
};

class USkeletalMesh : public UMesh
{
public:
    static UClass PrivateStaticClass; // 0x10cc0a78
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

class ULevel : public UObject
{
public:
    UBOOL MoveActor(
        AActor *Actor,
        const FVector &Delta,
        const FRotator &NewRotation,
        FCheckResult &Hit,
        UBOOL Test = 0,
        UBOOL IgnorePawns = 0,
        UBOOL bIgnoreBases = 0,
        UBOOL bNoFail = 0,
        UBOOL bExtra = 0
    ); // 0x10a1b780

    UBOOL SingleLineCheck(
        FCheckResult &Hit,
        AActor *SourceActor,
        const FVector &End,
        const FVector &Start,
        DWORD TraceFlags,
        const FVector &Extent
    ); // 0x10a1d200
};

class AActor : public UObject
{
public:
    virtual void V22(); virtual void V23(); virtual void V24(); virtual void V25();
    virtual void V26(); virtual void V27(); virtual void V28(); virtual void V29();
    virtual void V30(); virtual void V31(); virtual void V32(); virtual void V33();
    virtual void V34(); virtual void V35(); virtual void V36(); virtual void V37();
    virtual void V38(); virtual void V39(); virtual void V40(); virtual void V41();
    virtual void V42(); virtual void V43(); virtual void V44(); virtual void V45();
    virtual void V46();
    virtual void SetBase(AActor *NewBase, const FVector &NewFloor, INT bNotifyActor); // slot 47 (+0xbc)
    virtual void V48(); virtual void V49(); virtual void V50(); virtual void V51();
    virtual void V52(); virtual void V53(); virtual void V54(); virtual void V55();
    virtual void V56(); virtual void V57(); virtual void V58(); virtual void V59();
    virtual void V60(); virtual void V61(); virtual void V62();
    virtual void setPhysics(BYTE NewPhysics, AActor *NewFloor, const FVector &NewFloorV); // slot 63 (+0xfc)
    virtual void V64(); virtual void V65(); virtual void V66(); virtual void V67();
    virtual void V68(); virtual void V69();
    virtual void processHitWall(FVector &HitNormal, AActor *HitActor); // slot 70 (+0x118)
    virtual void stepUp(const FVector &GravDir, const FVector &DesiredDir, FVector Delta, FCheckResult &Hit); // slot 71 (+0x11c)

    BYTE     unk_28[0x80 - 0x28];
    FVector  Location;          // +0x80
    FVector  Velocity;          // +0x8c
    FVector  Acceleration;      // +0x98
    BYTE     unk_a4[0xe0 - 0xa4];
    FRotator Rotation;          // +0xe0
    BYTE     unk_ec[0x108 - 0xec];
    AActor  *Base;              // +0x108
    BYTE     unk_10c[0x1a4 - 0x10c];
    ULevel  *XLevel;            // +0x1a4
    BYTE     unk_1a8[0x1bc - 0x1a8];
    UMesh   *Mesh;              // +0x1bc
    BYTE     unk_1c0[0x268 - 0x1c0];
    FLOAT    CollisionRadius;   // +0x268
    FLOAT    CollisionHeight;   // +0x26c
    BYTE     unk_270[0x2d8 - 0x270];
    BYTE     Physics;           // +0x2d8
    BYTE     unk_2d9[0x2f0 - 0x2d9];
    DWORD    unk_2f0_0 : 30;    // +0x2f0
    DWORD    bJustTeleported : 1; // 0x40000000
    DWORD    unk_2f0_31 : 1;
    DWORD    unk_2f4;           // +0x2f4

    FVector GetCylinderExtent() const { return FVector(CollisionRadius, CollisionRadius, CollisionHeight); }
    ULevel *GetLevel() const { return XLevel; }

    void execMoveSmooth(FFrame &Stack, RESULT_DECL);
    UBOOL moveSmooth(FVector Delta);
    void FindBase();
    void TwoWallAdjust(const FVector &DesiredDir, FVector &Delta, const FVector &HitNormal, const FVector &OldHitNormal, FLOAT HitTime);
    void eventHitWall(FVector HitNormal, AActor *HitWall);
};

class AController : public AActor
{
public:
    UBOOL eventNotifyHitWall(FVector HitNormal, AActor *Wall);
};

class APawn : public AActor
{
public:
    BYTE         unk_2f8[0x38c - 0x2f8];
    AController *Controller; // +0x38c
};

class ASPawnAttaque : public APawn
{
public:
    virtual void processHitWall(FVector &HitNormal, AActor *HitActor);
};

// ---------------------------------------------------------------------------
// Target functions
// ---------------------------------------------------------------------------

// RVA 0x12aa30: AActor::execMoveSmooth
void AActor::execMoveSmooth(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Delta);
    P_FINISH;
    bJustTeleported = 0;
    *(UBOOL *)Result = moveSmooth(Delta);
}

// RVA 0x12aa90: AActor::moveSmooth
UBOOL AActor::moveSmooth(FVector Delta)
{
    FCheckResult Hit(1.f);
    UBOOL didHit = GetLevel()->MoveActor(this, Delta, Rotation, Hit, 0, 0, 0, 0, 0);
    if (Hit.Time < 1.f)
    {
        FVector GravDir = GDownVector;
        FVector DesiredDir = Delta.SafeNormal();
        FLOAT Dot = DesiredDir | GravDir;
        if (Abs(Hit.Normal.Z) < 0.2f && Dot < 0.5f && Dot > -0.2f)
        {
            stepUp(GravDir, DesiredDir, Delta * (1.f - Hit.Time), Hit);
        }
        else
        {
            FVector Adjusted = (Delta - Hit.Normal * (Delta | Hit.Normal)) * (1.f - Hit.Time);
            if ((Delta | Adjusted) >= 0.f)
            {
                FVector OldHitNormal = Hit.Normal;
                FVector DesiredDir = Delta.SafeNormal();
                GetLevel()->MoveActor(this, Adjusted, Rotation, Hit, 0, 0, 0, 0, 0);
                if (Hit.Time < 1.f)
                {
                    processHitWall(Hit.Normal, Hit.Actor);
                    TwoWallAdjust(DesiredDir, Adjusted, Hit.Normal, OldHitNormal, Hit.Time);
                    GetLevel()->MoveActor(this, Adjusted, Rotation, Hit, 0, 0, 0, 0, 0);
                }
            }
        }
    }
    return didHit;
}

// RVA 0x12ad80: AActor::processHitWall
void AActor::processHitWall(FVector &HitNormal, AActor *HitActor)
{
    eventHitWall(HitNormal, HitActor);
}

// RVA 0x12adb0: ASPawnAttaque::processHitWall
void ASPawnAttaque::processHitWall(FVector &HitNormal, AActor *HitActor)
{
    if (Controller)
    {
        if (Physics == PHYS_Walking)
            HitNormal.Z = 0.f;
        if (Controller->eventNotifyHitWall(HitNormal, HitActor))
            return;
    }
    eventHitWall(HitNormal, HitActor);
}

// RVA 0x12ae30: AActor::FindBase
void AActor::FindBase()
{
    FCheckResult Hit(1.f);
    FVector End = Location;
    End.Z -= 8.f;
    XLevel->SingleLineCheck(Hit, this, End, Location, TRACE_AllBlocking, GetCylinderExtent());
    if (Base != Hit.Actor)
        SetBase(Hit.Actor, Hit.Normal, 1);
}

// RVA 0x12af10: AActor::setPhysics
void AActor::setPhysics(BYTE NewPhysics, AActor *NewFloor, const FVector &NewFloorV)
{
    if (Physics == NewPhysics)
        return;

    if (Physics == PHYS_RootMotion)
    {
        USkeletalMesh *SkelMesh = Cast<USkeletalMesh>(Mesh);
        if (SkelMesh)
            ((USkeletalMeshInstance *)SkelMesh->MeshGetInstance(this))->LockRootMotion(0);
    }

    Physics = NewPhysics;

    if (Physics == PHYS_Walking || Physics == PHYS_None || Physics == PHYS_Rotating)
    {
        if (NewFloor == 0)
            FindBase();
        else if (Base != NewFloor)
            SetBase(NewFloor, NewFloorV, 1);
    }
    else if (Base != 0)
    {
        SetBase(0, GUpVector, 1);
    }

    if (Physics == PHYS_None || Physics == PHYS_Rotating)
    {
        Velocity = GZeroVector;
        Acceleration = GZeroVector;
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the units.
// ---------------------------------------------------------------------------

__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

__declspec(noinline) void AActor::TwoWallAdjust(const FVector &DesiredDir, FVector &Delta, const FVector &HitNormal, const FVector &OldHitNormal, FLOAT HitTime)
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

__declspec(noinline) void AActor::eventHitWall(FVector HitNormal, AActor *HitWall)
{
    if (IsProbing(NAME_HitWall))
    {
        struct AActor_eventHitWall_Parms { FVector HitNormal; AActor *HitWall; } Parms;
        Parms.HitNormal = HitNormal;
        Parms.HitWall = HitWall;
        ProcessEvent(FindFunctionChecked(NAME_HitWall), &Parms);
    }
}

__declspec(noinline) UBOOL AController::eventNotifyHitWall(FVector HitNormal, AActor *Wall)
{
    struct AController_eventNotifyHitWall_Parms { FVector HitNormal; AActor *Wall; UBOOL ReturnValue; } Parms;
    Parms.ReturnValue = 0;
    if (IsProbing(NAME_NotifyHitWall))
    {
        Parms.HitNormal = HitNormal;
        Parms.Wall = Wall;
        ProcessEvent(FindFunctionChecked(NAME_NotifyHitWall), &Parms);
    }
    return Parms.ReturnValue;
}

extern UBOOL MoveActorImpl(
    ULevel *, AActor *, FVector, const FRotator *, FCheckResult *,
    UBOOL, UBOOL, UBOOL, UBOOL, UBOOL);

__declspec(noinline) UBOOL ULevel::MoveActor(
    AActor *Actor,
    const FVector &Delta,
    const FRotator &NewRotation,
    FCheckResult &Hit,
    UBOOL Test,
    UBOOL IgnorePawns,
    UBOOL bIgnoreBases,
    UBOOL bNoFail,
    UBOOL bExtra)
{
    return MoveActorImpl(this, Actor, Delta, &NewRotation, &Hit, Test, IgnorePawns, bIgnoreBases, bNoFail, bExtra);
}

void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }

void Driver_12aa30(AActor *A, FFrame *S, void *R, FVector D)
{
    void (AActor::*Fn)(FFrame &, RESULT_DECL) = &AActor::execMoveSmooth;
    UBOOL (ULevel::*FnMA)(AActor *, const FVector &, const FRotator &, FCheckResult &, UBOOL, UBOOL, UBOOL, UBOOL, UBOOL) = &ULevel::MoveActor;
    Escape(&Fn);
    Escape(&FnMA);
    A->execMoveSmooth(*S, R);
    Escape((void *)(INT)A->moveSmooth(D));
}

void Driver_12ad80(void *ActorBuf, void *PawnBuf, AActor *A, FVector *N, AActor *H)
{
    Escape(new(ActorBuf) AActor);
    Escape(new(PawnBuf) ASPawnAttaque);
    A->eventHitWall(*N, H);
}

void Driver_12af10(void *Buf, AActor *A)
{
    Escape(new(Buf) AActor);
    A->FindBase();
}
