// Work item 0131: Versus RVA 0xbe8a0 and 0xbec50 (LTCG unit).
// The owning class is not identified; UnnamedClass_be8a0 is a neutral name.
// It eases six angle-like values (0x2e0-0x304) back toward rest or toward a
// target direction, according to a mode at 0x30c that 0xbec50 sets.
typedef float FLOAT;
typedef int INT;

#define SMALL_NUMBER 1.e-8f
#define DEG_TO_RAD 0.017453f


extern "C" double __cdecl asin(double);
#pragma intrinsic(asin)
extern "C" double __cdecl acos(double);
#pragma intrinsic(acos)
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

inline FLOAT Abs(FLOAT A) { return (A >= 0.f) ? A : -A; }
inline FLOAT ClampInline(FLOAT X, FLOAT Min, FLOAT Max) { return X < Min ? Min : X < Max ? X : Max; }
FLOAT Clamp(FLOAT X, FLOAT Min, FLOAT Max); // 0x4f040, called out of line

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator^(const FVector &V) const;
};

extern FVector *GZeroVectorPtr_10ccacc0;

// 0x40540 (another unit; defined so the link gives it its retail convention)
FVector FVector::operator^(const FVector &V) const
{
    return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
}

// 0x50d30 (another unit; defined so the link gives it its retail convention).
// Retail passes the result pointer in ECX and the vector in EDX, the order a
// non-member function gets, so it is written as one here.
FVector SafeNormal(const FVector &V)
{
    FLOAT SquareSum = V.X * V.X + V.Y * V.Y + V.Z * V.Z;
    if (SquareSum < SMALL_NUMBER)
        return *GZeroVectorPtr_10ccacc0;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale);
}

class UnnamedClass_be8a0
{
public:
    char Pad0[0x2e0];
    FLOAT Value2E0, Value2E4;   // 0x2e0
    FLOAT Value2E8;             // 0x2e8
    FLOAT Value2EC;             // 0x2ec
    FLOAT Value2F0, Value2F4;   // 0x2f0
    FLOAT Value2F8, Value2FC;   // 0x2f8
    FLOAT Value300, Value304;   // 0x300
    FLOAT DeltaTime;            // 0x308
    INT Mode;                   // 0x30c
    FLOAT Limit310, Limit314, Limit318, Limit31C; // 0x310
    FVector DirA;               // 0x320
    FVector DirB;               // 0x32c
    char Pad338[0x350 - 0x338];
    FLOAT TrackRate;            // 0x350
    FLOAT RestRate;             // 0x354

    void __stdcall Update();
    void SetMode(INT InMode, const FVector &InDirA, const FVector &InDirB, FLOAT A, FLOAT B, FLOAT C, FLOAT D);
};

// Helpers from work item 0129, defined here for their retail register conventions.

// 0xbdd60
void DecayToZero(FLOAT *Value, UnnamedClass_be8a0 *Owner)
{
    if (*Value > 0.f) {
        FLOAT V = *Value - Owner->RestRate * Owner->DeltaTime;
        *Value = 0.f >= V ? 0.f : V;
    } else if (*Value < 0.f) {
        FLOAT V = Owner->RestRate * Owner->DeltaTime + *Value;
        *Value = 0.f <= V ? 0.f : V;
    }
}

__forceinline void DecayToZeroRate(FLOAT *Value, FLOAT Rate, UnnamedClass_be8a0 *Owner)
{
    if (*Value > 0.f) {
        FLOAT V = *Value - Rate * Owner->DeltaTime;
        *Value = 0.f >= V ? 0.f : V;
    } else if (*Value < 0.f) {
        FLOAT V = Rate * Owner->DeltaTime + *Value;
        *Value = 0.f <= V ? 0.f : V;
    }
}

// 0xbddd0
void DecayPairToZero(UnnamedClass_be8a0 *Owner, FLOAT *A, FLOAT *B)
{
    FLOAT RateA = Owner->RestRate;
    FLOAT RateB = Owner->RestRate;
    if (*A != 0.f && *B != 0.f) {
        FLOAT Ratio = *A / *B;
        if (Abs(Ratio) > 1.f)
            RateB = Abs(Owner->RestRate / Ratio);
        else
            RateA = Abs(Ratio * Owner->RestRate);
    }
    DecayToZeroRate(A, RateA, Owner);
    DecayToZeroRate(B, RateB, Owner);
}

// 0xbdf40
void __stdcall TrackPitch(UnnamedClass_be8a0 *Owner, FLOAT Scale, FLOAT *Value, FLOAT Rate)
{
    FLOAT Delta = (FLOAT)asin(ClampInline(Owner->DirA.Z, -1.f, 1.f)) * Scale - *Value;
    Rate *= Owner->DeltaTime;
    Delta = ClampInline(Delta, -Rate, Rate);
    *Value = ClampInline(Delta + *Value, Scale * Owner->Limit318, Scale * Owner->Limit31C);
}

// 0xbe020
void __stdcall TrackPair(UnnamedClass_be8a0 *Owner, FLOAT Scale, FLOAT *Yaw, FLOAT *Pitch, FLOAT Rate)
{
    FLOAT PitchDelta = (FLOAT)asin(ClampInline(Owner->DirA.Z, -1.f, 1.f)) * Scale - *Pitch;
    FVector NormA = SafeNormal(FVector(Owner->DirA.X, Owner->DirA.Y, 0.f));
    FVector NormB = SafeNormal(FVector(Owner->DirB.X, Owner->DirB.Y, 0.f));
    FLOAT Angle = (FLOAT)acos(ClampInline(NormB | NormA, -1.f, 1.f));
    if (NormB.Y * NormA.X - NormA.Y * NormB.X > 0.f)
        Angle = -Angle;
    FLOAT YawDelta = Angle * Scale - *Yaw;
    FLOAT YawRate = Rate;
    FLOAT PitchRate = Rate;
    if (PitchDelta != 0.f && YawDelta != 0.f) {
        FLOAT Ratio = YawDelta / PitchDelta;
        if (Abs(Ratio) > 1.f)
            PitchRate = Abs(Rate / Ratio);
        else
            YawRate = Abs(Ratio * Rate);
    }
    YawRate *= Owner->DeltaTime;
    YawDelta = ClampInline(YawDelta, -YawRate, YawRate);
    *Yaw = ClampInline(YawDelta + *Yaw, Scale * Owner->Limit310, Scale * Owner->Limit314);
    PitchRate *= Owner->DeltaTime;
    PitchDelta = ClampInline(PitchDelta, -PitchRate, PitchRate);
    *Pitch = ClampInline(PitchDelta + *Pitch, Scale * Owner->Limit318, Scale * Owner->Limit31C);
}

// RVA 0xbe8a0
void __stdcall UnnamedClass_be8a0::Update()
{
    switch (Mode) {
    case 0:
        DecayPairToZero(this, &Value2E0, &Value2E4);
        DecayToZero(&Value2E8, this);
        DecayToZero(&Value2EC, this);
        DecayPairToZero(this, &Value2F0, &Value2F4);
        DecayPairToZero(this, &Value2F8, &Value2FC);
        DecayPairToZero(this, &Value300, &Value304);
        break;
    case 1:
        TrackPair(this, 0.7f, &Value2E0, &Value2E4, TrackRate);
        DecayToZero(&Value2E8, this);
        DecayToZero(&Value2EC, this);
        DecayPairToZero(this, &Value2F0, &Value2F4);
        DecayPairToZero(this, &Value2F8, &Value2FC);
        DecayPairToZero(this, &Value300, &Value304);
        break;
    case 2:
        DecayPairToZero(this, &Value2E0, &Value2E4);
        TrackPitch(this, 0.9f, &Value2E8, TrackRate);
        DecayToZero(&Value2EC, this);
        DecayPairToZero(this, &Value2F0, &Value2F4);
        DecayPairToZero(this, &Value2F8, &Value2FC);
        DecayPairToZero(this, &Value300, &Value304);
        break;
    case 3:
    {
        DecayPairToZero(this, &Value2E0, &Value2E4);
        DecayToZero(&Value2E8, this);
        FVector NormA = DirA;
        NormA.Z = 0.f;
        NormA = SafeNormal(NormA);
        FVector NormB = DirB;
        NormB.Z = 0.f;
        NormB = SafeNormal(NormB);
        if (Abs(NormA | NormB) < 0.707f) {
            FLOAT MaxStep = TrackRate * DeltaTime;
            FLOAT Target = (NormA ^ DirB).Z > 0.f ? Limit318 : Limit31C;
            Value2EC = Clamp(Clamp(Target - Value2EC, -MaxStep, MaxStep) + Value2EC, Limit318, Limit31C);
        }
        DecayPairToZero(this, &Value2F0, &Value2F4);
        DecayPairToZero(this, &Value2F8, &Value2FC);
        DecayPairToZero(this, &Value300, &Value304);
        break;
    }
    case 4:
        DecayPairToZero(this, &Value2E0, &Value2E4);
        DecayToZero(&Value2E8, this);
        DecayToZero(&Value2EC, this);
        TrackPair(this, 0.85f, &Value2F0, &Value2F4, TrackRate);
        DecayPairToZero(this, &Value2F8, &Value2FC);
        DecayPairToZero(this, &Value300, &Value304);
        break;
    case 5:
        DecayPairToZero(this, &Value2E0, &Value2E4);
        DecayToZero(&Value2E8, this);
        DecayToZero(&Value2EC, this);
        DecayPairToZero(this, &Value2F0, &Value2F4);
        TrackPair(this, 0.85f, &Value2F8, &Value2FC, TrackRate);
        DecayPairToZero(this, &Value300, &Value304);
        break;
    case 6:
        DecayPairToZero(this, &Value2E0, &Value2E4);
        DecayToZero(&Value2E8, this);
        DecayToZero(&Value2EC, this);
        DecayPairToZero(this, &Value2F0, &Value2F4);
        DecayPairToZero(this, &Value2F8, &Value2FC);
        TrackPair(this, 0.85f, &Value300, &Value304, TrackRate);
        break;
    }
    Mode = 0;
}

// RVA 0xbec50
void UnnamedClass_be8a0::SetMode(INT InMode, const FVector &InDirA, const FVector &InDirB, FLOAT A, FLOAT B, FLOAT C, FLOAT D)
{
    Mode = InMode;
    DirA = InDirA;
    DirB = InDirB;
    Limit310 = DEG_TO_RAD * A;
    Limit314 = DEG_TO_RAD * B;
    Limit318 = DEG_TO_RAD * C;
    Limit31C = DEG_TO_RAD * D;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
extern void (__stdcall UnnamedClass_be8a0::*GUpdateTaken)();
void Driver_be8a0(UnnamedClass_be8a0 *O)
{
    GUpdateTaken = &UnnamedClass_be8a0::Update;
    Escape(&GZeroVectorPtr_10ccacc0);
    O->Update();
}
void Driver_bec50(UnnamedClass_be8a0 *O, INT M, FVector *A, FVector *B, FLOAT a, FLOAT b, FLOAT c, FLOAT d)
{
    O->SetMode(M, *A, *B, a, b, c, d);
}
