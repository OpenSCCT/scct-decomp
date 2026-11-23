// campaign_leaf_182b90.cpp -- AActor::execIsPlayingAnyActor
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execIsPlayingAnyActor
void AActor::execIsPlayingAnyActor(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, Other);
    P_FINISH;
    if (Other)
    {
        UAudioSubsystem *Audio = XLevel->Engine->Audio;
        if (Audio)
        {
            *(DWORD *)Result = Audio->IsPlayingAnyActor(Other);
            return;
        }
    }
    *(DWORD *)Result = 0;
}
