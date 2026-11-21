#include "sound_memory.h"

void *__stdcall SND_fn_pvMallocSnd(unsigned long ulNbBytes)
{
    return sound_allocator->methods->allocate(sound_allocator, ulNbBytes, ulNbBytes, StaticTag);
}

void *__stdcall SND_fn_pvReAllocSnd(void *pvPtr, unsigned long ulNbBytes)
{
    return sound_allocator->methods->resize(sound_allocator, pvPtr, pvPtr, ulNbBytes, StaticTag);
}
