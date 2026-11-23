// campaign_leaf_183660.cpp -- AActor::execAddMaskingFadeOut
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execAddMaskingFadeOut
void AActor::execAddMaskingFadeOut(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->AddMaskingFadeOut(this);
}
