// Work item 0339: UPrimitive bounding virtuals (Engine, 0x10ef10-0x10f115).
// Slot names follow Unreal Engine 2 UPrimitive (GetRenderBoundingBox,
// GetRenderBoundingSphere, GetCollisionBoundingBox, GetCollisionExtent);
// the slot-to-name mapping is inferred from the vtable order and the bodies.
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator-() const { return FVector(-X, -Y, -Z); }
};

struct FPlane : public FVector {
    FLOAT W;
    FPlane() {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FSphere : public FPlane {
    FSphere() {}
    FSphere(const FVector &V, FLOAT InW) : FPlane(V, InW) {}
};

// Two-vector box (24 bytes; Versus copies it as six dwords).
struct FBox {
    FVector Min, Max;
    FBox() {}
    FBox(const FVector &A, const FVector &B);          // 0x81ad0, not part of this item
    FBox &operator+=(const FVector &Other);            // 0x4f820
};

class AActor {
public:
    BYTE Pad00[0x80];
    FVector Location;          // 0x80
    BYTE Pad8c[0x268 - 0x8c];
    FLOAT CollisionRadius;     // 0x268
    FLOAT CollisionHeight;     // 0x26c
};

class UPrimitive {
public:
    virtual ~UPrimitive();
    BYTE Pad04[0x28 - 0x04];
    FBox BoundingBox;          // 0x28
    FSphere BoundingSphere;    // 0x40

    FBox GetRenderBoundingBox(const AActor *Owner);       // slot 24
    FSphere GetRenderBoundingSphere(const AActor *Owner); // slot 25
    FBox GetCollisionBoundingBox(const AActor *Owner);    // slot 26
    FVector GetCollisionExtent(const AActor *Owner);      // slot 28
};

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// Constant vectors read through pointers (imported data, as in item 0307).
__declspec(dllimport) extern const FVector GMath_Zero;   // 0x10ccacc0
__declspec(dllimport) extern const FVector GMath_UnitX;  // 0x10ccacc4

// RVA 0x10ef10
FBox UPrimitive::GetCollisionBoundingBox(const AActor *Owner)
{
    if (Owner) {
        FVector Extent(Owner->CollisionRadius + 1.f, Owner->CollisionRadius + 1.f, Owner->CollisionHeight + 1.f);
        return FBox(Owner->Location - Extent, Owner->Location + Extent);
    }
    return BoundingBox;
}

// RVA 0x10efe0
FBox UPrimitive::GetRenderBoundingBox(const AActor *Owner)
{
    if (Owner) {
        FVector Extent(Owner->CollisionRadius + 1.f, Owner->CollisionRadius + 1.f, Owner->CollisionHeight + 1.f);
        return FBox(-Extent, Extent);
    }
    return BoundingBox;
}

// RVA 0x10f080
FSphere UPrimitive::GetRenderBoundingSphere(const AActor *Owner)
{
    if (Owner) {
        FLOAT R = Owner->CollisionRadius;
        FLOAT H = Owner->CollisionHeight;
        return FSphere(GMath_Zero, appSqrt(R * R + H * H));
    }
    return BoundingSphere;
}

// RVA 0x10f0f0
FVector UPrimitive::GetCollisionExtent(const AActor *Owner)
{
    return FVector(Owner->CollisionRadius, Owner->CollisionRadius, Owner->CollisionHeight);
}

// RVA 0x4f820 (item 0201) and 0x81ad0 (item 0307), copied so the LTCG link
// gives them their retail register conventions; not part of this item.
__declspec(noinline) FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, Other.X); Min.Y = ::Min(Min.Y, Other.Y); Min.Z = ::Min(Min.Z, Other.Z);
        Max.X = ::Max(Max.X, Other.X); Max.Y = ::Max(Max.Y, Other.Y); Max.Z = ::Max(Max.Z, Other.Z);
    }
    else
    {
        Min = Max = Other;
    }
    return *this;
}

__declspec(noinline) FBox::FBox(const FVector &InMin, const FVector &InMax)
    : Min(InMin), Max(InMax)
{
    Min = GMath_UnitX;
    Max = GMath_Zero;
    *this += InMin;
    *this += InMax;
}

// Scaffolding for the LTCG link, not part of the unit. Retail reaches these
// through the vtable, so the drivers only take their addresses, which keeps
// the standard thiscall convention.
void Escape(void *);
void Driver_10ef10() { Escape((void *)&GMath_Zero); Escape((void *)&GMath_UnitX); FBox (UPrimitive::*F)(const AActor *) = &UPrimitive::GetCollisionBoundingBox; Escape(&F); }
void Driver_10efe0() { Escape((void *)&GMath_Zero); Escape((void *)&GMath_UnitX); FBox (UPrimitive::*F)(const AActor *) = &UPrimitive::GetRenderBoundingBox; Escape(&F); }
void Driver_10f080() { Escape((void *)&GMath_Zero); FSphere (UPrimitive::*F)(const AActor *) = &UPrimitive::GetRenderBoundingSphere; Escape(&F); }
