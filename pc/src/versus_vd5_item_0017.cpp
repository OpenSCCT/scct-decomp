// Work item w3 0017: Versus RVA 0x52df0.
// Core math: builds a unit quaternion from an FRotator (Pitch/Yaw/Roll in
// 65536-unit angles). The name RotatorToQuat is neutral; the retail symbol is
// not known. The sine of each half angle is recovered from its cosine with the
// sign taken from the angle wrapped into (-2PI, 2PI). LTCG link: rotator in
// ESI, hidden return pointer in EDI.

typedef int INT;
typedef float FLOAT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, cos, fabs)

#define PI 3.1415926535897932f

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT appCos(FLOAT F) { return (FLOAT)cos(F); }
inline INT appTrunc(FLOAT F) { return (INT)F; } // _ftol at 0x10b83aa0
inline FLOAT Abs(FLOAT A) { return (FLOAT)fabs(A); }

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FQuat
{
    FLOAT X, Y, Z, W;
    UBOOL Normalize(); // RVA 0x4f940
};

// Sine and cosine of an angle in radians; the sine comes from the cosine.
__forceinline void HalfAngleSinCos(INT Angle, FLOAT &S, FLOAT &C)
{
    FLOAT A = Angle * (PI / 65536.f);
    FLOAT Wrapped = A - appTrunc(A * (1.f / (2.f * PI))) * (2.f * PI);
    C = appCos(A);
    FLOAT Sign;
    if (Abs(Wrapped) < PI)
        Sign = Wrapped < 0.f ? -1.f : (Wrapped > 0.f ? 1.f : 0.f);
    else
        Sign = -(Wrapped < 0.f ? -1.f : (Wrapped > 0.f ? 1.f : 0.f));
    S = appSqrt(1.f - C * C) * Sign;
}

FQuat RotatorToQuat(const FRotator &R)
{
    FLOAT SY, CY, SP, CP, SR, CR;
    HalfAngleSinCos(R.Yaw, SY, CY);
    HalfAngleSinCos(R.Pitch, SP, CP);
    HalfAngleSinCos(R.Roll, SR, CR);

    FQuat Q;
    Q.X = CY * (CR * SP) + (SR * CP) * SY;
    Q.Y = (CR * CP) * SY - (SR * SP) * CY;
    Q.Z = (SR * CP) * CY - (CR * SP) * SY;
    Q.W = (CR * CP) * CY + (SR * SP) * SY;
    Q.Normalize();
    return Q;
}

// Scaffolding for the link, not part of the unit.
void Driver_52df0(FQuat *Out, const FRotator *R) { *Out = RotatorToQuat(*R); }
