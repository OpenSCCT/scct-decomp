/* sound_sample_release.c -- unloads sample and multitrack data (sndmanager.cpp) */
#include "sound_manager.h"

/* release_sample.
   guess: SndManager::UnloadResourceSample of the sibling builds */
void __cdecl release_sample(tdstBlockResourceMem *res, int full)
{
    unload_resource_sample(res, full);
}

/* release_sample_collection.
   guess: SndManager::UnloadResourceMultiTrack of the sibling builds */
void __cdecl release_sample_collection(tdstBlockResourceMem *res, int full)
{
    unload_resource_multitrack(res, full);
}
