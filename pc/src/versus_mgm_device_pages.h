#ifndef VERSUS_MGM_DEVICE_PAGES_H
#define VERSUS_MGM_DEVICE_PAGES_H

#include "versus_mgm_hud_pages.h"
#include "versus_mgm_hud_context.h"

class AHUD;
class MgmArea;
class USPlayerProfile;

struct MgmPoint {
    short X, Y;
    MgmPoint() : X(0), Y(0) {}
};

class StickyCameraHudPage : public MgmHudPage {
public:
    StickyCameraHudPage();
    virtual void InitResources();
    virtual void CloseScreen();
    virtual void RefreshKeyBindings();

    AHUD *Hud;
    MgmArea *Background;
    APlayerController *Controller;
    USPlayerProfile *PlayerProfile;
};

class SpyBinocularHudPage : public MgmHudPage {
public:
    SpyBinocularHudPage();
    virtual bool UpdateScreen(INT, INT);
    virtual void InitResources();
    virtual void CloseScreen();
    virtual void RefreshKeyBindings();
    virtual void UpdateZoomDisplay();

    BYTE UnknownB4[0x228 - 0xb4];
    MgmPoint Right, Center, Left;
};

class MercBinocularHudPage : public MgmHudPage {
public:
    MercBinocularHudPage();
    virtual bool UpdateScreen(INT, INT);
    virtual void InitResources();
    virtual void CloseScreen();
    virtual void RefreshKeyBindings();
    virtual void RefreshTarget();
    virtual void RefreshTargetVisibility();
    virtual void RefreshTargetText();

    BYTE UnknownB4[0x118 - 0xb4];
    MgmPoint Position;
    BYTE Unknown11c[0x12c - 0x11c];
    FString DistanceText;
    BYTE Unknown138[0x2e0 - 0x138];
    FString TargetText;
};
#endif
