#ifndef VERSUS_MGM_DEVICE_PAGES_H
#define VERSUS_MGM_DEVICE_PAGES_H

#include "versus_mgm_hud_pages.h"
#include "versus_mgm_hud_context.h"
#include "versus_mgm_keyframes.h"

class AHUD;
class MgmArea;
class USPlayerProfile;
struct MgmImage;
struct MgmContent;
struct MgmTextContent;


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

    APlayerController *Controller;
    USPlayerProfile *PlayerProfile;
    AHUD *Hud;
    BYTE UnknownC0[0x1ec - 0xc0];
    TCHAR ZoomLabels[3][10];
    MgmPoint Right, Center, Left;
    MgmArea *Zoom;
    MgmTextContent *ZoomValue;
    MgmImage *ZoomInside;
    INT ZoomLevel;
    MgmArea *Speak;
    MgmContent *SpeakText;
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
