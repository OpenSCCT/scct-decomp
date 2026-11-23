// campaign_leaf_17bd00.cpp -- AActor::execGetSoundDuration
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_native_classes.h"

// AActor::execGetSoundDuration
void AActor::execGetSoundDuration(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_FINISH;
    if (Sound)
        *(FLOAT *)Result = Sound->GetDuration();
    else
        *(FLOAT *)Result = 0.0f;
}
