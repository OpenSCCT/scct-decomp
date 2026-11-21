#include "sound_space.h"
#include "sound_volume.h"

void __stdcall SND_fn_vVolPanToVolLR(SndReal rVol_dB, unsigned char ucPan, SndReal *prVolL_dB,
                                     SndReal *prVolR_dB)
{
    const SndReal minimum = SND_VOLUME_MIN_DB;
    if (prVolL_dB && prVolR_dB) {
        *prVolR_dB = rVol_dB + gs_arPanToRVol_dB[ucPan];
        *prVolL_dB = rVol_dB + gs_arPanToRVol_dB[128 - ucPan];
        if (*prVolR_dB < minimum)
            *prVolR_dB = minimum;
        if (*prVolL_dB < minimum)
            *prVolL_dB = minimum;
    }
}
