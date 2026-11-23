// campaign_leaf_179fa0.cpp -- AActor::execPollSleep
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execPollSleep
// Latent poll: Result carries the frame's delta time in seconds.
void AActor::execPollSleep(FFrame &Stack, RESULT_DECL)
{
    FLOAT DeltaSeconds = *(FLOAT *)Result;
    if ((LatentFloat -= DeltaSeconds) < 0.5 * DeltaSeconds)
        StateFrame->LatentAction = 0;
}
