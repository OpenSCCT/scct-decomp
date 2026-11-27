#include "versus_spy_hud.h"
#include "versus_pawn_action_events.h"
#include "versus_game_replication_info.h"

#include "versus_hud_objective_types.h"
#include "versus_native_class_init.h"
#include "versus_min_max.h"

INT appSprintf(TCHAR *Dest, const TCHAR *Format, ...);

void MgmPlayerHud::UpdateClock()
{
    if (!Controller->GameReplicationInfo)
        return;
    INT Minutes = Controller->GameReplicationInfo->TimeLimit - Controller->GameReplicationInfo->ElapsedTime / 60 - 1;
    if (Minutes < 0) {
        if (Clock->Visible)
            Clock->SetVisible(0, 1);
        return;
    }
    if (Minutes == 0 && !ClockActive) {
        ClockActive = 1;
        Clock->SetFrame(70, 1);
        Clock->SetPlaying(1);
    }
    if (!Clock->Visible)
        Clock->SetVisible(1, 1);
    appSprintf(ClockLabel, L"%u:%02u", Minutes, 59 - Controller->GameReplicationInfo->ElapsedTime % 60);
    ClockText->SetExternalText(ClockLabel);
}

void MgmPlayerHud::UpdateHackTimer()
{
    for (INT i = 0; i < Hud->ActorToDraw.Num(); ++i) {
        AActor *Actor = Hud->ActorToDraw(i);
        if (Actor->IsA(&ASTriggerInteraction::PrivateStaticClass) &&
            static_cast<ASTriggerInteraction *>(Actor)->MinTriggerTime != 0.0f) {
            ASTriggerInteraction *Trigger = static_cast<ASTriggerInteraction *>(Hud->ActorToDraw(i));
            INT Seconds = INT(Trigger->MinTriggerTime - Controller->GameReplicationInfo->ElapsedTime) + 1;
            appSprintf(HackLabel, L"0:%02u", Max(0, Seconds));
            HackTime->SetExternalText(HackLabel);
            if (!HackTimer->Visible) {
                HackTimer->SetVisible(1, 1);
                HackTimer->SetTime(0, 1);
                HackTimer->SetPlaying(1);
            } else if (!HackTimer->GetFrame()) {
                HackTimer->SetPlaying(1);
            }
            return;
        }
    }
    if (HackTimer->Visible)
        HackTimer->SetVisible(0, 1);
}

void MgmPlayerHud::UpdateAlarmTimer()
{
    TArray<ASAlarm *> &Alarms = Hud->AlarmsList;
    if (Alarms.Num() > 0) {
        INT Index = Hud->FindActiveAlarm();
        if (Index >= 0) {
            ASAlarm *Alarm = Alarms(Index);
            INT Seconds = Alarm->Duration - Controller->GameReplicationInfo->ElapsedTime + Alarm->StartTime;
            if (Seconds > 0) {
                appSprintf(AlarmLabel, L"0:%02u", Seconds % 60);
                AlarmTime->SetExternalText(AlarmLabel);
                if (!AlarmTimer->Visible) {
                    AlarmTimer->SetVisible(1, 1);
                    AlarmTimer->SetFrame(0, 1);
                    AlarmTimer->SetPlaying(1);
                } else if (!AlarmTimer->GetFrame()) {
                    AlarmTimer->SetPlaying(1);
                }
                return;
            }
        }
    }
    AlarmTimer->SetVisible(0, 1);
}
