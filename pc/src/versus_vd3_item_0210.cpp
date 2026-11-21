// Work item 0210: Versus RVA 0x52270-0x524ed.
// Point-to-segment / point-to-line distance helpers (UnMath, Core). Compiled
// with LTCG: the linker passes the vectors in EAX, ECX and EDX (and the out
// parameter of the third in ESI). Names are neutral; no symbol evidence.
typedef float FLOAT;
typedef int INT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT S) const { return FVector(X * S, Y * S, Z * S); }
    FVector operator-=(const FVector &V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
};

// RVA 0x52270: distance from Point to the segment Start-End.
FLOAT PointSegmentDist_52270(const FVector &Start, const FVector &Point, const FVector &End)
{
    FVector Delta = Point - Start;
    FVector Dir = End - Start;
    FLOAT Dot = Dir | Delta;
    if (Dot > 0.f) {
        FLOAT LenSq = Dir.SizeSquared();
        if (Dot >= LenSq)
            Delta -= Dir;
        else
            Delta -= Dir * (Dot / LenSq);
    }
    return Delta.Size();
}

// RVA 0x52350: distance from Point to the infinite line through Start and End.
FLOAT PointLineDist_52350(const FVector &Start, const FVector &Point, const FVector &End)
{
    FVector Delta = Point - Start;
    FVector Dir = End - Start;
    FLOAT T = (Dir | Delta) / Dir.SizeSquared();
    Delta -= Dir * T;
    return Delta.Size();
}

// RVA 0x52400: distance from Point to the segment Start-End; T receives the
// clamped parameter of the closest point along the segment.
FLOAT PointSegmentDist_52400(const FVector &Start, const FVector &End, const FVector &Point, FLOAT &T)
{
    FVector Delta = Point - Start;
    FVector Dir = End - Start;
    FLOAT Dot = Dir | Delta;
    T = Dot;
    if (Dot > 0.f) {
        if (Dot >= Dir.SizeSquared()) {
            T = 1.f;
            Delta -= Dir;
        } else {
            T = Dot / Dir.SizeSquared();
            Delta -= Dir * T;
        }
    } else {
        T = 0.f;
    }
    return Delta.Size();
}

// Scaffolding for the link, not part of the unit.
FLOAT Driver_52270(const FVector &A, const FVector &P, const FVector &B)
{
    return PointSegmentDist_52270(A, P, B);
}
FLOAT Driver_52350(const FVector &A, const FVector &P, const FVector &B)
{
    return PointLineDist_52350(A, P, B);
}
FLOAT Driver_52400(const FVector &A, const FVector &P, const FVector &B, FLOAT &T)
{
    return PointSegmentDist_52400(A, B, P, T);
}
