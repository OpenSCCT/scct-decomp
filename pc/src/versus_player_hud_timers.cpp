#include "versus_spy_hud.h"
#include "versus_pawn_action_events.h"
#include "versus_game_replication_info.h"

INT appSprintf(TCHAR *Dest, const TCHAR *Format, ...);

void MgmPlayerHud::UpdateClock()
{
    if (!Controller->GameReplicationInfo)
        return;
    INT Minutes = Controller->GameReplicationInfo->TimeLimit - Controller->GameReplicationInfo->ElapsedTime / 60 - 1;
    if (Minutes < 0) {
        if (Clock->Visible)
            Clock->SetVisible(0, 1);
        return;
    }
    if (Minutes == 0 && !ClockActive) {
        ClockActive = 1;
        Clock->SetFrame(70, 1);
        Clock->SetPlaying(1);
    }
    if (!Clock->Visible)
        Clock->SetVisible(1, 1);
    appSprintf(ClockLabel, L"%u:%02u", Minutes, 59 - Controller->GameReplicationInfo->ElapsedTime % 60);
    ClockText->SetExternalText(ClockLabel);
}
