// campaign_leaf_103900.cpp -- AController::execRemoveController
#include "unreal_script.h"
#include "unreal_pawn.h"
#include "campaign_level_info.h"

// AController::execRemoveController
void AController::execRemoveController(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    AController *Next = Level->ControllerList;
    if (Next == this)
        Level->ControllerList = Next->NextController;
    else
    {
        while (Next)
        {
            if (Next->NextController == this)
            {
                Next->NextController = NextController;
                break;
            }
            Next = Next->NextController;
        }
    }
}
