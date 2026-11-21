/* sound_timer.h -- timers of the sound library */
#ifndef SOUND_TIMER_H
#define SOUND_TIMER_H

/* A timer's identifier is the address of its structure. The ticks are those of the Win32
   performance counter here; the sibling build keeps them as floats. */
typedef struct _tdstSndTimer {
    int bPaused;
    __int64 initTick;
    __int64 pauseTick;
} tdstSndTimer;

/* The identifier of no timer. The macro's name is invented. */
#define SND_TIMER_NONE (-2)

long __stdcall SND_fn_lCreateTimer(void);
float __stdcall SND_fn_fGetCurrentTime(long lTimerId);
void __stdcall SND_fn_vResetTimer(long lTimerId);
void __stdcall SND_fn_vPauseTimer(long lTimerId);
void __stdcall SND_fn_vResumeTimer(long lTimerId);
void __stdcall SND_fn_vDestroyTimer(long lTimerId);

#endif
