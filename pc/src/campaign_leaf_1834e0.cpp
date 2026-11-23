// campaign_leaf_1834e0.cpp -- AActor::execSetReverbEffect
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execSetReverbEffect
void AActor::execSetReverbEffect(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(Effect);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->SetReverbEffect(Effect, this);
}
