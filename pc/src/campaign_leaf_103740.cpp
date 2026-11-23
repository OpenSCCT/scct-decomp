// campaign_leaf_103740.cpp -- APlayerController::execSetViewTarget
#include "unreal_script.h"
#include "unreal_pawn.h"

// APlayerController::execSetViewTarget
void APlayerController::execSetViewTarget(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, NewViewTarget);
    P_FINISH;
    if (NewViewTarget)
        ViewTarget = NewViewTarget;
    else if (Pawn && !(Pawn->unk_28 & 4))
        ViewTarget = Pawn;
    else
        ViewTarget = this;
}
