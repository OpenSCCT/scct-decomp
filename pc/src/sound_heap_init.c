#include "sound_error.h"
#include "sound_memory.h"

static int missing_cpu_feature(void)
{
    SND_fn_vDisplayError(E_uwSndBadHostConfiguration, "This game require support for Intel MMX instructions");
    return 0;
}

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
