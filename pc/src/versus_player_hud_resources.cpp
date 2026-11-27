#include "versus_spy_hud.h"
#include "versus_mgm_bindings.h"
#include "versus_mgm_hud_context.h"
#include "versus_pawn_action_events.h"
#include "versus_game_replication_info.h"
#include "versus_registration_arrays.h"
#include "versus_array_growth.inl"

INT appSprintf(TCHAR *Dest, const TCHAR *Format, ...);
static inline MgmImage *GetMgmImage(MgmChild *Child)
{
    return static_cast<MgmImageContent *>(Child->Content)->Image;
}

void MgmPlayerHud::InitResources()
{
    Page->SetVisible(0, 1);
    Active = 1;
    ClockActive = 0;

    Gauge = FindMgmArea(Package, "A_Jauge");
    GaugeBar = &GetMgmImage(FindMgmChild(Gauge, "jaugeinterne"))->Region;
    GaugeLeft = &GetMgmImage(FindMgmChild(Gauge, "jaugeindicator_gauche"))->Region;
    GaugeRight = &GetMgmImage(FindMgmChild(Gauge, "jaugeindicator_droite"))->Region;
    PoisonGauge = FindMgmArea(Package, "jauge_poison");
    PoisonGauge->SetVisible(0, 1);
    GaugeHeight = 133.0f;
    ReferenceGaugeValue = 100.0f;
    GaugeSample = 0;

    Gadget = FindMgmArea(Package, "A_Gadget");
    Gadget->SetVisible(0, 1);
    GadgetIcon = FindMgmChild(Gadget, "Gadget")->Content;
    GadgetName = FindMgmChild(Gadget, "NomGadget")->Content;
    GadgetNumber = FindMgmChild(Gadget, "NbGadget")->Content;

    Clock = FindMgmArea(Package, "A_Chrono");
    ClockText = static_cast<MgmTextContent *>(FindMgmChild(Clock, "Chrono")->Content);
    if (Controller->GameReplicationInfo->GameMode == GM_DeathMatch) {
        FindMgmArea(Package, "A_Objectif")->SetVisible(0, 1);
        Objective = FindMgmArea(Package, "A_deathmatch");
        ObjectiveText = static_cast<MgmTextContent *>(FindMgmChild(Objective, "objectif")->Content);
    } else {
        FindMgmArea(Package, "A_deathmatch")->SetVisible(0, 1);
        Objective = FindMgmArea(Package, "A_Objectif");
        ObjectiveText = static_cast<MgmTextContent *>(FindMgmChild(Objective, "objectif")->Content);
    }

    HackTimer = FindMgmArea(Package, "A_ChronoHack");
    HackTimer->SetVisible(0, 1);
    HackTime = static_cast<MgmTextContent *>(FindMgmChild(HackTimer, "Chrono_Hack")->Content);
    ObjectiveTimers[0] = FindMgmArea(Package, "A_ChronoObjectif");
    ObjectiveTimers[0]->SetVisible(0, 1);
    ObjectiveTimes[0] = FindMgmChild(ObjectiveTimers[0], "Chrono_Objectif")->Content;
    ObjectiveTimers[1] = FindMgmArea(Package, "A_ChronoObjectif2");
    ObjectiveTimers[1]->SetVisible(0, 1);
    ObjectiveTimes[1] = FindMgmChild(ObjectiveTimers[1], "Chrono_Objectif2")->Content;
    AlarmTimer = FindMgmArea(Package, "A_ChronoAlarme");
    AlarmTimer->SetVisible(0, 1);
    AlarmTime = static_cast<MgmTextContent *>(FindMgmChild(AlarmTimer, "Chrono_Alarm")->Content);

    Options = FindMgmPackage(&GMgmMenuSystem->Packages, "Options");
    Ballistic = FindMgmArea(Package, "A_Ballistic");
    BallisticState = 0;
    Ballistic->SetVisible(0, 1);

    BindMgmArea(Radar, Package, "A_Radar");
    BindMgmArea(CompassBackground, Package, "FondBoussole");
    TArray<MgmChild *> &RadarTeammates = Teammates;
    RadarTeammates.ArrayNum = 0;
    TArray<MgmChild *> &RadarTeammatesHigher = TeammatesHigher;
    RadarTeammatesHigher.ArrayNum = 0;
    TArray<MgmChild *> &RadarTeammatesLower = TeammatesLower;
    RadarTeammatesLower.ArrayNum = 0;
    RadarTeammates.AddItem(FindMgmChild(Radar, "IconTeammate1"));
    RadarTeammatesHigher.AddItem(FindMgmChild(Radar, "IconTeammate1Higher"));
    RadarTeammatesLower.AddItem(FindMgmChild(Radar, "IconTeammate1Lower"));
    RadarTeammates.AddItem(FindMgmChild(Radar, "IconTeammate2"));
    RadarTeammatesHigher.AddItem(FindMgmChild(Radar, "IconTeammate2Higher"));
    RadarTeammatesLower.AddItem(FindMgmChild(Radar, "IconTeammate2Lower"));
    for (INT i = 0; i < 2; ++i) {
        RadarTeammates(i)->Visible = 0;
        RadarTeammatesHigher(i)->Visible = 0;
        RadarTeammatesLower(i)->Visible = 0;
    }

    RadarTeammateCount = 0;
    TArray<MgmChild *> &RadarEnemies = Enemies;
    RadarEnemies.ArrayNum = 0;
    TArray<MgmChild *> &RadarEnemiesHigher = EnemiesHigher;
    RadarEnemiesHigher.ArrayNum = 0;
    TArray<MgmChild *> &RadarEnemiesLower = EnemiesLower;
    RadarEnemiesLower.ArrayNum = 0;
    TArray<MgmChild *> &RadarEnemyArrows = EnemyArrows;
    RadarEnemyArrows.ArrayNum = 0;
    RadarEnemies.AddItem(FindMgmChild(Radar, "IconEnemy1"));
    RadarEnemiesHigher.AddItem(FindMgmChild(Radar, "IconEnemy1Higher"));
    RadarEnemiesLower.AddItem(FindMgmChild(Radar, "IconEnemy1Lower"));
    RadarEnemyArrows.AddItem(FindMgmChild(Radar, "IconEnemyArrow1"));
    RadarEnemies.AddItem(FindMgmChild(Radar, "IconEnemy2"));
    RadarEnemiesHigher.AddItem(FindMgmChild(Radar, "IconEnemy2Higher"));
    RadarEnemiesLower.AddItem(FindMgmChild(Radar, "IconEnemy2Lower"));
    RadarEnemyArrows.AddItem(FindMgmChild(Radar, "IconEnemyArrow2"));
    RadarEnemies.AddItem(FindMgmChild(Radar, "IconEnemy3"));
    RadarEnemiesHigher.AddItem(FindMgmChild(Radar, "IconEnemy3Higher"));
    RadarEnemiesLower.AddItem(FindMgmChild(Radar, "IconEnemy3Lower"));
    RadarEnemyArrows.AddItem(FindMgmChild(Radar, "IconEnemyArrow3"));
    for (INT enemy = 0; enemy < 3; ++enemy) {
        RadarEnemies(enemy)->Visible = 0;
        RadarEnemiesHigher(enemy)->Visible = 0;
        RadarEnemiesLower(enemy)->Visible = 0;
        RadarEnemyArrows(enemy)->Visible = 0;
    }

    RadarEnemyCount = 0;
    CompassImage = GetMgmImage(FindMgmChild(CompassBackground, "Fond"));
    MgmImageRegion RadarRegion = GetMgmImage(Teammates(0))->Region;
    RadarIconLeft = RadarRegion.Left;

    BindMgmArea(SystemMessage, Package, "A_MessageSystem");
    BindMgmArea(StateMessage, Package, "A_MessageState");
    BindMgmArea(GameMessage, Package, "A_MessageGame");
    BindMgmArea(TutorialMessage, Package, "A_TutoMessage");
    TutorialMessage->SetVisible(0, 1);
    TutorialMessageChild = FindMgmChild(TutorialMessage, "messageTuto");
    BindMgmArea(ZoneMessage, Package, "A_ZoneMessage");
    ZoneMessageChild = FindMgmChild(ZoneMessage, "_ZoneMessage");
    ZoneMessage->SetVisible(0, 1);
    SystemMessageText = static_cast<MgmTextContent *>(FindMgmChild(SystemMessage, "messageSystem")->Content);
    StateMessageText = static_cast<MgmTextContent *>(FindMgmChild(StateMessage, "messageState")->Content);
    GameMessageText = static_cast<MgmTextContent *>(FindMgmChild(GameMessage, "messageGame")->Content);
    TutorialMessageText = static_cast<MgmTextContent *>(TutorialMessageChild->Content);
    ZoneMessageText = static_cast<MgmTextContent *>(ZoneMessageChild->Content);

    BindMgmArea(Heart[0], Package, "A_Heart");
    BindMgmArea(Heart[1], Package, "A_Heart1");
    Heart[0]->SetVisible(0, 1);
    Heart[1]->SetVisible(0, 1);
    BindMgmArea(RadarTrap, Package, "radar_piege");
    RadarTrap->SetVisible(0, 1);

    BindMgmArea(ConnectedPlayers, Package, "A_PCConnectedPlayers");
    PlayerChildren[0] = FindMgmChild(ConnectedPlayers, "PCTextPlayer1");
    PlayerChildren[1] = FindMgmChild(ConnectedPlayers, "PCTextPlayer2");
    PlayerChildren[2] = FindMgmChild(ConnectedPlayers, "PCTextPlayer3");
    PlayerChildren[3] = FindMgmChild(ConnectedPlayers, "PCTextPlayer4");
    ObjectiveChildren[0] = FindMgmChild(ConnectedPlayers, "PCText_ObjOrKills1");
    ObjectiveChildren[1] = FindMgmChild(ConnectedPlayers, "PCText_ObjOrKills2");
    ObjectiveChildren[2] = FindMgmChild(ConnectedPlayers, "PCText_ObjOrKills3");
    ObjectiveChildren[3] = FindMgmChild(ConnectedPlayers, "PCText_ObjOrKills4");
    LivesChildren[0] = FindMgmChild(ConnectedPlayers, "PCText_Lives1");
    LivesChildren[1] = FindMgmChild(ConnectedPlayers, "PCText_Lives2");
    LivesChildren[2] = FindMgmChild(ConnectedPlayers, "PCText_Lives3");
    LivesChildren[3] = FindMgmChild(ConnectedPlayers, "PCText_Lives4");

    for (INT j = 0; j < 4; ++j) {
        PlayerText[j] = static_cast<MgmTextContent *>(PlayerChildren[j]->Content);
        PlayerObjectiveText[j] = static_cast<MgmTextContent *>(ObjectiveChildren[j]->Content);
        LivesText[j] = static_cast<MgmTextContent *>(LivesChildren[j]->Content);
        appSprintf(LivesLabels[j], L"");
        appSprintf(ObjectiveLabels[j], L"");
        PlayerObjectiveText[j]->SetExternalText(ObjectiveLabels[j]);
        LivesText[j]->SetExternalText(LivesLabels[j]);
    }

    SpyIcons[0] = FindMgmChild(ConnectedPlayers, "IcoSpy1");
    SpyIcons[1] = FindMgmChild(ConnectedPlayers, "IcoSpy2");
    SpyIcons[2] = FindMgmChild(ConnectedPlayers, "IcoSpy3");
    SpyIcons[3] = FindMgmChild(ConnectedPlayers, "IcoSpy4");
    MercIcons[0] = FindMgmChild(ConnectedPlayers, "IcoMerc1");
    MercIcons[1] = FindMgmChild(ConnectedPlayers, "IcoMerc2");
    MercIcons[2] = FindMgmChild(ConnectedPlayers, "IcoMerc3");
    MercIcons[3] = FindMgmChild(ConnectedPlayers, "IcoMerc4");
    SpectatorIcons[0] = FindMgmChild(ConnectedPlayers, "IcoSpectator1");
    SpectatorIcons[1] = FindMgmChild(ConnectedPlayers, "IcoSpectator2");
    SpectatorIcons[2] = FindMgmChild(ConnectedPlayers, "IcoSpectator3");
    SpectatorIcons[3] = FindMgmChild(ConnectedPlayers, "IcoSpectator4");

    FindMgmArea(Package, "A_GameInvite")->SetVisible(0, 1);
    MgmHudPage::InitResources();
}
