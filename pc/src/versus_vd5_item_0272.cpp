// Work item 0272 (Versus RVA 0xfbc70-0xfbfd7). All functions here come from a
// link-time code generated object (Engine particle code); they are checked
// with try_ltcg.py. Class and member names are neutral where the evidence
// does not name them.
typedef float FLOAT;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT Size() const { return (FLOAT)sqrt(X * X + Y * Y + Z * Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector SafeNormal() const;             // 0x50d30 (LTCG: result in ecx, this in edx)
    FVector operator+=(const FVector &V);   // 0x40680 (LTCG: this in ecx, V in edx, result in eax)
};

// The actor fields used below. Offsets from retail; names are guesses.
struct AActor
{
    BYTE Pad0[0x80];
    FVector Location;           // 0x80
    FVector Velocity;           // 0x8c
    BYTE Pad98[0x29c - 0x98];
    FLOAT CollisionRadius;      // 0x29c
    FLOAT Field_2a0;            // 0x2a0, scales the push
    BYTE Pad2a4[0x2e6 - 0x2a4];
    BYTE Physics;               // 0x2e6
};

// Particle records are 0xc8 bytes.
struct FParticle
{
    FVector Location;           // 0x00
    BYTE Pad0c[0x18 - 0x0c];
    FVector Velocity;           // 0x18
    BYTE Pad24[0xb4 - 0x24];
    FLOAT Field_b4;             // 0xb4
    BYTE Padb8[0xbc - 0xb8];
    DWORD Flags;                // 0xbc
    BYTE Padc0[0xc8 - 0xc0];
};

template<class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

// UParticleEmitter (vtable slot 26 is shared by USpriteEmitter, UMeshEmitter
// and UFlicFlocEmitter).
class UParticleEmitter
{
public:
    BYTE Pad4[0x3a4 - 4];
    TArray<FParticle> Particles;    // 0x3a4
    INT ActiveParticles;            // 0x3b0

    virtual void UnnamedVirtual_fbc70(AActor *Other, FLOAT Strength);
};

// 0xfbc70: push live particles inside Other's collision radius away from it.
void UParticleEmitter::UnnamedVirtual_fbc70(AActor *Other, FLOAT Strength)
{
    switch (Other->Physics)
    {
    case 1:
        if (Other->CollisionRadius == 0.f)
            break;
    {
        FLOAT Radius = Other->CollisionRadius;
        FLOAT RadiusSquared = Radius * Radius;
        FLOAT InvRadiusSquared = 1.f / RadiusSquared;
        FParticle *P = &Particles(0);
        for (INT i = 0; i < ActiveParticles; i++)
        {
            if (!(P->Flags & 1))
                continue;
            if (P->Field_b4 != 0.f)
            {
                FLOAT DistSquared = (Other->Location - P->Location).SizeSquared();
                if (DistSquared < RadiusSquared)
                {
                    FVector Dir = (P->Location - Other->Location).SafeNormal();
                    INT Sign = 1;
                    if (!((Dir | Other->Velocity) > 0.f))
                        Sign = -1;
                    Dir *= (FLOAT)Sign;
                    FLOAT Push = Other->Velocity.Size() - (Dir | P->Velocity);
                    if (Push > 0.f)
                    {
                        Push = Push * Other->Field_2a0 * Strength;
                        if (Push > 0.f)
                        {
                            P->Velocity += Dir * (Push * DistSquared * InvRadiusSquared);
                            P->Flags &= ~2;
                        }
                    }
                }
            }
            P++;
        }
    }
    }
}

// 0xfbec0: FSArray::Add for 200-byte elements (strings "FSArray::Add" and
// "FSArray"). LTCG: this in esi, Count in eax.
struct FSArray
{
    void *Data;
    INT ArrayNum;
    INT Add(INT Count);
};

INT FSArray::Add(INT Count)
{
    INT Index = ArrayNum;
    ArrayNum += Count;
    INT Bytes = ArrayNum * 200;
    if (Data == 0)
    {
        Data = Bytes > 0 ? GMalloc->Malloc(Bytes, L"FSArray::Add") : 0;
    }
    else
        Data = GMalloc->Realloc(Data, Bytes, L"FSArray");
    return Index;
}

// 0xfbf20: blend two bytes. LTCG: A in eax, B in ecx; tail-calls _ftol.
INT LerpByte(const BYTE &A, const BYTE &B, FLOAT Alpha)
{
    return (INT)((B - A) * Alpha + A);
}

// 0xfbf60: scalar deleting destructor; the destructor (0xfca50) takes this in eax.
// The base's vtable is 0x10c03dc0 (its own deleting destructor is 0xff2c0).
struct UnnamedBase_fbf60
{
    virtual ~UnnamedBase_fbf60() {}
    inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }
};
struct UnnamedClass_fbf60 : public UnnamedBase_fbf60
{
    ~UnnamedClass_fbf60();
};

// 0xfca50 (outside this item): only the inlined base destructor's vtable store remains.
UnnamedClass_fbf60::~UnnamedClass_fbf60()
{
}

// 0xfbf90: set or clear a byte flag in an object's property block.
struct UnnamedOwner_fbf90
{
    BYTE Pad0[0x30];
    BYTE *Block;                // 0x30
};
struct UnnamedContext_fbf90
{
    BYTE Pad0[0xd60];
    UnnamedOwner_fbf90 *Owner;  // 0xd60
    BYTE Padd64[4];
    INT Mode;                   // 0xd68
};
struct UnnamedClass_fbf90
{
    INT Offset;                 // 0x4
    UBOOL bCheckFlag;           // 0x8
    virtual void Apply(UnnamedContext_fbf90 *Context);
};

void UnnamedClass_fbf90::Apply(UnnamedContext_fbf90 *Context)
{
    BYTE *Block = Context->Owner->Block;
    if (bCheckFlag && (*(DWORD *)(Block + 0x5f0) & 0x1000))
        return;
    BYTE *Value = Block + Offset;
    if (Context->Mode == 1)
        *Value = 1;
    else if (Context->Mode == 3 && *Value)
        *Value = 0;
}

// ---- Scaffolding for the LTCG link, not part of the unit. ----
void Escape(void *);

// Definitions of out-of-object callees, so the link gives them retail's
// register conventions (matched separately elsewhere).
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return FVector(0.f, 0.f, 0.f);
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}
__declspec(noinline) FVector FVector::operator+=(const FVector &V)
{
    X += V.X; Y += V.Y; Z += V.Z;
    return *this;
}

inline void *operator new(unsigned int, void *Mem) { return Mem; }
// Constructing the objects emits their vtables, which keeps the virtuals.
void Driver_fbc70(void *Mem, UParticleEmitter *E, AActor *A, FLOAT S) { Escape(new(Mem) UParticleEmitter); E->UnnamedVirtual_fbc70(A, S); }
INT Driver_fbec0(FSArray *A, INT N) { Escape(&GMalloc); return A->Add(N) + A->Add(1); }
INT Driver_fbf20(const BYTE *A, const BYTE *B, FLOAT F) { return LerpByte(A[0], B[0], F) + LerpByte(A[1], B[1], F); }
void Driver_fbf60(void *Mem, UnnamedClass_fbf60 *P) { Escape(&GMalloc); { UnnamedClass_fbf60 L; Escape(&L); } delete P; }
void Driver_fbf90(UnnamedClass_fbf90 *C, UnnamedContext_fbf90 *X) { C->Apply(X); }
