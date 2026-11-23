// campaign_leaf_1838e0.cpp -- AActor::execSetLaserMicSession
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execSetLaserMicSession
// The parameter is named by position; the script declaration is not decoded yet.
void AActor::execSetLaserMicSession(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Option1);
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->SetLaserMicSession(Option1);
}
