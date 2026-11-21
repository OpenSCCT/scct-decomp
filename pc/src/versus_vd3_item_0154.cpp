// Work item 0154: Versus RVA 0x40910-0x40b91.
// Core math helpers: FRotator::operator+=, a sine/cosine helper for Unreal
// rotation units, and FVector transforms by FCoords.

typedef int INT;
typedef float FLOAT;


struct FCoords;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector TransformPointBy(const FCoords &Coords) const;
    FVector TransformVectorBy(const FCoords &Coords) const;
};

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator operator+=(const FRotator &R)
    {
        Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
        return *this;
    }
};

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, cos, fabs)

extern const FLOAT RotationToRadians_4095; // 0x10c10a84
extern const FLOAT InvTwoPi_4095;          // 0x10c10c64
extern const FLOAT TwoPi_4095;             // 0x10c10c38
extern const FLOAT HalfPi_4095;            // 0x10c10c60

inline FLOAT Sgn(FLOAT A)
{
    return A < 0.f ? -1.f : (A > 0.f ? 1.f : 0.f);
}

// RVA 0x40950: cosine of an Unreal rotation angle, with the sine rebuilt from
// it and the sign of the angle wrapped into (-pi, pi].
void __stdcall SinCos_40950(INT Angle, FLOAT *OutSin, FLOAT *OutCos)
{
    FLOAT Rad = Angle * RotationToRadians_4095;
    FLOAT Wrapped = Rad - (INT)(Rad * InvTwoPi_4095) * TwoPi_4095;
    FLOAT C = (FLOAT)cos(Rad);
    *OutCos = C;
    FLOAT Sign;
    if ((FLOAT)fabs(Wrapped) < HalfPi_4095)
        Sign = Sgn(Wrapped);
    else
        Sign = -Sgn(Wrapped);
    *OutSin = (FLOAT)sqrt(1.f - C * C) * Sign;
}

// RVA 0x40a30 and 0x40ab0 are UnMath.h's ASMTransformPoint and
// ASMTransformVector: their bodies are whole __asm blocks in the original
// (esi = vector, edx = coords, edi = result), so they are declared here and
// not reproduced in C.
void ASMTransformPoint(const FCoords &Coords, const FVector &InVector, FVector &OutVector);
void ASMTransformVector(const FCoords &Coords, const FVector &InVector, FVector &OutVector);

// RVA 0x40b20
FVector FVector::TransformPointBy(const FCoords &Coords) const
{
    FVector Temp;
    ASMTransformPoint(Coords, *this, Temp);
    return Temp;
}

// RVA 0x40b60
FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Temp;
    ASMTransformVector(Coords, *this, Temp);
    return Temp;
}

// RVA 0x40910 is the out-of-line FRotator::operator+= (LTCG register call).
// Scaffolding for the link, not part of the unit.
#pragma inline_depth(0)
void Driver_40910(FRotator *A, const FRotator *B, FRotator *Out)
{
    *Out = (*A += *B);
}
