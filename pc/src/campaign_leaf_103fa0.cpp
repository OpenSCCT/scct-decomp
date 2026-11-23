// campaign_leaf_103fa0.cpp -- AController::execClearPaths
#include "unreal_script.h"
#include "unreal_pawn.h"

// AController::execClearPaths
void AController::execClearPaths(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (Pawn)
        Pawn->ClearPaths();
}
