// Work item 0129: float damping helpers near RVA 0xbdd60.
// Owner class is unidentified; UnnamedClass_bdd60 is a neutral name.
typedef float FLOAT;

extern const FLOAT Zero_10c109f8;   // 0.0f constant in .rdata

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector SafeNormal() const; // RVA 0x50d30
};

struct UnnamedClass_bdd60
{
    char Pad0[0x2E0];
    FLOAT Values[10];               // 0x2E0..0x304, decayed in pairs
    FLOAT Scale308;
    char Pad30C[0x310 - 0x30C];
    FLOAT Min310;
    FLOAT Max314;
    FLOAT Min318;
    FLOAT Max31C;
    FVector Dir320;
    FVector Dir32C;
    char Pad338[0x350 - 0x338];
    FLOAT Rate350;
    FLOAT Rate354;

    void DecayPairToZero(FLOAT *X, FLOAT *Y);
    void ApproachAsin_bdf40(FLOAT *Value, FLOAT Scale, FLOAT MaxRate);
    void ApproachDirection_be020(FLOAT *Yaw, FLOAT *Pitch, FLOAT Scale, FLOAT MaxRate);
};

// Moves *Value toward zero by Rate*Scale without overshooting.
void __fastcall DecayToZero_bdd60(FLOAT *Value, UnnamedClass_bdd60 *Owner)
{
    if (*Value > Zero_10c109f8)
    {
        FLOAT V = *Value - Owner->Rate354 * Owner->Scale308;
        if (Zero_10c109f8 >= V)
            V = Zero_10c109f8;
        *Value = V;
    }
    else if (*Value < Zero_10c109f8)
    {
        FLOAT V = Owner->Rate354 * Owner->Scale308 + *Value;
        if (Zero_10c109f8 <= V)
            V = Zero_10c109f8;
        *Value = V;
    }
}

extern const FLOAT One_10c109fc;    // 1.0f constant in .rdata
extern "C" double __cdecl asin(double);
extern "C" double __cdecl acos(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(asin, acos, sqrt)

inline FLOAT appSqrt(FLOAT A) { return (FLOAT)sqrt(A); }
inline FLOAT appAsin(FLOAT A) { return (FLOAT)asin(A); }
inline FLOAT appAcos(FLOAT A) { return (FLOAT)acos(A); }

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

inline FLOAT Abs(FLOAT A)
{
    return (A >= Zero_10c109f8) ? A : -A;
}

inline void DecayToZero(FLOAT *Value, FLOAT Step)
{
    if (*Value > Zero_10c109f8)
    {
        FLOAT V = *Value - Step;
        if (Zero_10c109f8 >= V)
            V = Zero_10c109f8;
        *Value = V;
    }
    else if (*Value < Zero_10c109f8)
    {
        FLOAT V = Step + *Value;
        if (Zero_10c109f8 <= V)
            V = Zero_10c109f8;
        *Value = V;
    }
}

// Decays two values toward zero together, splitting the rate by their ratio
// so they reach zero at the same time. LTCG: X in ECX, this in EDX, Y in ESI.
__declspec(noinline) void UnnamedClass_bdd60::DecayPairToZero(FLOAT *X, FLOAT *Y)
{
    FLOAT RateX = Rate354;
    FLOAT RateY = Rate354;
    if (*X != Zero_10c109f8 && *Y != Zero_10c109f8)
    {
        FLOAT Ratio = *X / *Y;
        if (Abs(Ratio) > One_10c109fc)
            RateY = Abs(Rate354 / Ratio);
        else
            RateX = Abs(Ratio * Rate354);
    }
    DecayToZero(X, RateX * Scale308);
    DecayToZero(Y, RateY * Scale308);
}

// Moves *Value toward asin(Dir320.Z)*Scale (the pitch of Dir320), at most MaxRate*Scale308 per call,
// keeping it within [Scale*Min318, Scale*Max31C]. LTCG: this in ESI, Value in EDI.
__declspec(noinline) void UnnamedClass_bdd60::ApproachAsin_bdf40(FLOAT *Value, FLOAT Scale, FLOAT MaxRate)
{
    FLOAT Delta = appAsin(Clamp(Dir320.Z, -1.f, 1.f)) * Scale - *Value;
    MaxRate *= Scale308;
    Delta = Clamp(Delta, -MaxRate, MaxRate);
    MaxRate = Scale * Max31C;
    Scale = Scale * Min318;
    *Value = Clamp(Delta + *Value, Scale, MaxRate);
}

// Callee published elsewhere (RVA 0x50d30); defined here only so the LTCG
// link gives it the retail register convention (result in ECX, this in EDX).
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return FVector(0.f, 0.f, 0.f);
    FLOAT Scale = 1.f / appSqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// Turns *Yaw and *Pitch toward the heading of Dir320 relative to Dir32C, at a
// shared rate split so both arrive together. LTCG: this in ESI, Yaw in EBX,
// Pitch in EDI.
__declspec(noinline) void UnnamedClass_bdd60::ApproachDirection_be020(FLOAT *Yaw, FLOAT *Pitch, FLOAT Scale, FLOAT MaxRate)
{
    FLOAT RateYaw = MaxRate;
    FLOAT RatePitch = MaxRate;
    FLOAT DeltaPitch = appAsin(Clamp(Dir320.Z, -1.f, 1.f)) * Scale - *Pitch;

    FVector Base = Dir32C;
    Base.Z = 0.f;
    Base = Base.SafeNormal();
    FVector Heading = Dir320;
    Heading.Z = 0.f;
    Heading = Heading.SafeNormal();

    FLOAT CosAngle = Clamp(Base | Heading, -1.f, 1.f);
    FLOAT Angle = appAcos(CosAngle);
    if ((Base ^ Heading).Z > Zero_10c109f8)
        Angle = -Angle;
    FLOAT DeltaYaw = Angle * Scale - *Yaw;

    if (DeltaPitch != Zero_10c109f8 && DeltaYaw != Zero_10c109f8)
    {
        FLOAT Ratio = DeltaYaw / DeltaPitch;
        if (Abs(Ratio) > One_10c109fc)
            RatePitch = Abs(MaxRate / Ratio);
        else
            RateYaw = Abs(Ratio * MaxRate);
    }

    MaxRate = RateYaw * Scale308;
    DeltaYaw = Clamp(DeltaYaw, -MaxRate, MaxRate);
    FLOAT YawMax = Scale * Max314;
    FLOAT YawMin = Scale * Min310;
    *Yaw = Clamp(DeltaYaw + *Yaw, YawMin, YawMax);

    MaxRate = RatePitch * Scale308;
    DeltaPitch = Clamp(DeltaPitch, -MaxRate, MaxRate);
    MaxRate = Scale * Max31C;
    Scale = Scale * Min318;
    *Pitch = Clamp(DeltaPitch + *Pitch, Scale, MaxRate);
}

// Scaffolding for the link, not part of the unit.
void Driver_bddd0(FLOAT *X, UnnamedClass_bdd60 *O, FLOAT *Y)
{
    O->DecayPairToZero(X, Y);
    O->DecayPairToZero(Y, X);
}
void Driver_bdf40(UnnamedClass_bdd60 *O)
{
    O->ApproachAsin_bdf40(&O->Values[2], 0.9f, O->Rate350);
    O->ApproachAsin_bdf40(&O->Values[3], 0.7f, O->Rate350);
}
void Driver_be020(UnnamedClass_bdd60 *O)
{
    O->ApproachDirection_be020(&O->Values[0], &O->Values[1], 0.7f, O->Rate350);
    O->ApproachDirection_be020(&O->Values[4], &O->Values[5], 0.9f, O->Rate350);
}
