// Work item 0211: segment / line / sphere geometry helpers (UE2 UnMath style).
// All three come from an LTCG object (VC7.0 /GL): arguments arrive in
// registers and the results through ESI / EBX. Names are descriptive guesses;
// no symbol evidence names these functions.
typedef float FLOAT;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
inline double appSqrt(double Value) { return sqrt(Value); }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector &operator-=(const FVector &V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    FLOAT Size() const { return (FLOAT)appSqrt(X * X + Y * Y + Z * Z); }
    UBOOL Normalize(); // 0x4f7a0
};

// 0x52b10: closest point to Point on the segment Start-End.
void ClosestPointOnSegment(FVector &OutClosest, const FVector &Point, const FVector &Start, const FVector &End)
{
    FVector StartToPoint = Point - Start;
    FVector Segment = End - Start;
    FLOAT Dot = Segment | StartToPoint;
    if (Dot > 0.f)
    {
        FLOAT LengthSquared = Segment.SizeSquared();
        if (Dot >= LengthSquared)
            OutClosest = End;
        else
            OutClosest = Segment * (Dot / LengthSquared) + Start;
    }
    else
        OutClosest = Start;
}

// 0x52c20: distance from Point to the line through Origin and LinePoint;
// the closest point on the line is written to OutClosest.
FLOAT PointDistToLine(FVector &OutClosest, const FVector &Point, const FVector &LinePoint, const FVector &Origin)
{
    FVector Offset = Point - Origin;
    FVector Line = LinePoint - Origin;
    FVector Projected = Line * ((Line | Offset) / Line.SizeSquared());
    OutClosest = Projected + Origin;
    Offset -= Projected;
    return Offset.Size();
}

// 0x52d00: ray / sphere intersection; writes the hit distance along the ray.
UBOOL LineSphereIntersection(const FVector &Origin, const FVector &Center, const FVector &Direction, FLOAT Radius, FLOAT &OutTime)
{
    FVector Dir = Direction;
    Dir.Normalize();
    FVector Delta = Center - Origin;
    // Written out rather than Delta | Dir: this grouping is what reproduces retail's x87 stack order.
    FLOAT B = Dir.X * Delta.X + (Dir.Y * Delta.Y + Dir.Z * Delta.Z);
    FLOAT DistSquared = Delta | Delta;
    Radius = Radius * Radius;
    if (B < 0.f && DistSquared > Radius)
        return 0;
    FLOAT M = DistSquared - B * B;
    if (M > Radius)
        return 0;
    FLOAT Q = (FLOAT)appSqrt(Radius - M);
    if (DistSquared > Radius)
        OutTime = B - Q;
    else
        OutTime = B + Q;
    return 1;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_52b10(FVector *R, const FVector *P, const FVector *A, const FVector *B) { ClosestPointOnSegment(*R, *P, *A, *B); }
void Driver_52c20(FLOAT *D, const FVector *P, const FVector *A, const FVector *B, FVector *C) { *D = PointDistToLine(*C, *P, *A, *B); }
void Driver_52d00(UBOOL *R, const FVector *C, const FVector *O, const FVector *D, FLOAT Rad, FLOAT *T) { *R = LineSphereIntersection(*O, *C, *D, Rad, *T); }
