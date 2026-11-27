#include "unreal_containers.h"
#include "versus_mgm_hud_pages.h"
#include "versus_mgm.h"

ANSICHAR *appToAnsi(const TCHAR *Source, ANSICHAR *Destination);

MgmChild *MgmScreen::FindChild(const FString &Name)
{
    return FindMgmChild(Page, appToAnsi(*Name, 0));
}
