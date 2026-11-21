// Work item 0348: FConvexVolume helpers (Versus RVA 0x111050-0x111564).
// FConvexVolume layout (32 planes + count at 0x200) follows UE2's FConvexVolume.
// 0x111050 (FConvexVolume box check with an SSE path under GIsSSE) is not reproduced here.
// FConvexPoly is SCCT's clipping polygon (neutral name): two vectors, 16
// vertices, two dwords and a 16-bit vertex count, 0xe4 bytes in all.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned short _WORD;
typedef unsigned char BYTE;

class FVector {
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
};

class FPlane : public FVector {
public:
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane operator*(FLOAT Scale) const { return FPlane(X * Scale, Y * Scale, Z * Scale, W * Scale); }
};

#define FPOLY_MAX_VERTICES 16

class FConvexPoly {
public:
    FVector Base;
    FVector Normal;
    FVector Vertex[FPOLY_MAX_VERTICES];
    DWORD Flags;
    DWORD Extra;
    _WORD NumVertices;
    INT Split(const FVector &Normal, const FVector &Base, INT NoOverflow);
    INT SplitWithPlane(const FVector &Base, const FVector &Normal, FConvexPoly *Front, FConvexPoly *Back, INT VeryPrecise) const;
};

class FConvexVolume {
public:
    FPlane BoundingPlanes[32];
    INT NumPlanes;
    FConvexPoly ClipPolygon(FConvexPoly Polygon) const;
};

extern const FLOAT ClipPolygon_Threshold; // 0.001f

FConvexPoly FConvexVolume::ClipPolygon(FConvexPoly Polygon) const
{
    for (INT PlaneIndex = 0; PlaneIndex < NumPlanes; PlaneIndex++) {
        const FPlane &Plane = BoundingPlanes[PlaneIndex];
        if (!Polygon.Split(-FVector(Plane), Plane * Plane.W, 1)) {
            Polygon.NumVertices = 0;
            return Polygon;
        }
    }
    FVector *Dest = &Polygon.Vertex[1];
    FVector *End = &Polygon.Vertex[Polygon.NumVertices];
    for (FVector *Src = &Polygon.Vertex[1]; Src != End; Src++) {
        if ((*Src - Dest[-1]).SizeSquared() > 0.001f) {
            if (Src != Dest)
                *Dest = *Src;
            Dest++;
        }
    }
    Polygon.NumVertices = (_WORD)(Dest - Polygon.Vertex);
    return Polygon;
}

// Scaffolding for the link, not part of the unit: a stand-in body for
// FConvexPoly::Split (0x0e74f0, not in this item) so the linker sees it.
#pragma auto_inline(off)
INT FConvexPoly::Split(const FVector &Normal, const FVector &Base, INT NoOverflow)
{
    if (NoOverflow && NumVertices >= FPOLY_MAX_VERTICES)
        return 0;
    FVector N = Normal, B = Base;
    FConvexPoly Front, Back;
    switch (SplitWithPlane(B, N, &Front, &Back, 1)) {
    case 1: return 0;
    case 3: *this = Front; return NumVertices;
    default: return NumVertices;
    }
}
#pragma auto_inline(on)
void Escape(void *);
void Driver_111380(const FConvexVolume *V, FConvexPoly *Out, FConvexPoly *In)
{
    *Out = V->ClipPolygon(*In);
}
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_1114e0(FConvexPoly *Out, FConvexPoly *In)
{
    new (Out) FConvexPoly(*In);
}
