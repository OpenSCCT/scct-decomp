#ifndef VERSUS_FRUSTUM_QUERY_H
#define VERSUS_FRUSTUM_QUERY_H

#include "versus_build.h"
#include "unreal_types.h"

struct FLightFrustum;
class FConvexVolume;

UBOOL IntersectsFrustumFaces(const FLightFrustum &Frustum, const FConvexVolume &Volume);

#endif
