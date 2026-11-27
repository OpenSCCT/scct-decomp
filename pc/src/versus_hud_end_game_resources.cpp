#include "versus_build.h"
#include "versus_sbase_classes.h"
#include "versus_canvas_viewport.h"
#include "versus_mgm_hud_pages.h"
#include "versus_mgm_hud_context.h"
#include "versus_mgm_bindings.h"

void EndGameHudPage::InitResources()
{
    BindMgmArea(YouWin, Package, "A_YouWin");
    BindMgmArea(YouLose, Package, "A_YouLose");
    BindMgmArea(Finish, Package, "A_Finish");
    BindMgmArea(FinishSpectator, Package, "A_FinishSpect");
    YouWin->SetVisible(0, 1);
    YouLose->SetVisible(0, 1);
    Finish->SetVisible(0, 1);
    FinishSpectator->SetVisible(0, 1);
    MgmHudPage::InitResources();
    if (GetMgmViewport() && GetMgmViewport()->Actor)
        static_cast<ASPlayerController *>(GetMgmPlayerController())->bEndGame = 1;
}
