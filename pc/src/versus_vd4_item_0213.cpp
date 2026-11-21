// Work item 0213: Versus RVA 0x53930.
// Line segment against capped cylinder: returns whether the segment Start->End
// hits the cylinder (CylStart..CylEnd, Radius) and the first hit time in [0,1].
// Names are neutral guesses; the callee at 0x53460 solves the ray/cylinder
// quadratic and writes up to two hit times.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector SafeNormal() const;
    void FindBestAxisVectors(FVector &Axis1, FVector &Axis2) const;
};

// RVA 0x53460 (LTCG custom convention: Times in EBX, Dir in EDI, Axis in EAX).
// The real body is a ray/cylinder solve; here only enough to keep it out of line.
INT LineCylinderTimes_53460(FLOAT *Times, const FVector &Dir, const FVector &Axis,
                            const FVector &Start, const FVector &CylStart, FLOAT Radius);

// RVA 0x53930
UBOOL SegmentHitsCylinder_53930(const FVector &Start, const FVector &End,
                                const FVector &CylEnd, const FVector &CylStart,
                                FLOAT Radius, FLOAT &Time)
{
    FLOAT Times[3];
    FVector Dir = End - Start;
    FVector Axis = CylEnd - CylStart;
    INT Count = LineCylinderTimes_53460(Times, Dir, Axis, Start, CylStart, Radius);
    Time = 2.0f;
    for (INT i = 0; i < Count; i++)
    {
        if (0.0f <= Times[i] && Times[i] <= 1.0f && Times[i] < Time)
            Time = Times[i];
    }
    return Time < 2.0f;
}

// Scaffolding for the link, not part of the unit.
// Approximations of the retail callees (RVA 0x50d30 FVector::SafeNormal, 0x53380
// FVector::FindBestAxisVectors, 0x53460 the ray/cylinder solve), so LTCG gives
// 0x53460 a register convention like retail's. Only 0x53930 is the match target.
extern FVector GZeroVector;
FVector FVector::SafeNormal() const
{
    FLOAT S = X * X + Y * Y + Z * Z;
    if (S < 1.e-8f) return GZeroVector;
    FLOAT Scale = 1.0f / appSqrt(S);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}
void FVector::FindBestAxisVectors(FVector &Axis1, FVector &Axis2) const
{
    FLOAT NX = X < 0 ? -X : X, NY = Y < 0 ? -Y : Y;
    if (NX < NY) { FLOAT L = 1.0f / appSqrt(Y * Y + Z * Z); Axis1.X = 0; Axis1.Y = Z * L; Axis1.Z = -Y * L; }
    else { FLOAT L = 1.0f / appSqrt(X * X + Z * Z); Axis1.X = -Z * L; Axis1.Y = 0; Axis1.Z = X * L; }
    Axis2 = FVector(Axis1.Z * Y - Axis1.Y * Z, Axis1.X * Z - Axis1.Z * X, Axis1.Y * X - Axis1.X * Y);
}
INT LineCylinderTimes_53460(FLOAT *Times, const FVector &Dir, const FVector &AxisIn,
                            const FVector &Start, const FVector &CylStart, FLOAT Radius)
{
    FVector Axis = AxisIn;
    FLOAT Height = appSqrt(Axis | Axis);
    FVector N = Axis.SafeNormal();
    FVector U, V;
    N.FindBestAxisVectors(V, U);
    FVector D(V | Dir, U | Dir, N | Dir);
    FLOAT LenSq = D | D;
    D = D.SafeNormal();
    FLOAT InvLen = 1.0f / appSqrt(LenSq);
    FVector P = Start - CylStart;
    FVector L(P | V, P | U, P | N);
    FLOAT R2 = Radius * Radius;
    if ((D.Z < 0 ? -D.Z : D.Z) >= 1.0f)
    {
        FLOAT Disc = R2 - L.X * L.X - L.Y * L.Y;
        if (Disc < 0) return 0;
        FLOAT S = appSqrt(Disc);
        Times[0] = -((L.Z + S) * InvLen);
        Times[1] = (Height - L.Z + S) * InvLen;
        return 2;
    }
    FLOAT A = D.X * D.X + D.Y * D.Y;
    FLOAT B = D.X * L.X + D.Y * L.Y;
    FLOAT C = L.X * L.X + L.Y * L.Y - R2;
    FLOAT Disc = B * B - A * C;
    if (Disc < 0) return 0;
    INT Count = 0;
    if (Disc > 0)
    {
        FLOAT S = appSqrt(Disc);
        FLOAT InvA = 1.0f / A;
        FLOAT T = (-B - S) * InvA;
        FLOAT H = T * D.Z + L.Z;
        if (0 <= H && H <= Height) Times[Count++] = T * InvLen;
        T = (S - B) * InvA;
        H = T * D.Z + L.Z;
        if (0 <= H && H <= Height) Times[Count++] = T * InvLen;
        if (Count == 2) return Count;
    }
    else
    {
        FLOAT T = -(B / A);
        FLOAT H = T * D.Z + L.Z;
        if (0 <= H && H <= Height) { Times[0] = T * InvLen; return 1; }
    }
    // Bottom sphere.
    B += L.Z * D.Z;
    C += L.Z * L.Z;
    Disc = B * B - C;
    if (Disc > 0)
    {
        FLOAT S = appSqrt(Disc);
        FLOAT T = -B - S;
        if (D.Z * T + L.Z <= 0) { Times[Count++] = T * InvLen; if (Count == 2) return Count; }
        T = S - B;
        if (D.Z * T + L.Z <= 0) { Times[Count++] = T * InvLen; if (Count == 2) return Count; }
    }
    else if (Disc == 0)
    {
        FLOAT T = -B;
        if (D.Z * T + L.Z <= 0) { Times[Count++] = T * InvLen; if (Count == 2) return Count; }
    }
    // Top sphere.
    B -= D.Z * Height;
    Disc = B * B - ((Height - (L.Z + L.Z)) * Height + C);
    if (Disc > 0)
    {
        FLOAT S = appSqrt(Disc);
        FLOAT T = -B - S;
        if (D.Z * T + L.Z >= Height) { Times[Count++] = T * InvLen; if (Count == 2) return Count; }
        T = S - B;
        if (D.Z * T + L.Z >= Height) { Times[Count++] = T * InvLen; if (Count == 2) return Count; }
    }
    else if (Disc == 0)
    {
        FLOAT T = -B;
        if (D.Z * T + L.Z >= Height) { Times[Count++] = T * InvLen; if (Count == 2) return Count; }
    }
    return Count;
}
void Escape(void *);
INT Driver_53930(const FVector &Start, const FVector &End, const FVector &CylEnd,
                 const FVector &CylStart, FLOAT Radius, FLOAT *Out)
{
    FLOAT T;
    if (SegmentHitsCylinder_53930(Start, End, CylEnd, CylStart, Radius, T))
    {
        *Out = T;
        return 1;
    }
    return 0;
}
