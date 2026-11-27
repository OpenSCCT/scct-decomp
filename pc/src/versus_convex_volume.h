#ifndef VERSUS_CONVEX_VOLUME_H
#define VERSUS_CONVEX_VOLUME_H

#include "versus_plane.h"
#include "versus_poly.h"

class FConvexVolume
{
public:
    enum { MaxPlanes = 32 };
    FPlane BoundingPlanes[MaxPlanes];
    INT NumPlanes;

    FConvexVolume() : NumPlanes(0) {}
    FPoly ClipPolygon(FPoly Polygon) const;
};

struct FLightFrustum
{
    FVector Vertices[8];
    FPlane Planes[6];
};

#endif
