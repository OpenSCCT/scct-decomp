#ifndef VERSUS_SPY_HUD_H
#define VERSUS_SPY_HUD_H

#include "versus_arrays.h"
#include "versus_mgm_hud_pages.h"
#include "versus_mgm.h"

// The MGM rectangle position setter preserves Right - Left and Bottom - Top.
struct MgmImageRegion {
    short Left, Right, Top, Bottom;
};

struct MgmImage {
    BYTE UnknownBeforeRegion[12];
    MgmImageRegion Region;
};

// A child owns this polymorphic object and invokes its deleting destructor.
struct MgmContent {
    virtual ~MgmContent();
};

struct MgmImageContent : MgmContent {
    MgmImage *Image;
};

class MgmPlayerHud : public MgmHudPage {
public:
    virtual void InitResources();

    BYTE UnknownBeforeStatus[0xc0 - 0xb4];
    DWORD Status[3];
    BYTE UnknownBeforeRadar[0x278 - 0xcc];
    MgmArea *Radar;
    BYTE UnknownBeforeSpeak[0x2b34 - 0x27c];
    MgmArea *Speak;
    MgmContent *SpeakText;
    BYTE UnknownBeforeSpyHud[0x2c74 - 0x2b3c];
};

class SpyHud : public MgmPlayerHud {
public:
    virtual void InitResources();

    DWORD EnergyState;
    MgmArea *Energy;
    MgmImageRegion *EnergyGauge, *EnergyLeft, *EnergyRight;
    FLOAT EnergyGaugeHeight, EnergyReferenceValue;
    MgmArea *StickyCam;
    TArray<MgmChild *> StickyCamText;
    MgmImage *StickyCamButtonImage;
    MgmChild *StickyCamButton;
    MgmArea *CoopMove[4];
    MgmChild *CoopButton[4];
    MgmArea *Speed;
    BYTE SpeedActive;
};

#endif
