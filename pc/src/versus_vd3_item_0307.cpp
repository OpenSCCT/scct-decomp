// Work item 0307: Versus RVA 0x81810-0x81b34.
// Core math (UnMath.h style) compiled with /GL and linked with /LTCG:
// FRotationMatrix, FScaleMatrix and FTranslationMatrix constructors, a
// TArray<INT>-style AddItem on an unnamed class, FBox::ExpandBy and the
// two-point FBox constructor. Retail calls use LTCG register conventions.

typedef int INT;
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
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
};

// RVA 0x4fbc0 (item 0202), copied so LTCG gives it its retail convention
// (this in EAX, InZ in EDX, InW in ECX, InX and InY on the stack).
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}

// FGlobalMath at 0x10ccac00; its sine/cosine helper is RVA 0x40950.
struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;

// Constant vectors read through pointers (imported data, as in item 0206).
__declspec(dllimport) extern const FVector GMath_Zero;   // 0x10ccacc0
__declspec(dllimport) extern const FVector GMath_UnitX;  // 0x10ccacc4

struct FRotationMatrix : public FMatrix
{
    FRotationMatrix(const FRotator &Rot);
};

// RVA 0x81810 (LTCG: this in ESI, Rot in EDI).
__declspec(noinline) FRotationMatrix::FRotationMatrix(const FRotator &Rot)
{
    FLOAT SR, SP, SY, CR, CP, CY;
    GMath.SinCos(Rot.Yaw, &SY, &CY);
    GMath.SinCos(Rot.Pitch, &SP, &CP);
    GMath.SinCos(Rot.Roll, &SR, &CR);

    M[0][0] = CP * CY;
    M[0][1] = CP * SY;
    M[0][2] = SP;
    M[0][3] = 0.f;

    M[1][0] = SR * SP * CY - CR * SY;
    M[1][1] = SR * SP * SY + CR * CY;
    M[1][2] = -SR * CP;
    M[1][3] = 0.f;

    M[2][0] = -(CR * SP * CY + SR * SY);
    M[2][1] = CY * SR - CR * SP * SY;
    M[2][2] = CR * CP;
    M[2][3] = 0.f;

    M[3][0] = 0.f;
    M[3][1] = 0.f;
    M[3][2] = 0.f;
    M[3][3] = 1.f;
}

struct FScaleMatrix : public FMatrix
{
    FScaleMatrix(const FVector &Scale);
};

// RVA 0x81910 (LTCG: this in ESI, Scale in EAX). Near miss: our build passes
// Scale in ECX and this in EAX, reusing the FMatrix constructor's returned
// this; retail keeps this in ESI and reloads EAX around the call.
__declspec(noinline) FScaleMatrix::FScaleMatrix(const FVector &Scale)
    : FMatrix(
        FPlane(Scale.X, 0.f, 0.f, 0.f),
        FPlane(0.f, Scale.Y, 0.f, 0.f),
        FPlane(0.f, 0.f, Scale.Z, 0.f),
        FPlane(0.f, 0.f, 0.f, 1.f))
{
}

struct FTranslationMatrix : public FMatrix
{
    FTranslationMatrix(const FVector &Delta);
};

// RVA 0x819b0 (LTCG: this in ESI, Delta in EAX). Near miss, as 0x81910.
__declspec(noinline) FTranslationMatrix::FTranslationMatrix(const FVector &Delta)
    : FMatrix(
        FPlane(1.f, 0.f, 0.f, 0.f),
        FPlane(0.f, 1.f, 0.f, 0.f),
        FPlane(0.f, 0.f, 1.f, 0.f),
        FPlane(Delta.X, Delta.Y, Delta.Z, 1.f))
{
}

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);   // RVA 0x44e0
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        ((T *)Data)[Index] = Item;
        return Index;
    }
};

// Neutral name: an unnamed class holding a 4-byte-element TArray at +0x28.
class UnnamedClass_81a50
{
public:
    void AddEntry(INT Entry);
    char Pad[0x28];
    TArray<INT> Entries;
};

// RVA 0x81a50 (LTCG: this in EAX, Entry on the stack).
__declspec(noinline) void UnnamedClass_81a50::AddEntry(INT Entry)
{
    Entries.AddItem(Entry);
}

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// SCCT's FBox has no IsValid flag: an invalid box has Min.X - Max.X == 1
// (Min = UnitX, Max = Zero).
struct FBox
{
    FVector Min, Max;
    FBox(const FVector &InMin, const FVector &InMax);
    FBox &operator+=(const FVector &Other);
    FBox ExpandBy(FLOAT W) const;
};

// RVA 0x4f820 (item 0201), copied so LTCG gives it its retail convention
// (this in ECX, Other in EDX).
__declspec(noinline) FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X != 1.f)
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

// RVA 0x81ad0 (LTCG: this in ESI, InMin in EDX, InMax in EDI).
__declspec(noinline) FBox::FBox(const FVector &InMin, const FVector &InMax)
    : Min(InMin), Max(InMax)
{
    Min = GMath_UnitX;
    Max = GMath_Zero;
    *this += InMin;
    *this += InMax;
}

// RVA 0x81a70 (LTCG: this in EAX, result in ECX, W on the stack).
__declspec(noinline) FBox FBox::ExpandBy(FLOAT W) const
{
    return FBox(Min - FVector(W, W, W), Max + FVector(W, W, W));
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_81810(FMatrix *Out, const FRotator *R) { Escape(&GMath); new (Out) FRotationMatrix(*R); }
void Driver_81a50(UnnamedClass_81a50 *C, INT E) { C->AddEntry(E); }
void Driver_81a70(FBox *Out, const FBox *B, FLOAT W) { Escape((void *)&GMath_Zero); Escape((void *)&GMath_UnitX); new (Out) FBox(B->ExpandBy(W)); }
void Driver_81ad0(FBox *Out, const FVector *A, const FVector *B) { Escape((void *)&GMath_Zero); Escape((void *)&GMath_UnitX); new (Out) FBox(*A, *B); }
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
// Retail callers compose the matrices in one expression.
void Driver_Compose(FMatrix *Out, const FVector *A, const FRotator *R, const FVector *S, const FVector *B)
{
    Escape(&GMath);
    *Out = FTranslationMatrix(*A) * FRotationMatrix(*R) * FScaleMatrix(*S) * FScaleMatrix(*B) * FTranslationMatrix(*B);
}
