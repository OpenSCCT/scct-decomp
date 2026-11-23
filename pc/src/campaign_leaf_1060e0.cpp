// campaign_leaf_1060e0.cpp -- AController::execCanSee
#include "unreal_script.h"
#include "unreal_pawn.h"

// AController::execCanSee
void AController::execCanSee(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(APawn, Other);
    P_FINISH;
    *(DWORD *)Result = CanSee(Other, 0);
}
