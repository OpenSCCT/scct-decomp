// campaign_leaf_182fd0.cpp -- AActor::execGetSoundPosition
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execGetSoundPosition
void AActor::execGetSoundPosition(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_FINISH;
    if (Sound)
    {
        UAudioSubsystem *Audio = XLevel->Engine->Audio;
        if (Audio)
        {
            *(FLOAT *)Result = Audio->GetSoundPosition(this, Sound);
            return;
        }
    }
    *(FLOAT *)Result = 0.0f;
}
