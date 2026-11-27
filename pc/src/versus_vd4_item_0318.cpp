// Work item 0318 (RVA 0x86b40-0x86daa), Engine, built with /GL and linked with
// /LTCG: two archive serializers and two USpriteEmitter virtuals.
// - 0x86b40: operator<< for a 32-byte record (two vectors and two floats);
//   archive in ESI, record in EAX. Used by the TArray serializer at 0x1fd450.
//   The record's name is not known (UnnamedStruct_86b40).
// - 0x86bb0: bulk operator<< for TArray<FVector>; array in EBX, archive in EAX.
// - 0x86c50 / 0x86cc0: USpriteEmitter::Initialize and UpdateParticles (vtable
//   slots 22 and 29 of USpriteEmitter at 0x30b5b8). Layout as in item 0306.
#include "versus_build.h"
#include "unreal_object.h"

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR TEXT_operator_TArray[];   // L"operator<<(TArray)"

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
    void Realloc(INT ElementSize);              // 0x4600
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
};

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector SafeNormal() const;     // 0x50d30
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

struct FBox
{
    FVector Min, Max;
    FBox() {}
    FBox(const FVector &InMin, const FVector &InMax);   // 0x81ad0
    FBox &operator+=(const FVector &Other);            // 0x4f820
    UBOOL IsValid() const { return Min.X - Max.X != 1.f; }
    FBox ExpandBy(FLOAT W) const;                      // 0x81a70
};

struct FRange
{
    FLOAT Min, Max;
    FLOAT GetMax() const { return ::Max(Min, Max); }
};

struct FRangeVector
{
    FRange X, Y, Z;
};

// 32-byte record serialized at 0x86b40 (name unknown).
struct UnnamedStruct_86b40
{
    FVector A;
    FVector B;
    FLOAT C;
    FLOAT D;
};

// RVA 0x86b40.
FArchive &operator<<(FArchive &Ar, UnnamedStruct_86b40 &S)
{
    return Ar << S.A << S.B << S.C << S.D;
}

// RVA 0x86bb0: TArray<FVector> serialized in bulk.
FArchive &operator<<(FArchive &Ar, TArray<FVector> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayMax == 0)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayMax * sizeof(FVector), TEXT_operator_TArray);
        } else if (A.ArrayMax) {
            A.Realloc(sizeof(FVector));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FVector));
    return Ar;
}

class UParticleEmitter : public UObject
{
public:
    UParticleEmitter();
    virtual ~UParticleEmitter();
    virtual void Initialize(INT InMaxParticles);     // slot 22 (0xf8f50)
    virtual void CleanUp();                          // slot 23
#define SLOT(n) virtual void Slot##n();
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28)
#undef SLOT
    virtual INT UpdateParticles(FLOAT DeltaTime);    // slot 29 (0xf9ff0)

    virtual void Slot30();
    virtual void Slot31();

    BYTE Pad28[0xc0 - 0x28];
    FBox BoundingBox;            // 0xc0
    BYTE Padd8[0x1e0 - 0xd8];
    DWORD Flags1e0 : 27;
    DWORD UniformSize : 1;       // 0x1e0 bit 27
    DWORD Flags1e0c : 4;
    BYTE Pad1e4[0x294 - 0x1e4];
    FRangeVector StartSizeRange; // 0x294
    BYTE Pad2ac[0x3d8 - 0x2ac];
    FLOAT Scale3d8;              // 0x3d8 (neutral name)
    BYTE Pad3dc[0x3e8 - 0x3dc];
};

class USpriteEmitter : public UParticleEmitter
{
public:
    virtual void Slot32();
    FVector ProjectionNormal;     // 0x3e8
    FVector RealProjectionNormal; // 0x3f4
    BYTE Byte400;                 // 0x400 (neutral name)
    BYTE Pad401[0x408 - 0x401];

    USpriteEmitter() {}
    void Initialize(INT InMaxParticles);
    INT UpdateParticles(FLOAT DeltaTime);
};

// RVA 0x86c50.
void USpriteEmitter::Initialize(INT InMaxParticles)
{
    UParticleEmitter::Initialize(InMaxParticles);
    RealProjectionNormal = ProjectionNormal.SafeNormal();
    UniformSize = UniformSize || !Byte400;
}

// RVA 0x86cc0.
INT USpriteEmitter::UpdateParticles(FLOAT DeltaTime)
{
    INT Result = UParticleEmitter::UpdateParticles(DeltaTime);
    if (BoundingBox.IsValid()) {
        FLOAT Size = Scale3d8;
        if (UniformSize)
            Size *= StartSizeRange.X.GetMax();
        else
            Size *= Max(StartSizeRange.X.GetMax(), StartSizeRange.Y.GetMax());
        BoundingBox = BoundingBox.ExpandBy(Size);
    }
    return Result;
}

// ---- Not part of this item: callees defined so LTCG gives them their retail
// register conventions (copied from items 0116, 0184 and 0307).
extern const FVector GMath_UnitX;
extern const FVector GMath_Zero;

// RVA 0x1ea40 (archive in ESI, index in EDI).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
// RVA 0x50d30 (result in ECX, this in EDX).
__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return FVector(0.f, 0.f, 0.f);
    FLOAT Scale = 1.f / (FLOAT)sqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

// RVA 0x4f820 (this in ECX, Other in EDX).
__declspec(noinline) FBox &FBox::operator+=(const FVector &Other)
{
    if (IsValid())
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

// RVA 0x81ad0 (this in ESI, InMin in EDX, InMax in EDI).
__declspec(noinline) FBox::FBox(const FVector &InMin, const FVector &InMax)
    : Min(InMin), Max(InMax)
{
    Min = GMath_UnitX;
    Max = GMath_Zero;
    *this += InMin;
    *this += InMax;
}

// RVA 0x81a70 (this in EAX, result in ECX, W on the stack).
__declspec(noinline) FBox FBox::ExpandBy(FLOAT W) const
{
    return FBox(Min - FVector(W, W, W), Max + FVector(W, W, W));
}

// ---- Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);

// Like the retail TArray serializer at 0x1fd450.
FArchive &SerializeRecords(FArchive &Ar, TArray<UnnamedStruct_86b40> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(sizeof(UnnamedStruct_86b40), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((UnnamedStruct_86b40 *)A.Data)[A.Add(1, sizeof(UnnamedStruct_86b40))]) UnnamedStruct_86b40;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

struct Holder_86bb0
{
    BYTE Pad[0x78];
    TArray<FVector> A;
    TArray<FVector> B;
};

void Driver_86b40(FArchive *Ar, TArray<UnnamedStruct_86b40> *A, Holder_86bb0 *H, void *Mem)
{
    // Constructing one emits the vtable, so the virtuals keep the plain thiscall convention.
    Escape(new (Mem) USpriteEmitter);
    Escape(&GMalloc);
    Escape((void *)&GMath_UnitX);
    Escape((void *)&GMath_Zero);
    SerializeRecords(*Ar, *A);
    // Retail 0xcb070 reads three records into locals in a row.
    UnnamedStruct_86b40 R[3];
    *Ar << R[0] << R[1] << R[2];
    Escape(R);
    *Ar << H->A << H->B;
}
