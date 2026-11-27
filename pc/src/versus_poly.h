#ifndef VERSUS_POLY_H
#define VERSUS_POLY_H

struct FPlane;
extern const FVector &GMath_Zero;

class FPoly
{
public:
    enum { MAX_VERTICES = 16, VERTEX_THRESHOLD = MAX_VERTICES - 2 };

    FVector Base;                   // +0x00
    FVector Normal;                 // +0x0C
    FVector Vertex[MAX_VERTICES];   // +0x18
    DWORD   PolyFlags;              // +0xD8
    DWORD   Unknown_dc;             // +0xDC
    _WORD   NumVertices;            // +0xE0

    void Init()
    {
        Base        = GMath_Zero;
        Normal      = GMath_Zero;
        PolyFlags   = 0;
        Unknown_dc  = 0;
        NumVertices = 0;
    }
    FLOAT Area();
    INT SplitWithPlaneFast(const FPlane &Plane, FPoly *FrontPoly, FPoly *BackPoly) const;
    INT Split(const FVector &Normal, const FVector &Base, INT NoOverflow);
};

#endif
