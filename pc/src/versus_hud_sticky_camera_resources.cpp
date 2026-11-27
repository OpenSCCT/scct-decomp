#include "versus_build.h"
#include "versus_pawn_action_events.h"
#include "versus_persistent_data.h"
#include "versus_mgm_device_pages.h"
#include "versus_mgm_bindings.h"

void StickyCameraHudPage::InitResources()
{
    APlayerController *Player = GetMgmPlayerController();
    if (Player)
        Hud = Player->myHUD;
    PlayerProfile = GetMgmPersistentData()->PlayerProfile;
    BindMgmArea(Background, Package, "StickyCamFond");
    FindMgmChild(Background, "IconStickyCamUp")->Visible = 0;
    FindMgmChild(Background, "IconStickyCamA")->Visible = 0;
    FindMgmChild(Background, "IconStickyCamB")->Visible = 0;
    FindMgmChild(Background, "textStickyCam1")->Visible = 0;
    FindMgmChild(Background, "textStickyCam2")->Visible = 0;
    FindMgmChild(Background, "textStickyCam3")->Visible = 0;
    FindMgmChild(Background, "cadre")->Visible = 0;
    RefreshKeyBindings();
    FindMgmArea(Package, "A_GameInvite")->SetVisible(0, 1);
    MgmHudPage::InitResources();
}
