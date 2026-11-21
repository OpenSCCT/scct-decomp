/* dolby_coefficients.c -- Dolby Surround matrix coefficients by angle (sndspace.c) */
#include "sound_space.h"

/* SND_fn_fGetDolbyLtCoef: the left-total coefficient at an angle below 720 degrees */
float __stdcall SND_fn_fGetDolbyLtCoef(long lAngle)
{
    if (lAngle < 360)
        return g_fDolbyLtCoef[lAngle];
    return -g_fDolbyLtCoef[lAngle - 360];
}

/* SND_fn_fGetDolbyRtCoef: the right-total coefficient at an angle below 720 degrees */
float __stdcall SND_fn_fGetDolbyRtCoef(long lAngle)
{
    if (lAngle < 360)
        return g_fDolbyRtCoef[lAngle];
    return -g_fDolbyRtCoef[lAngle - 360];
}
