#include "sound_memory.h"

void __stdcall SND_fn_vFreeSnd(void *pvPtr)
{
    SoundAllocationArg block = { pvPtr };
    sound_allocator->methods->release(sound_allocator, block);
}
