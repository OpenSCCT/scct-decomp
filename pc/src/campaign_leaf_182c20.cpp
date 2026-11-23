// campaign_leaf_182c20.cpp -- AActor::execStopAllVoicesActor
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execStopAllVoicesActor
// Parameters are named by position; the script declaration is not decoded yet.
void AActor::execStopAllVoicesActor(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Option1);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        *(DWORD *)Result = Audio->StopAllVoicesActor(this, Option1);
    else
        *(DWORD *)Result = 0;
}
