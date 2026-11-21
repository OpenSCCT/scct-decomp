// Core math: FSphere::FSphere(const FVector*,INT) (0x50ac0),
// FBox::FBox(const FVector*,INT) (0x50ce0) and FVector::SafeNormal (0x50d30).
// All three were link-time code generated: FSphere takes this in edi and
// Count in eax, FBox takes this in esi and Count in eax, SafeNormal takes the
// result in ecx and this in edx.
typedef float FLOAT;
typedef int INT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator/(FLOAT Scale) const { FLOAT RScale = 1.f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FVector SafeNormal() const;
};

// Retail reads these through pointers (imported data, locally defined):
// 0x10ccacc0 is the zero vector SafeNormal returns, 0x10ccacc4 the vector
// FBox starts Min from. Names are neutral.
__declspec(dllimport) extern const FVector GZeroVector;
__declspec(dllimport) extern const FVector GBoxStartMin;

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FBox
{
    FVector Min, Max;
    FBox(const FVector *Points, INT Count);
    FVector GetCenter() const { return FVector((Min + Max) * 0.5f); }
    FBox &operator+=(const FVector &Other); // 0x4f820
};

struct FSphere : public FPlane
{
    FSphere() {}
    FSphere(const FVector &V, FLOAT InW) : FPlane(V, InW) {}
    FSphere(const FVector *Pts, INT Count);
};

inline FLOAT FDistSquared(const FVector &V1, const FVector &V2)
{
    return (V1 - V2).SizeSquared();
}

FBox::FBox(const FVector *Points, INT Count)
    : Min(GBoxStartMin), Max(GZeroVector)
{
    for (INT i = 0; i < Count; i++)
        *this += Points[i];
}

FSphere::FSphere(const FVector *Pts, INT Count)
    : FPlane(0, 0, 0, 0)
{
    if (Count)
    {
        FBox Box(Pts, Count);
        *this = FSphere(Box.GetCenter(), 0);
        for (INT i = 0; i < Count; i++)
        {
            FLOAT Dist = FDistSquared(*this, Pts[i]);
            if (Dist > W)
                W = Dist;
        }
        W = (FLOAT)sqrt(W) * 1.001f;
    }
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
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_50ac0(FSphere *Out, const FVector *P, INT C) { new(Out) FSphere(P, C); }
void Driver_50d30(const FVector *V, FVector *Out) { FVector N = V->SafeNormal(); Escape(&N); }
// FBox::operator+= (retail 0x4f820, outside this item; also matches byte for
// byte). An invalid box is marked by Min.X - Max.X == 1.
template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
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
