/* sound_timer_resume.c -- resumes a paused timer */
#include "sound_timer.h"
#include "sound_win32.h"

/* SND_fn_vResumeTimer: moves the timer's start forward by the time it was paused */
void __stdcall SND_fn_vResumeTimer(long lTimerId)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)lTimerId;
    __int64 Current_tick;
    if (pSndTimer && pSndTimer != (tdstSndTimer *)SND_TIMER_NONE && pSndTimer->bPaused) {
        pSndTimer->bPaused = 0;
        if (QueryPerformanceCounter(&Current_tick))
            pSndTimer->initTick += Current_tick - pSndTimer->pauseTick;
    }
}
