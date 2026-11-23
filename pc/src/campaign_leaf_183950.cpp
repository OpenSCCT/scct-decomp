// campaign_leaf_183950.cpp -- AActor::execStartFadeOut
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execStartFadeOut
// The parameter is named by position; the script declaration is not decoded yet.
void AActor::execStartFadeOut(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Option1);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->StartFadeOut(Option1);
}
