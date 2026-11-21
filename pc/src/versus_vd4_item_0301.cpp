// Work item 0301: Versus RVA 0x7c470.
// FCoords::operator+(const FVector&): translate the origin, keep the axes.
// Built with VC7.0 /GL and linked /LTCG: `this` in ECX, the point in EDX and
// the hidden return pointer in EAX.

typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+=(const FVector &V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }
};

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords operator+(const FVector &Point) const;
};

// RVA 0x7c470
__declspec(noinline) FCoords FCoords::operator+(const FVector &Point) const
{
    FCoords Result(*this);
    Result.Origin += Point;
    return Result;
}

// Scaffolding for the link, not part of the unit.
void Driver_7c470(const FCoords *C, const FVector *P, FCoords *Out) { *Out = *C + *P; }
