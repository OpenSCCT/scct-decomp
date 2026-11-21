/* sound_real.h -- real numbers of the sound library: signed 16.16 fixed point (sndreal.c) */
#ifndef SOUND_REAL_H
#define SOUND_REAL_H

/* The typedef's name follows the exports SND_fn_vSndRealTwinToSndReal and
   SND_fn_rtSndRealToSndRealTwin; no symbol table carries the typedef itself. */
typedef long SndReal;

SndReal __stdcall SND_fn_rMulRealRealSnd(SndReal r1, SndReal r2);
SndReal __stdcall SND_fn_rMulRealRealQuickSnd(SndReal r1, SndReal r2);
SndReal __stdcall SND_fn_rDivRealRealSnd(SndReal r1, SndReal r2);
SndReal __stdcall SND_fn_rDivRealRealQuickSnd(SndReal r1, SndReal r2);
SndReal __stdcall SND_fn_rAbsRealSnd(SndReal r);
void __stdcall SND_fn_vSndRealTwinToSndReal(long rtwin, SndReal *pr1, SndReal *pr2);
long __stdcall SND_fn_rtSndRealToSndRealTwin(SndReal r1, SndReal r2);

#endif
