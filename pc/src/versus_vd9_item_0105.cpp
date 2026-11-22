// Work item 0105 (Versus RVA 0xb0150-0xb05f6).
// 0xb0150 AActor::execMakeNoise (enhanced annotation). Field offsets follow
// the retail code; names after Unreal Engine 2 where the role is evident.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

struct FFrame;
class UObject
{
public:
};
typedef void (UObject::*Native)(FFrame &TheStack, void *Result);
extern Native GNatives[];

struct FFrame
{
    void *VfTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    void Step(UObject *Context, void *Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

class ALevelInfo;
class APawn;

class AActor : public UObject
{
public:
    BYTE Pad0[0x104];
    AActor *Owner;              // 0x104
    BYTE Pad1[0x194 - 0x108];
    APawn *Instigator;          // 0x194
    BYTE Pad2[0x1a0 - 0x198];
    ALevelInfo *Level;          // 0x1a0
    void execMakeNoise(FFrame &Stack, void *Result);
    void CheckNoiseHearing(FLOAT Loudness);
};

class ALevelInfo : public AActor
{
public:
    BYTE Pad3[0x4a8 - 0x1a4];
    BYTE NetMode;               // 0x4a8
};

class APawn : public AActor
{
public:
    BYTE Pad3[0x440 - 0x1a4];
    FLOAT SoundDampening;       // 0x440
    BYTE Pad4[0x4a2 - 0x444];
    BYTE Posture_4a2;           // 0x4a2 (unidentified enum byte)
};

enum { NM_Client = 3 };

void AActor::execMakeNoise(FFrame &Stack, void *Result)
{
    FLOAT Loudness = 0.f;
    Stack.Step(Stack.Object, &Loudness);
    Stack.Code++;
    if (Level->NetMode != NM_Client && Instigator) {
        if (Owner == (AActor *)Instigator || (AActor *)Instigator == this)
            Loudness *= Instigator->SoundDampening;
        if (Instigator->Posture_4a2 < 2)
            Loudness *= 0.3f;
        CheckNoiseHearing(Loudness);
    }
}

// Scaffolding for the link, not part of the unit.
// Stand-in body for AActor::CheckNoiseHearing (retail 0xf1a50, which the
// linker gave `this` in EDI); it is defined here only so the linker sees it
// as LTCG code and chooses the same register convention.
void NoiseStandIn(AActor *, FLOAT);
void AActor::CheckNoiseHearing(FLOAT Loudness)
{
    for (AActor *A = Owner; A; A = A->Owner)
        NoiseStandIn(A, Loudness);
    for (AActor *A = Owner; A; A = A->Owner)
        NoiseStandIn(Instigator, Loudness);
    for (AActor *A = Owner; A; A = A->Owner)
        NoiseStandIn(this, Loudness * 2.f);
}
// execMakeNoise is reached through the native table, so its address is taken.
void Escape(void *);
void Driver_b0150()
{
    Native N = (Native)&AActor::execMakeNoise;
    Escape(&N);
    Escape(&GNatives);
}

// ---------------------------------------------------------------------------
// 0xb03c0: ASPawnAttaque vtable slot 27 (reflected vtable 0x2f9ec8). Name not
// recovered; it scales a delay by the distance between this pawn and Other
// after extrapolating both along their velocities.
struct FVector
{
    FLOAT X, Y, Z;
    FVector operator+(const FVector &V) const;      // 0x405a0
    FVector operator-(const FVector &V) const;      // 0x405d0
    FLOAT Size() const;                             // 0x40750
    friend FVector operator*(FLOAT Scale, const FVector &V); // 0x40570
};

class AController_b03c0
{
public:
    BYTE Pad0[0x310];
    DWORD bFlag0 : 1;           // 0x310 bit 0
};

class ASPawnAttaque
{
public:
    BYTE Pad0[0x80 - 4];        // after the vtable pointer
    FVector Location;           // 0x80
    FVector Velocity;           // 0x8c
    BYTE Pad1[0x190 - 0x98];
    FLOAT Scale_190;            // 0x190
    BYTE Pad2[0x2d8 - 0x194];
    BYTE Mode_2d8;              // 0x2d8
    BYTE Pad3[0x2e8 - 0x2d9];
    DWORD Bits0 : 12;           // 0x2e8
    DWORD bTeam_2e8 : 1;        // 0x2e8 bit 12
    BYTE Pad4[0x2f4 - 0x2ec];
    DWORD bExcluded_2f4 : 1;    // 0x2f4 bit 0
    BYTE Pad5[0x38c - 0x2f8];
    AController_b03c0 *Controller; // 0x38c
    BYTE Pad6[0x3cc - 0x390];
    FLOAT Speed_3cc;            // 0x3cc
    virtual FLOAT Unnamed_b03c0(ASPawnAttaque *Other, FLOAT Delay, FLOAT Lead);
};

FLOAT ASPawnAttaque::Unnamed_b03c0(ASPawnAttaque *Other, FLOAT Delay, FLOAT Lead)
{
    if (Controller && Controller->bFlag0 && Other && !Other->bExcluded_2f4
        && Other->bTeam_2e8 == bTeam_2e8 && Mode_2d8 == 1) {
        double T = Lead * 0.5;
        FLOAT Dist = ((Other->Location + (FLOAT)(Delay + T) * Other->Velocity)
                      - (Location + (FLOAT)T * Velocity)).Size();
        return (Dist / Speed_3cc * 2.f + Delay * 0.5f) * Scale_190;
    }
    return Delay * Scale_190;
}

// ---------------------------------------------------------------------------
// 0xb01e0: AActor::SuggestFallVelocity-style solver (UE2 has a function of this
// shape; gravity is fixed at -1500 here). LTCG: result in ECX, Dest in EDX,
// Start in EAX, `this` (unused) on the stack, then the four floats.
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

struct FVec3
{
    FLOAT X, Y, Z;
    FVec3() {}
    FVec3(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVec3 operator-(const FVec3 &V) const { return FVec3(X - V.X, Y - V.Y, Z - V.Z); }
    FVec3 operator/(FLOAT Scale) const { FLOAT RScale = 1.f / Scale; return FVec3(X * RScale, Y * RScale, Z * RScale); }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
};

class AFallActor
{
public:
    BYTE Pad0[0x200];
    FVec3 SuggestFallVelocity(const FVec3 &Dest, const FVec3 &Start, FLOAT XYSpeed,
                              FLOAT BaseZ, FLOAT JumpZ, FLOAT MaxXYSpeed);
};

FVec3 AFallActor::SuggestFallVelocity(const FVec3 &Dest, const FVec3 &Start, FLOAT XYSpeed,
                                      FLOAT BaseZ, FLOAT JumpZ, FLOAT MaxXYSpeed)
{
    FVec3 SuggestedVelocity = Dest - Start;
    FLOAT DistZ = SuggestedVelocity.Z;
    SuggestedVelocity.Z = 0.f;
    FLOAT XYDist = SuggestedVelocity.Size();
    if (XYDist == 0.f || XYSpeed == 0.f)
        return FVec3(0.f, 0.f, BaseZ < JumpZ ? JumpZ : BaseZ);
    SuggestedVelocity = SuggestedVelocity / XYDist;

    FLOAT ReachTime = XYDist / XYSpeed;
    if (DistZ < 0.f)
        ReachTime -= appSqrt(DistZ * -0.0013333333f);
    FLOAT ZVel = DistZ / ReachTime - ReachTime * -750.f;
    if (DistZ > 0.f)
        ZVel += 50.f;
    if (ZVel < BaseZ) {
        FLOAT FallTime = (appSqrt(BaseZ * BaseZ - DistZ * 3000.f) - BaseZ) * -0.00066666666f;
        if (FallTime < 0.05f)
            FallTime = 0.05f;
        XYSpeed = XYDist / FallTime;
        if (MaxXYSpeed <= XYSpeed)
            XYSpeed = MaxXYSpeed;
        ZVel = BaseZ;
    } else {
        BaseZ += JumpZ;
        if (ZVel > BaseZ) {
            XYSpeed = BaseZ / ZVel * XYSpeed;
            ZVel = BaseZ;
        }
    }
    return FVec3(SuggestedVelocity.X * XYSpeed, SuggestedVelocity.Y * XYSpeed, ZVel);
}

// ---------------------------------------------------------------------------
// 0xb04d0: fades a range of skeletal animation channels by Amount and, once
// none is still blending, resets them. LTCG: the owning actor in EAX.
// 0x10cc0b90 is the private static class object Cast<> compares against
// (a USkeletalMeshInstance-like class; name not recovered).
class UClass_b04d0;
class UField_b04d0
{
public:
    BYTE Pad0[0x28];
    UClass_b04d0 *SuperField;   // 0x28
};
class UClass_b04d0 : public UField_b04d0 {};
extern UClass_b04d0 USkelInstance_PrivateStaticClass;

struct FAnimChannel             // 0x90 bytes
{
    BYTE Pad0[0x0c];
    FLOAT Rate_0c;              // 0x0c
    BYTE Pad1[0x20 - 0x10];
    FLOAT Rate_20;              // 0x20
    BYTE Pad2[0x50 - 0x24];
    FLOAT Blend_50;             // 0x50
    BYTE Pad3[0x90 - 0x54];
};

#define V(n) virtual void Pad##n();
class USkelInstance
{
public:
    V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
    V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
    V(60) V(61)
    virtual void StopChannel_f8(INT Channel, INT A, INT B);    // +0xf8
    BYTE Pad0[0x24 - 4];
    UClass_b04d0 *Class;        // 0x24
    BYTE Pad1[0x100 - 0x28];
    FAnimChannel *Channels;     // 0x100 (TArray data)
    INT NumChannels;            // 0x104
};
#undef V

inline USkelInstance *CastSkel(USkelInstance *Src)
{
    if (Src) {
        for (UClass_b04d0 *C = Src->Class; C; C = C->SuperField)
            if (C == &USkelInstance_PrivateStaticClass)
                return Src;
    }
    return 0;
}

template <class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }

class AChannelActor
{
public:
    BYTE Pad0[0x1d4];
    USkelInstance *MeshInstance; // 0x1d4
    void FadeChannels(INT Start, INT End, FLOAT Amount);
};

void AChannelActor::FadeChannels(INT Start, INT End, FLOAT Amount)
{
    USkelInstance *Inst = CastSkel(MeshInstance);
    UBOOL AllDone = 1;
    for (INT i = Start; i < End; i++) {
        if (i >= 0 && i < Inst->NumChannels && Inst->Channels[i].Blend_50 > 0.f) {
            FAnimChannel &C = Inst->Channels[i];
            AllDone = 0;
            if (Abs(C.Blend_50) <= Amount)
                C.Blend_50 = 0.f;
            else if (0.f <= C.Blend_50)
                C.Blend_50 = C.Blend_50 - Amount;
            else
                C.Blend_50 = Amount + C.Blend_50;
        }
    }
    if (!AllDone)
        return;
    for (INT i = Start; i < End; i++) {
        if (i >= 0 && i < Inst->NumChannels)
            Inst->Channels[i].Rate_0c = Inst->Channels[i].Rate_20 * 0.f;
        Inst->StopChannel_f8(i, 0, 0);
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_b01e0(AFallActor *A, FVec3 *D, FVec3 *S, FLOAT XY, FLOAT J, FLOAT M)
{
    FVec3 R = A->SuggestFallVelocity(*D, *S, XY, 0.f, J, M);
    Escape(&R);
    R = A->SuggestFallVelocity(*S, *D, J, 0.f, M, M);
    Escape(&R);
}
void Driver_b04d0(AChannelActor *A, FLOAT F)
{
    A->FadeChannels(2, 4, 10000.f);
    A->FadeChannels(6, 8, F);
    A->FadeChannels(1, 15, 10000.f);
}
