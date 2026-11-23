// campaign_leaf_103880.cpp -- AController::execStopWaiting
#include "unreal_script.h"
#include "unreal_pawn.h"

// AController::execStopWaiting
void AController::execStopWaiting(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (StateFrame->LatentAction == EPOLL_Sleep)
        LatentFloat = -1.0f;
}
