#include "unreal_containers.h"
#include "versus_mgm_hud_pages.h"
#include "versus_mgm.h"
#include "versus_mgm_hud_context.h"

extern MgmScreen *GMgmScreens[];
extern INT GMgmScreenIndex;
ANSICHAR *appToAnsi(const TCHAR *Source, ANSICHAR *Destination);

void OpenMgmScreen(MgmScreen *Screen, UBOOL TopLevel, UBOOL DeleteOnClose)
{
    Screen->TopLevel = TopLevel;
    if (!Screen->Package) {
        const TCHAR *Name = *Screen->PackageName;
        MgmMenuSystem *Menu = GMgmMenuSystem;
        Screen->Package = FindMgmPackage(&Menu->Packages, appToAnsi(Name, 0));
    }

    Screen->Page = FindMgmArea(Screen->Package, MgmNameId(appToAnsi(*Screen->PageName, 0)));
    if (Screen->Page) {
        Screen->InitResources();
        GMgmScreens[++GMgmScreenIndex] = Screen;
        Screen->DeleteOnClose = DeleteOnClose;
        GMgmMenuSystem->PageStack.PushPage(Screen->Page, TopLevel != 0, 0);
    }
}
