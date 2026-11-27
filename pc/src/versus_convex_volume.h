#ifndef VERSUS_CONVEX_VOLUME_H
#define VERSUS_CONVEX_VOLUME_H

#include "versus_level_trace_vector.h"
#include "versus_plane.h"
#include "versus_poly.h"

class FConvexVolume
{
public:
    FPlane BoundingPlanes[32];
    INT NumPlanes;

    FPoly ClipPolygon(FPoly Polygon) const;
};

struct FLightFrustum
{
    FVector Vertices[8];
    FPlane Planes[6];
};

#endif
