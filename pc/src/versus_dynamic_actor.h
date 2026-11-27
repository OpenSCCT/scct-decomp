#ifndef VERSUS_DYNAMIC_ACTOR_H
#define VERSUS_DYNAMIC_ACTOR_H

#include "versus_build.h"
#include "unreal_types.h"
#include "versus_scene_list.h"

class FLevelSceneNode;
class FRenderInterface;
class FProjectorRenderInfo;
struct FDynamicLightList;
class AActor;

struct FDynamicActor {
    AActor *Actor;
    INT Revision;
    FLOAT Determinant;
    BYTE unk_c[0xe8 - 0x0c];
    FDynamicLightList *Lights;
    DWORD unk_ec;
    FDynamicLightList *SectionLights;
    TList<FProjectorRenderInfo *> *Projectors;
    void UpdateLightFade(FLevelSceneNode *SceneNode);
    void Render(FLevelSceneNode *SceneNode, FDynamicLightList *InLights, void *InProjectors,
                FRenderInterface *RI, INT Pass, void *PostActors);
};


#endif
