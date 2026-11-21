/* sound_timers.c -- restarts and pauses a timer */
#include "sound_timer.h"
#include "sound_win32.h"

/* SND_fn_vResetTimer */
void __stdcall SND_fn_vResetTimer(long lTimerId)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)lTimerId;
    if (pSndTimer && pSndTimer != (tdstSndTimer *)SND_TIMER_NONE &&
        QueryPerformanceCounter(&pSndTimer->initTick))
        pSndTimer->bPaused = 0;
}

/* SND_fn_vPauseTimer */
void __stdcall SND_fn_vPauseTimer(long lTimerId)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)lTimerId;
    if (pSndTimer && pSndTimer != (tdstSndTimer *)SND_TIMER_NONE && !pSndTimer->bPaused &&
        QueryPerformanceCounter(&pSndTimer->pauseTick))
        pSndTimer->bPaused = 1;
}
