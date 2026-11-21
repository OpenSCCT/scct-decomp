// Work item 0050: Versus RVA 0x12fb60-0x12ff28 (AActor / APawn Tick methods).
// - 0x12fb60: AActor::TickAuthoritative (ltcg /O2 /Gy)
// - 0x12fc40: APawn::TickSpecial (vc70 /O2 /Gy)
// - 0x12fce0: APawn::PlayerControlled (vc70 /O2 /Gy)
// - 0x12fd00: AActor::Tick (ltcg /O2 /Gy)

typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;
typedef float FLOAT;
typedef double DOUBLE;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;

enum EName
{
    NAME_None              = 0,
    NAME_PROBEMIN          = 0x12c,
    ENGINE_Tick            = 0x150,
    ENGINE_UpdateEyeHeight = 0x157,
    NAME_PROBEMAX          = 0x16c
};

struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

struct FVector
{
    FLOAT X, Y, Z;
    UBOOL IsZero() const; // retail 0x407a0
};

#pragma pack(push, 4)
struct FStateFrame
{
    BYTE  unk_00[0x1c];
    QWORD ProbeMask; // 0x1c
};
#pragma pack(pop)

enum ELevelTick
{
    LEVELTICK_TimeOnly      = 0,
    LEVELTICK_ViewportsOnly = 1,
    LEVELTICK_All           = 2
};

enum EPhysics
{
    PHYS_None     = 0,
    PHYS_Walking  = 1,
    PHYS_Falling  = 2,
    PHYS_Rotating = 3
};

enum ENetRole
{
    ROLE_None            = 0,
    ROLE_DumbProxy       = 1,
    ROLE_SimulatedProxy  = 2,
    ROLE_AutonomousProxy = 3,
    ROLE_Authority       = 4
};

enum ENetMode
{
    NM_Standalone      = 0,
    NM_DedicatedServer = 1,
    NM_ListenServer    = 2,
    NM_Client          = 3
};

class UFunction;
class UClass;
class UMesh;
class ULevel;
class ALevelInfo;
class AActor;
class AController;
class APlayerController;
class APawn;

class FUnknown
{
public:
    virtual DWORD __stdcall QueryInterface(const void *RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown
{
public:
    virtual ~UObject();                                                                 // slot 3  (+0x0c)
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);      // slot 4  (+0x10)
    virtual void VirtualSlot5();                                                        // slot 5  (+0x14)
    virtual void ProcessState(FLOAT DeltaSeconds);                                      // slot 6  (+0x18)
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

    INT          Index;       // 0x04
    BYTE         unk_08[4];   // 0x08
    FStateFrame *StateFrame;  // 0x0c
    BYTE         unk_10[0x14];// 0x10
    UClass      *Class;       // 0x24

    UFunction *FindFunctionChecked(FName InName, INT Global = 0); // retail 0x16830
    inline UBOOL IsProbing(FName ProbeName)
    {
        return (ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN))));
    }
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject
{
public:
    UField *SuperField; // 0x28
};

class UClass : public UField {};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *C = Class; C; C = (UClass *)C->SuperField)
        if (C == SomeBase)
            return 1;
    return SomeBase == 0;
}

class ULevel : public UObject
{
public:
    BYTE   unk_28[0x168];    // 0x28
    DOUBLE TimeSeconds;      // 0x190
    BYTE   unk_198[0x38c0];  // 0x198
    UBOOL  Ticked;           // 0x3a58

    UBOOL DestroyActor(AActor *ThisActor, UBOOL bNetForce = 0); // retail 0x11a790
};

struct AActor_eventTick_Parms
{
    FLOAT DeltaTime;
};

struct APawn_eventUpdateEyeHeight_Parms
{
    FLOAT DeltaTime;
};

class AActor : public UObject
{
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual UBOOL Tick(FLOAT DeltaSeconds, ELevelTick TickType);  // slot 29 (+0x74)
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
    virtual void UpdateAnimation(FLOAT DeltaSeconds);             // slot 49 (+0xc4)
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual UBOOL CheckOwnerUpdated();                            // slot 52 (+0xd0)
    virtual void TickAuthoritative(FLOAT DeltaSeconds);           // slot 53 (+0xd4)
    virtual void TickSimulated(FLOAT DeltaSeconds);               // slot 54 (+0xd8)
    virtual void TickSpecial(FLOAT DeltaSeconds);                 // slot 55 (+0xdc)
    virtual UBOOL PlayerControlled();                             // slot 56 (+0xe0)
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void performPhysics(FLOAT DeltaSeconds);              // slot 64 (+0x100)
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();

    BYTE        unk_28[0x64];        // 0x28
    FVector     Velocity;            // 0x8c
    BYTE        unk_98[0x6c];        // 0x98
    AActor     *Owner;               // 0x104
    BYTE        unk_108[0x98];       // 0x108
    ALevelInfo *Level;               // 0x1a0
    ULevel     *XLevel;              // 0x1a4
    FLOAT       LifeSpan;            // 0x1a8
    BYTE        unk_1ac[0x0c];       // 0x1ac
    FLOAT       TimerRate;           // 0x1b8
    UMesh      *Mesh;                // 0x1bc
    FLOAT       LastRenderTime;      // 0x1c0
    BYTE        unk_1c4[0x0c];       // 0x1c4
    FLOAT       TimerCounter;        // 0x1d0
    BYTE        unk_1d4[0x104];      // 0x1d4
    BYTE        Physics;             // 0x2d8
    BYTE        unk_2d9[0x04];       // 0x2d9
    BYTE        RemoteRole;          // 0x2dd
    BYTE        Role;                // 0x2de
    BYTE        unk_2df[0x09];       // 0x2df
    BITFIELD    unk_2e8_0 : 15;      // 0x2e8 bits 0..14
    BITFIELD    bDeleteMe : 1;       // 0x2e8 bit 15 (0x8000)
    BITFIELD    bTicked : 1;         // 0x2e8 bit 16 (0x10000)
    BITFIELD    unk_2e8_17 : 1;      // 0x2e8 bit 17
    BITFIELD    bTimerLoop : 1;      // 0x2e8 bit 18 (0x40000)
    BITFIELD    unk_2e8_19 : 4;      // 0x2e8 bits 19..22
    BITFIELD    bStasis : 1;         // 0x2e8 bit 23 (0x800000)
    BITFIELD    unk_2e8_24 : 8;      // 0x2e8 bits 24..31
    BYTE        unk_2ec[0x04];       // 0x2ec
    BITFIELD    unk_2f0_0 : 29;      // 0x2f0 bits 0..28
    BITFIELD    bTearOff : 1;        // 0x2f0 bit 29 (0x20000000)
    BITFIELD    unk_2f0_30 : 2;      // 0x2f0 bits 30..31
    BITFIELD    unk_2f4_0 : 16;      // 0x2f4 bits 0..15
    BITFIELD    bIsPlayer : 1;       // 0x2f4 bit 16 (byte 0x2f6 bit 0)
    BITFIELD    unk_2f4_17 : 15;     // 0x2f4 bits 17..31

    ULevel *GetLevel() const { return XLevel; }
    void UpdateTimers(FLOAT DeltaSeconds);
    void eventTick(FLOAT DeltaTime)
    {
        AActor_eventTick_Parms Parms;
        if (IsProbing(ENGINE_Tick))
        {
            Parms.DeltaTime = DeltaTime;
            ProcessEvent(FindFunctionChecked(ENGINE_Tick), &Parms);
        }
    }
};

class ALevelInfo : public AActor
{
public:
    BYTE  unk_2f8[0xb8];     // 0x2f8
    FLOAT TimeSeconds;       // 0x3b0
    BYTE  unk_3b4[0xf4];     // 0x3b4
    BYTE  NetMode;           // 0x4a8
};

class AController : public AActor
{
public:
    virtual void VirtualSlot78();            // slot 78 (+0x138)
    virtual void VirtualSlot79();            // slot 79 (+0x13c)
    virtual UBOOL IsLocalPlayerController(); // slot 80 (+0x140)
    virtual void VirtualSlot81();            // slot 81 (+0x144)
    virtual void VirtualSlot82();            // slot 82 (+0x148)

    BYTE unk_2f8[0xcc]; // 0x2f8..0x3c4
};

class APlayerController : public AController
{
public:
    virtual void VirtualSlot83(); // slot 83 (+0x14c)

    BYTE  unk_3c4[0xe4];   // 0x3c4
    FLOAT MaxResponseTime; // 0x4a8
    BYTE  unk_4ac[0x90];   // 0x4ac
    FLOAT ServerTimeStamp; // 0x53c
};

class APawn : public AActor
{
public:
    virtual void VirtualSlot78();                             // slot 78 (+0x138)
    virtual void VirtualSlot79();                             // slot 79 (+0x13c)
    virtual void VirtualSlot80();                             // slot 80 (+0x140)
    virtual void VirtualSlot81();                             // slot 81 (+0x144)
    virtual void VirtualSlot82();                             // slot 82 (+0x148)
    virtual void UpdateMovementAnimation(FLOAT DeltaSeconds); // slot 83 (+0x14c)

    virtual void TickSpecial(FLOAT DeltaSeconds);
    virtual UBOOL PlayerControlled();

    BYTE         unk_2f8[0x94];          // 0x2f8
    AController *Controller;             // 0x38c
    BYTE         unk_390[0x118];         // 0x390
    BITFIELD     unk_4a8_0 : 20;         // 0x4a8 bits 0..19
    BITFIELD     bUpdateEyeheight : 1;   // 0x4a8 bit 20 (0x100000)
    BITFIELD     unk_4a8_21 : 11;        // 0x4a8 bits 21..31
    BITFIELD     unk_4ac_0 : 16;         // 0x4ac bits 0..15
    BITFIELD     bPhysicsAnimUpdate : 1; // 0x4ac bit 16 (byte 0x4ae bit 0)
    BITFIELD     unk_4ac_17 : 15;        // 0x4ac bits 17..31

    void eventUpdateEyeHeight(FLOAT DeltaTime)
    {
        APawn_eventUpdateEyeHeight_Parms Parms;
        if (IsProbing(ENGINE_UpdateEyeHeight))
        {
            Parms.DeltaTime = DeltaTime;
            ProcessEvent(FindFunctionChecked(ENGINE_UpdateEyeHeight), &Parms);
        }
    }
};

AActor *GetTopOwner(AActor *A); // retail 0xe1c10

// ---------------------------------------------------------------------------
// 0x12fb60: AActor::TickAuthoritative
void AActor::TickAuthoritative(FLOAT DeltaSeconds)
{
    eventTick(DeltaSeconds);
    ProcessState(DeltaSeconds);
    UpdateTimers(DeltaSeconds);

    if (LifeSpan != 0.f)
    {
        LifeSpan -= DeltaSeconds;
        if (LifeSpan <= 0.0001f)
        {
            GetLevel()->DestroyActor(this);
            return;
        }
    }

    if (!bDeleteMe && Physics != PHYS_None && Role != ROLE_AutonomousProxy)
        performPhysics(DeltaSeconds);
}

// ---------------------------------------------------------------------------
// 0x12fc40: APawn::TickSpecial
void APawn::TickSpecial(FLOAT DeltaSeconds)
{
    if (!bTearOff && bPhysicsAnimUpdate && Mesh)
        UpdateMovementAnimation(DeltaSeconds);
    if (bUpdateEyeheight || (Controller && Controller->bIsPlayer))
        eventUpdateEyeHeight(DeltaSeconds);
}

// ---------------------------------------------------------------------------
// 0x12fce0: APawn::PlayerControlled
UBOOL APawn::PlayerControlled()
{
    return (Controller && Controller->IsLocalPlayerController());
}

// ---------------------------------------------------------------------------
// 0x12fd00: AActor::Tick
UBOOL AActor::Tick(FLOAT DeltaSeconds, ELevelTick TickType)
{
    if (bStasis && (Physics == PHYS_None || Physics == PHYS_Rotating)
        && (GetLevel()->TimeSeconds - LastRenderTime > 5.0)
        && (Level->NetMode == NM_Standalone))
    {
        bTicked = GetLevel()->Ticked;
        return 1;
    }

    if (!CheckOwnerUpdated())
        return 0;

    bTicked = GetLevel()->Ticked;

    if (TickType == LEVELTICK_ViewportsOnly && !PlayerControlled())
        return 1;

    UpdateAnimation(DeltaSeconds);

    if (RemoteRole == ROLE_AutonomousProxy)
    {
        APlayerController *TopOwner = (APlayerController *)GetTopOwner(this);
        if (TopOwner && TopOwner->IsLocalPlayerController())
        {
            TickAuthoritative(DeltaSeconds);
        }
        else
        {
            eventTick(DeltaSeconds);
            ProcessState(DeltaSeconds);
            UpdateTimers(DeltaSeconds);
            if (!bDeleteMe && Physics != PHYS_None && TopOwner)
            {
                FLOAT Delta = Level->TimeSeconds - TopOwner->ServerTimeStamp;
                if (Delta > TopOwner->MaxResponseTime * 0.5f && TopOwner->ServerTimeStamp != 0.f)
                {
                    if (!Velocity.IsZero())
                        performPhysics(Delta);
                    TopOwner->ServerTimeStamp = Level->TimeSeconds;
                }
            }
        }
    }
    else if (Role > ROLE_SimulatedProxy)
    {
        TickAuthoritative(DeltaSeconds);
    }
    else if (Role == ROLE_SimulatedProxy)
    {
        TickSimulated(DeltaSeconds);
    }
    else if (!bDeleteMe && (Physics == PHYS_Falling || Physics == PHYS_Rotating))
    {
        performPhysics(DeltaSeconds);
    }

    if (!bDeleteMe)
        TickSpecial(DeltaSeconds);

    return 1;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
// Separate retail callees defined here only so the linker assigns their retail
// register/stack conventions (GetTopOwner: A in EAX; UpdateTimers: this in EAX,
// DeltaSeconds on stack; DestroyActor: all three args on stack, ret 0xc).
extern UClass GPlayerControllerClass;
void Escape(void *);
void DestroyActor_Unlink(ULevel *Level, AActor *ThisActor);
void DestroyActor_Cleanup(ULevel *Level, AActor *ThisActor, UBOOL bNetForce);
INT DestroyActor_Work(INT, INT, INT, INT, INT);
inline void *operator new(unsigned int, void *P) { return P; }

__declspec(noinline) AActor *GetTopOwner(AActor *A)
{
    while (A->Owner)
        A = A->Owner;
    if (A->bIsPlayer && A->IsA(&GPlayerControllerClass))
        return A;
    return 0;
}

__declspec(noinline) void AActor::UpdateTimers(FLOAT DeltaSeconds)
{
    if (bTimerLoop)
        TimerCounter = DeltaSeconds;
}

__declspec(noinline) UBOOL ULevel::DestroyActor(AActor *ThisActor, UBOOL bNetForce)
{
    Escape(&ThisActor);
    Escape(&bNetForce);
    if (ThisActor->bDeleteMe)
        return 0;
    INT r1 = DestroyActor_Work(1, 2, 3, 4, 5);
    INT r2 = DestroyActor_Work(r1, 2, 3, 4, 5);
    INT r3 = DestroyActor_Work(r1, r2, 3, 4, 5);
    INT r4 = DestroyActor_Work(r1, r2, r3, 4, 5);
    INT r5 = DestroyActor_Work(r1, r2, r3, r4, 5);
    DestroyActor_Unlink(this, ThisActor);
    DestroyActor_Cleanup(this, ThisActor, bNetForce);
    return (r1 + r2 + r3 + r4 + r5) != 0;
}

void Driver_12fb60(void *Mem, AActor *A, ULevel *L, UBOOL bNetForce)
{
    Escape((void *)&GPlayerControllerClass);
    Escape(new (Mem) AActor);
    L->DestroyActor(A, bNetForce);
}

void Driver_12fd00(void *Mem)
{
    Escape((void *)&GPlayerControllerClass);
    Escape(new (Mem) AActor);
}
