// ESB (soft-body) particle helpers and FVector/FBox inlines that were emitted
// out of line in the ESB unit (0x9dee0-0x9e1e3). The particle layout matches
// FESBParticle from item_0354; member names past Location are neutral guesses.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

extern const FLOAT SMALL_NUMBER_Value; // 0x10c10b64
extern const FLOAT One_Value;          // 0x10c109fc

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    FArchive &ByteOrderSerialize(void *V, INT Length) { Serialize(V, Length); return *this; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { return Ar.ByteOrderSerialize(&F, sizeof(F)); }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { return Ar.ByteOrderSerialize(&D, sizeof(D)); }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }

    // 0x9dfd0
    UBOOL operator==(const FVector &V) const;
    // 0x9e000
    FVector &Normalize(FLOAT Scale);
    // 0x9e130
    FVector BoundToCube(FLOAT Radius) const;

    friend FArchive &operator<<(FArchive &Ar, FVector &V)
    {
        return Ar << V.X << V.Y << V.Z;
    }
};

extern FVector *GZeroVector; // 0x10ccacc0, pointer to a zero vector

struct FBox
{
    FVector Min, Max;
    // 0x9e0f0
    FVector GetExtent() const;
};

struct FESBParticle // 0x48 bytes
{
    DWORD Flags;          // 0x00 bit 0: fixed
    FVector Location;     // 0x04
    FVector OldLocation;  // 0x10
    FVector Force;        // 0x1c
    FVector Velocity;     // 0x28
    FVector Accel;        // 0x34
    FLOAT InvMass;        // 0x40
    FLOAT Damping;        // 0x44

    // 0x9e060
    FESBParticle(DWORD InFlags, const FVector &InLocation, FLOAT InInvMass, FLOAT InDamping);

    // 0x9dee0
    friend FArchive &operator<<(FArchive &Ar, FESBParticle &P);
};

FArchive &operator<<(FArchive &Ar, FESBParticle &P)
{
    return Ar << P.Flags << P.Location << P.OldLocation << P.Force << P.Velocity
              << P.Accel << P.InvMass << P.Damping;
}

UBOOL FVector::operator==(const FVector &V) const
{
    return X == V.X && Y == V.Y && Z == V.Z;
}

FVector &FVector::Normalize(FLOAT Scale)
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum >= SMALL_NUMBER_Value)
    {
        Scale *= One_Value / appSqrt(SquareSum);
        X *= Scale; Y *= Scale; Z *= Scale;
    }
    return *this;
}

FESBParticle::FESBParticle(DWORD InFlags, const FVector &InLocation, FLOAT InInvMass, FLOAT InDamping)
    : Flags(InFlags), Location(InLocation), OldLocation(InLocation),
      InvMass(InInvMass), Damping(InDamping)
{
    Accel = *GZeroVector;
    Velocity = *GZeroVector;
    Force = *GZeroVector;
}

FVector FBox::GetExtent() const
{
    return (Max - Min) * 0.5f;
}

FVector FVector::BoundToCube(FLOAT Radius) const
{
    return FVector(Clamp(X, -Radius, Radius), Clamp(Y, -Radius, Radius), Clamp(Z, -Radius, Radius));
}

// Scaffolding for the link, not part of the unit. 0x9dfd0 and 0x9e0f0 are
// out-of-line (non-inline) definitions; link them with /Ob1 so the drivers
// call them instead of inlining them.
inline void *operator new(unsigned int, void *P) { return P; }
void Escape(void *);
void Driver_9dee0(FArchive &Ar, FESBParticle &P) { Ar << P; }
INT Driver_9dfd0(FVector *A, FVector *B) { return *A == *B; }
void Driver_9e060(FESBParticle *P, DWORD F, FVector *L, FLOAT a, FLOAT b) { Escape(&GZeroVector); new (P) FESBParticle(F, *L, a, b); }
void Driver_9e0f0(FBox *B, FVector *Out) { *Out = B->GetExtent(); }
void Driver_9e130(FVector *A, FVector *Out, FLOAT R) { *Out = A->BoundToCube(R); }
