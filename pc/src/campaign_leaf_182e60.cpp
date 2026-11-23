// campaign_leaf_182e60.cpp -- AActor::execStopAllSoundsType
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execStopAllSoundsType
void AActor::execStopAllSoundsType(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(Type);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->StopAllSoundsType(Type);
}
