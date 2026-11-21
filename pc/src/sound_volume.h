/* sound_volume.h -- decibel conversions and fade curves (sndVolume.c) */
#ifndef SOUND_VOLUME_H
#define SOUND_VOLUME_H

#include "sound_real.h"

/* The quietest volume the library works with, in decibels as a 16.16 real.
   The macro's name is invented. */
#define SND_VOLUME_MIN_DB (-96 * 65536)

typedef enum _SND_tdeFadeType {
    SND_E_FADE_LINEAR,
    SND_E_FADE_LOG,
    SND_E_FADE_POW_9,
    SND_E_FADE_POW_12,
    SND_E_FADE_POW_18,
    SND_E_FADE_POW_3,
    SND_E_FADE_POW_4,
    SND_E_FADE_POW_5,
    SND_E_FADE_SCURVE_1_5,
    SND_E_FADE_SCURVE_0_75,
    SND_E_FADE_INV_SCURVE_5,
    SND_E_FADE_INV_SCURVE_5_75
} SND_tdeFadeType;

/* One curve per fade type: the volume in decibels at each of 128 positions.
   File-static in sndVolume.c of the sibling builds. */
extern SndReal rFade_Lin[128];
extern SndReal rFade_Log[128];
extern SndReal rFade_Pow_9[128];
extern SndReal rFade_Pow_12[128];
extern SndReal rFade_Pow_18[128];
extern SndReal rFade_Pow_3[128];
extern SndReal rFade_Pow_4[128];
extern SndReal rFade_Pow_5[128];
extern SndReal rFade_scurve_1_5[128];
extern SndReal rFade_scurve_0_75[128];
extern SndReal rFade_Inv_scurve_5[128];
extern SndReal rFade_Inv_scurve_5_75[128];

long __cdecl SND_fn_lConvertDb2LinearVolume(SndReal rValue_dB, long lNbBits);
SndReal __cdecl fn_rGetVolFadeAttenuation(SndReal rPos, SND_tdeFadeType eFadeType);

#endif
