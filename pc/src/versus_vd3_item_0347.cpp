// Work item 0347: Versus RVA 0x97eb0-0x981e6.
// UTexPanner::GetMatrix, UTexFriendlyPanner::GetMatrix and
// UTexScaler::GetMatrix (vtable slot 35 of each class). The unit was compiled
// with /GL and linked with /LTCG: the FMatrix constructor uses the LTCG
// register convention (this in EAX, InZ in EDX, InW in ECX, InX/InY pushed).
typedef int INT;
typedef float FLOAT;
typedef unsigned char BYTE;

extern "C" __declspec(dllimport) double floor(double);

inline INT appTrunc(FLOAT F) { return (INT)F; }
inline INT appFloor(FLOAT F) { return appTrunc((FLOAT)floor(F)); }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};
struct FRotator
{
    INT Pitch, Yaw, Roll;
    FVector Vector() const;
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
};

struct FMatrix
{
    FPlane XPlane, YPlane, ZPlane, WPlane;
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
};

// RVA 0x4fbc0 (item 0202), copied so LTCG gives it its retail convention.
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}

struct FCoords
{
    FVector Origin, XAxis, YAxis, ZAxis;
    FCoords operator/(const FRotator &Rot) const;   // RVA 0x411a0
};

// The coordinate system passed to FCoords::operator/ lives at 0x10ccac00,
// the start of GMath in this build.
struct FGlobalMath
{
    FCoords UnitCoords;
};
extern FGlobalMath GMath;

inline FVector FRotator::Vector() const { return (GMath.UnitCoords / *this).XAxis; }

class UMaterial
{
public:
    // Slots 0-25 are not needed here.
    virtual void VSlot00(); virtual void VSlot01(); virtual void VSlot02(); virtual void VSlot03();
    virtual void VSlot04(); virtual void VSlot05(); virtual void VSlot06(); virtual void VSlot07();
    virtual void VSlot08(); virtual void VSlot09(); virtual void VSlot10(); virtual void VSlot11();
    virtual void VSlot12(); virtual void VSlot13(); virtual void VSlot14(); virtual void VSlot15();
    virtual void VSlot16(); virtual void VSlot17(); virtual void VSlot18(); virtual void VSlot19();
    virtual void VSlot20(); virtual void VSlot21(); virtual void VSlot22(); virtual void VSlot23();
    virtual void VSlot24(); virtual void VSlot25();
    virtual INT MaterialUSize();   // slot 26 (+0x68)
    virtual INT MaterialVSize();   // slot 27 (+0x6c)
    BYTE Pad_04[0x54];
};

class UTexModifier : public UMaterial
{
public:
    virtual FMatrix *GetMatrix(FLOAT TimeSeconds);
};

// UTexPanner: PanDirection +0x58, PanRate +0x64, M +0x68.
class UTexPanner : public UTexModifier
{
public:
    FRotator PanDirection;
    FLOAT PanRate;
    FMatrix M;
    virtual FMatrix *GetMatrix(FLOAT TimeSeconds);
};

// RVA 0x97eb0. Near miss: the instruction stream matches, but VC7.0 gives the
// FCoords temporary its own 0x30-byte slot (frame 0xbc) where retail shares it
// with the plane and matrix temporaries (frame 0x8c), so stack offsets differ.
FMatrix *UTexPanner::GetMatrix(FLOAT TimeSeconds)
{
    FVector D = PanDirection.Vector();
    FLOAT Rate = TimeSeconds * PanRate;
    FLOAT du = D.X * Rate;
    FLOAT dv = D.Y * Rate;
    du -= appFloor(du);
    dv -= appFloor(dv);
    M = FMatrix(
        FPlane(1, 0, 0, 0),
        FPlane(0, 1, 0, 0),
        FPlane(du, dv, 1, 0),
        FPlane(0, 0, 0, 1));
    return &M;
}

// UTexFriendlyPanner (SCCT class): field names are neutral guesses.
// Scale U +0x58, scale V +0x5c, pan U +0x60, pan V +0x64, rate +0x68, M +0x6c.
class UTexFriendlyPanner : public UTexModifier
{
public:
    FLOAT UScale, VScale;
    FLOAT UPan, VPan;
    FLOAT PanRate;
    FMatrix M;
    virtual FMatrix *GetMatrix(FLOAT TimeSeconds);
};

// RVA 0x97fe0
FMatrix *UTexFriendlyPanner::GetMatrix(FLOAT TimeSeconds)
{
    FLOAT T = TimeSeconds * PanRate;
    FLOAT du = T * UPan;
    FLOAT dv = T * VPan;
    du -= appFloor(du);
    dv -= appFloor(dv);
    M = FMatrix(
        FPlane(UScale, 0, 0, 0),
        FPlane(0, VScale, 0, 0),
        FPlane(du, dv, 1, 0),
        FPlane(0, 0, 0, 1));
    return &M;
}

// UTexScaler: M +0x58, UScale +0x98, VScale +0x9c, UOffset +0xa0, VOffset +0xa4.
class UTexScaler : public UTexModifier
{
public:
    FMatrix M;
    FLOAT UScale, VScale, UOffset, VOffset;
    virtual FMatrix *GetMatrix(FLOAT TimeSeconds);
};

// RVA 0x980f0
FMatrix *UTexScaler::GetMatrix(FLOAT TimeSeconds)
{
    M = FMatrix(
        FPlane(1.f / UScale, 0, 0, 0),
        FPlane(0, 1.f / VScale, 0, 0),
        FPlane(UOffset / MaterialUSize(), VOffset / MaterialVSize(), 1, 0),
        FPlane(0, 0, 0, 1));
    return &M;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_97eb0(UTexPanner *P, FLOAT T) { Escape(&GMath); P->UTexPanner::GetMatrix(T); }
void Driver_97fe0(UTexFriendlyPanner *P, FLOAT T) { P->UTexFriendlyPanner::GetMatrix(T); }
void Driver_980f0(UTexScaler *P, FLOAT T) { P->UTexScaler::GetMatrix(T); }
