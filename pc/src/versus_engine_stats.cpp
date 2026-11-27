// FEngineStats::Init. The editor retains its guard and renders the same grouped stats.
#include "versus_build.h"
#include "versus_engine_stats.h"

TCHAR ActorSection[] = L"Game";
TCHAR ActorFormat[] = L"Actor %ld";

#define ENGINE_STAT(member, category, section, description, unit) \
    TCHAR StatSection_##member[] = L##section; \
    TCHAR StatDescription_##member[] = L##description;
#include "versus_engine_stat_list.inl"
#undef ENGINE_STAT

void FEngineStats::Init()
{
    if (GStats.Registered[STATSTYPE_Render]) {
        INT *next = &FrameTime;
        for (INT i = 0; i < GStats.Stats[STATSTYPE_Render].Num(); ++i)
            *next++ = GStats.Stats[STATSTYPE_Render](i).Index;
        next = &GameScript;
        for (i = 0; i < GStats.Stats[STATSTYPE_Game].Num(); ++i)
            *next++ = GStats.Stats[STATSTYPE_Game](i).Index;
        next = &NetPing;
        for (i = 0; i < GStats.Stats[STATSTYPE_Net].Num(); ++i)
            *next++ = GStats.Stats[STATSTYPE_Net](i).Index;
        return;
    }
    enum { MaxTrackedActors = 10000 };
    for (INT i = 0; i < MaxTrackedActors; ++i)
        ActorIndices.AddItem(GStats.RegisterStats(STATSTYPE_Game, STATSDATATYPE_Integer,
            *FString::Printf(ActorFormat, i), ActorSection, STATSUNIT_MSec));
    BspDynamicLightCounts = new TMap<UObject *, INT>;

#define ENGINE_STAT(member, category, section, description, unit) \
    member = GStats.RegisterStats(category, STATSDATATYPE_Integer, StatDescription_##member, \
                                  StatSection_##member, unit);
#include "versus_engine_stat_list.inl"
#undef ENGINE_STAT

    GStats.Registered[STATSTYPE_Render] = 1;
    GStats.Registered[STATSTYPE_Game] = 1;
    GStats.Registered[STATSTYPE_Net] = 1;
}
