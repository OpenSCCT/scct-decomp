// campaign_poll_interpolation.cpp -- latent completion of actor interpolation
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execPollFinishInterpolation
void AActor::execPollFinishInterpolation(FFrame &Stack, RESULT_DECL)
{
    if (!bInterpolating)
        StateFrame->LatentAction = 0;
}
