#include "versus_spy_hud.h"
#include "versus_pawn_action_events.h"
#include "versus_scene_level_types.h"
#include "versus_hud_objective_types.h"
#include "versus_mgm_hud_context.h"

INT appSprintf(TCHAR *Dest, const TCHAR *Format, ...);

void MgmPlayerHud::UpdateTutorialMessage()
{
    if (Hud->sTutoMap.Len() >= 4 &&
        GetMgmPlayerController()->GetLevel()->GetLevelInfo()->NetMode == NM_Standalone) {
        // The x86 variadic call passes the FString by value. Its first word supplies the %s buffer.
        appSprintf(TutorialLabel, L"%s", Hud->sTutoMap);
        if (!TutorialMessage->Visible) {
            TutorialMessage->SetVisible(1, 1);
            TutorialMessage->SetTime(0, 1);
            TutorialMessage->SetPlaying(1);
        }
    } else {
        appSprintf(TutorialLabel, L"");
        if (TutorialMessage->Visible)
            TutorialMessage->SetVisible(0, 1);
    }
    TutorialMessageText->SetExternalText(TutorialLabel);
}
