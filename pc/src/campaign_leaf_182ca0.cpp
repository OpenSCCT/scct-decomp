// campaign_leaf_182ca0.cpp -- AActor::execNotifyAudioEndConversation
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execNotifyAudioEndConversation
void AActor::execNotifyAudioEndConversation(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->NotifyAudioEndConversation(this);
}
