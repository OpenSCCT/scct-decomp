#include "versus_arrays.h"
#include "versus_pawn_action_events.h"
#include "versus_game_replication_info.h"
#include "versus_hud_objective_types.h"

INT ASHud::FindActiveAlarm()
{
    if (AlarmsList.Num()) {
        INT Index = -1;
        INT Longest = 0;
        for (INT i = 0; i < AlarmsList.Num(); ++i) {
            ASAlarm *Alarm = AlarmsList(i);
            INT Remaining = Alarm->Duration + Alarm->StartTime - PlayerOwner->GameReplicationInfo->ElapsedTime + 1;
            if (Alarm->MessagePriority > 4 && Remaining > Longest) {
                Index = i;
                Longest = Remaining;
            }
        }
        return Index;
    }
    return -1;
}
