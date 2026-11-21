/* sound_allocator.c -- frees through the game's allocator (sndmem.c) */
#include "sound_memory.h"

/* SND_fn_vFreeSnd */
void __stdcall SND_fn_vFreeSnd(void *pvPtr)
{
    SoundAllocationArg block = { pvPtr };
    sound_allocator->methods->release(sound_allocator, block);
}
