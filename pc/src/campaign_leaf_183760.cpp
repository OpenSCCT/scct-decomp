// campaign_leaf_183760.cpp -- AActor::execPauseSound
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execPauseSound
// The parameter is named by position; the script declaration is not decoded yet.
void AActor::execPauseSound(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(Option1);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
    {
        if (Option1)
            Audio->VirtualSlot56();
        else
            Audio->VirtualSlot55();
    }
}
