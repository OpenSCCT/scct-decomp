#include "sound_error.h"
#include "sound_space.h"
#include "sound_volume.h"

SndReal __cdecl fn_rDist2Vol(SndReal rDist, SndReal rDistSatur)
{
    SndReal rDistRatio;
    int i, j;
    if (rDistSatur <= 0) {
        SND_fn_vDisplayErrorEx(E_uwSndInvalidStaticParamForResource, "\nDistSatur must be greater than 0.\n)", 3);
        return SND_VOLUME_MIN_DB;
    }
    rDistRatio = SND_fn_rDivRealRealSnd(rDist, rDistSatur);
    if (rDistRatio <= g_rLimitTab[3]) {
        i = 0;
        while (rDistRatio > g_rLimitTab[i])
            ++i;
        j = (SND_fn_rMulRealRealSnd(g_rCoefA[i], rDistRatio) + g_rCoefB[i]) >> 16;
        return LocalisedVolume_table[i][j];
    }
    j = (SND_fn_rMulRealRealSnd(g_rCoefA[3], rDistRatio) + g_rCoefB[3]) >> 16;
    if (j <= 127)
        return LocalisedVolume_table[3][j];
    return SND_fn_rMulRealRealSnd(g_rCoefLinA, rDistRatio) + g_rCoefLinB;
}
