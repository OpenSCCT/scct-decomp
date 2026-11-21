/* sound_heap_init.c -- starts the memory services (sndmem.c) */
#include "sound_error.h"
#include "sound_memory.h"

/* Reports that the processor lacks a feature the library needs. */
static int missing_cpu_feature(void)
{
    SND_fn_vDisplayError(E_uwSndBadHostConfiguration, "This game require support for Intel MMX instructions");
    return 0;
}

/* SND_fn_bInitMallocSnd: fails on a processor without CPUID or MMX */
int __stdcall SND_fn_bInitMallocSnd(void)
{
    unsigned long cpuid, mmx;
    sound_heap_detect_cpu(&cpuid, &mmx);
    if (!cpuid)
        return missing_cpu_feature();
    if (!mmx)
        return missing_cpu_feature();
    return 1;
}
