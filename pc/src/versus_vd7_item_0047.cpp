// Work item w4 0047: Versus RVA 0x12f260 (AActor vtable slot 65).
// Clamps Velocity (+0x8c) to the magnitude of the vector at +0x98 when +0x98
// is non-zero. Link-time code generated because it calls FVector::SafeNormal
// (0x50d30) with its LTCG register convention (result in ecx, this in edx).

typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef int INT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FLOAT Size() const { return (FLOAT)sqrt(X * X + Y * Y + Z * Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    UBOOL IsZero() const { return X == 0.f && Y == 0.f && Z == 0.f; }
    FVector &operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FVector SafeNormal() const; // RVA 0x50d30
};

// Zero vector (retail 0x10ccacc0, read through a pointer).
__declspec(dllimport) extern const FVector GZeroVector;

class AActor
{
public:
    virtual void VirtualSlot65();

    BYTE unk_04[0x7c];
    FVector Location;   // 0x80
    FVector Velocity;   // 0x8c
    FVector unk_98;     // 0x98
};

// RVA 0x12f260 (AActor vtable slot 65)
void AActor::VirtualSlot65()
{
    if (!unk_98.IsZero())
    {
        if (Velocity.SizeSquared() > unk_98.SizeSquared())
        {
            Velocity = Velocity.SafeNormal();
            Velocity *= unk_98.Size();
        }
    }
}

// Callee, defined here so the link gives it its retail register convention.
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_12f260(AActor *A)
{
    void (AActor::*P)() = &AActor::VirtualSlot65;
    Escape(&P);
    A->AActor::VirtualSlot65();
}
