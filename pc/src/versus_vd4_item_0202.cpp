// Work item 0202: Versus RVA 0x4f940-0x4ff34.
// Core math (UnMath.h): FQuat::Normalize, AlignFQuatWith, SlerpQuat,
// FMatrix plane constructor, FMatrix::operator*= and FMatrix::TransformFPlane.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

FLOAT appAcos(FLOAT A);   // RVA 0x40290
FLOAT appSin(FLOAT A);    // RVA 0x402a0

inline FLOAT appSqrt(FLOAT A) { return (FLOAT)sqrt(A); }
inline FLOAT Square(FLOAT A) { return A * A; }

#define DELTA (0.00001f)

struct FPlane
{
    FLOAT X, Y, Z, W;
    FPlane() {}
    FPlane(const FPlane &P) : X(P.X), Y(P.Y), Z(P.Z), W(P.W) {}
};

struct FQuat
{
    FLOAT X, Y, Z, W;
    FQuat() {}
    UBOOL Normalize();
};

// RVA 0x4f940
UBOOL FQuat::Normalize()
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z + W * W;
    if (SquareSum >= DELTA)
    {
        FLOAT Scale = 1.0f / appSqrt(SquareSum);
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
        W *= Scale;
        return 1;
    }
    else
    {
        X = 0.0f;
        Y = 0.0f;
        Z = 0.1f;
        W = 0.0f;
        return 0;
    }
}

// RVA 0x4f9c0 (LTCG: Quat1 in ECX, Quat2 in EAX).
void AlignFQuatWith(FQuat &Quat1, const FQuat &Quat2)
{
    FLOAT Minus = Square(Quat1.X - Quat2.X) + Square(Quat1.Y - Quat2.Y) + Square(Quat1.Z - Quat2.Z) + Square(Quat1.W - Quat2.W);
    FLOAT Plus = Square(Quat1.X + Quat2.X) + Square(Quat1.Y + Quat2.Y) + Square(Quat1.Z + Quat2.Z) + Square(Quat1.W + Quat2.W);
    if (Minus > Plus)
    {
        Quat1.X = -Quat1.X;
        Quat1.Y = -Quat1.Y;
        Quat1.Z = -Quat1.Z;
        Quat1.W = -Quat1.W;
    }
}

// RVA 0x4fa70 (built without optimisation in retail; the lower-case UnMath.h
// local names matter, since the unoptimised frame layout follows them).
#pragma optimize("", off)
FQuat SlerpQuat(const FQuat &quat1, const FQuat &quat2, FLOAT slerp)
{
    FQuat result;
    FLOAT omega, cosom, sininv, scale0, scale1;

    cosom = quat1.X * quat2.X + quat1.Y * quat2.Y + quat1.Z * quat2.Z + quat1.W * quat2.W;
    if (cosom < 0.99999999f)
    {
        omega = appAcos(cosom);
        sininv = 1.f / appSin(omega);
        scale0 = appSin((1.f - slerp) * omega) * sininv;
        scale1 = appSin(slerp * omega) * sininv;

        result.X = scale0 * quat1.X + scale1 * quat2.X;
        result.Y = scale0 * quat1.Y + scale1 * quat2.Y;
        result.Z = scale0 * quat1.Z + scale1 * quat2.Z;
        result.W = scale0 * quat1.W + scale1 * quat2.W;
        return result;
    }
    else
    {
        return quat1;
    }
}

#pragma optimize("", on)

struct FMatrix
{
    union
    {
        struct { FPlane XPlane, YPlane, ZPlane, WPlane; };
        FLOAT M[4][4];
    };
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    void operator*=(const FMatrix &Other);
    FPlane TransformFPlane(const FPlane &P) const;
};

// RVA 0x4fbc0 (LTCG: this in EAX, InZ in EDX, InW in ECX, InX and InY on the stack).
FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}

// RVA 0x4fc30 (LTCG: this in ECX, Other in EAX).
void FMatrix::operator*=(const FMatrix &Other)
{
    FMatrix Result;
    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];

    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];

    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];

    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
    *this = Result;
}

// RVA 0x4fe60: not matched. Retail is the hand-scheduled x87 inline-assembly
// block of UnMath.h (P reloaded for every product, fxch/faddp st(7) chains,
// this spilled for "mov edx, this"); this is the C fallback path.
FPlane FMatrix::TransformFPlane(const FPlane &P) const
{
    FPlane Result;
    Result.X = P.X * M[0][0] + P.Y * M[1][0] + P.Z * M[2][0] + P.W * M[3][0];
    Result.Y = P.X * M[0][1] + P.Y * M[1][1] + P.Z * M[2][1] + P.W * M[3][1];
    Result.Z = P.X * M[0][2] + P.Y * M[1][2] + P.Z * M[2][2] + P.W * M[3][2];
    Result.W = P.X * M[0][3] + P.Y * M[1][3] + P.Z * M[2][3] + P.W * M[3][3];
    return Result;
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_4f9c0(FQuat *A, const FQuat *B) { AlignFQuatWith(*A, *B); AlignFQuatWith(A[1], B[1]); }
void Driver_4fa70(FQuat *Out, const FQuat *A, const FQuat *B, FLOAT S) { *Out = SlerpQuat(*A, *B, S); }
void Driver_4fbc0(FMatrix *Out, const FPlane *P)
{
    for (INT i = 0; i < 8; i++)
    {
        new (&Out[i * 4 + 0]) FMatrix(P[0], P[1], P[2], P[3]);
        new (&Out[i * 4 + 1]) FMatrix(P[4], P[5], P[6], P[7]);
        new (&Out[i * 4 + 2]) FMatrix(P[8], P[9], P[10], P[11]);
        new (&Out[i * 4 + 3]) FMatrix(P[12], P[13], P[14], P[15]);
    }
}
void Driver_4fc30(FMatrix *A, const FMatrix *B) { *A *= *B; A[1] *= B[1]; }
