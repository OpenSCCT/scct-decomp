#include "sound_space.h"

SndReal __stdcall SND_fn_rDopplerPitch(const SndVector *Ps, const SndVector *Vs, const SndVector *Pm,
                                       const SndVector *Vm)
{
    SndVector MS;
    SndReal rDistanceMS, rC, rVs_Projected, rVm_Projected;
    if (!gs_lSoundSpeed)
        return 65536;
    MS.x = (Ps->x - Pm->x) >> 8;
    MS.y = (Ps->y - Pm->y) >> 8;
    MS.z = (Ps->z - Pm->z) >> 8;
    rDistanceMS = SND_fn_rPseudoNormeVectorSnd(&MS);
    if (!rDistanceMS)
        return 65536;
    if (rDistanceMS > 64 * 65536)
        return 65536;
    rC = gs_lSoundSpeed * rDistanceMS;
    rVs_Projected = SND_fn_rScalaireVectorSnd(Vs, &MS);
    rVm_Projected = SND_fn_rScalaireVectorSnd(Vm, &MS);
    if (rVs_Projected >= rC || rVm_Projected >= rC)
        return 65536;
    return SND_fn_rDivRealRealSnd(rC - rVs_Projected, rC - rVm_Projected);
}
