#include "sound_memory.h"
#include "sound_timer.h"

void __stdcall SND_fn_vDestroyTimer(long lTimerId)
{
    tdstSndTimer *pSndTimer = (tdstSndTimer *)lTimerId;
    if (pSndTimer && pSndTimer != (tdstSndTimer *)SND_TIMER_NONE)
        SND_fn_vFreeSnd(pSndTimer);
}
