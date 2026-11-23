// campaign_leaf_182f90.cpp -- AActor::execVerifyOcclusion
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execVerifyOcclusion
void AActor::execVerifyOcclusion(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->VerifyOcclusion();
}
