// campaign_leaf_1837e0.cpp -- AActor::execResumeSound
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execResumeSound
// The parameter is named by position; the script declaration is not decoded yet.
void AActor::execResumeSound(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(Option1);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
    {
        if (Option1)
            Audio->VirtualSlot58();
        else
            Audio->VirtualSlot57();
    }
}
