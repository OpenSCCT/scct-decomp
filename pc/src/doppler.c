/* doppler.c -- the Doppler factor (sndspace.c) */
#include "sound_space.h"

/* SND_fn_vSetDopplerFactor: sets the speed of sound to 300 m/s divided by the factor */
void __stdcall SND_fn_vSetDopplerFactor(SndReal rFactor)
{
    if (rFactor)
        gs_lSoundSpeed = SND_fn_rDivRealRealSnd(300 * 65536, rFactor) >> 16;
    else
        gs_lSoundSpeed = 0;
}

/* SND_fn_rGetDopplerFactor */
SndReal __stdcall SND_fn_rGetDopplerFactor(void)
{
    if (gs_lSoundSpeed)
        return SND_fn_rDivRealRealSnd(300 * 65536, (unsigned long)gs_lSoundSpeed << 16);
    return 0;
}
