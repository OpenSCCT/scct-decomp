// campaign_leaf_182b00.cpp -- AActor::execIsPlaying
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execIsPlaying
void AActor::execIsPlaying(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_FINISH;
    if (Sound)
    {
        UAudioSubsystem *Audio = XLevel->Engine->Audio;
        if (Audio)
        {
            *(DWORD *)Result = Audio->IsPlaying(this, Sound);
            return;
        }
    }
    *(DWORD *)Result = 0;
}
