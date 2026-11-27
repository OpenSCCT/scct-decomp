#include "versus_mgm_device_pages.h"

StickyCameraHudPage::StickyCameraHudPage() : MgmHudPage("Hud", "P_StickyCam")
{
    Controller = GetMgmPlayerController();
}
