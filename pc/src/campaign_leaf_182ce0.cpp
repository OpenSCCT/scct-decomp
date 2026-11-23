// campaign_leaf_182ce0.cpp -- AActor::execIsAConversationPlaying
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execIsAConversationPlaying
void AActor::execIsAConversationPlaying(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        *(DWORD *)Result = Audio->IsAConversationPlaying(this);
    else
        *(DWORD *)Result = 0;
}
