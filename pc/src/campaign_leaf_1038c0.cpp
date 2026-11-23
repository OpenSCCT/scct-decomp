// campaign_leaf_1038c0.cpp -- AController::execAddController
#include "unreal_script.h"
#include "unreal_pawn.h"
#include "campaign_level_info.h"

// AController::execAddController
void AController::execAddController(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    NextController = Level->ControllerList;
    Level->ControllerList = this;
}
