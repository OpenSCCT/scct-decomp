#ifndef VERSUS_LIGHT_FRUSTUM_H
#define VERSUS_LIGHT_FRUSTUM_H

#include "versus_plane.h"

struct FLightFrustum
{
    FVector Vertices[8];
    FPlane Planes[6];
};

#endif
