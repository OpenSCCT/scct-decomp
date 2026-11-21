#include "sound_timer.h"
#include "sound_win32.h"

void __stdcall SND_fn_vResetTimer(long lTimerId)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)lTimerId;
    if (pSndTimer && pSndTimer != (tdstSndTimer *)SND_TIMER_NONE &&
        QueryPerformanceCounter(&pSndTimer->initTick))
        pSndTimer->bPaused = 0;
}

void __stdcall SND_fn_vPauseTimer(long lTimerId)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)lTimerId;
    if (pSndTimer && pSndTimer != (tdstSndTimer *)SND_TIMER_NONE && !pSndTimer->bPaused &&
        QueryPerformanceCounter(&pSndTimer->pauseTick))
        pSndTimer->bPaused = 1;
}
