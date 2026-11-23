// campaign_leaf_105190.cpp -- APlayerController::execResetKeyboard
#include "unreal_script.h"
#include "unreal_class.h"
#include "unreal_pawn.h"
#include "campaign_player.h"

// APlayerController::execResetKeyboard
void APlayerController::execResetKeyboard(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UViewport *Viewport = Cast<UViewport>(Player);
    if (Viewport && Viewport->unk_5c)
        ResetConfig(Viewport->unk_5c->GetClass(), L"", 1);
}
