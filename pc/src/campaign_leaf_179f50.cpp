// campaign_leaf_179f50.cpp -- AActor::execFinishInterpolation
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execFinishInterpolation
void AActor::execFinishInterpolation(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    StateFrame->LatentAction = EPOLL_FinishInterpolation;
}
