#include "versus_polygon_splitting.inl"
#include "versus_convex_volume.h"
#include "versus_frustum_query.h"

FPoly FConvexVolume::ClipPolygon(FPoly Polygon) const
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

INT GFrustumFaceVertices[6][4] = {
    {0, 1, 3, 2},
    {6, 0, 2, 4},
    {6, 7, 1, 0},
    {5, 7, 6, 4},
    {5, 4, 2, 3},
    {5, 3, 1, 7}
};

UBOOL IntersectsFrustumFaces(const FLightFrustum &Frustum, const FConvexVolume &Volume)
{
    FPoly Face;
    Face.NumVertices = 4;
    for (INT Side = 0; Side < 6; ++Side) {
        Face.Vertex[0] = Frustum.Vertices[GFrustumFaceVertices[Side][0]];
        Face.Vertex[1] = Frustum.Vertices[GFrustumFaceVertices[Side][1]];
        Face.Vertex[2] = Frustum.Vertices[GFrustumFaceVertices[Side][2]];
        Face.Vertex[3] = Frustum.Vertices[GFrustumFaceVertices[Side][3]];
        Face.Normal = Frustum.Planes[Side];
        Face.Base = Face.Vertex[0];
        FPoly Clipped;
        Clipped = Volume.ClipPolygon(Face);
        if (Clipped.NumVertices)
            return 1;
    }
    return 0;
}
