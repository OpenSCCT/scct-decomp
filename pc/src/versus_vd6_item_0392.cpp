// Work item 0392: Versus RVA 0x11e460-0x11e8bb.
// FDynamicLight::SampleIntensity (0x11e4f0) and its radial attenuation helper (0x11e460),
// plus fast table-driven inverse-sqrt (0x11e860) and sqrt (0x11e890) helpers.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef double DOUBLE;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT Abs(FLOAT A) { return (FLOAT)fabs(A); }

template<class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

template<class T> inline T Square(const T A)
{
    return A * A;
}

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
};

enum ELightEffect
{
    LE_None                  = 0,
    LE_StaticSpot            = 8,
    LE_Spotlight             = 12,
    LE_NonIncidence          = 13,
    LE_Cylinder              = 17,
    LE_Sunlight              = 19,
    LE_QuadraticNonIncidence = 20,
};

class AActor
{
public:
    BYTE unk_000[0x2d2];
    BYTE LightEffect;
    BYTE unk_2d3[0x4];
    BYTE LightCone;
};

struct FDynamicLight
{
    AActor *Actor;
    BYTE unk_04[0x14];
    FVector Position;
    FVector Direction;
    FLOAT Radius;

    FLOAT SampleIntensity(FVector Position, FVector Normal);
};

// RVA 0x11e460: radial attenuation helper called by FDynamicLight::SampleIntensity.
FLOAT RadialAttenuation(
    const FVector &LightDirection,
    const FVector &Normal,
    FLOAT Distance,
    FLOAT Radius)
{
    FLOAT Dot = LightDirection | Normal;
    if (Dot > 0.0f && Distance <= Radius)
    {
        FLOAT InvRadius = 1.0f / Radius;
        FLOAT A = Distance * InvRadius;
        FLOAT A2 = A * A;
        return 2.0f * Abs(InvRadius * Dot) * ((2.0f * A2 * A - 3.0f * A2 + 1.0f) / A);
    }
    return 0.0f;
}

// RVA 0x11e4f0: FDynamicLight::SampleIntensity
FLOAT FDynamicLight::SampleIntensity(FVector InPosition, FVector InNormal)
{
    if (Actor->LightEffect == LE_Sunlight)
    {
        if ((InNormal | Direction) < 0.0f)
            return -2.0f * (InNormal | Direction);
        else
            return 0.0f;
    }
    else if (Actor->LightEffect == LE_Cylinder)
    {
        FVector LightDirection = Position - InPosition;
        if (LightDirection.Size() < Radius)
            return 2.0f * Max(
                0.0f,
                1.0f - (Square(LightDirection.X) + Square(LightDirection.Y)) / Square(Radius));
        else
            return 0.0f;
    }
    else if (Actor->LightEffect == LE_NonIncidence)
    {
        FVector LightDirection = Position - InPosition;
        FLOAT Distance = LightDirection.Size();
        if ((LightDirection | InNormal) > 0.0f && Distance < Radius)
            return 2.0f * appSqrt(1.02f - Distance / Radius);
        else
            return 0.0f;
    }
    else if (Actor->LightEffect == LE_QuadraticNonIncidence)
    {
        FVector LightDirection = Position - InPosition;
        FLOAT DistanceSquared = LightDirection.SizeSquared();
        FLOAT RadiusSquared = Square(Radius);
        if ((LightDirection | InNormal) > 0.0f && DistanceSquared < RadiusSquared)
            return 2.0f * (1.02f - DistanceSquared / RadiusSquared);
        else
            return 0.0f;
    }
    else if (Actor->LightEffect == LE_Spotlight || Actor->LightEffect == LE_StaticSpot)
    {
        FVector LightDirection = Position - InPosition;
        FLOAT DistanceSquared = LightDirection.SizeSquared();
        FLOAT Distance = appSqrt(DistanceSquared);
        FLOAT Intensity = RadialAttenuation(LightDirection, InNormal, Distance, Radius);
        if (Intensity > 0.0f)
        {
            FLOAT Cone = (FLOAT)(1.0 - Actor->LightCone / 256.0);
            FLOAT ConeScale = (FLOAT)(1.0 / (1.0 - Cone));
            FLOAT SpotDot = (-LightDirection) | Direction;
            if (SpotDot > 0.0 && Square(SpotDot) > Square(Cone) * DistanceSquared)
            {
                return Square((SpotDot / Distance) * ConeScale - ConeScale * Cone) * Intensity;
            }
        }
        return 0.0f;
    }
    else
    {
        FVector LightDirection = Position - InPosition;
        return RadialAttenuation(
            LightDirection, InNormal, appSqrt(LightDirection.SizeSquared()), Radius);
    }
}

// Fast math lookup tables (BSS, initialized by FUN_10a1e8c0 / FUN_10a1e9f0).
extern FLOAT GFastInvSqrtExpTable[512];
extern FLOAT GFastInvSqrtMantTable[1024];
extern DWORD GFastSqrtTable[2048];

// RVA 0x11e860: fast table-based inverse square root.
// Original used inline __asm with ebx and an fstp/fld parameter-slot round-trip.
FLOAT FastInvSqrt(FLOAT Value)
{
    DWORD Bits = *(DWORD *)&Value;
    return GFastInvSqrtMantTable[(Bits >> 13) & 0x3ff] * GFastInvSqrtExpTable[Bits >> 23];
}

// RVA 0x11e890: fast table-based square root (original used inline __asm with ebx).
FLOAT FastSqrt(FLOAT Value)
{
    DWORD Bits = *(DWORD *)&Value;
    DWORD ResultBits = GFastSqrtTable[(Bits >> 13) & 0x7ff] + ((Bits & 0x7f000000) >> 1);
    return *(FLOAT *)&ResultBits;
}

// Scaffolding for the LTCG link, not part of the unit.
FLOAT Driver_11e4f0(FDynamicLight *Light, FVector Pos, FVector Norm)
{
    return Light->SampleIntensity(Pos, Norm);
}
