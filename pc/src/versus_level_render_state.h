#ifndef VERSUS_LEVEL_RENDER_STATE_H
#define VERSUS_LEVEL_RENDER_STATE_H

#include "versus_build.h"
#include "unreal_types.h"

class FBspDrawList;
class FLevelSceneNode;
class FRenderInterface;
class ULevel;
class UModel;
struct FDynamicActor;
struct FDynamicLightList;
struct FTranslucentListNode;
#include "versus_zone_visibility.h"
#include "versus_dynamic_actor.h"

struct FLevelRenderState {
    FLevelSceneNode *SceneNode;
    FRenderInterface *RI;
    ULevel *Level;
    UModel *Model;
    BYTE unk_10[0x1c - 0x10];
    TList<AActor *> *LightActors;
    TList<class FSpotShadowLight *> *SpotShadowLights;
    FZoneVisibility Zones[64];
    TList<INT> *VisibleZones;
    BYTE unk_228[0x244 - 0x228];
    TList<FDynamicActor *> *Actors;
    TList<FDynamicActor *> *RegularActors;
    TList<FDynamicActor *> *LightFriendlyActors;
    TList<FDynamicActor *> *StaticActors;
    FTranslucentListNode *Translucent;
    TList<FDynamicActor *> *PostActors;
    DWORD unk_25c;
    TList<FDynamicActor *> *AdditionalActors;
    BYTE unk_264[4];
    TList<FDynamicActor *> *LightBeamActors;
    BYTE unk_26c[0x280 - 0x26c];
    FBspDrawList **SectionDrawLists;
    TList<INT> *SectionList;
    TList<class FDynamicLight *> **SectionProjectors;
    FDynamicLightList **SectionLights;

    void DrawActor(FDynamicActor *Actor, UBOOL UpdateLights, INT Pass = 1);
};

#endif
