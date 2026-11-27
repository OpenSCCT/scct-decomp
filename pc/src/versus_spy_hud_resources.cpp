#include "versus_spy_hud.h"
#include "versus_mgm_bindings.h"

static inline void BindMgmChild(MgmChild *&Child, MgmArea *Area, const ANSICHAR *Name)
{
    Child = FindMgmChild(Area, Name);
}

void SpyHud::InitResources()
{
    Energy = FindMgmArea(Package, "A_JaugeEnergie");
    EnergyGauge = &static_cast<MgmImageContent *>(FindMgmChild(Energy, "jaugeinterne")->Content)->Image->Region;
    EnergyLeft = &static_cast<MgmImageContent *>(FindMgmChild(Energy, "jaugeindicator_gauche")->Content)->Image->Region;
    EnergyRight = &static_cast<MgmImageContent *>(FindMgmChild(Energy, "jaugeindicator_droite")->Content)->Image->Region;
    EnergyGaugeHeight = 133.0f;
    EnergyReferenceValue = 100.0f;

    BindMgmArea(StickyCam, Package, "A_InteractionStickyCam");
    StickyCamButtonImage = static_cast<MgmImageContent *>(FindMgmChild(StickyCam, "PC_Button")->Content)->Image;
    StickyCamButton = FindMgmChild(StickyCam, "A_Button");
    TArray<MgmChild *> &Labels = StickyCamText;
    Labels.ArrayNum = 0;
    Labels.AddItem(FindMgmChild(StickyCam, "textSticky1"));
    Labels.AddItem(FindMgmChild(StickyCam, "textSticky2"));
    Labels.AddItem(FindMgmChild(StickyCam, "textSticky3"));
    StickyCam->SetVisible(0, 1);

    BindMgmArea(Radar, Package, "A_Radar");
    FindMgmChild(Radar, "IconAlarm1")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm1Higher")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm1Lower")->Visible = 0;
    FindMgmChild(Radar, "IconAlarmArrow1")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm2")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm2Higher")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm2Lower")->Visible = 0;
    FindMgmChild(Radar, "IconAlarmArrow2")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm3")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm3Higher")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm3Lower")->Visible = 0;
    FindMgmChild(Radar, "IconAlarmArrow3")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm4")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm4Higher")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm4Lower")->Visible = 0;
    FindMgmChild(Radar, "IconAlarmArrow4")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm5")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm5Higher")->Visible = 0;
    FindMgmChild(Radar, "IconAlarm5Lower")->Visible = 0;
    FindMgmChild(Radar, "IconAlarmArrow5")->Visible = 0;

    BindMgmArea(CoopMove[0], Package, "Move_coop");
    BindMgmArea(CoopMove[1], Package, "Move_coop2");
    BindMgmArea(CoopMove[2], Package, "Move_coop3");
    BindMgmArea(CoopMove[3], Package, "Move_coop4");
    CoopMove[2]->SetVisible(0, 1);
    CoopMove[3]->SetVisible(0, 1);
    BindMgmChild(CoopButton[0], CoopMove[0], "button_White");
    BindMgmChild(CoopButton[1], CoopMove[1], "button_White");
    BindMgmChild(CoopButton[2], CoopMove[2], "button_White");
    BindMgmChild(CoopButton[3], CoopMove[3], "button_White");

    BindMgmArea(Speak, Package, "A_SpeakATT");
    SpeakText = FindMgmChild(Speak, "_TextSpeakATT")->Content;
    HideMgmChild(Speak, "Element1");
    HideMgmChild(Speak, "Element2");
    HideMgmChild(Speak, "Element3");
    HideMgmChild(Speak, "Element4");

    BindMgmArea(Speed, Package, "A_Spy_Speed");
    Status[0] = 0;
    EnergyState = 0;
    Status[1] = 0;
    Status[2] = 0;
    SpeedActive = 0;
    MgmPlayerHud::InitResources();
}
