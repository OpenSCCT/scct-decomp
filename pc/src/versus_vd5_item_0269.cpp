// Work item 0269: UParticleEmitter methods (Versus RVA 0xf8de0-0xf9203).
// Field names are guesses from the layout; offsets are retail.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned char BYTE;

extern "C" __declspec(dllimport) int __cdecl rand(void);

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector SafeNormal() const;
};
// 0x10ccacc0, read through the import pointer.
__declspec(dllimport) extern const FVector GZeroVector;
struct FFrame { BYTE Pad[0xc]; BYTE *Code; };

struct FMalloc {
    virtual void *Malloc(DWORD Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

// Global particle counters (0x10c92414 / 0x10c92418).
extern INT GActiveParticleMemory;
extern INT GPeakParticleMemory;

// Tags for the SCCT simple array (no ArrayMax); retail keeps them in .data.
extern const unsigned short FSArray_Tag[];      // L"FSArray"
extern const unsigned short FSArray_Add_Tag[];  // L"FSArray::Add"

// Simple dynamic array used by the emitters: Data and Num only.
template<class T> struct TSArray
{
    T *Data;
    INT Num;
    void Empty()
    {
        Num = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
    }
    INT Add(INT Count);
};

// 200-byte particle record; contents not needed here.
struct FParticle { BYTE Pad[200]; };

inline FLOAT appFrand() { return rand() / 32768.f; }

class UParticleEmitter
{
public:
    virtual void Vf00(); virtual void Vf01(); virtual void Vf02(); virtual void Vf03();
    virtual void Vf04(); virtual void Vf05(); virtual void Vf06(); virtual void Vf07();
    virtual void Vf08(); virtual void Vf09(); virtual void Vf10(); virtual void Vf11();
    virtual void Vf12(); virtual void Vf13(); virtual void Vf14(); virtual void Vf15();
    virtual void Vf16(); virtual void Vf17(); virtual void Vf18(); virtual void Vf19();
    virtual void Vf20(); virtual void Vf21();
    virtual void Initialize(INT InMaxParticles);  // 0x58
    virtual void CleanUp();                       // 0x5c
    virtual void Reset();                         // 0x60
    virtual void Scale(FLOAT ScaleFactor);        // 0x64

    void execTrigger(FFrame &Stack, void *Result);
    void PostEditChange_8e80();
    void AllocateParticles(INT Count);

    BYTE Pad04[0x30];
    FVector Location;        // 0x34
    BYTE Pad40[0x44];
    FLOAT Scale84[3];        // 0x84
    FVector OldLocation;     // 0x90
    BYTE Pad9C[0xc];
    FVector Direction;       // 0xa8
    FVector Velocity;        // 0xb4
    BYTE PadC0[0x90];
    INT MaxParticles;        // 0x150
    FLOAT Range154[2];       // 0x154
    BYTE Pad15C[0xc];
    FLOAT Scale168[6];       // 0x168
    BYTE Pad180[0x1c];
    FLOAT Scale19C[2];       // 0x19c
    BYTE Pad1A4[0x3c];
    DWORD Flags1E0;          // 0x1e0
    DWORD Flags1E4;          // 0x1e4
    BYTE Pad1E8[0xac];
    FLOAT Scale294[6];       // 0x294
    BYTE Pad2AC[0x6c];
    FLOAT Range318[2];       // 0x318
    FLOAT Range320[2];       // 0x320
    BYTE Pad328[4];
    FLOAT Scale32C[6];       // 0x32c
    BYTE Pad344[0x58];
    INT Field39C;            // 0x39c
    BYTE Pad3A0[4];
    TSArray<FParticle> Particles; // 0x3a4
    INT Field3AC;            // 0x3ac
    INT Field3B0;            // 0x3b0
    BYTE Pad3B4[4];
    INT Field3B8;            // 0x3b8
    FLOAT Field3BC;          // 0x3bc
    FLOAT Field3C0;          // 0x3c0
    BYTE Pad3C4[4];
    INT Field3C8;            // 0x3c8
    BYTE Pad3CC[0x18];
    INT Field3E4;            // 0x3e4
};

void UParticleEmitter::execTrigger(FFrame &Stack, void *Result)
{
    Stack.Code++;
    DWORD F = Flags1E4;
    if (F & 1)
        Flags1E0 = ((~Flags1E0 ^ Flags1E0) & 0x800) ^ Flags1E0;
    if (F & 2)
        Reset();
    FLOAT R = appFrand();
    if ((Field3E4 = (INT)((Range320[0] - Range320[1]) * R + Field3E4 + Range320[1])) != 0)
        Flags1E4 &= ~0x18;
}

void UParticleEmitter::PostEditChange_8e80()
{
    if (Particles.Num != MaxParticles || (Flags1E0 & 0x80)) {
        CleanUp();
        Initialize(MaxParticles);
    }
}

void UParticleEmitter::Reset()
{
    Field3B0 = 0;
    Field3AC = 0;
    Field3B8 = 0;
    Flags1E4 &= ~0x30;
    Field39C = 0;
    Field3BC = Range318[1] + (Range318[0] - Range318[1]) * appFrand();
    Field3C0 = Range154[1] + (Range154[0] - Range154[1]) * appFrand();
}

void UParticleEmitter::Initialize(INT InMaxParticles)
{
    GActiveParticleMemory -= Particles.Num;
    Particles.Empty();
    Particles.Add(InMaxParticles);
    GActiveParticleMemory += Particles.Num;
    if (GActiveParticleMemory > GPeakParticleMemory)
        GPeakParticleMemory = GActiveParticleMemory;
    Reset();
    OldLocation = Location;
    Direction = Velocity.SafeNormal();
    Field3C8 = InMaxParticles;
    Flags1E4 |= 4;
}

void UParticleEmitter::CleanUp()
{
    GActiveParticleMemory -= Particles.Num;
    Particles.Empty();
    Field3B0 = 0;
    Field3AC = 0;
    Flags1E4 &= ~4;
}

void UParticleEmitter::Scale(FLOAT S)
{
    Scale168[0] *= S; Scale168[1] *= S; Scale168[2] *= S;
    Scale168[3] *= S; Scale168[4] *= S; Scale168[5] *= S;
    Scale294[0] *= S; Scale294[1] *= S; Scale294[2] *= S;
    Scale294[3] *= S; Scale294[4] *= S; Scale294[5] *= S;
    Scale32C[0] *= S; Scale32C[1] *= S; Scale32C[2] *= S;
    Scale32C[3] *= S; Scale32C[4] *= S; Scale32C[5] *= S;
    Scale84[0] *= S; Scale84[1] *= S; Scale84[2] *= S;
    Scale19C[0] *= S; Scale19C[1] *= S;
}

// Callees from other objects, defined so the link-time code generator gives
// them their retail register conventions (TSArray::Add at 0xfbec0 takes this
// in esi and Count in eax; FVector::SafeNormal at 0x950d30 takes the result
// in ecx and this in edx). Both belong to other work items.
template<class T> __declspec(noinline) INT TSArray<T>::Add(INT Count)
{
    INT Index = Num;
    Num += Count;
    INT Bytes = Num * sizeof(T);
    if (Data)
        Data = (T *)GMalloc->Realloc(Data, Bytes, FSArray_Tag);
    else if (Bytes > 0)
        Data = (T *)GMalloc->Malloc(Bytes, FSArray_Add_Tag);
    else
        Data = 0;
    return Index;
}

FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return GZeroVector;
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_f8f50(UParticleEmitter *E, INT N)
{
    Escape(&GMalloc);
    E->UParticleEmitter::Initialize(N);
}
