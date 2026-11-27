#include "versus_build.h"
#include "versus_engine_stats.h"
#include "versus_memory.h"

INT FArray::AddZeroed(INT ElementSize, INT Count)
{
    INT first = Add(Count, ElementSize);
    appMemzero((BYTE *)Data + first * ElementSize, Count * ElementSize);
    return first;
}

// SmoothCounter is a descriptive name. The three mesh displays in FStats::Render
// all apply this moving average to the current integer counters.
void FStats::SmoothCounter(INT Index, INT Window)
{
    enum { WarmupFrames = 3 };
    DWORD &value = GStats.Integers.Current(Index);
    INT needed = Index + 1 - History.Num();
    if (needed > 0)
        History.AddZeroed(needed);
    if (History(Index).Window != Window) {
        History(Index).Window = Window;
        History(Index).Samples.Empty();
        History(Index).Samples.AddZeroed(Window);
        History(Index).Count = 0;
    }
    INT count = History(Index).Count + 1;
    INT limit = History(Index).Window + WarmupFrames;
    History(Index).Count = limit > count ? count : limit;
    INT current = History(Index).Count;
    if (current > WarmupFrames) {
        History(Index).Samples(History(Index).WriteIndex) = value;
        INT used = current - WarmupFrames;
        __int64 total = 0;
        for (INT i = 0; i < used; ++i)
            total += History(Index).Samples(i);
        History(Index).WriteIndex = (History(Index).WriteIndex + 1) % History(Index).Window;
        value = (DWORD)(total / used);
    }
}

// Recovered excerpt of FStats::Render, grouped under a local name. The fourth
// render page smooths these seven counters in sequence before drawing their values.
void SmoothMeshCounters(FStats &Stats)
{
    enum { MeshWindow = 40 };
    Stats.SmoothCounter(GEngineStats.MeshSkin, MeshWindow);
    Stats.SmoothCounter(GEngineStats.MeshResult, MeshWindow);
    Stats.SmoothCounter(GEngineStats.MeshLOD, MeshWindow);
    Stats.SmoothCounter(GEngineStats.MeshPose, MeshWindow);
    Stats.SmoothCounter(GEngineStats.MeshSkel, MeshWindow);
    Stats.SmoothCounter(GEngineStats.MeshRigid, MeshWindow);
    Stats.SmoothCounter(GEngineStats.MeshDraw, MeshWindow);
}
