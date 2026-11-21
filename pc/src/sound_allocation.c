/* sound_allocation.c -- allocates and resizes through the game's allocator (sndmem.c) */
#include "sound_memory.h"

/* SND_fn_pvMallocSnd */
void *__stdcall SND_fn_pvMallocSnd(unsigned long ulNbBytes)
{
    return sound_allocator->methods->allocate(sound_allocator, ulNbBytes, ulNbBytes, StaticTag);
}

/* SND_fn_pvReAllocSnd */
void *__stdcall SND_fn_pvReAllocSnd(void *pvPtr, unsigned long ulNbBytes)
{
    return sound_allocator->methods->resize(sound_allocator, pvPtr, pvPtr, ulNbBytes, StaticTag);
}
