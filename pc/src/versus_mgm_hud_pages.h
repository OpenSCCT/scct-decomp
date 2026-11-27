#ifndef VERSUS_MGM_HUD_PAGES_H
#define VERSUS_MGM_HUD_PAGES_H

#include "versus_ansi_fstring.h"

class MgmArea;
class MgmPackage;
class ASPlayerController;

// Construction of each screen takes its MGM package and page names by reference.
class MgmScreen {
public:
    MgmScreen(const FString &PackageName, const FString &PageName);
    virtual ~MgmScreen();
    virtual bool ScreenEvent1(INT);
    virtual bool ScreenEvent2(INT);
    virtual bool ScreenEvent3(INT, INT);
    virtual bool ScreenEvent4(INT, INT);
    virtual bool UpdateScreen(INT, INT);
    virtual void InitResources();
    virtual void CloseScreen();
    virtual bool ScreenQuery8();
    virtual INT ScreenQuery9(INT, INT);
    virtual bool ScreenEvent10(INT, INT, INT);
    virtual void ScreenEvent11(INT);

    INT RefCount;
    BYTE Unknown08;
    FString PackageName;
    FString PageName;
    MgmPackage *Package;
    MgmArea *Page;
    BYTE Unknown2c[0xb4 - 0x2c];
};

class MgmGameScreen : public MgmScreen {
public:
    MgmGameScreen(const FString &PackageName, const FString &PageName);
    virtual void InitResources();
    virtual void CloseScreen();
    virtual void ApplyPlayerSettings();
    virtual void ReadPlayerSettings();
};

class MgmHudPage : public MgmGameScreen {
public:
    MgmHudPage(const FString &PackageName, const FString &PageName);
    virtual bool ScreenEvent1(INT);
    virtual void InitResources();
    virtual void CloseScreen();
    virtual void ScreenEvent14(INT);
};

class MgmInteractionPage : public MgmHudPage {
public:
    MgmInteractionPage(const FString &PackageName, const FString &PageName);
    virtual bool UpdateScreen(INT, INT);
    virtual void InitResources();
    virtual void CloseScreen();
};

class EndGameHudPage : public MgmHudPage {
public:
    EndGameHudPage();
    virtual bool UpdateScreen(INT, INT);
    virtual void InitResources();

    ASPlayerController *Controller;
    MgmArea *YouWin, *YouLose, *Finish, *FinishSpectator;
};

class SpectatorHudPage : public MgmHudPage {
public:
    SpectatorHudPage();
    virtual bool UpdateScreen(INT, INT);
    virtual void InitResources();
    virtual void CloseScreen();
    virtual void UpdateSpectatorTarget();
};

class MercInteractionHudPage : public MgmInteractionPage {
public:
    MercInteractionHudPage();
};

class SpyInteractionHudPage : public MgmInteractionPage {
public:
    SpyInteractionHudPage();
};

#endif
