#include "versus_spy_hud.h"
#include "versus_pawn_action_events.h"
#include "versus_game_replication_info.h"

struct MgmAreaContent : MgmContent {
    BYTE UnknownBeforeArea[0x10 - sizeof(MgmContent)];
    MgmArea *Area;
};

bool MgmPlayerHud::UpdateScreen(INT Message, INT Argument)
{
    UpdateGauge();
    UpdateGadget();
    UpdateClock();
    UpdateObjective();
    UpdateHackTimer();
    UpdateAlarmTimer();
    UpdateRadar();
    UpdateMessages();
    UpdateBallistic();
    UpdateSpeak();
    UpdateRadarTrap();
    UpdateConnectedPlayers();

    if (Controller->GameReplicationInfo && Controller->PlayerReplicationInfo && Active) {
        Active = 0;
        for (INT i = 0; i < Page->NumChildren(); ++i) {
            MgmArea *Child = static_cast<MgmAreaContent *>(Page->Children[i]->Content)->Area;
            Child->SetTime(0, 1);
            Child->SetPlaying(0);
        }
        Radar->SetPlaying(1);
        Page->SetVisible(1, 1);
    }
    UpdateTutorialMessage();
    return false;
}
