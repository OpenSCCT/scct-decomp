#include "sound_manager.h"

void __cdecl release_sample(tdstBlockResourceMem *res, int full)
{
    unload_resource_sample(res, full);
}

void __cdecl release_sample_collection(tdstBlockResourceMem *res, int full)
{
    unload_resource_multitrack(res, full);
}
