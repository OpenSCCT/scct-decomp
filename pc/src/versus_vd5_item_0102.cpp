// Work item 0102: AMover virtual methods (vtable 0x308cc0 slots 8, 30, 16, 32, 78).
// Names follow UE2 AMover (PostLoad, PostEditMove, PostEditChange,
// PostRaytrace, SetWorldRaytraceKey); field offsets from the disassembly.

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef int INT;

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    FRotator operator+(const FRotator &R) const { return FRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll); }
    FRotator operator-(const FRotator &R) const { return FRotator(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll); }
};

struct ULevel
{
    BYTE  Pad[0x3a48];
    void *Hash;         // 0x3a48
};

class AActor;
// Collision hash helpers (neutral names; RVA 0x119a20 and 0x1198a0).
void __stdcall FUN_10a19a20(void *Hash, AActor *Actor);
void __stdcall FUN_10a198a0(void *Hash);

// Zero vector reached through a reference (0x10ccacc0).
extern const FVector &GMath_Zero;

class AActor
{
public:
    BYTE     Pad004[0x80 - 4];
    FVector  Location;  // 0x80
    BYTE     Pad08C[0xe0 - 0x8c];
    FRotator Rotation;  // 0xe0
    BYTE     Pad0EC[0x1a4 - 0xec];
    ULevel  *XLevel;    // 0x1a4
    BYTE     Pad1A8[0x2f0 - 0x1a8];
    DWORD    Bits2F0_0_11 : 12;  // 0x2f0, bits 0-11
    DWORD    bCollideActors : 1; // 0x2f0, bit 12
    DWORD    Bits2F0_13 : 19;

    virtual ~AActor();                  // slot 0
    virtual void Vfn01();
    virtual void Vfn02();
    virtual void Vfn03();
    virtual void Vfn04();
    virtual void Vfn05();
    virtual void Vfn06();
    virtual void Vfn07();
    virtual void PostLoad();            // slot 8
    virtual void Vfn09();
    virtual void Vfn10();
    virtual void Vfn11();
    virtual void Vfn12();
    virtual void Vfn13();
    virtual void Vfn14();
    virtual void Vfn15();
    virtual void PostEditChange();      // slot 16
    virtual void Vfn17();
    virtual void Vfn18();
    virtual void Vfn19();
    virtual void Vfn20();
    virtual void Vfn21();
    virtual void Vfn22();
    virtual void Vfn23();
    virtual void Vfn24();
    virtual void Vfn25();
    virtual void Vfn26();
    virtual void Vfn27();
    virtual void Vfn28();
    virtual void Vfn29();
    virtual void PostEditMove();        // slot 30
    virtual void Vfn31();
    virtual void PostRaytrace();        // slot 32
    virtual void Vfn33();
    virtual void Vfn34();
    virtual void Vfn35();
    virtual void Vfn36();
    virtual void Vfn37();
    virtual void Vfn38();
    virtual void Vfn39();
    virtual void Vfn40();
    virtual void Vfn41();
    virtual void Vfn42();
    virtual void Vfn43();
    virtual void Vfn44();
    virtual void Vfn45();
    virtual void Vfn46();
    virtual void Vfn47();
    virtual void Vfn48();
    virtual void Vfn49();
    virtual void Vfn50();
    virtual void Vfn51();
    virtual void Vfn52();
    virtual void Vfn53();
    virtual void Vfn54();
    virtual void Vfn55();
    virtual void Vfn56();
    virtual void Vfn57();
    virtual void Vfn58();
    virtual void Vfn59();
    virtual void Vfn60();
    virtual void Vfn61();
    virtual void Vfn62();
    virtual void Vfn63();
    virtual void Vfn64();
    virtual void Vfn65();
    virtual void Vfn66();
    virtual void Vfn67();
    virtual void Vfn68();
    virtual void Vfn69();
    virtual void Vfn70();
    virtual void Vfn71();
    virtual void Vfn72();
    virtual void Vfn73();
    virtual void Vfn74();
    virtual void Vfn75();
    virtual void Vfn76();
    virtual void Vfn77();
    virtual void SetWorldRaytraceKey(); // slot 78
};

class AMover : public AActor
{
public:
    BYTE     Pad2F4[0x31c - 0x2f4];
    FVector  KeyPos[8];     // 0x31c
    FVector  BasePos;       // 0x37c
    FVector  OldPos;        // 0x388
    FVector  OldPrePivot;   // 0x394
    FVector  SavedPos;      // 0x3a0
    FRotator KeyRot[8];     // 0x3ac
    FRotator BaseRot;       // 0x40c
    FRotator OldRot;        // 0x418
    FRotator SavedRot;      // 0x424
    BYTE     Pad430[0x4df - 0x430];
    BYTE     KeyNum;        // 0x4df
    BYTE     Pad4E0[2];
    BYTE     WorldRaytraceKey;  // 0x4e2

    void PostLoad();
    void PostEditMove();
    void PostEditChange();
    void PostRaytrace();
    void SetWorldRaytraceKey();
};

// RVA 0xaf670, slot 8.
void AMover::PostLoad()
{
    AActor::PostLoad();
    SavedPos = FVector(-12345.f, -12345.f, -12345.f);
    SavedRot = FRotator(123, 456, 789);
}

// RVA 0xaf6d0, slot 30.
void AMover::PostEditMove()
{
    if (KeyNum == 0)
    {
        BasePos = Location - OldPos;
        BaseRot = Rotation - OldRot;
    }
    else
    {
        KeyPos[KeyNum] = Location - (BasePos + KeyPos[0]);
        KeyRot[KeyNum] = Rotation - (BaseRot + KeyRot[0]);
        OldPos = KeyPos[KeyNum];
        OldRot = KeyRot[KeyNum];
    }
    Location = BasePos + KeyPos[KeyNum];
}

// RVA 0xaf8c0, slot 16.
void AMover::PostEditChange()
{
    AActor::PostEditChange();
    KeyNum = Clamp((INT)KeyNum, 0, 7);
    BasePos = Location - OldPos;
    BaseRot = Rotation - OldRot;
    OldPos = KeyPos[KeyNum];
    OldRot = KeyRot[KeyNum];
    Location = BasePos + OldPos;
    Rotation = BaseRot + OldRot;
    PostEditMove();
}

// RVA 0xafa40, slot 32.
void AMover::PostRaytrace()
{
    SavedPos = GMath_Zero;
    SavedRot = FRotator(0, 0, 0);
    SetWorldRaytraceKey();
}

// RVA 0xafa80, slot 78.
void AMover::SetWorldRaytraceKey()
{
    if (WorldRaytraceKey != 255)
    {
        WorldRaytraceKey = Clamp((INT)WorldRaytraceKey, 0, 7);
        if (bCollideActors && XLevel->Hash)
            FUN_10a19a20(XLevel->Hash, this);
        Location = KeyPos[WorldRaytraceKey] + BasePos;
        Rotation = BaseRot + KeyRot[WorldRaytraceKey];
        if (bCollideActors && XLevel->Hash)
            FUN_10a198a0(XLevel->Hash);
    }
}
