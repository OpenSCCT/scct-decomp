#include "versus_spy_hud.h"
#include "versus_pawn_action_events.h"
#include "versus_game_replication_info.h"
#include "versus_mgm_localize.h"

INT appSprintf(TCHAR *Dest, const TCHAR *Format, ...);

void MgmPlayerHud::UpdateObjective()
{
    if (!Controller->GameReplicationInfo || !Controller->PlayerReplicationInfo)
        return;
    if (!Objective->Visible)
        Objective->SetVisible(1, 1);

    if (Controller->GameReplicationInfo->GameMode == GM_DeathMatch) {
        if (Controller->GameReplicationInfo->TotalTeamLives[0] +
            Controller->GameReplicationInfo->TotalTeamLives[1] != LastObjectiveCount) {
            LastObjectiveCount = Controller->GameReplicationInfo->TotalTeamLives[0] +
                                 Controller->GameReplicationInfo->TotalTeamLives[1];
            Objective->SetFrame(0, 1);
            Objective->SetPlaying(1);
        }
        const INT InfiniteLives = 1000;
        if (Controller->GameReplicationInfo->TotalTeamLives[0] > InfiniteLives &&
            Controller->GameReplicationInfo->TotalTeamLives[1] < InfiniteLives) {
            appSprintf(ObjectiveLabel, L"%s/%u", LocalizeMgm(NAME_Inifite_Short),
                       Controller->GameReplicationInfo->TotalTeamLives[1]);
        } else if (Controller->GameReplicationInfo->TotalTeamLives[0] < InfiniteLives &&
                   Controller->GameReplicationInfo->TotalTeamLives[1] > InfiniteLives) {
            appSprintf(ObjectiveLabel, L"%u/%s", Controller->GameReplicationInfo->TotalTeamLives[0],
                       LocalizeMgm(NAME_Inifite_Short));
        } else if (Controller->GameReplicationInfo->TotalTeamLives[0] > InfiniteLives &&
                   Controller->GameReplicationInfo->TotalTeamLives[1] > InfiniteLives) {
            appSprintf(ObjectiveLabel, L"%s/%s", LocalizeMgm(NAME_Inifite_Short), LocalizeMgm(NAME_Inifite_Short));
        } else {
            appSprintf(ObjectiveLabel, L"%u/%u", Controller->GameReplicationInfo->TotalTeamLives[0],
                       Controller->GameReplicationInfo->TotalTeamLives[1]);
        }
    } else if (Controller->GameReplicationInfo->GameMode == GM_DiskHunt) {
        if (Controller->eventGetObjectivesLeft() != LastObjectiveCount) {
            LastObjectiveCount = Controller->eventGetObjectivesLeft();
            Objective->SetFrame(0, 1);
            Objective->SetPlaying(1);
        }
        appSprintf(ObjectiveLabel, L"%u/%u",
                   Controller->GameReplicationInfo->NumDisks - Controller->eventGetObjectivesLeft(),
                   Controller->GameReplicationInfo->NumDisksToWin);
    } else {
        if (Controller->eventGetObjectivesLeft() != LastObjectiveCount) {
            LastObjectiveCount = Controller->eventGetObjectivesLeft();
            Objective->SetFrame(0, 1);
            Objective->SetPlaying(1);
        }
        appSprintf(ObjectiveLabel, L"%u", Controller->eventGetObjectivesLeft());
    }
    ObjectiveText->SetExternalText(ObjectiveLabel);
}
