#include "versus_build.h"
#include "versus_pawn_action_events.h"
#include "versus_persistent_data.h"
#include "versus_mgm_device_pages.h"
#include "versus_mgm_content.h"
#include "versus_mgm_bindings.h"

INT appSprintf(TCHAR *Dest, const TCHAR *Format, ...);

void SpyBinocularHudPage::InitResources()
{
    Controller = GetMgmPlayerController();
    if (Controller)
        Hud = Controller->myHUD;
    PlayerProfile = GetMgmPersistentData()->PlayerProfile;
    BindMgmArea(Zoom, Package, "A_ZoomAtt");
    FindMgmChild(Zoom, "IconZoomUp")->Visible = 0;
    FindMgmChild(Zoom, "IconZoomDown")->Visible = 0;
    FindMgmChild(Zoom, "textZoomAtt1")->Visible = 0;
    FindMgmChild(Zoom, "textZoomAtt2")->Visible = 0;
    FindMgmChild(Zoom, "PCtextZoomAtt3")->Visible = 0;
    FindMgmChild(Zoom, "PCtextZoomAtt3Binding")->Visible = 0;
    appSprintf(ZoomLabels[0], L"x6");
    appSprintf(ZoomLabels[1], L"x4");
    appSprintf(ZoomLabels[2], L"x2");
    ZoomValue = static_cast<MgmTextContent *>(FindMgmChild(Zoom, "ZoomValue")->Content);
    ZoomValue->SetExternalText(ZoomLabels[2]);
    ZoomLevel = 1;
    ZoomInside = static_cast<MgmImageContent *>(FindMgmChild(Zoom, "zoomInside")->Content)->Image;
    ZoomInside->GetPosition(Center);
    Right.X = Center.X + 35;
    Right.Y = Center.Y;
    Left.X = Center.X - 35;
    Left.Y = Center.Y;
    RefreshKeyBindings();
    BindMgmArea(Speak, Package, "A_SpeakATTBin");
    SpeakText = FindMgmChild(Speak, "_TextSpeakATT")->Content;
    HideMgmChild(Speak, "Element4");
    FindMgmArea(Package, "A_GameInvite")->SetVisible(0, 1);
    MgmHudPage::InitResources();
}
