// campaign_leaf_103970.cpp -- AController::execWaitForLanding
#include "unreal_script.h"
#include "unreal_pawn.h"

// AController::execWaitForLanding
void AController::execWaitForLanding(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    LatentFloat = 4.0f;
    if (Pawn && Pawn->unk_4c == 2)
        StateFrame->LatentAction = EPOLL_528;
}
