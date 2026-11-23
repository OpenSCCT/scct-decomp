// campaign_leaf_104340.cpp -- AController::execFinishRotation
#include "unreal_script.h"
#include "unreal_pawn.h"

// AController::execFinishRotation
void AController::execFinishRotation(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    StateFrame->LatentAction = EPOLL_509;
}
