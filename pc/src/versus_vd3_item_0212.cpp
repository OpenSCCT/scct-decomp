// Work item 0212: Versus RVA 0x530c0-0x5345b.
// Core math helpers (UnMath): matrix to quaternion, rotation-unit and float
// constant-rate interpolation, vector constant-rate move, perpendicular axes.

typedef int INT;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
template <class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}
template <class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator^(const FVector &V) const
    {
        return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X);
    }
    FVector &operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
    void FindPerpendicularAxes(FVector &Axis1, FVector &Axis2) const;
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FMatrix
{
    FLOAT M[4][4];
};

struct FQuat
{
    FLOAT X, Y, Z, W;
    void Normalize();  // RVA 0x4f940
};

// RVA 0x530c0 (LTCG: matrix in ECX, result pointer on the stack, caller pops).
FQuat FMatrixToQuat(const FMatrix &M)
{
    FQuat Q;
    FLOAT Trace = M.M[0][0] + M.M[1][1] + M.M[2][2];
    if (Trace > 0.f)
    {
        FLOAT S = appSqrt(Trace + 1.f);
        Q.W = 0.5f * S;
        S = 0.5f / S;
        Q.X = (M.M[1][2] - M.M[2][1]) * S;
        Q.Y = (M.M[2][0] - M.M[0][2]) * S;
        Q.Z = (M.M[0][1] - M.M[1][0]) * S;
    }
    else
    {
        INT Next[3] = { 1, 2, 0 };
        INT i = 0;
        if (M.M[1][1] > M.M[0][0])
            i = 1;
        if (M.M[2][2] > M.M[i][i])
            i = 2;
        INT j = Next[i];
        INT k = Next[j];
        FLOAT *Qt = &Q.X;
        FLOAT S = appSqrt(M.M[i][i] - (M.M[j][j] + M.M[k][k]) + 1.f);
        Qt[i] = 0.5f * S;
        S = 0.5f / S;
        Qt[3] = (M.M[j][k] - M.M[k][j]) * S;
        Qt[j] = (M.M[j][i] + M.M[i][j]) * S;
        Qt[k] = (M.M[k][i] + M.M[i][k]) * S;
    }
    Q.Normalize();
    return Q;
}

// RVA 0x53200 (LTCG: Desired in EDX, Rate and Current on the stack).
// Turns a 16-bit rotation component toward Desired by at most Rate.
INT FixedTurnTo(INT Desired, FLOAT Rate, INT Current)
{
    Current &= 0xFFFF;
    Desired &= 0xFFFF;
    INT Result = 0;
    if (Current == Desired)
        Result = Current;
    if (Current > Desired)
    {
        INT Delta = Current - Desired;
        if (Delta < 0x8000)
        {
            if (Delta > Rate)
                Result = (INT)(Current - Rate);
            else
                Result = Desired;
        }
        else
        {
            if (0x10000 - Delta > Rate)
                Result = (INT)(Current + Rate);
            else
                Result = Desired;
        }
    }
    else if (Desired > Current)
    {
        INT Delta = Desired - Current;
        if (Delta < 0x8000)
        {
            if (Delta > Rate)
                Result = (INT)(Current + Rate);
            else
                Result = Desired;
        }
        else
        {
            if (0x10000 - Delta > Rate)
                Result = (INT)(Current - Rate);
            else
                Result = Desired;
        }
    }
    return Result & 0xFFFF;
}

// RVA 0x532c0: move Current toward Target by at most DeltaTime * Speed.
FLOAT FInterpConstantTo(FLOAT Current, FLOAT Target, FLOAT DeltaTime, FLOAT Speed)
{
    FLOAT MaxStep = DeltaTime * Speed;
    FLOAT Delta = Clamp(Target - Current, -MaxStep, MaxStep);
    return Delta + Current;
}

// RVA 0x53310 (LTCG: Current in ECX, Target in EAX, result pointer in EDX).
FVector VInterpConstantTo(const FVector &Current, const FVector &Target, FLOAT DeltaTime, FLOAT Speed)
{
    FLOAT MaxStep = DeltaTime * Speed;
    FLOAT DX = Target.X - Current.X;
    FLOAT DY = Target.Y - Current.Y;
    FLOAT DZ = Target.Z - Current.Z;
    FLOAT Dist = appSqrt((DX * DX + DZ * DZ) + DY * DY);
    if (Dist > MaxStep)
    {
        FLOAT Scale = MaxStep / Dist;
        DX *= Scale; DY *= Scale; DZ *= Scale;
    }
    return FVector(Current.X + DX, Current.Y + DY, Current.Z + DZ);
}
// RVA 0x53380 (LTCG: this in ECX, Axis1 in EDX, Axis2 in ESI). Near miss:
// the cross product loads two operand pairs in the other order (8 bytes).
// Neutral name: two unit axes perpendicular to this vector.
void FVector::FindPerpendicularAxes(FVector &Axis1, FVector &Axis2) const
{
    if (Abs(X) >= Abs(Y))
    {
        FLOAT Scale = 1.f / appSqrt(X * X + Z * Z);
        Axis1.X = -(Scale * Z);
        Axis1.Y = 0.f;
        Axis1.Z = Scale * X;
    }
    else
    {
        FLOAT Scale = 1.f / appSqrt(Y * Y + Z * Z);
        Axis1.X = 0.f;
        Axis1.Y = Scale * Z;
        Axis1.Z = -(Scale * Y);
    }
    Axis2 = *this ^ Axis1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_530c0(FQuat *Out, const FMatrix *M) { *Out = FMatrixToQuat(*M); }
INT Driver_53200(INT D, FLOAT R, INT C) { return FixedTurnTo(D, R, C); }
void Driver_53310(FVector *Out, const FVector *C, const FVector *T, FLOAT A, FLOAT B) { *Out = VInterpConstantTo(*C, *T, A, B); }
void Driver_53380(const FVector *N, FVector *A, FVector *B) { N->FindPerpendicularAxes(*A, *B); }
