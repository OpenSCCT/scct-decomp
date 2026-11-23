// campaign_leaf_1834a0.cpp -- AActor::execFlushRequests
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execFlushRequests
void AActor::execFlushRequests(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->FlushRequests(this);
}
