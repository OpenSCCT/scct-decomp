#ifndef VERSUS_SPY_HUD_H
#define VERSUS_SPY_HUD_H

#include "versus_arrays.h"
#include "versus_mgm_hud_pages.h"
#include "versus_mgm.h"
#include "versus_mgm_content.h"

class ASPlayerController;
class ASHud;

class MgmPlayerHud : public MgmHudPage {
public:
    virtual void InitResources();
    virtual void PlayerHudSlot15();
    virtual void UpdateGauge();
    virtual void UpdateGadget();
    virtual void UpdateClock();
    virtual void UpdateHackTimer();
    virtual void UpdateAlarmTimer();
    virtual bool UpdateObjectiveTimers();
    virtual void UpdateObjective();

    ASPlayerController *Controller;
    ASHud *Hud;
    BYTE Unknownbc[0xc0 - 0xbc];
    DWORD Status[3];
    MgmArea *Gauge;
    MgmImageRegion *GaugeBar;
    MgmImageRegion *GaugeLeft;
    MgmImageRegion *GaugeRight;
    FLOAT GaugeHeight;
    FLOAT ReferenceGaugeValue;
    INT GaugeSample;
    MgmInterpolator GaugeInterpolator;
    MgmArea *PoisonGauge;
    BYTE Unknown10c[0x134 - 0x10c];
    MgmArea *Gadget;
    MgmContent *GadgetIcon;
    MgmContent *GadgetNumber;
    BYTE Unknown140[0x17c - 0x140];
    MgmContent *GadgetName;
    MgmPackage *Options;
    TCHAR ClockLabel[20];
    MgmArea *Clock;
    MgmTextContent *ClockText;
    BYTE ClockActive;
    TCHAR HackLabel[20];
    MgmArea *HackTimer;
    MgmTextContent *HackTime;
    TCHAR AlarmLabel[20];
    MgmArea *AlarmTimer;
    MgmTextContent *AlarmTime;
    BYTE Unknown218[0x230 - 0x218];
    MgmArea *ObjectiveTimers[2];
    MgmContent *ObjectiveTimes[2];
    MgmArea *Objective;
    TCHAR ObjectiveLabel[20];
    MgmTextContent *ObjectiveText;
    INT LastObjectiveCount;
    BYTE Unknown274[4];
    MgmArea *Radar;
    MgmArea *CompassBackground;
    INT RadarIconLeft;
    MgmImage *CompassImage;
    BYTE Unknown288[0x28c - 0x288];
    INT RadarTeammateCount;
    INT RadarEnemyCount;
    TArray<MgmChild *> Teammates;
    TArray<MgmChild *> TeammatesHigher;
    TArray<MgmChild *> TeammatesLower;
    TArray<MgmChild *> Enemies;
    TArray<MgmChild *> EnemiesHigher;
    TArray<MgmChild *> EnemiesLower;
    TArray<MgmChild *> EnemyArrows;
    MgmArea *Ballistic;
    INT BallisticState;
    BYTE Unknown2f0[0x2af0 - 0x2f0];
    MgmArea *ZoneMessage;
    MgmArea *SystemMessage;
    MgmArea *StateMessage;
    MgmArea *GameMessage;
    MgmChild *TutorialMessageChild;
    MgmChild *ZoneMessageChild;
    MgmTextContent *SystemMessageText;
    MgmTextContent *StateMessageText;
    MgmTextContent *GameMessageText;
    MgmTextContent *TutorialMessageText;
    MgmTextContent *ZoneMessageText;
    MgmArea *TutorialMessage;
    MgmArea *Heart[2];
    BYTE Unknown2b28[0x2b30 - 0x2b28];
    BYTE Active;
    BYTE Unknown2b31[0x2b34 - 0x2b31];
    MgmArea *Speak;
    MgmContent *SpeakText;
    MgmArea *RadarTrap;
    MgmArea *ConnectedPlayers;
    MgmChild *PlayerChildren[4];
    MgmChild *ObjectiveChildren[4];
    MgmChild *LivesChildren[4];
    MgmTextContent *PlayerText[4];
    MgmTextContent *PlayerObjectiveText[4];
    MgmTextContent *LivesText[4];
    TCHAR ObjectiveLabels[4][10];
    TCHAR LivesLabels[4][10];
    MgmChild *SpyIcons[4];
    MgmChild *MercIcons[4];
    MgmChild *SpectatorIcons[4];
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
