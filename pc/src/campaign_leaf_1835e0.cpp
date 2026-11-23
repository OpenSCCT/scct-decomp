// campaign_leaf_1835e0.cpp -- AActor::execGetVolumeLineValue
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execGetVolumeLineValue
void AActor::execGetVolumeLineValue(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Line);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        *(FLOAT *)Result = Audio->GetVolumeLineValue(Line);
    else
        *(FLOAT *)Result = 0.0f;
}
