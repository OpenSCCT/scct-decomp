// campaign_leaf_179f90.cpp -- AActor::execPollFinishSequence
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execPollFinishSequence
void AActor::execPollFinishSequence(FFrame &Stack, RESULT_DECL)
{
    StateFrame->LatentAction = 0;
}
