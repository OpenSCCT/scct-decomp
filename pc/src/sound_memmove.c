/* sound_memmove.c -- moves bytes between overlapping ranges (sndmem.c) */
#include "sound_memory.h"

/* SND_fn_vMemMoveSnd */
void __stdcall SND_fn_vMemMoveSnd(void *ptr_dest, const void *ptr_source, unsigned long ulNbBytes)
{
    memmove(ptr_dest, ptr_source, ulNbBytes);
}
