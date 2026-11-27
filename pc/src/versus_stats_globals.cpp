#include "versus_build.h"
#include "versus_stats_arrays.h"
#include "versus_name_table.h"
#include "versus_pawn_action_events.h"
#include "versus_engine_stats.h"

FStats GStats;
FEngineStats GEngineStats;
TArray<FNameEntry *> FName_Names;
DOUBLE GSecondsPerCycle = 1.0;
FLOAT GActorStatMinimum = 0.5f;
