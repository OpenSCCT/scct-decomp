// Work item 0063: Versus RVA 0x136290 (318 bytes).
// Dynamic light sort-key computation for actor lighting (UnRender.cpp / UnLight.cpp).

typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

enum { MAXINT = 0x7fffffff };

template<class T> inline T Square(const T A)
{
    return A * A;
}

inline INT appFloor(FLOAT F)
{
    return (INT)floor(F);
}

inline INT appRound(FLOAT F)
{
    return appFloor(F + 0.5f);
}

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector SafeNormal() const;
};

__declspec(dllimport) extern const FVector GZeroVector;

struct FPlane : public FVector
{
    FLOAT W;

    FPlane() {}
    FPlane(const FVector &V) : FVector(V), W(0.0f) {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}

    FPlane operator-(const FPlane &V) const
    {
        return FPlane(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
    }
};

struct FSphere : public FPlane
{
    FSphere() {}
    FSphere(const FVector &V, FLOAT InW) : FPlane(V.X, V.Y, V.Z, InW) {}
};

enum ELightEffect
{
    LE_None       = 0,
    LE_StaticSpot = 8,
    LE_Spotlight  = 12,
    LE_Sunlight   = 19,
};

class AActor
{
public:
    BYTE unk_000[0xf8];
    FLOAT LightBrightness;          // 0x0f8
    BYTE unk_0fc[0x2d2 - 0x0fc];
    BYTE LightEffect;               // 0x2d2
    BYTE unk_2d3[0x2d7 - 0x2d3];
    BYTE LightCone;                 // 0x2d7
};

struct FDynamicActor;

struct FDynamicLight
{
    AActor *Actor;                  // 0x00
    BYTE unk_04[0x14];
    FVector Position;               // 0x18
    FVector Direction;              // 0x24
    FLOAT Radius;                   // 0x30
    BYTE unk_34[0x04];
    INT SortKey;                    // 0x38
};

// RVA 0x136290: compute dynamic light sort priority against a bounding sphere (neutral name).
void ComputeLightSortKey(FDynamicLight *Light, FDynamicActor *DynamicActor, FSphere BoundingSphere)
{
    AActor *Actor = Light->Actor;

    if (Actor->LightEffect == LE_Sunlight)
    {
        Light->SortKey = MAXINT - 1;
        return;
    }

    if (Actor->LightEffect == LE_Spotlight || Actor->LightEffect == LE_StaticSpot)
    {
        FLOAT Dot = (BoundingSphere - Light->Position).SafeNormal() | Light->Direction;
        if (!(Dot > 0.0f && Dot > Square(1.0f - Actor->LightCone / 256.0f)))
        {
            Light->SortKey = 0;
            return;
        }
    }

    Light->SortKey = appRound(
        (1.0f - (Light->Position - BoundingSphere).SizeSquared() / Square(BoundingSphere.W + Light->Radius))
        * Actor->LightBrightness
        * 1024.0f);
}

// Scaffolding for the LTCG link, not part of the unit.
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

void Driver_136290(FDynamicLight *Light, FDynamicActor *DynamicActor, FSphere BoundingSphere)
{
    ComputeLightSortKey(Light, DynamicActor, BoundingSphere);
}
