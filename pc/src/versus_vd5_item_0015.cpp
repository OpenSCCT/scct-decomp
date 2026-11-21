// Work item 0015 (w3): RVA 0x52000, an LTCG helper that intersects a ray with a
// triangle. Neutral name: no symbol evidence names it. Arguments in retail:
// ESI = Dir, EDI = Origin, ECX = plane normal, EDX = vertex A, EBX = vertex C,
// stack = vertex B, &T, &U, &V (caller cleans). Source order (Origin, Dir,
// A, B, C, Normal, T, U, V) is what makes the LTCG code match.
typedef float FLOAT;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

inline FLOAT Abs(FLOAT A) { return (A >= 0.f) ? A : -A; }

struct FVector
{
    FLOAT X, Y, Z;
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT &operator[](INT i) { return (&X)[i]; }
    const FVector operator*(FLOAT F) const;
};

UBOOL RayTriangleIntersect_52000(const FVector &Origin, const FVector &Dir,
                                 const FVector &A, const FVector &B, const FVector &C,
                                 const FVector &Normal, FLOAT &T, FLOAT &U, FLOAT &V)
{
    FLOAT Denom = Dir | Normal;
    if (Denom > -0.0001f && Denom < 0.0001f)
        return 0;
    T = ((Normal | A) - (Origin | Normal)) / Denom;
    if (T < 0.f)
        return 0;

    // Project onto the plane that drops the normal's dominant axis.
    FLOAT AX = Abs(Normal.X);
    FLOAT AY = Abs(Normal.Y);
    FLOAT AZ = Abs(Normal.Z);
    INT I0, I1;
    if (AX > AY && AX > AZ) { I0 = 1; I1 = 2; }
    else if (AY > AZ)       { I0 = 2; I1 = 0; }
    else                    { I0 = 0; I1 = 1; }

    const FLOAT *O = &Origin.X, *D = &Dir.X, *PA = &A.X, *PB = &B.X, *PC = &C.X;
    FLOAT P0 = T * D[I0] + O[I0] - PA[I0];
    FLOAT P1 = T * D[I1] + O[I1] - PA[I1];
    FLOAT B0 = PB[I0] - PA[I0];
    FLOAT B1 = PB[I1] - PA[I1];
    FLOAT C0 = PC[I0] - PA[I0];
    FLOAT C1 = PC[I1] - PA[I1];

    if (B0 < -0.0001f || B0 > 0.0001f)
    {
        V = (B0 * P1 - B1 * P0) / (C1 * B0 - C0 * B1);
        if (V < 0.f || V > 1.f)
            return 0;
        U = (P0 - V * C0) / B0;
    }
    else
    {
        V = P0 / C0;
        if (V < 0.f || V > 1.f)
            return 0;
        U = (P1 - V * C1) / B1;
    }
    if (U < 0.f || U + V > 1.f)
        return 0;
    return 1;
}

// Scaffolding for the link, not part of the unit.
UBOOL Sink(UBOOL);
void Driver_52000(const FVector &O, const FVector &D, const FVector &A, const FVector &B,
                  const FVector &C, const FVector &N, const FVector &N2, FLOAT &T, FLOAT &U, FLOAT &V)
{
    if (!RayTriangleIntersect_52000(O, D, A, B, C, N, T, U, V))
        Sink(RayTriangleIntersect_52000(O, D, A, B, N, N2, T, U, V));
}
