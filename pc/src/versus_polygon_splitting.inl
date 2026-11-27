// Work item 0209: Versus RVA 0xe7110-0xe7670.
// FPoly helpers (UnPoly / UnMath, Unreal Engine 2), compiled with /GL and
// linked with /LTCG: polygon area, the fast plane split and FPoly::Split.
// This FPoly is the slim SCCT layout: no texture vectors, 16 vertices,
// a word vertex count at +0xE0, total size 0xE4.

#include "versus_build.h"
#include "versus_level_trace_vector.h"
#include "versus_plane.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT FVector::Size() const { return (FLOAT)sqrt(SizeSquared()); }

#define THRESH_SPLIT_POLY_WITH_PLANE 0.25f

enum ESplitType
{
    SP_Coplanar = 0,
    SP_Front    = 1,
    SP_Back     = 2,
    SP_Split    = 3,
};

#include "versus_poly.h"

// RVA 0xe7670 (item 0210); defined here so LTCG gives it the retail convention.
__declspec(noinline) FVector FLinePlaneIntersection(const FVector &Point1, const FVector &Point2, const FPlane &Plane)
{
    return Point1 + (Point2 - Point1) * ((Plane.W - (Point1 | Plane)) / ((Point2 - Point1) | Plane));
}

// RVA 0xe7110
FLOAT FPoly::Area()
{
    FVector Side1, Side2;
    FLOAT Area;
    int i;
    Area  = 0.f;
    Side1 = Vertex[1] - Vertex[0];
    for (i = 2; i < NumVertices; i++)
    {
        Side2 = Vertex[i] - Vertex[0];
        Area += (Side1 ^ Side2).Size();
        Side1 = Side2;
    }
    return Area;
}

// RVA 0xe7200
INT FPoly::SplitWithPlaneFast(const FPlane &Plane, FPoly *FrontPoly, FPoly *BackPoly) const
{
    enum EPlaneClassification { V_FRONT = 0, V_BACK = 1 };
    int Front = 0, Back = 0;
    EPlaneClassification Status, PrevStatus;
    EPlaneClassification VertStatus[MAX_VERTICES];

    EPlaneClassification *StatusPtr = &VertStatus[0];
    for (int i = 0; i < NumVertices; i++)
    {
        FLOAT Dist = Plane.PlaneDot(Vertex[i]);
        if (Dist >= 0.f)
        {
            *StatusPtr++ = V_FRONT;
            if (Dist > +THRESH_SPLIT_POLY_WITH_PLANE)
                Front = 1;
        }
        else
        {
            *StatusPtr++ = V_BACK;
            if (Dist < -THRESH_SPLIT_POLY_WITH_PLANE)
                Back = 1;
        }
    }
    if (!Front)
    {
        if (Back) return SP_Back;
        else      return SP_Coplanar;
    }
    if (!Back)
    {
        return SP_Front;
    }
    else
    {
        if (FrontPoly)
        {
            const FVector *WrapVertex = &Vertex[NumVertices - 1];
            const FVector *V1         = &Vertex[0];
            FVector *F1               = &FrontPoly->Vertex[0];
            FVector *B1               = &BackPoly->Vertex[0];
            int Front_NumVertices     = 0;
            int Back_NumVertices      = 0;
            PrevStatus                = VertStatus[NumVertices - 1];
            StatusPtr                 = &VertStatus[0];

            for (int i = 0; i < NumVertices; i++)
            {
                Status = *StatusPtr++;
                if (Status != PrevStatus)
                {
                    // Crossing.
                    *F1++ = *B1++ = FLinePlaneIntersection(*WrapVertex, *V1, Plane);
                    if (PrevStatus == V_FRONT)
                    {
                        *B1++ = *V1;
                        Front_NumVertices++;
                        Back_NumVertices += 2;

                    }
                    else
                    {
                        *F1++ = *V1;
                        Back_NumVertices++;
                        Front_NumVertices += 2;

                    }
                }
                else if (Status == V_FRONT)
                {
                    *F1++ = *V1;
                    Front_NumVertices++;
                }
                else
                {
                    *B1++ = *V1;
                    Back_NumVertices++;
                }
                PrevStatus = Status;
                WrapVertex = V1++;
            }
            FrontPoly->NumVertices = Front_NumVertices;
            FrontPoly->Base        = Base;
            FrontPoly->Normal      = Normal;
            FrontPoly->PolyFlags   = PolyFlags;

            BackPoly->NumVertices  = Back_NumVertices;
            BackPoly->Base         = Base;
            BackPoly->Normal       = Normal;
            BackPoly->PolyFlags    = PolyFlags;
        }
        return SP_Split;
    }
}

// RVA 0xe74f0
INT FPoly::Split(const FVector &Normal, const FVector &Base, INT NoOverflow)
{
    if (NoOverflow && NumVertices >= VERTEX_THRESHOLD)
    {
        // Don't split it, just reject it.
        if (SplitWithPlaneFast(FPlane(Base, Normal), 0, 0) == SP_Back)
            return 0;
        else
            return NumVertices;
    }
    else
    {
        // Split it.
        FPoly Front, Back;
        Front.Init();
        Back.Init();
        switch (SplitWithPlaneFast(FPlane(Base, Normal), &Front, &Back))
        {
            case SP_Back:
                return 0;
            case SP_Split:
                *this = Front;
                return NumVertices;
            default:
                return NumVertices;
        }
    }
}
