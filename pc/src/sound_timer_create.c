/* sound_timer_create.c -- creates a sound timer */
#include "sound_memory.h"
#include "sound_timer.h"
#include "sound_win32.h"

/* SND_fn_lCreateTimer */
long __stdcall SND_fn_lCreateTimer(void)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)SND_fn_pvMallocSnd(sizeof(tdstSndTimer));
    if (!pSndTimer) {
        return SND_TIMER_NONE;
    } else {
        if (!QueryPerformanceCounter(&pSndTimer->initTick)) {
            return SND_TIMER_NONE;
        } else {
            pSndTimer->bPaused = 0;
            return (long)pSndTimer;
        }
    }
}
