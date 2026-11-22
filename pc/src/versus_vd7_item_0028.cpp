// w4_item_0028.cpp -- Versus AActor script natives: execTrace, execFastTrace, execSpawn, execDestroy

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef double DOUBLE;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned short TCHAR;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(struct FFrame &Stack, RESULT_DECL);

enum EName {
    NAME_None = 0
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
};

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

// Imported/pointer zero vector used as default Extent and initial FCheckResult vectors.
extern __declspec(dllimport) const FVector GZeroVector;

struct FRotator {
    INT Pitch, Yaw, Roll;

    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

struct FGuid;
class UClass;
class UField;
class UStruct;
class UProperty;
class UMaterial;
class UPrimitive;
class ULevel;
class AActor;
class APawn;
class AController;

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
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
    virtual void NetDirty(UProperty *Property);

    INT     Index;
    BYTE    unk_8[0x1c];
    UClass *Class;

    UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject {
public:
    virtual ~UField();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();

    UField *SuperField;
    BYTE    unk_2c[0x4];
};

class UStruct : public UField {
public:
    virtual ~UStruct();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();

    BYTE unk_30[0x38];
};

class UState : public UStruct {
public:
    virtual ~UState();

    BYTE unk_68[0x20];
};

class UClass : public UState {
public:
    virtual ~UClass();

    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

typedef void (UObject::*Native)(struct FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
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

extern BYTE      *GPropAddr;
extern UObject   *GPropObject;
extern UProperty *GProperty;

#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_UBOOL_OPTX(Var, Def) DWORD Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME(Var) FName Var = NAME_None; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR_OPTX(Var, Def) FVector Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR_OPTX(Var, Def) FRotator Var = Def; Stack.Step(Stack.Object, &Var)

#define P_GET_VECTOR_REF(Var) \
    FVector Var##T; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    FVector *Var = GPropAddr ? (FVector *)GPropAddr : &Var##T

#define P_GET_OBJECT_REF(Cls, Var) \
    Cls *Var##T = 0; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    Cls **Var = GPropAddr ? (Cls **)GPropAddr : &Var##T

#define P_GET_INT_REF(Var) \
    INT Var##T = 0; GPropAddr = 0; Stack.Step(Stack.Object, &Var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    INT *Var = GPropAddr ? (INT *)GPropAddr : &Var##T

#define P_FINISH Stack.Code++

enum ETraceFlags {
    TRACE_World          = 0x00086,
    TRACE_AllColliding   = 0x000bf,
    TRACE_StopAtFirstHit = 0x00200,
    TRACE_Material       = 0x01000,
    TRACE_Flag80000      = 0x80000
};

struct FCheckResult {
    FCheckResult *Next;
    AActor       *Actor;
    FVector       Location;
    FVector       Normal;
    UPrimitive   *Primitive;
    FLOAT         Time;
    INT           Item;
    UMaterial    *Material;
    INT           HitInfo;      // neutral name; exact script out-param name not yet recovered
    BYTE          unk_34[0x4];

    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0)
        : Next(InNext), Actor(0), Location(GZeroVector), Normal(GZeroVector),
          Primitive(0), Time(InTime), Item(0), Material(0) {}
};

class ULevel {
public:
    UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                          const FVector &Start, DWORD TraceFlags,
                          const FVector &Extent = GZeroVector);
    AActor *SpawnActor(UClass *Class, FName InName, const FVector &Location,
                       const FRotator &Rotation, AActor *Template, UBOOL bNoCollisionFail,
                       UBOOL bRemoteOwned, AActor *Owner, APawn *Instigator);
    UBOOL DestroyActor(AActor *Actor, UBOOL bNetForce = 0);
};

class AActor : public UObject {
public:
    BYTE     unk_28[0x58];
    FVector  Location;
    BYTE     unk_8c[0x54];
    FRotator Rotation;
    BYTE     unk_ec[0xa8];
    APawn   *Instigator;
    BYTE     unk_198[0xc];
    ULevel  *XLevel;
    BYTE     unk_1a8[0x114];
    FName    Tag;
    BYTE     unk_2c0[0x30];
    BITFIELD unk_2f0_0 : 12;
    BITFIELD bCollideActors : 1;
    BITFIELD unk_2f0_13 : 19;
    BYTE     unk_2f4[0x4];

    ULevel *GetLevel() const { return XLevel; }

    DECLARE_NATIVE(execTrace)
    DECLARE_NATIVE(execFastTrace)
    DECLARE_NATIVE(execSpawn)
    DECLARE_NATIVE(execDestroy)
};

class APawn : public AActor {
};

class AController : public AActor {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    BYTE   unk_2f8[0x4];
    APawn *Pawn;
};

// AActor::execTrace (RVA 0x127450)
void AActor::execTrace(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR_REF(HitLocation);
    P_GET_VECTOR_REF(HitNormal);
    P_GET_VECTOR(TraceEnd);
    P_GET_VECTOR_OPTX(TraceStart, Location);
    P_GET_UBOOL_OPTX(bTraceActors, bCollideActors);
    P_GET_VECTOR_OPTX(Extent, GZeroVector);
    P_GET_OBJECT_REF(UMaterial, Material);
    P_GET_INT_REF(HitInfo);
    P_FINISH;

    FCheckResult Hit(1.0f);

    DWORD TraceFlags = bTraceActors ? TRACE_AllColliding : TRACE_World;
    if (Material)
        TraceFlags |= TRACE_Material;
    TraceFlags |= TRACE_Flag80000;

    AActor *SourceActor = this;
    if (IsA(AController::StaticClass()) && ((AController *)this)->Pawn)
        SourceActor = ((AController *)this)->Pawn;

    GetLevel()->SingleLineCheck(Hit, SourceActor, TraceEnd, TraceStart, TraceFlags, Extent);
    *(AActor **)Result = Hit.Actor;
    *HitLocation = Hit.Location;
    *HitNormal = Hit.Normal;
    *HitInfo = Hit.HitInfo;
    if (Material)
        *Material = Hit.Material;
}

// AActor::execFastTrace (RVA 0x127750)
void AActor::execFastTrace(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(TraceEnd);
    P_GET_VECTOR_OPTX(TraceStart, Location);
    P_FINISH;

    FCheckResult Hit(1.0f);
    GetLevel()->SingleLineCheck(Hit, this, TraceEnd, TraceStart, TRACE_World | TRACE_StopAtFirstHit, GZeroVector);
    *(DWORD *)Result = (Hit.Actor == 0);
}

// AActor::execSpawn (RVA 0x127800)
void AActor::execSpawn(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, SpawnClass);
    P_GET_OBJECT(AActor, SpawnOwner);
    P_GET_NAME(SpawnName);
    P_GET_VECTOR_OPTX(SpawnLocation, Location);
    P_GET_ROTATOR_OPTX(SpawnRotation, Rotation);
    P_GET_UBOOL(bNoCollisionFail);
    P_FINISH;

    AActor *Spawned = SpawnClass
        ? GetLevel()->SpawnActor(SpawnClass, NAME_None, SpawnLocation, SpawnRotation, 0,
                                 bNoCollisionFail, 0, SpawnOwner, Instigator)
        : 0;
    if (Spawned && SpawnName != NAME_None)
        Spawned->Tag = SpawnName;
    *(AActor **)Result = Spawned;
}

// AActor::execDestroy (RVA 0x127980)
void AActor::execDestroy(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(DWORD *)Result = GetLevel()->DestroyActor(this, 0);
}

// Scaffolding for the LTCG link (not part of the unit).
extern int GScaffoldingSink;
extern float GScaffoldingFloat;
void Escape(void *);
INT ExternalLineCheck(ULevel *, AActor *, const FVector &, const FVector &, DWORD, const FVector &);
void ExternalDestroy(ULevel *, AActor *, UBOOL);
AActor *ExternalSpawn(ULevel *, FName, const FRotator &, UBOOL, UBOOL, AActor *, APawn *);

__declspec(noinline) UBOOL ULevel::SingleLineCheck(FCheckResult &Hit, AActor *SourceActor,
                                                   const FVector &End, const FVector &Start,
                                                   DWORD TraceFlags, const FVector &Extent)
{
    INT R = ExternalLineCheck(this, SourceActor, End, Start, TraceFlags, Extent);
    if (R)
    {
        Hit.Actor = SourceActor;
        Hit.Location = End;
        Hit.Normal = Start;
        Hit.Material = (UMaterial *)R;
        Hit.HitInfo = R;
    }
    return R;
}

__declspec(noinline) UBOOL ULevel::DestroyActor(AActor *Actor, UBOOL bNetForce)
{
    Escape(&Actor);
    Escape(&bNetForce);
    ExternalDestroy(this, Actor, bNetForce);
    return GScaffoldingSink;
}

__declspec(noinline) AActor *ULevel::SpawnActor(UClass *Class, FName InName,
                                                const FVector &Location, const FRotator &Rotation,
                                                AActor *Template, UBOOL bNoCollisionFail,
                                                UBOOL bRemoteOwned, AActor *Owner, APawn *Instigator)
{
    if (Template)
        GScaffoldingSink = Template->Index;
    if (Class)
        GScaffoldingSink = Class->Index;
    GScaffoldingFloat = Location.X;
    return ExternalSpawn(this, InName, Rotation, bNoCollisionFail, bRemoteOwned, Owner, Instigator);
}

void Driver_127450(AActor *A, FFrame &Stack, void *const Result, ULevel *L,
                   FCheckResult &H, AActor *S, const FVector &E, const FVector &St, DWORD F, const FVector &Ex)
{
    void (AActor::*ExecP)(FFrame &, void *const) = &AActor::execTrace;
    UBOOL (ULevel::*CheckP)(FCheckResult &, AActor *, const FVector &, const FVector &, DWORD, const FVector &)
        = &ULevel::SingleLineCheck;
    Escape(&ExecP);
    Escape(&CheckP);
    A->execTrace(Stack, Result);
    L->SingleLineCheck(H, S, E, St, F, Ex);
}

void Driver_127750(AActor *A, FFrame &Stack, void *const Result, ULevel *L,
                   FCheckResult &H, AActor *S, const FVector &E, const FVector &St, DWORD F, const FVector &Ex)
{
    void (AActor::*ExecP)(FFrame &, void *const) = &AActor::execFastTrace;
    UBOOL (ULevel::*CheckP)(FCheckResult &, AActor *, const FVector &, const FVector &, DWORD, const FVector &)
        = &ULevel::SingleLineCheck;
    Escape(&ExecP);
    Escape(&CheckP);
    A->execFastTrace(Stack, Result);
    L->SingleLineCheck(H, S, E, St, F, Ex);
}

void Driver_127800(AActor *A, FFrame &Stack, void *const Result, ULevel *L,
                   UClass *C, FName N, const FVector &Loc, const FRotator &Rot,
                   AActor *T, UBOOL bNCF, UBOOL bRO, AActor *O, APawn *I)
{
    void (AActor::*ExecP)(FFrame &, void *const) = &AActor::execSpawn;
    Escape(&ExecP);
    A->execSpawn(Stack, Result);
    L->SpawnActor(C, N, Loc, Rot, T, bNCF, bRO, O, I);
}

void Driver_127980(AActor *A, FFrame &Stack, void *const Result)
{
    void (AActor::*ExecP)(FFrame &, void *const) = &AActor::execDestroy;
    Escape(&ExecP);
    A->execDestroy(Stack, Result);
}
