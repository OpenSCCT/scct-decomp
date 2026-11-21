#include "sound_space.h"

float __stdcall SND_fn_fGetDolbyLtCoef(long lAngle)
{
    if (lAngle < 360)
        return g_fDolbyLtCoef[lAngle];
    return -g_fDolbyLtCoef[lAngle - 360];
}

float __stdcall SND_fn_fGetDolbyRtCoef(long lAngle)
{
    if (lAngle < 360)
        return g_fDolbyRtCoef[lAngle];
    return -g_fDolbyRtCoef[lAngle - 360];
}
