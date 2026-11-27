#ifndef VERSUS_DYNAMIC_LIGHT_H
#define VERSUS_DYNAMIC_LIGHT_H

#include "versus_light_frustum.h"
#include "versus_frustum_query.h"

class AActor;

class FDynamicLight {
public:
    AActor *Actor;
    INT Revision;
    FPlane Color;
    FVector Position, Direction;
    FLOAT Radius;
    BITFIELD Dynamic : 1;
    BITFIELD Changed : 1;
    BITFIELD unk_34_b2 : 2;
    BITFIELD InLightList : 1;
    BITFIELD unk_34_b5 : 1;
    BITFIELD unk_34_b6 : 1;
    BITFIELD unk_34_b7 : 1;
    BITFIELD Visible : 1;
    BITFIELD unk_34_b9 : 23;
    INT unk_38;
    FLOAT Alpha;
};

// LE_ESpotShadow allocates the extended 0x2a4-byte render data object.
class FSpotShadowLight : public FDynamicLight {
public:
    INT ShadowSlot;
    BYTE unk_44[0x50 - 0x44];
    FLightFrustum Frustum;
    BYTE unk_110[0x298 - 0x110];
    TArray<INT> Zones;
};

struct FDynamicLightList {
    FDynamicLight *Light;
    FDynamicLightList *Next;

    FDynamicLightList(FDynamicLight *InLight, FDynamicLightList *InNext)
        : Light(InLight), Next(InNext) {}
};

struct FLevelRenderState;
UBOOL IsLightVisibleInContext(FSpotShadowLight *Light, FLevelRenderState *Context, const FConvexVolume &ViewVolume);

#endif
