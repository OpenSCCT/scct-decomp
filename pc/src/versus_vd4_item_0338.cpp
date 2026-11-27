// Work item 0338: Versus RVA 0x92b40-0x92db2.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }

// Neutral name: an object holding a period-like divisor at 0x10c and a
// counter at 0x110 (evidence too thin for an Unreal name).
struct UnnamedTick_92b40
{
    char Pad[0x10c];
    DWORD Period;   // 0x10c
    DWORD Counter;  // 0x110
};

// Neutral name for the thiscall owner at 0x92b40.
class UnnamedClass_92b40
{
public:
    char Pad[0x24];
    UnnamedTick_92b40 *Current; // 0x24
    UBOOL IsInPhase(UnnamedTick_92b40 *Other);
};

// RVA 0x92b40
UBOOL UnnamedClass_92b40::IsInPhase(UnnamedTick_92b40 *Other)
{
    if (Other && Current != Other)
        return Current->Counter % Other->Period == 0;
    return 1;
}

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    const TCHAR *operator*() const { return Num() ? Data : L""; }
    UBOOL operator!=(const FString &Other) const;
};

// RVA 0x92bf0
UBOOL FString::operator!=(const FString &Other) const
{
    return appStricmp(**this, *Other) != 0;
}

// Neutral name: an actor-like object with flag words at 0x2f0/0x2f4
// (LTCG: this arrives in EAX). Bit meanings are not recovered.
class UnnamedActor_92b80
{
public:
    char Pad0[0x100];
    void *Ref100;        // 0x100
    char Pad1[0x238 - 0x104];
    void *Ref238;        // 0x238
    char Pad2[0x2f0 - 0x23c];
    DWORD Flags2F0;      // 0x2f0
    DWORD Flags2F4;      // 0x2f4
    UBOOL CheckA();
    UBOOL CheckB();
};

// RVA 0x92b80
UBOOL UnnamedActor_92b80::CheckA()
{
    return (Flags2F0 & 0x1000) && Ref100 && (Flags2F4 & 0x4000);
}

// RVA 0x92bb0
UBOOL UnnamedActor_92b80::CheckB()
{
    return Ref238 && (Flags2F4 & 0x2000);
}

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FLOAT operator|(const FVector &V) const { return X*V.X + Y*V.Y + Z*V.Z; }
    FVector TransformVectorBy(const class FCoords &Coords) const;
};

class FCoords
{
public:
    FVector Origin, XAxis, YAxis, ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords &operator*=(const FCoords &Coords);
    FCoords operator*(const FCoords &Coords) const;
    FCoords Transpose() const;
};

// Retail helper at 0x40ab0 (cdecl, writes the result through Out).
void TransformVectorByCoords(const FCoords &Coords, const FVector &V, FVector &Out);

inline FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Result;
    TransformVectorByCoords(Coords, *this, Result);
    return Result;
}

// RVA 0x92c40
FCoords FCoords::Transpose() const
{
    return FCoords
    (
        -Origin.TransformVectorBy(*this),
        FVector(XAxis.X, YAxis.X, ZAxis.X),
        FVector(XAxis.Y, YAxis.Y, ZAxis.Y),
        FVector(XAxis.Z, YAxis.Z, ZAxis.Z)
    );
}

// RVA 0x92d00
FCoords FCoords::operator*(const FCoords &Coords) const
{
    return FCoords(*this) *= Coords;
}

// Scaffolding for the link, not part of the unit.
UBOOL Driver_92b80(UnnamedActor_92b80 *A) { return A->CheckA(); }
UBOOL Driver_92bb0(UnnamedActor_92b80 *A) { return A->CheckB(); }
void Driver_92c40(FCoords *Out, const FCoords *C) { *Out = C->Transpose(); }
void Driver_92d00(FCoords *Out, const FCoords *C, const FCoords *Transform) { *Out = *C * *Transform; }
