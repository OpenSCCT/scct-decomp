/* sound_timer_lifetime.c -- destroys a timer */
#include "sound_memory.h"
#include "sound_timer.h"

/* SND_fn_vDestroyTimer */
void __stdcall SND_fn_vDestroyTimer(long lTimerId)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)lTimerId;
    if (pSndTimer && pSndTimer != (tdstSndTimer *)SND_TIMER_NONE)
        SND_fn_vFreeSnd(pSndTimer);
}
