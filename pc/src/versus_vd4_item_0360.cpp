// Work item 0360: Versus RVA 0x9e1f0-0x9e5ae.
// Code compiled with /GL and linked with /LTCG, so retail uses register
// conventions only whole-program optimisation produces.

typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator/(FLOAT Scale) const { FLOAT RScale = 1.f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

// Neutral name: a 28-byte record of an integer and two vectors.
struct FUnnamed_9e370
{
    INT     A;
    FVector B;
    FVector C;
    FUnnamed_9e370(INT InA, const FVector &InB, const FVector &InC);
};

// RVA 0x9e370 (LTCG: this in EAX, InB in EDX, InC in ECX, InA on the stack).
__declspec(noinline) FUnnamed_9e370::FUnnamed_9e370(INT InA, const FVector &InB, const FVector &InC)
    : A(InA), B(InB), C(InC)
{
}

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR MemChunk_Tag[]; // L"MemChunk"
inline void *appMalloc(INT Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// FMemStack (UE2).
struct FTaggedMemory
{
    FTaggedMemory *Next;
    INT DataSize;
    BYTE Data[1];
};
class FMemStack
{
public:
    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;
    static FTaggedMemory *UnusedChunks;
    BYTE *AllocateNewChunk(INT MinSize);        // RVA 0x577c0 (size in EAX, this in EDI)
    BYTE *PushBytes(INT AllocSize, INT Align)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
        Top = Result + AllocSize;
        if (Top > End) {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

// RVA 0x9e4d0 (UE2 operator new on a memory stack; LTCG: Mem in EAX,
// Align in EBX, Size and Count on the stack).
__declspec(noinline) void *operator new(unsigned int Size, FMemStack &Mem, INT Count, INT Align)
{
    return Mem.PushBytes(Size * Count, Align);
}

// RVA 0x577c0 (UE2 FMemStack::AllocateNewChunk), copied from item 0358 so
// LTCG gives it its retail convention.
__declspec(noinline) BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next) {
        if ((*Link)->DataSize >= MinSize) {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk) {
        INT DataSize = Max(MinSize, DefaultChunkSize - (INT)sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)appMalloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FMatrix
{
    union
    {
        struct { FPlane XPlane, YPlane, ZPlane, WPlane; };
        FLOAT M[4][4];
    };
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    FMatrix operator*(const FMatrix &Other) const;
    void operator*=(const FMatrix &Other);
    FVector TransformFPlane(const FPlane &P) const;     // RVA 0x4fe60
    FVector TransformNormal(const FVector &V) const;
};

// RVA 0x9e330 (UE2 FMatrix::TransformNormal; LTCG: result in ESI, V in EAX,
// this on the stack, ret 4).
__declspec(noinline) FVector FMatrix::TransformNormal(const FVector &V) const
{
    return TransformFPlane(FPlane(V.X, V.Y, V.Z, 0.f));
}

// Ken Perlin's reference gradient noise (with one setup temporary per axis), held in an object (neutral name):
// permutation table at +0x04 and 1-, 2- and 3-D gradient tables after it.
#define NOISE_B  0x100
#define NOISE_BM 0xff
#define NOISE_N  4096.f
class FPerlinNoise_9e1f0
{
public:
    INT   Unknown0;
    INT   p[NOISE_B + NOISE_B + 2];         // 0x0004
    FLOAT g3[NOISE_B + NOISE_B + 2][3];     // 0x080c
    FLOAT g2[NOISE_B + NOISE_B + 2][2];     // 0x2024
    FLOAT Noise2(const FLOAT *vec);
};

#define s_curve(t) ( t * t * (3.f - 2.f * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i, b0, b1, r0, r1, t) \
    t = vec[i] + NOISE_N; \
    b0 = ((INT)t) & NOISE_BM; \
    b1 = (b0 + 1) & NOISE_BM; \
    r0 = t - (INT)t; \
    r1 = r0 - 1.f;
#define at2(rx, ry) ( rx * q[0] + ry * q[1] )

// RVA 0x9e1f0 (Perlin's noise2; LTCG: this in ESI, vec in EAX).
__declspec(noinline) FLOAT FPerlinNoise_9e1f0::Noise2(const FLOAT *vec)
{
    INT bx0, bx1, by0, by1, b00, b10, b01, b11;
    FLOAT rx0, rx1, ry0, ry1, *q, sx, sy, a, b, tx, ty, u, v;
    INT i, j;

    setup(0, bx0, bx1, rx0, rx1, tx);
    setup(1, by0, by1, ry0, ry1, ty);

    i = p[bx0];
    j = p[bx1];

    b00 = p[i + by0];
    b10 = p[j + by0];
    b01 = p[i + by1];
    b11 = p[j + by1];

    sx = s_curve(rx0);
    sy = s_curve(ry0);

    q = g2[b00]; u = at2(rx0, ry0);
    q = g2[b10]; v = at2(rx1, ry0);
    a = lerp(sx, u, v);

    q = g2[b01]; u = at2(rx0, ry1);
    q = g2[b11]; v = at2(rx1, ry1);
    b = lerp(sx, u, v);

    return lerp(sy, a, b);
}

// FGlobalMath at 0x10ccac00; its sine/cosine helper is RVA 0x40950.
struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;
extern const FVector &GMath_UnitY;  // 0x10ccacb8
extern const FVector &GMath_UnitZ;  // 0x10ccacbc
extern const FVector &GMath_Zero;   // 0x10ccacc0
extern const FVector &GMath_UnitX;  // 0x10ccacc4

struct FTranslationMatrix : public FMatrix { FTranslationMatrix(const FVector &Delta); };
struct FScaleMatrix : public FMatrix { FScaleMatrix(const FVector &Scale); };
struct FInverseRotationMatrix : public FMatrix { FInverseRotationMatrix(const FRotator &Rot); };

// Only the members WorldToLocal reads (UE2 AActor layout in SCCT).
class AActor
{
public:
    BYTE Pad00[0x80];
    FVector Location;           // 0x080
    BYTE Pad8C[0xb0 - 0x8c];
    FVector DrawScale3D;        // 0x0b0
    FVector PrePivot;           // 0x0bc
    BYTE PadC8[0xe0 - 0xc8];
    FRotator Rotation;          // 0x0e0
    BYTE PadEC[0x23c - 0xec];
    FLOAT DrawScale;            // 0x23c
    FMatrix WorldToLocal() const;
};

// RVA 0x9e3b0 (UE2 AActor::WorldToLocal; LTCG: this in EAX, result on the
// stack, ret 4). Not matching: the FScaleMatrix/FTranslationMatrix calls and
// the result pointer link with different registers (see below).
__declspec(noinline) FMatrix AActor::WorldToLocal() const
{
    return FTranslationMatrix(-Location)
        * FInverseRotationMatrix(Rotation)
        * FScaleMatrix(FVector(1.f / DrawScale3D.X, 1.f / DrawScale3D.Y, 1.f / DrawScale3D.Z) / DrawScale)
        * FTranslationMatrix(PrePivot);
}

// The out-of-line UnMath helpers WorldToLocal calls, copied from items 0202,
// 0207, 0299 and 0307 so LTCG gives them their retail conventions.
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}

__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix &Other) const
{
    FMatrix Result;
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            Result.M[i][j] = M[i][0] * Other.M[0][j] + M[i][1] * Other.M[1][j] + M[i][2] * Other.M[2][j] + M[i][3] * Other.M[3][j];
    return Result;
}

__declspec(noinline) void FMatrix::operator*=(const FMatrix &Other)
{
    *this = *this * Other;
}

__declspec(noinline) FInverseRotationMatrix::FInverseRotationMatrix(const FRotator &Rot)
{
    FLOAT S, C;
    GMath.SinCos(-Rot.Yaw, &S, &C);
    FPlane W(GMath_Zero, 1.f);
    *(FMatrix *)this = FMatrix(FPlane(+C, +S, 0.f, 0.f), FPlane(-S, +C, 0.f, 0.f), FPlane(GMath_UnitZ, 0.f), W);
    GMath.SinCos(-Rot.Pitch, &S, &C);
    *this *= FMatrix(FPlane(+C, 0.f, +S, 0.f), FPlane(GMath_UnitY, 0.f), FPlane(-S, 0.f, +C, 0.f), W);
    GMath.SinCos(-Rot.Roll, &S, &C);
    *this *= FMatrix(FPlane(GMath_UnitX, 0.f), FPlane(0.f, +C, -S, 0.f), FPlane(0.f, +S, +C, 0.f), W);
}

// RVA 0x81910 and 0x819b0 (item 0307). Retail passes this in ESI and the
// vector in EAX; these link with this in EAX and the vector in ECX, which is
// why 0x9e3b0 does not match yet.
__declspec(noinline) FScaleMatrix::FScaleMatrix(const FVector &Scale)
    : FMatrix(
        FPlane(Scale.X, 0.f, 0.f, 0.f),
        FPlane(0.f, Scale.Y, 0.f, 0.f),
        FPlane(0.f, 0.f, Scale.Z, 0.f),
        FPlane(0.f, 0.f, 0.f, 1.f))
{
}

__declspec(noinline) FTranslationMatrix::FTranslationMatrix(const FVector &Delta)
    : FMatrix(
        FPlane(1.f, 0.f, 0.f, 0.f),
        FPlane(0.f, 1.f, 0.f, 0.f),
        FPlane(0.f, 0.f, 1.f, 0.f),
        FPlane(Delta.X, Delta.Y, Delta.Z, 1.f))
{
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_9e370(FUnnamed_9e370 *Out, INT A, const FVector *B, const FVector *C) { new (Out) FUnnamed_9e370(A, *B, *C); }
void *Driver_9e4d0(FMemStack *M, unsigned int S, INT C, INT A)
{
    Escape(&GMalloc); Escape(&FMemStack::UnusedChunks);
    void *P = operator new(S, *M, C, A);
    Escape(P);
    return operator new(S + 4, *M, C + 1, A * 2);
}
void Driver_9e330(FVector *Out, const FMatrix *M, const FVector *V)
{
    new (Out) FVector(M->TransformNormal(*V));
    new (Out + 1) FVector(M[1].TransformNormal(V[1]));
}
FLOAT Driver_9e1f0(FPerlinNoise_9e1f0 *N, const FLOAT *V)
{
    return N->Noise2(V) + N[1].Noise2(V + 2);
}
void Driver_9e3b0(FMatrix *Out, const AActor *A)
{
    Escape(&GMath);
    new (Out) FMatrix(A->WorldToLocal());
}
// Many direct FMatrix constructions, as in retail, fix 0x4fbc0's register convention.
void Driver_4fbc0(FMatrix *Out, const FPlane *P)
{
    for (INT i = 0; i < 8; i++)
    {
        new (&Out[i * 4 + 0]) FMatrix(P[0], P[1], P[2], P[3]);
        new (&Out[i * 4 + 1]) FMatrix(P[4], P[5], P[6], P[7]);
        new (&Out[i * 4 + 2]) FMatrix(P[8], P[9], P[10], P[11]);
        new (&Out[i * 4 + 3]) FMatrix(P[12], P[13], P[14], P[15]);
    }
}
