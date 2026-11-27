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
template<class T> struct TList;

struct FLevelRenderState {
    FLevelSceneNode *SceneNode;
    FRenderInterface *RI;
    ULevel *Level;
    UModel *Model;
    BYTE unk_10[0x244 - 0x10];
    TList<FDynamicActor *> *Actors;
    TList<FDynamicActor *> *RegularActors;
    TList<FDynamicActor *> *LightFriendlyActors;
    TList<FDynamicActor *> *StaticActors;
    FTranslucentListNode *Translucent;
    TList<FDynamicActor *> *PostActors;
    DWORD unk_25c;
    TList<FDynamicActor *> *AdditionalActors;
    BYTE unk_264[0x280 - 0x264];
    FBspDrawList **SectionDrawLists;
    TList<INT> *SectionList;
    TList<class FDynamicLight *> **SectionProjectors;
    FDynamicLightList **SectionLights;

    void DrawActor(FDynamicActor *Actor, UBOOL UpdateLights, INT Pass = 1);
};

#endif
