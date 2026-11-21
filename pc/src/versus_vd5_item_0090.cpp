// Work item 0090: two AVolume virtuals (vtable slots 40 and 41, shared by
// ABlockingVolume and ASDamageVolume) that build a coordinate system from the
// actor's Location (0x80), -PrePivot (0xbc) and Rotation (0xe0).
// LTCG unit. Names: the UE2 method names are not recovered, so the methods
// are named after their RVAs; field names follow UE2 AActor (Location,
// PrePivot, Rotation) by layout.

typedef unsigned char BYTE;
typedef float FLOAT;
typedef int INT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector &operator+=(const FVector &V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }
    FVector &operator-=(const FVector &V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
};
struct FRotator { INT Pitch, Yaw, Roll; };

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FCoords &C) : Origin(C.Origin), XAxis(C.XAxis), YAxis(C.YAxis), ZAxis(C.ZAxis) {}
    FCoords &operator*=(const FVector &Point) { Origin -= Point; return *this; }
    FCoords &operator/=(const FVector &Point) { Origin += Point; return *this; }
    FCoords &operator/=(const FRotator &R);             // retail 0x10940d90
    FCoords operator*(const FVector &Point) const;      // retail 0x109862a0
    FCoords operator/(const FVector &Point) const;      // retail 0x1097c470
    FCoords operator*(const FRotator &R) const;         // retail 0x109411a0
    FCoords operator/(const FRotator &R) const;         // retail 0x10940f40
};

struct FGlobalMath
{
    FCoords UnitCoords;
};
extern FGlobalMath GMath;

class AVolume
{
public:
    BYTE     Pad000[0x80];
    FVector  Location;                  // 0x80
    BYTE     Pad08C[0xbc - 0x8c];
    FVector  PrePivot;                  // 0xbc
    BYTE     Pad0C8[0xe0 - 0xc8];
    FRotator Rotation;                  // 0xe0

    FCoords Coords_ac630() const;       // vtable slot 40
    FCoords Coords_ac6a0() const;       // vtable slot 41
};

// RVA 0xac630
FCoords AVolume::Coords_ac630() const
{
    return GMath.UnitCoords / -PrePivot * Rotation / Location;
}

// RVA 0xac6a0
FCoords AVolume::Coords_ac6a0() const
{
    return GMath.UnitCoords * Location / Rotation * -PrePivot;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: stand-in bodies for the
// retail callees so the linker gives them retail's register conventions,
// and drivers calling the functions the way retail callers do.

struct FUnnamedSinCos { void SinCos(INT Angle, FLOAT *C, FLOAT *S); };
extern FUnnamedSinCos GUnnamedSinCos;
void UnnamedTransform(FCoords *C, FLOAT A, FLOAT B, INT Axis);

__declspec(noinline) FCoords &FCoords::operator/=(const FRotator &R)
{
    FLOAT S, C;
    GUnnamedSinCos.SinCos(R.Yaw, &C, &S);
    UnnamedTransform(this, C, S, 2);
    GUnnamedSinCos.SinCos(R.Pitch, &C, &S);
    UnnamedTransform(this, C, S, 1);
    GUnnamedSinCos.SinCos(R.Roll, &C, &S);
    UnnamedTransform(this, C, S, 0);
    return *this;
}
__declspec(noinline) FCoords FCoords::operator/(const FRotator &R) const { return FCoords(*this) /= R; }
inline FCoords FCoords::operator*(const FVector &Point) const { return FCoords(*this) *= Point; }
inline FCoords FCoords::operator/(const FVector &Point) const { return FCoords(*this) /= Point; }

void Escape(void *);
template <class T> void EscapeMember(T M) { Escape(*(void **)&M); }
void Driver_ac630()
{
    Escape(&GMath);
    EscapeMember((FCoords (FCoords::*)(const FRotator &) const)&FCoords::operator*);
    EscapeMember(&AVolume::Coords_ac630);
    EscapeMember(&AVolume::Coords_ac6a0);
}
