#include "sound_volume.h"

SndReal __cdecl fn_rGetVolFadeAttenuation(SndReal rPos, SND_tdeFadeType eFadeType)
{
    long lIndice = rPos >> 9;
    if (lIndice >= 128)
        lIndice = 127;
    switch (eFadeType) {
    case SND_E_FADE_LINEAR: return rFade_Lin[lIndice];
    case SND_E_FADE_LOG: return rFade_Log[lIndice];
    case SND_E_FADE_POW_9: return rFade_Pow_9[lIndice];
    case SND_E_FADE_POW_12: return rFade_Pow_12[lIndice];
    case SND_E_FADE_POW_18: return rFade_Pow_18[lIndice];
    case SND_E_FADE_POW_3: return rFade_Pow_3[lIndice];
    case SND_E_FADE_POW_4: return rFade_Pow_4[lIndice];
    case SND_E_FADE_POW_5: return rFade_Pow_5[lIndice];
    case SND_E_FADE_SCURVE_1_5: return rFade_scurve_1_5[lIndice];
    case SND_E_FADE_SCURVE_0_75: return rFade_scurve_0_75[lIndice];
    case SND_E_FADE_INV_SCURVE_5: return rFade_Inv_scurve_5[lIndice];
    case SND_E_FADE_INV_SCURVE_5_75: return rFade_Inv_scurve_5_75[lIndice];
    default: return SND_VOLUME_MIN_DB;
    }
}
