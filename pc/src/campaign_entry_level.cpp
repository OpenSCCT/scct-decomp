// campaign_entry_level.cpp -- the entry level exposed by the player controller
#include "unreal_script.h"
#include "unreal_pawn.h"
#include "campaign_engine_classes.h"

// APlayerController::execGetEntryLevel
void APlayerController::execGetEntryLevel(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(ALevelInfo **)Result = ((UGameEngine *)XLevel->Engine)->GEntry->GetLevelInfo();
}
