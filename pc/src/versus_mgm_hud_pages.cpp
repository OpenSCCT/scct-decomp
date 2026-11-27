#include "versus_mgm_hud_pages.h"

MgmGameScreen::MgmGameScreen(const FString &PackageName, const FString &PageName)
    : MgmScreen(PackageName, PageName)
{
}

MgmHudPage::MgmHudPage(const FString &PackageName, const FString &PageName)
    : MgmGameScreen(PackageName, PageName)
{
}

MgmInteractionPage::MgmInteractionPage(const FString &PackageName, const FString &PageName)
    : MgmHudPage(PackageName, PageName)
{
}
