// Work item 0152: FVector arithmetic members (UE2 UnMath.h).
// 0x40680-0x40710 come from an LTCG object (this in ECX, vector argument in EDX,
// hidden return pointer in EAX); they match with try_ltcg.py at /O2 /Gy /Ob1.
// The explicit member-wise copy constructor is what makes "return *this"
// copy through EDX the way retail does.
typedef float FLOAT;
typedef int INT;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
inline double appSqrt(double Value) { return sqrt(Value); }

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-() const;
    FVector operator+=(const FVector &V);
    FVector operator-=(const FVector &V);
    FVector operator*=(FLOAT Scale);
    FVector operator/=(FLOAT V);
    FLOAT Size() const;
};

// 0x40660
FVector FVector::operator-() const
{
    return FVector(-X, -Y, -Z);
}

// 0x40680
FVector FVector::operator+=(const FVector &V)
{
    X += V.X; Y += V.Y; Z += V.Z;
    return *this;
}

// 0x406b0
FVector FVector::operator-=(const FVector &V)
{
    X -= V.X; Y -= V.Y; Z -= V.Z;
    return *this;
}

// 0x406e0
FVector FVector::operator*=(FLOAT Scale)
{
    X *= Scale; Y *= Scale; Z *= Scale;
    return *this;
}

// 0x40710
FVector FVector::operator/=(FLOAT V)
{
    FLOAT RV = 1.0f / V;
    X *= RV; Y *= RV; Z *= RV;
    return *this;
}

// 0x40750
FLOAT FVector::Size() const
{
    return (FLOAT)appSqrt(X * X + Y * Y + Z * Z);
}

// Scaffolding for the LTCG link, not part of the unit.
void Driver_40680(FVector *A, const FVector *B) { *A += *B; }
void Driver_406b0(FVector *A, const FVector *B) { *A -= *B; }
void Driver_406e0(FVector *A, FLOAT S) { *A *= S; }
void Driver_40710(FVector *A, FLOAT S) { *A /= S; }
