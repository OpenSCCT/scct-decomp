#include "sound_memory.h"

void __stdcall SND_fn_vMemMoveSnd(void *ptr_dest, const void *ptr_source, unsigned long ulNbBytes)
{
    memmove(ptr_dest, ptr_source, ulNbBytes);
}
