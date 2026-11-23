// campaign_leaf_182e20.cpp -- AActor::execStopAllSounds
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execStopAllSounds
void AActor::execStopAllSounds(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->StopAllSounds();
}
