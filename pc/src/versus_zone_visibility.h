#ifndef VERSUS_ZONE_VISIBILITY_H
#define VERSUS_ZONE_VISIBILITY_H

#include "versus_frustum_query.h"
#include "versus_scene_list.h"

class FBox;
class FSphere;

struct FZoneVisibility {
    TList<FConvexVolume *> *Portals;
    TList<FConvexVolume *> *AntiPortals;

    UBOOL FilterBox(const FBox &Box) const;
    UBOOL FilterSphere(const FSphere &Sphere) const;
    UBOOL FilterBounds(const FLightFrustum &Frustum) const;
};

#endif
