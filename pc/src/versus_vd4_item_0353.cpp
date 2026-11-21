// UESBPatch (Epic soft body patch) virtual methods, RVA 0x9b040-0x9b628.
// Member names are inferred from what the code does; the original ESB
// source is not published.
typedef int INT;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT Clamp(FLOAT V, FLOAT Lo, FLOAT Hi) { return V < Lo ? Lo : V < Hi ? V : Hi; }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT S) const { return FVector(X * S, Y * S, Z * S); }
    FVector operator+=(const FVector &V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    UBOOL operator==(const FVector &V) const { return X == V.X && Y == V.Y && Z == V.Z; }
    UBOOL operator!=(const FVector &V) const { return X != V.X || Y != V.Y || Z != V.Z; }
    FVector UnsafeNormal() const
    {
        FLOAT Scale = 1.0f / appSqrt(X * X + Y * Y + Z * Z);
        return FVector(X * Scale, Y * Scale, Z * Scale);
    }
    FVector SafeNormal() const;                  // RVA 0x50d30 (another unit)
    FVector BoundToCube(FLOAT Radius) const;     // RVA 0x9e130 (another unit)
    FLOAT SegmentDist(const FVector &Start, const FVector &End, FLOAT &T) const; // RVA 0x52400 (another unit)
};


extern __declspec(dllimport) FVector ZeroVector_Ref; // retail reads a pointer at 0x10ccacc0

struct FESBParticle            // 0x48 bytes
{
    BYTE    Flags;             // 0x00, bit 0 = fixed
    FVector Location;          // 0x04
    FVector OldLocation;       // 0x10
    FVector Acceleration;      // 0x1c
    FVector ConstantForce;     // 0x28
    FVector Force;             // 0x34
    BYTE    Pad40[8];
};

struct FESBCollider            // 0x1c bytes
{
    INT     Type;              // 0x00
    FVector Location;          // 0x04
    BYTE    Data[0x0c];        // 0x10, passed to NotifyCollision
};

struct FESBPatchTemplate { BYTE Pad[0x27c]; FLOAT Mass; };

class UESBPatch
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38();
    virtual void AccumulateForces();       // 39, 0x9b040
    virtual void Verlet();                 // 40, 0x9b130
    virtual void TimeStep();               // 41, 0x9b2d0
    virtual void SatisfyConstraints();     // 42 (0xa8)
    virtual UBOOL CollideCylinder(INT ParticleIndex, INT ColliderIndex, FLOAT HalfHeight, FLOAT Radius); // 43, 0x9b310
    virtual UBOOL CollideCapsule(INT ParticleIndex, INT ColliderIndex, const FVector &Start, const FVector &End, FLOAT Radius); // 44, 0x9b4a0
    virtual void Integrate();              // 45 (0xb4)
    virtual void v46(); virtual void v47();
    virtual void NotifyCollision(INT ParticleIndex, BYTE *ColliderData); // 48 (0xc0)

    BYTE  Pad04[0x54 - 4];
    FESBPatchTemplate *Template;   // 0x54
    BYTE  Pad58[0x70 - 0x58];
    FESBParticle *Particles;       // 0x70 (TArray data)
    INT   NumParticles;            // 0x74
    BYTE  Pad78[0xb8 - 0x78];
    FVector Gravity;               // 0xb8
    BYTE  PadC4[0x100 - 0xc4];
    INT   NumIterations;           // 0x100
    BYTE  Pad104[0x108 - 0x104];
    INT   SizeX;                   // 0x108
    INT   SizeY;                   // 0x10c
    FLOAT Damping;                 // 0x110
    BYTE  Pad114[0x118 - 0x114];
    BYTE  Pad118[0x11c - 0x118];
    FESBCollider *Colliders;       // 0x11c
    BYTE  Pad120[0x12c - 0x120];
    FLOAT DeltaTime;               // 0x12c
};

// RVA 0x9b040, vtable slot 39
void UESBPatch::AccumulateForces()
{
    FLOAT InvMass = (FLOAT)(SizeY * SizeX) / Template->Mass;
    for (INT i = 0; i < NumParticles; i++) {
        if (!(Particles[i].Flags & 1)) {
            FESBParticle &P = Particles[i];
            P.Acceleration = (P.ConstantForce + P.Force) * InvMass + Gravity;
            Particles[i].Force = ZeroVector_Ref;
        }
    }
}

// RVA 0x9b2d0, vtable slot 41
void UESBPatch::TimeStep()
{
    for (INT i = 0; i < NumIterations; i++) {
        SatisfyConstraints();
        Integrate();
    }
}

// RVA 0x9b130, vtable slot 40 (LTCG unit)
void UESBPatch::Verlet()
{
    for (INT i = 0; i < NumParticles; i++) {
        FESBParticle &P = Particles[i];
        if (!(P.Flags & 1)) {
            FVector Accel = P.Acceleration * (DeltaTime * DeltaTime);
            FVector Old = P.Location;
            P.Location = P.Location * 2.f - P.OldLocation + Accel;
            P.OldLocation = Old;
            P.OldLocation += (P.Location - P.OldLocation) * Damping;
            P.Location = P.Location.BoundToCube(1000.f);
            P.OldLocation = P.OldLocation.BoundToCube(1000.f);
        }
    }
}

// RVA 0x9b310, vtable slot 43 (LTCG unit)
UBOOL UESBPatch::CollideCylinder(INT ParticleIndex, INT ColliderIndex, FLOAT HalfHeight, FLOAT Radius)
{
    FESBCollider &C = Colliders[ColliderIndex];
    BYTE *Data = C.Data;
    FVector &Loc = Particles[ParticleIndex].Location;
    FLOAT Top = C.Location.Z + HalfHeight;
    FLOAT Bottom = C.Location.Z - HalfHeight;
    FVector Delta(Loc.X - C.Location.X, Loc.Y - C.Location.Y, 0.f);
    FLOAT Dist = appSqrt(Delta.X * Delta.X + Delta.Y * Delta.Y);
    if (Loc.Z < Top && Loc.Z > Bottom && Dist < Radius) {
        FLOAT DistRadial = Radius - Dist;
        FLOAT DistTop = Top - Loc.Z;
        FLOAT DistBottom = Loc.Z - Bottom;
        if (DistTop < DistRadial && DistTop < DistBottom)
            Loc.Z += DistTop;
        else if (DistBottom < DistRadial && DistBottom < DistTop)
            Loc.Z -= DistBottom;
        else
            Loc += Delta.SafeNormal() * DistRadial;
        Loc = Loc.BoundToCube(1000.f);
        NotifyCollision(ParticleIndex, Data);
        return 1;
    }
    return 0;
}


// RVA 0x9b4a0, vtable slot 44 (LTCG unit)
UBOOL UESBPatch::CollideCapsule(INT ParticleIndex, INT ColliderIndex, const FVector &Start, const FVector &End, FLOAT Radius)
{
    FVector &Loc = Particles[ParticleIndex].Location;
    FLOAT T = 0.f;
    if (Loc.SegmentDist(Start, End, T) < Radius) {
        FVector Closest = Start + (End - Start) * T;
        if (Loc != Closest)
            Loc = Closest + (Loc - Closest).UnsafeNormal() * Radius;
        else
            Loc.X += 0.1f;
        Loc = Loc.BoundToCube(1000.f);
        return 1;
    }
    return 0;
}

// Out-of-unit callees, defined so the LTCG link gives them retail's register
// conventions. Not part of this item.
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return ZeroVector_Ref;
    FLOAT Scale = 1.0f / appSqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}
__declspec(noinline) FVector FVector::BoundToCube(FLOAT Radius) const
{
    return FVector(Clamp(X, -Radius, Radius), Clamp(Y, -Radius, Radius), Clamp(Z, -Radius, Radius));
}
__declspec(noinline) FLOAT FVector::SegmentDist(const FVector &Start, const FVector &End, FLOAT &T) const
{
    const FVector &Point = *this;
    FLOAT PX = Point.X - Start.X, PY = Point.Y - Start.Y, PZ = Point.Z - Start.Z;
    FLOAT SX = End.X - Start.X, SY = End.Y - Start.Y, SZ = End.Z - Start.Z;
    FLOAT Dot = SX * PX + SY * PY + SZ * PZ;
    T = Dot;
    if (Dot > 0.f) {
        FLOAT LenSq = SX * SX + SY * SY + SZ * SZ;
        if (Dot < LenSq) {
            T = Dot / LenSq;
            PX -= SX * T; PY -= SY * T; PZ -= SZ * T;
        } else {
            T = 1.f;
            PX -= SX; PY -= SY; PZ -= SZ;
        }
    } else {
        T = 0.f;
    }
    return appSqrt(PX * PX + PY * PY + PZ * PZ);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_9b130(UESBPatch *P) { Escape(&ZeroVector_Ref); P->UESBPatch::Verlet(); }
void Driver_9b310(UESBPatch *P, INT A, INT B, FLOAT H, FLOAT R) { Escape(&ZeroVector_Ref); P->UESBPatch::CollideCylinder(A, B, H, R); }
void Driver_9b4a0(UESBPatch *P, INT A, INT B, const FVector &S, const FVector &E, FLOAT R) { Escape(&ZeroVector_Ref); P->UESBPatch::CollideCapsule(A, B, S, E, R); }
void Driver_9b040(UESBPatch *P) { Escape(&ZeroVector_Ref); P->UESBPatch::AccumulateForces(); }
