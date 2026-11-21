// Work item 0327: AActor setters that re-hash the actor in the level's
// collision hash (RVA 0x903d0, 0x90440, 0x904a0) and the relative-rotation
// update (RVA 0x90510).  LTCG unit: callers pass the actor in EAX.
// Field names follow UE2 where the evidence supports it (XLevel, Hash,
// bCollideActors, Base, BaseBone, Rotation); otherwise neutral offsets.

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef int INT;

struct FVector { FLOAT X, Y, Z; };
struct FRotator { INT Pitch, Yaw, Roll; };
struct FBox { FVector Min, Max; };

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FCoords &C) : Origin(C.Origin), XAxis(C.XAxis), YAxis(C.YAxis), ZAxis(C.ZAxis) {}
    FCoords &operator/=(const FRotator &R);             // retail 0x10940d90
    FCoords operator/(const FRotator &R) const;         // retail 0x10940f40
    FCoords operator*(const FRotator &R) const;         // retail 0x109411a0
    FRotator OrthoRotation() const;                     // retail 0x10950770
};

struct FGlobalMath
{
    FCoords UnitCoords;
};
extern FGlobalMath GMath;

class AActor;

class FCollisionHash
{
public:
    void AddActor(AActor *Actor);       // retail 0x10a198a0 (LTCG: Actor in EBX)
};

// retail 0x10a19a20, FCollisionHash::RemoveActor (LTCG: hash and actor on the stack)
void __stdcall FCollisionHash_RemoveActor(FCollisionHash *Hash, AActor *Actor);

struct ULevel
{
    BYTE Pad[0x3a48];
    FCollisionHash *Hash;               // 0x3a48
};

class AActor
{
public:
    BYTE    Pad000[0xb0];
    FVector F0B0;                       // 0xb0
    BYTE    Pad0BC[0xc8 - 0xbc];
    FBox    Box;                        // 0xc8
    FRotator Rotation;                  // 0xe0
    FRotator RelativeRotation;          // 0xec
    BYTE    Pad0F8[0x100 - 0xf8];
    DWORD   F100;                       // 0x100
    BYTE    Pad104[0x108 - 0x104];
    AActor *Base;                       // 0x108
    BYTE    Pad10C[0x134 - 0x10c];
    INT     F134;                       // 0x134
    BYTE    Pad138[0x1a4 - 0x138];
    ULevel *XLevel;                     // 0x1a4
    BYTE    Pad1A8[0x1c4 - 0x1a8];
    INT    *F1C4;                       // 0x1c4
    INT     F1C8;                       // 0x1c8
    BYTE    Pad1CC[0x250 - 0x1cc];
    DWORD   F250;                       // 0x250
    BYTE    Pad254[0x2b8 - 0x254];
    DWORD   BaseBone;                   // 0x2b8, FName index
    BYTE    Pad2BC[0x2d9 - 0x2bc];
    BYTE    F2D9;                       // 0x2d9
    BYTE    Pad2DA[0x2e8 - 0x2da];
    DWORD   Pad2E8Bits : 24;            // 0x2e8
    DWORD   bWorldGeometry : 1;         // 0x2eb bit 0
    DWORD   Pad2EBBits : 7;
    DWORD   Flags2EC;                   // 0x2ec
    DWORD   Flags2F0;                   // 0x2f0, bit 12 = bCollideActors

    void Refresh_90de0();
    void Set100(DWORD Value);
    __declspec(noinline) void Set2D9(BYTE Value);   // noinline: the scaffold driver alone would inline it
    void SetB0(FVector Value);
    void UpdateRelativeRotation();
};

void UnnamedUse(AActor *Actor, INT Index);

// RVA 0x903d0
void AActor::Set100(DWORD Value)
{
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    F100 = Value;
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    Flags2EC |= 4;
    Refresh_90de0();
}

// RVA 0x90440
void AActor::Set2D9(BYTE Value)
{
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    F2D9 = Value;
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    Flags2EC |= 4;
}

// RVA 0x904a0
void AActor::SetB0(FVector Value)
{
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    F0B0 = Value;
    if ((Flags2F0 & 0x1000) && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    Flags2EC |= 4;
}

// RVA 0x90510 (near: retail builds RelCoords in BaseCoords' stack slot, frame 0x78;
// this compiles to a separate slot, frame 0xa8, otherwise identical)
void AActor::UpdateRelativeRotation()
{
    if (!Base || Base->bWorldGeometry || BaseBone != 0)
        return;
    FCoords BaseCoords = GMath.UnitCoords / Base->Rotation;
    FCoords Coords = GMath.UnitCoords * Rotation;
    FCoords RelCoords = Coords * BaseCoords.OrthoRotation();
    RelativeRotation = RelCoords.OrthoRotation();
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: stand-in bodies for the
// retail callees so the linker gives them retail's register conventions,
// and drivers calling the functions the way retail callers do.

FBox *UnnamedBox(AActor *Actor, FBox *Out);
FBox *UnnamedExpand(FBox *In, FBox *Out, FLOAT By);
void UnnamedInsert(FCollisionHash *Hash, AActor *Actor, INT X);

__declspec(noinline) void FCollisionHash::AddActor(AActor *Actor)
{
    FBox Tmp, Tmp2;
    if (!Actor || (Actor->Flags2F0 & 0x40))
        return;
    if (Actor->F134 > 0)
        FCollisionHash_RemoveActor(this, Actor);
    Actor->Box = *UnnamedBox(Actor, &Tmp);
    Actor->Box = *UnnamedExpand(&Actor->Box, &Tmp2, 4.2f);
    for (INT i = 0; i < Actor->F1C8; i++)
        UnnamedInsert(this, Actor, Actor->F1C4[i]);
}

__declspec(noinline) void AActor::Refresh_90de0()
{
    F134++;
    if (F250)
        for (INT i = 0; i < F1C8; i++)
            UnnamedUse(this, F1C4[i]);
}

INT appRound(FLOAT F);
FLOAT appAtan2(FLOAT Y, FLOAT X);
FLOAT appSqrt(FLOAT F);

struct FUnnamedSinCos { void SinCos(INT Angle, FLOAT *C, FLOAT *S); };
extern FUnnamedSinCos GUnnamedSinCos;
void UnnamedTransform(FCoords *C, FLOAT A, FLOAT B, INT Axis);

__declspec(noinline) FCoords &FCoords::operator/=(const FRotator &R)
{
    FLOAT S, C;
    GUnnamedSinCos.SinCos(R.Yaw, &C, &S);
    UnnamedTransform(this, C, S, 2);
    GUnnamedSinCos.SinCos(R.Pitch, &C, &S);
    UnnamedTransform(this, C, S, 1);
    GUnnamedSinCos.SinCos(R.Roll, &C, &S);
    UnnamedTransform(this, C, S, 0);
    return *this;
}

__declspec(noinline) FCoords FCoords::operator/(const FRotator &R) const
{
    return FCoords(*this) /= R;
}

__declspec(noinline) FRotator FCoords::OrthoRotation() const
{
    FRotator R;
    R.Pitch = appRound(appAtan2(XAxis.Z, appSqrt(XAxis.X * XAxis.X + XAxis.Y * XAxis.Y)) * 10430.378f);
    R.Yaw = appRound(appAtan2(XAxis.Y, XAxis.X) * 10430.378f);
    R.Roll = appRound(appAtan2(YAxis.Z, ZAxis.Z) * 10430.378f);
    return R;
}

void Escape(void *);
void Driver_903d0(AActor *A, AActor *B, DWORD V) { A->Set100(V); B->Set100(V); }
void Driver_90440(AActor *A, AActor *B, BYTE V) { A->Set2D9(V); B->Set2D9(V); }
void Driver_904a0(AActor *A, AActor *B, FVector V) { A->SetB0(V); B->SetB0(V); }
void Driver_90510(AActor *A, AActor *B) { Escape(&GMath); A->UpdateRelativeRotation(); B->UpdateRelativeRotation(); }
