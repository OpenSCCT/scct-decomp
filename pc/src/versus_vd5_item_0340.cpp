// UPrimitive::PointCheck (retail 0x10f150): cylinder point check against the
// owner's collision cylinder. Slot 22 of the UPrimitive vtable.
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef int INT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const;  // 0x405d0
    FVector operator*(const FVector &V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    friend FVector operator*(FLOAT Scale, const FVector &V);  // 0x40570
    FVector SafeNormal() const; // 0x50d30; LTCG passes the result in ecx, this in edx
};


template <class T> inline T Square(const T A) { return A * A; }

class AActor
{
public:
    char Pad0[0x80];
    FVector Location;               // 0x80
    char Pad8C[0x268 - 0x8C];
    FLOAT CollisionRadius;          // 0x268
    FLOAT CollisionHeight;          // 0x26c
};

struct FCheckResult
{
    FCheckResult *Next;             // 0x00
    AActor *Actor;                  // 0x04
    FVector Location;               // 0x08
    FVector Normal;                 // 0x14
};

class UPrimitive
{
public:
    virtual UBOOL PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Point, const FVector &Extent, DWORD ExtraNodeFlags);
};

UBOOL UPrimitive::PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Point, const FVector &Extent, DWORD ExtraNodeFlags)
{
    if (Owner
        && Square(Owner->Location.Z - Point.Z) < Square(Owner->CollisionHeight + Extent.Z)
        && Square(Owner->Location.X - Point.X) + Square(Owner->Location.Y - Point.Y) < Square(Owner->CollisionRadius + Extent.X))
    {
        Result.Actor = Owner;
        const FVector &Location = Owner->Location;
        Result.Normal = FVector(Point.X - Location.X, Point.Y - Location.Y, Point.Z - Location.Z).SafeNormal();
        if (Result.Normal.Z < -0.5)
            Result.Location = FVector(Point.X, Point.Y, Owner->Location.Z - Extent.Z);
        else if (Result.Normal.Z > 0.5)
            Result.Location = FVector(Point.X, Point.Y, Owner->Location.Z - Extent.Z);
        else
            Result.Location = (Location - Extent.X * (Result.Normal * FVector(1, 1, 0)).SafeNormal()) + FVector(0, 0, Point.Z);
        return 0;
    }
    return 1;
}

// Scaffolding for the link, not part of the unit: retail reaches PointCheck
// through the vtable, so call it virtually.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_10f150(void *Mem, FCheckResult *R, AActor *A, FVector *L, FVector *E)
{
    UPrimitive *P = new (Mem) UPrimitive;
    Escape(P);
    P->PointCheck(*R, A, *L, *E, 0);
}

// FVector::SafeNormal (retail 0x50d30), reproduced here only so the link
// sees its definition and gives it the same register convention as retail.
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return FVector(0.f, 0.f, 0.f);
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}
