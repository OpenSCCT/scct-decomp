// campaign_leaf_179cf0.cpp -- AActor::execSleep
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execSleep
void AActor::execSleep(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Seconds);
    P_FINISH;
    StateFrame->LatentAction = EPOLL_Sleep;
    LatentFloat = Seconds;
}
