// campaign_leaf_183550.cpp -- AActor::execSetVolumeLineValue
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execSetVolumeLineValue
void AActor::execSetVolumeLineValue(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Line);
    P_GET_FLOAT(Value);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->SetVolumeLineValue(Line, Value);
}
