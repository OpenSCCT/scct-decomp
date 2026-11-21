// w4_item_0045.cpp -- Versus work item 0045: AActor::processLanded (RVA 0x12d200).
// Names follow Unreal Engine 2 AActor / ULevel / FCheckResult conventions
// (bDeleteMe, bOrientOnSlope, Physics, Velocity, Rotation, XLevel, setPhysics,
// FindSlopeRotation, eventLanded, MoveActor).

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef DWORD BITFIELD;
typedef DWORD UBOOL;
typedef int INT;
typedef float FLOAT;

struct FName {
    INT Index;
};

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FRotator {
    INT Pitch, Yaw, Roll;
};

enum EPhysics {
    PHYS_None    = 0,
    PHYS_Walking = 1,
    PHYS_Falling = 2
};

class AActor;
class UFunction;
class UPrimitive;
class UMaterial;

struct FCheckResult {
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    UPrimitive *Primitive;
    FLOAT Time;
    INT Item;
    UMaterial *Material;
    DWORD unk_30;
    DWORD unk_34;

    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0);
};

class ULevel {
public:
    UBOOL MoveActor(
        AActor *Actor,
        const FVector &Delta,
        const FRotator &NewRotation,
        FCheckResult &Hit,
        UBOOL bTest = 0,
        UBOOL bIgnorePawns = 0,
        UBOOL bIgnoreBases = 0,
        UBOOL bNoFail = 0,
        UBOOL bExtra = 0
    );
};

extern const FVector &GZeroVector;

class AActor {
public:
    virtual void Vf00();
    virtual void Vf01();
    virtual void Vf02();
    virtual void Vf03();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void Vf05();
    virtual void Vf06();
    virtual void Vf07();
    virtual void Vf08();
    virtual void Vf09();
    virtual void Vf10();
    virtual void Vf11();
    virtual void Vf12();
    virtual void Vf13();
    virtual void Vf14();
    virtual void Vf15();
    virtual void Vf16();
    virtual void Vf17();
    virtual void Vf18();
    virtual void Vf19();
    virtual void Vf20();
    virtual void Vf21();
    virtual void Vf22();
    virtual void Vf23();
    virtual void Vf24();
    virtual void Vf25();
    virtual void Vf26();
    virtual void Vf27();
    virtual void Vf28();
    virtual void Vf29();
    virtual void Vf30();
    virtual void Vf31();
    virtual void Vf32();
    virtual void Vf33();
    virtual void Vf34();
    virtual void Vf35();
    virtual void Vf36();
    virtual void Vf37();
    virtual void Vf38();
    virtual void Vf39();
    virtual void Vf40();
    virtual void Vf41();
    virtual void Vf42();
    virtual void Vf43();
    virtual void Vf44();
    virtual void Vf45();
    virtual void Vf46();
    virtual void Vf47();
    virtual void Vf48();
    virtual void Vf49();
    virtual void Vf50();
    virtual void Vf51();
    virtual void Vf52();
    virtual void Vf53();
    virtual void Vf54();
    virtual void Vf55();
    virtual void Vf56();
    virtual void Vf57();
    virtual void Vf58();
    virtual void Vf59();
    virtual void Vf60();
    virtual void Vf61();
    virtual void Vf62();
    // Slot 63 (0xfc)
    virtual void setPhysics(BYTE NewPhysics, AActor *NewFloor, const FVector &NewFloorV);
    virtual void Vf64();
    virtual void Vf65();
    virtual void Vf66();
    // Slot 67 (0x10c)
    virtual void processLanded(
        const FVector &HitNormal,
        AActor *HitActor,
        FLOAT remainingTime,
        INT Iterations
    );
    virtual void Vf68();
    // Slot 69 (0x114)
    virtual FRotator FindSlopeRotation(
        const FVector &FloorNormal,
        const FRotator &NewRotation
    );

    BYTE unk_04[0x8c - 0x04];
    FVector Velocity;               // 0x8c
    BYTE unk_98[0xe0 - 0x98];
    FRotator Rotation;              // 0xe0
    BYTE unk_ec[0x1a4 - 0xec];
    ULevel *XLevel;                 // 0x1a4
    BYTE unk_1a8[0x2d8 - 0x1a8];
    BYTE Physics;                   // 0x2d8
    BYTE unk_2d9[0x2e8 - 0x2d9];
    BITFIELD unk_2e8_0 : 15;
    BITFIELD bDeleteMe : 1;         // 0x00008000
    BITFIELD unk_2e8_16 : 10;
    BITFIELD bOrientOnSlope : 1;    // 0x04000000
    BITFIELD unk_2e8_27 : 5;

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
    void eventLanded(FVector HitNormal);
};

extern FName ENGINE_Landed;

struct AActor_eventLanded_Parms {
    FVector HitNormal;
};

// AActor::eventLanded -- dispatches the UnrealScript Landed event (0x12f560, out-of-line in retail).
__declspec(noinline) void AActor::eventLanded(FVector HitNormal)
{
    AActor_eventLanded_Parms Parms;
    Parms.HitNormal = HitNormal;
    ProcessEvent(FindFunctionChecked(ENGINE_Landed), &Parms);
}

// AActor::processLanded -- handles an actor landing from a fall and optional slope alignment.
void AActor::processLanded(
    const FVector &HitNormal,
    AActor *HitActor,
    FLOAT remainingTime,
    INT Iterations)
{
    if (bDeleteMe)
        return;

    eventLanded(HitNormal);

    if (Physics == PHYS_Falling) {
        setPhysics(PHYS_None, HitActor, HitNormal);
        Velocity = GZeroVector;
    }

    if (bOrientOnSlope && Physics == PHYS_None) {
        FCheckResult Hit(1.0f);
        FRotator NewRotation = FindSlopeRotation(HitNormal, Rotation);
        XLevel->MoveActor(this, GZeroVector, NewRotation, Hit);
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Ptr) { return Ptr; }

void Driver_12d200(
    void *Mem,
    AActor *Other,
    const FVector &HitNormal,
    AActor *HitActor,
    FLOAT remainingTime,
    INT Iterations)
{
    Escape((void *)&GZeroVector);
    AActor *A = new (Mem) AActor;
    A->processLanded(HitNormal, HitActor, remainingTime, Iterations);
    Other->eventLanded(HitNormal);
}
