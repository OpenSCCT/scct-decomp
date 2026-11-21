#include "sound_memory.h"
#include "sound_space.h"
#include "sound_volume.h"

static __forceinline SndReal evaluate_rolloff(SndReal rDist, RollOffParam *pstRollOff)
{
    if (pstRollOff->rDistBackGround != ROLLOFF_NONE && rDist > pstRollOff->rDistBackGround)
        rDist = pstRollOff->rDistBackGround;
    if (rDist < pstRollOff->rDistSatur)
        return 0;
    if (pstRollOff->rDistTransitLinear != ROLLOFF_NONE && pstRollOff->rDistInaudible != ROLLOFF_NONE
        && rDist >= pstRollOff->rDistTransitLinear) {
        SndReal rStartVol, rPos;
        if (rDist < pstRollOff->rDistInaudible) {
            rStartVol = fn_rDist2Vol(pstRollOff->rDistTransitLinear, pstRollOff->rDistSatur);
            rStartVol = SND_fn_lConvertDb2LinearVolume(rStartVol, 8);
            rStartVol = SND_fn_rDivRealRealSnd(rStartVol, 128);
            rPos = SND_fn_rDivRealRealSnd(rDist - pstRollOff->rDistTransitLinear,
                                          pstRollOff->rDistInaudible - pstRollOff->rDistTransitLinear);
            rPos = 65536 - rPos;
            rPos = SND_fn_rMulRealRealSnd(rPos, rStartVol);
            return fn_rGetVolFadeAttenuation(rPos, SND_E_FADE_LINEAR);
        }
        return SND_VOLUME_MIN_DB;
    }
    return fn_rDist2Vol(rDist, pstRollOff->rDistSatur);
}

SndReal __stdcall SND_fn_rDistanceToVolumeEx(SndReal _rDist, const RollOffParam *_pstRollOff)
{
    RollOffParam stRollOff;
    if (!_pstRollOff) {
        RollOffParam rolloff;
        rolloff.rDistSatur = gs_rDefaultDistSatur;
        rolloff.rDistBackGround = gs_rDefaultDistBackGround;
        rolloff.rDistTransitLinear = gs_rDefaultDistTransitLinear;
        rolloff.rDistInaudible = gs_rDefaultDistInaudible;
        return SND_fn_rDistanceToVolumeEx(_rDist, &rolloff);
    }
    SND_fn_vMemCopySnd(&stRollOff, _pstRollOff, sizeof(stRollOff));
    if (stRollOff.rDistSatur == ROLLOFF_DEFAULT)
        stRollOff.rDistSatur = gs_rDefaultDistSatur;
    if (stRollOff.rDistBackGround == ROLLOFF_DEFAULT)
        stRollOff.rDistBackGround = gs_rDefaultDistBackGround;
    if (stRollOff.rDistTransitLinear == ROLLOFF_DEFAULT)
        stRollOff.rDistTransitLinear = gs_rDefaultDistTransitLinear;
    if (stRollOff.rDistInaudible == ROLLOFF_DEFAULT)
        stRollOff.rDistInaudible = gs_rDefaultDistInaudible;
    return evaluate_rolloff(_rDist, &stRollOff);
}
