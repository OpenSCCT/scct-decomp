/* sound_timer_seconds.c -- reads a timer */
#include "sound_timer.h"
#include "sound_win32.h"

/* SND_fn_fGetCurrentTime: the seconds since the timer was reset, pauses left out */
float __stdcall SND_fn_fGetCurrentTime(long lTimerId)
{
    const tdstSndTimer *pSndTimer = (const tdstSndTimer *)lTimerId;
    __int64 currentTick, frequency;
    __int64 deltaTick;
    if (!pSndTimer || pSndTimer == (const tdstSndTimer *)SND_TIMER_NONE
        || !QueryPerformanceFrequency(&frequency))
        return 0.0f;

    if (pSndTimer->bPaused) {
        deltaTick = pSndTimer->pauseTick - pSndTimer->initTick;
    } else {
        if (!QueryPerformanceCounter(&currentTick))
            return 0.0f;
        deltaTick = currentTick - pSndTimer->initTick;
    }
    return (float)deltaTick / (float)frequency;
}
